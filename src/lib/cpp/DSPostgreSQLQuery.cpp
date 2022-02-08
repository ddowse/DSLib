#include "DSPostgreSQLQuery.h"
#include "DSCasts.h"
#include <libpq/libpq-fs.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

DynSoft::DSPostgreSQLQuery::DSPostgreSQLQuery(DSPostgreSQLDatabase *db) : DSQuery(db) {
	if(db)
		connection = db->GetConnection();
	rowsCount = 0;
}

DynSoft::DSPostgreSQLQuery::DSPostgreSQLQuery(dsPostgreSQL *db) : DSQuery(db->GetNewDbObject()) {
	if(db && db->GetNewDbObject()) {
		db->GetNewDbObject()->Reconnect();
		connection = db->GetNewDbObject()->GetConnection();
	}
	rowsCount = 0;
}

DynSoft::DSClassInfo DynSoft::DSPostgreSQLQuery::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_POSTGRESQL_QUERY_NAME,
		DS_POSTGRESQL_QUERY_VERSION,
		DS_POSTGRESQL_QUERY_AUTHOR
	);
}

bool DynSoft::DSPostgreSQLQuery::Exec(const bool storeResult) {
	db->Reconnect();
	bool ok = false;
	running = false;
	rowsCount = 0;
	const char *tmpQuery = DSCasts::ToChar(GetParsedQuery());
	if((result = PQexec(connection, tmpQuery))) {
		if(!result) {
			running = false;
		} else {
			int stat = PQresultStatus(result);
			if(stat == PGRES_TUPLES_OK || stat == PGRES_COMMAND_OK) {
				if(!storeResult)
					PQclear(result);
				else
					running = true;
				ok = true;
			} else {
				running = false;
			}
		}
	}

	delete [] tmpQuery;
	return ok;
}

DynSoft::DSCasts DynSoft::DSPostgreSQLQuery::GetField(const wxString &field, const bool caseSensitive) {
	wxString tmp(field);
	if(caseSensitive)
		tmp = (_N("\"") + field + _N("\""));
	const char *tmpField = DynSoft::DSCasts::ToChar(tmp);
	DSCasts resultField = GetField(PQfnumber(result, tmpField));
	delete [] tmpField;
	return resultField;
}

DynSoft::DSCasts DynSoft::DSPostgreSQLQuery::GetField(const int column) {
	if(PQgetisnull(result, rowsCount - 1, column))
		return DynSoft::DSCasts::Convert(wxEmptyString);
	return DynSoft::DSCasts::Convert(PQgetvalue(result, rowsCount - 1, column));
}

bool DynSoft::DSPostgreSQLQuery::IsNull(const wxString &field) {
	const char *tmpField = DynSoft::DSCasts::ToChar(field);
	bool isNull = IsNull(PQfnumber(result, tmpField));
	delete [] tmpField;
	return isNull;
}

bool DynSoft::DSPostgreSQLQuery::IsNull(const int column) {
	return PQgetisnull(result, rowsCount - 1, column);
}

DynSoft::DSCasts DynSoft::DSPostgreSQLQuery::GetColumn(const int column) {
	return DSCasts::ToString(PQfname(result, column));
}

unsigned int DynSoft::DSPostgreSQLQuery::GetRowCount() const {
	if(IsRunning())
		return PQntuples(result);
	return 0;
}

unsigned int DynSoft::DSPostgreSQLQuery::GetColumnCount() const {
	if(IsRunning())
		return PQnfields(result);
	return 0;
}

bool DynSoft::DSPostgreSQLQuery::Begin() {
	return Query(_N("BEGIN"), false);
}

bool DynSoft::DSPostgreSQLQuery::Commit() {
	return Query(_N("COMMIT"));
}

bool DynSoft::DSPostgreSQLQuery::Rollback() {
	return Query(_N("ROLLBACK"));
}

void DynSoft::DSPostgreSQLQuery::FreeResult() {
	running = false;
	PQclear(result);
}

bool DynSoft::DSPostgreSQLQuery::NextRecord() {
	if(running) {
		if(rowsCount < PQntuples(result)) {
			rowsCount++;
			return true;
		} else {
			return false;
		}
	}

	return false;
}

unsigned char *DynSoft::DSPostgreSQLQuery::EscapeByteA(unsigned char *buffer, const size_t size, size_t &newSize) {
	return PQescapeBytea(buffer, size, &newSize);
}

char *DynSoft::DSPostgreSQLQuery::GetFieldByteA(const wxString &field, size_t &newSize) {
	const char *tmp = PQgetvalue(result, rowsCount - 1, PQfnumber(result, (const char *) field.mb_str(wxConvUTF8)));
	char *escaped   = (char *) PQunescapeBytea((unsigned char *) tmp, &newSize);

	return escaped;
}

bool DynSoft::DSPostgreSQLQuery::ExecWithoutResultByCString(const char *query) {
	db->Reconnect();
	bool ok = false;
	PGresult *result = PQexec(connection, query);
	if(result) {
		int stat = PQresultStatus(result);
		if(stat == PGRES_TUPLES_OK || stat == PGRES_COMMAND_OK) {
			PQclear(result);
			ok = true;
		}
	}

	return ok;
}

unsigned int DynSoft::DSPostgreSQLQuery::ImportLargeObject(wxString filename, const unsigned int oid) {
	if(filename.IsEmpty())
		return 0;
	
	if(oid > 0)
		lo_unlink(connection, oid);

#ifdef __WINDOWS__
	wxStandardPaths paths = wxStandardPaths::Get();
	wxString path(paths.GetTempDir());
	const wxString tmpfilename(wxFileName::CreateTempFileName(path));
	if(tmpfilename.IsEmpty())
		return 0;
	
	if(!wxCopyFile(filename, tmpfilename))
		return 0;
	
	filename = tmpfilename;
#endif

	const unsigned int result = lo_import(connection, static_cast<const char *>(filename.mb_str(wxConvUTF8)));

#ifdef __WINDOWS__
	wxRemoveFile(tmpfilename);
#endif

	return result;
}

bool DynSoft::DSPostgreSQLQuery::ExportLargeObject(const wxString &filename, const unsigned int oid) {
	return lo_export(connection, oid, static_cast<const char *>(filename.mb_str(wxConvUTF8))) == 1;
}

bool DynSoft::DSPostgreSQLQuery::RemoveLargeObject(const unsigned int oid) {
	return lo_unlink(connection, oid) == 1;
}

bool DynSoft::DSPostgreSQLQuery::ExistsLargeObject(const unsigned int oid) {
	const int fid = lo_open(connection, oid, INV_READ);
	if(fid > -1) {
		lo_close(connection, fid);
		return true;
	}

	return false;
}
