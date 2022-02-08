#include "DSSQLiteQuery.h"
#include "DSCasts.h"

DynSoft::DSSQLiteQuery::DSSQLiteQuery(DSSQLiteDatabase *db) : DSQuery(db) {
	db->Reconnect();
	connection  = db->GetConnection();
	rowCount    = 0;
	columnCount = 0;
	row         = 0;
}

DynSoft::DSClassInfo DynSoft::DSSQLiteQuery::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SQLITE_QUERY_NAME,
		DS_SQLITE_QUERY_VERSION,
		DS_SQLITE_QUERY_AUTHOR
	);
}

bool DynSoft::DSSQLiteQuery::Exec(const bool storeResult) {
	const char *tmpQuery = DSCasts::ToChar(GetParsedQuery());
	int rc = sqlite3_get_table(
		connection,
		tmpQuery,
		&result,
		&rowCount,
		&columnCount,
		&errorMessage
	);

	bool ok = rc == SQLITE_OK;

	if(!storeResult) {
		FreeResult();
	} else {
		if(ok) {
			row = 0;
			columns.Clear();
			for(unsigned int i = 0; i < GetColumnCount(); i++)
				columns.Add(result[i] == NULL ? wxString() : DSCasts::ToString(result[i]));
		}
	}
	delete [] tmpQuery;

	return ok;
}

DynSoft::DSCasts DynSoft::DSSQLiteQuery::GetField(const wxString &field, const bool caseSensitive) {
	int index = columns.Index(field);
	if(index != wxNOT_FOUND)
		return GetField(index);
	return DSCasts::Convert(wxString());
}

DynSoft::DSCasts DynSoft::DSSQLiteQuery::GetField(const int column) {
	if((unsigned int) column < GetColumnCount())
		return DSCasts::Convert(result[row * GetColumnCount() + column] != NULL ? DSCasts::ToString(result[row * GetColumnCount() + column]) : wxString());
	return DSCasts::Convert(wxString());
}

bool DynSoft::DSSQLiteQuery::IsNull(const wxString &field) {
	int index = columns.Index(field);
	if(index != wxNOT_FOUND)
		return IsNull(index);
	return true;
}

bool DynSoft::DSSQLiteQuery::IsNull(const int column) {
	return result[row * GetColumnCount() + column] == NULL;
}

DynSoft::DSCasts DynSoft::DSSQLiteQuery::GetColumn(const int column) {
	return (unsigned int) column >= GetColumnCount() ? DSCasts::Convert(wxString()) : DSCasts::Convert(result[column] == NULL ? wxString() : DSCasts::ToString(result[column]));
}

unsigned int DynSoft::DSSQLiteQuery::GetRowCount() const {
	return rowCount;
}

unsigned int DynSoft::DSSQLiteQuery::GetColumnCount() const {
	return columnCount;
}

bool DynSoft::DSSQLiteQuery::Begin() {
	return Query(_N("BEGIN TRANSACTION"), false);
}

bool DynSoft::DSSQLiteQuery::Commit() {
	return Query(_N("COMMIT"), false);
}

bool DynSoft::DSSQLiteQuery::Rollback() {
	return Query(_N("ROLLBACK"), false);
}

void DynSoft::DSSQLiteQuery::FreeResult() {
	sqlite3_free_table(result);
	columns.Clear();
	row = 0;
}

bool DynSoft::DSSQLiteQuery::NextRecord() {
	if(row < GetRowCount()) {
		row++;
		return true;
	}

	return false;
}

