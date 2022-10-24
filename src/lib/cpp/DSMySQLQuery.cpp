#include "DSMySQLQuery.h"
#include "DSCasts.h"

DynSoft::DSMySQLQuery::DSMySQLQuery(DSMySQLDatabase *db) : DSQuery(db) {
	db->Reconnect();
	connection = db->GetConnection();
	running = false;

	Prepare(_N("SET NAMES :encoding:"));
	Bind(_N("encoding"), db->GetEncoding(), false);
	Exec(false);
}

DynSoft::DSClassInfo DynSoft::DSMySQLQuery::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_MYSQL_QUERY_NAME,
		DS_MYSQL_QUERY_VERSION,
		DS_MYSQL_QUERY_AUTHOR
	);
}

bool DynSoft::DSMySQLQuery::Exec(const bool storeResult) {
	bool ok = false;
	running = false;
	const char *tmpQuery = DSCasts::ToChar(GetParsedQuery());
	if(mysql_query(connection, tmpQuery) == 0) {
		if(!storeResult) {
			running = false;
			ok      = true;
		} else {
			result = mysql_store_result(connection);
			if(result != NULL) {
				running = true;
			} else {
				running = false;
			}

			ok = running;
		}
	}

	delete [] tmpQuery;
	return ok;
}

DynSoft::DSCasts DynSoft::DSMySQLQuery::GetField(const wxString &field, const bool caseSensitive) {
	return GetField(GetFieldNumber(field));
}

DynSoft::DSCasts DynSoft::DSMySQLQuery::GetField(const int column) {
	return row[column] == NULL ? DSCasts::Convert(wxString()) : DSCasts::Convert(row[column]);
}

bool DynSoft::DSMySQLQuery::IsNull(const wxString &field) {
	return IsNull(GetField(field).ToInt());
}

bool DynSoft::DSMySQLQuery::IsNull(const int column) {
	return row[column] == NULL;
}

DynSoft::DSCasts DynSoft::DSMySQLQuery::GetColumn(const int column) {
    MYSQL_FIELD *columns = mysql_fetch_fields(result);
	return DSCasts::Convert(columns[column].name);
}

unsigned int DynSoft::DSMySQLQuery::GetRowCount() const {
	if(running)
		return mysql_num_rows(result);
	return 0;
}

unsigned int DynSoft::DSMySQLQuery::GetColumnCount() const {
	return mysql_num_fields(result);
}

bool DynSoft::DSMySQLQuery::Begin() {
	return Query(_N("BEGIN"), false);
}

bool DynSoft::DSMySQLQuery::Commit() {
	return Query(_N("COMMIT"));
}

bool DynSoft::DSMySQLQuery::Rollback() {
	return Query(_N("ROLLBACK"));
}

void DynSoft::DSMySQLQuery::FreeResult() {
	running = false;
	mysql_free_result(result);
}

bool DynSoft::DSMySQLQuery::NextRecord() {
	if(running)
		if((row = mysql_fetch_row(result)) != NULL)
			return true;
	
	running = false;
	return false;
}

int DynSoft::DSMySQLQuery::GetFieldNumber(const wxString &field) const {
	int numColumns = mysql_num_fields(result);
    MYSQL_FIELD *columns = mysql_fetch_fields(result);
    for (int i = 0; i < numColumns; i++)
        if(field == DSCasts::ToString(columns[i].name))
            return i;
    return -1;
}

unsigned int DynSoft::DSMySQLQuery::GetLastInsertId() const {
	return (unsigned int) mysql_insert_id(connection);
}
