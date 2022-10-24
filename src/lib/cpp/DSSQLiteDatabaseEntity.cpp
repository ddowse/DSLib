#include "DSSQLiteDatabaseEntity.h"
#include "DSSQLiteQuery.h"

DynSoft::DSSQLiteDatabaseEntity::DSSQLiteDatabaseEntity(
	DynSoft::DSSQLiteDatabase *db,
	const bool getAutoSequence
) : DSDatabaseEntity(
	getAutoSequence
) {
	this->db = db;
}

DynSoft::DSSQLiteDatabaseEntity::DSSQLiteDatabaseEntity(
	DynSoft::DSSQLiteDatabase *db,
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

DynSoft::DSSQLiteDatabaseEntity::~DSSQLiteDatabaseEntity() {
}

DynSoft::DSClassInfo DynSoft::DSSQLiteDatabaseEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SQLITE_DATABASE_ENTITY_NAME,
		DS_SQLITE_DATABASE_ENTITY_VERSION,
		DS_SQLITE_DATABASE_ENTITY_AUTHOR
	);
}

DynSoft::DSSQLiteDatabaseEntity::DSEntityInternalType DynSoft::DSSQLiteDatabaseEntity::GetInternalType() const {
	return DynSoft::DSEntity::DS_SQLITE_DATABASE_ENTITY;
}

void DynSoft::DSSQLiteDatabaseEntity::SetDatabase(DSSQLiteDatabase *db) {
	this->db = db;
}

DynSoft::DSSQLiteDatabase *DynSoft::DSSQLiteDatabaseEntity::GetDatabase() const {
	return db;
}

wxString DynSoft::DSSQLiteDatabaseEntity::CreateInsertQuery(const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildInsertQuery(withoutPrimaryKey, _N(""), _N(""), withoutFields));
}

wxString DynSoft::DSSQLiteDatabaseEntity::CreateUpdateQuery(const wxString &where, const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildUpdateQuery(where, withoutPrimaryKey, _N(""), _N(""), withoutFields));
}

wxString DynSoft::DSSQLiteDatabaseEntity::CreateDeleteQuery(const wxString &where) {
	return BindValues(BuildDeleteQuery(where, _N(""), _N("")));
}

bool DynSoft::DSSQLiteDatabaseEntity::ExecInsertQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, INSERT);
}

bool DynSoft::DSSQLiteDatabaseEntity::ExecUpdateQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, UPDATE);
}

bool DynSoft::DSSQLiteDatabaseEntity::ExecDeleteQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, REMOVE);
}

bool DynSoft::DSSQLiteDatabaseEntity::ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind) {
	DSSQLiteQuery *tmp = (DSSQLiteQuery *) queryObject;

	const bool transaction = tmp != NULL;
	if(!transaction)
		tmp = new DSSQLiteQuery(db);
	
	const bool ok = tmp->Query(query, false);
	// TODO implement last_insert_id

	if(!transaction)
		delete tmp;
	
	return ok;
}
