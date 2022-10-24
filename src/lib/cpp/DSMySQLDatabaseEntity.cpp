#include "DSMySQLDatabaseEntity.h"
#include "DSMySQLQuery.h"

DynSoft::DSMySQLDatabaseEntity::DSMySQLDatabaseEntity(
	DynSoft::DSMySQLDatabase *db,
	const bool getAutoSequence
) : DSDatabaseEntity(
	getAutoSequence
) {
	this->db = db;
}

DynSoft::DSMySQLDatabaseEntity::DSMySQLDatabaseEntity(
	DynSoft::DSMySQLDatabase *db,
	const wxString &name,
	const wxString &primaryKey,
	const bool getAutoSequence,
	const wxString &foreignKey,
	const wxString &foreignTable,
	const unsigned int reference
) : DSDatabaseEntity(
	name,
	primaryKey,
	getAutoSequence,
	foreignKey,
	foreignTable,
	reference
) {
	this->db = db;
}

DynSoft::DSMySQLDatabaseEntity::~DSMySQLDatabaseEntity() {
}

DynSoft::DSClassInfo DynSoft::DSMySQLDatabaseEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_MYSQL_DATABASE_ENTITY_NAME,
		DS_MYSQL_DATABASE_ENTITY_VERSION,
		DS_MYSQL_DATABASE_ENTITY_AUTHOR
	);
}

DynSoft::DSMySQLDatabaseEntity::DSEntityInternalType DynSoft::DSMySQLDatabaseEntity::GetInternalType() const {
	return DynSoft::DSEntity::DS_MYSQL_DATABASE_ENTITY;
}

void DynSoft::DSMySQLDatabaseEntity::SetDatabase(DSMySQLDatabase *db) {
	this->db = db;
}

DynSoft::DSMySQLDatabase *DynSoft::DSMySQLDatabaseEntity::GetDatabase() const {
	return db;
}

wxString DynSoft::DSMySQLDatabaseEntity::CreateInsertQuery(const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildInsertQuery(withoutPrimaryKey, _N(""), _N(""), withoutFields));
}

wxString DynSoft::DSMySQLDatabaseEntity::CreateUpdateQuery(const wxString &where, const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildUpdateQuery(where, withoutPrimaryKey, _N(""), _N(""), withoutFields));
}

wxString DynSoft::DSMySQLDatabaseEntity::CreateDeleteQuery(const wxString &where) {
	return BindValues(BuildDeleteQuery(where, _N(""), _N("")));
}

bool DynSoft::DSMySQLDatabaseEntity::ExecInsertQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, INSERT);
}

bool DynSoft::DSMySQLDatabaseEntity::ExecUpdateQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, UPDATE);
}

bool DynSoft::DSMySQLDatabaseEntity::ExecDeleteQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, REMOVE);
}

bool DynSoft::DSMySQLDatabaseEntity::ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind) {
	DSMySQLQuery *tmp = (DSMySQLQuery *) queryObject;

	const bool transaction = tmp != NULL;
	if(!transaction)
		tmp = new DSMySQLQuery(db);
	
	wxString pk(GetPrimaryKey());
	const bool ok = tmp->Query(query, false);
	if(GetGetAutoSequence() && kind == INSERT && !pk.IsEmpty() && !GetName().IsEmpty())
		SetValue(pk, (unsigned int) mysql_insert_id(db->GetConnection()));

	if(!transaction)
		delete tmp;
	
	return ok;
}
