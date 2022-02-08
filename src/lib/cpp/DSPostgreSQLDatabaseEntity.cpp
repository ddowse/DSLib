#include "DSPostgreSQLDatabaseEntity.h"
#include "DSPostgreSQLQuery.h"

DynSoft::DSPostgreSQLDatabaseEntity::DSPostgreSQLDatabaseEntity(
	DynSoft::DSPostgreSQLDatabase *db,
	const bool getAutoSequence
) : DSDatabaseEntity(
	getAutoSequence
) {
	this->db = db;
}

DynSoft::DSPostgreSQLDatabaseEntity::DSPostgreSQLDatabaseEntity(
	DynSoft::DSPostgreSQLDatabase *db,
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

DynSoft::DSPostgreSQLDatabaseEntity::~DSPostgreSQLDatabaseEntity() {
}

DynSoft::DSClassInfo DynSoft::DSPostgreSQLDatabaseEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_POSTGRESQL_DATABASE_ENTITY_NAME,
		DS_POSTGRESQL_DATABASE_ENTITY_VERSION,
		DS_POSTGRESQL_DATABASE_ENTITY_AUTHOR
	);
}

DynSoft::DSPostgreSQLDatabaseEntity::DSEntityInternalType DynSoft::DSPostgreSQLDatabaseEntity::GetInternalType() const {
	return DynSoft::DSEntity::DS_POSTGRESQL_DATABASE_ENTITY;
}

void DynSoft::DSPostgreSQLDatabaseEntity::SetDatabase(DSPostgreSQLDatabase *db) {
	this->db = db;
}

DynSoft::DSPostgreSQLDatabase *DynSoft::DSPostgreSQLDatabaseEntity::GetDatabase() const {
	return db;
}

wxString DynSoft::DSPostgreSQLDatabaseEntity::CreateInsertQuery(const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildInsertQuery(withoutPrimaryKey, _N("\""), _N("\""), withoutFields));
}

wxString DynSoft::DSPostgreSQLDatabaseEntity::CreateUpdateQuery(const wxString &where, const bool withoutPrimaryKey, wxArrayString *withoutFields) {
	return BindValues(BuildUpdateQuery(where, withoutPrimaryKey, _N("\""), _N("\""), withoutFields));
}

wxString DynSoft::DSPostgreSQLDatabaseEntity::CreateDeleteQuery(const wxString &where) {
	return BindValues(BuildDeleteQuery(where, _N("\""), _N("\"")));
}

bool DynSoft::DSPostgreSQLDatabaseEntity::ExecInsertQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, INSERT);
}

bool DynSoft::DSPostgreSQLDatabaseEntity::ExecUpdateQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, UPDATE);
}

bool DynSoft::DSPostgreSQLDatabaseEntity::ExecDeleteQuery(const wxString &query, DSQuery *queryObject) {
	return ExecQuery(query, queryObject, REMOVE);
}

bool DynSoft::DSPostgreSQLDatabaseEntity::ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind) {
	DSPostgreSQLQuery *tmp = (DSPostgreSQLQuery *) queryObject;

	const bool transaction = tmp != NULL;
	if(!transaction) {
		tmp = new DSPostgreSQLQuery(db);
		tmp->Begin();
	}
	
	bool ok = tmp->Query(query, false);
	wxString pk(GetPrimaryKey());
	wxString name(GetName());
	if(GetGetAutoSequence() && kind == INSERT && ok && !pk.IsEmpty() && !name.IsEmpty()) {
		wxString seqName(_N("\"") + name + _N("_") + pk + _N("_seq\""));
		tmp->Prepare(_N("SELECT CURRVAL(:sequence:) AS id"));
		tmp->Bind(_N("sequence"), seqName);
		ok = tmp->Exec();
		if(ok) {
			if(tmp->NextRecord())
				SetValue(pk, tmp->GetField(_N("id")).ToUnsignedInt());
			tmp->FreeResult();
		}
	}

	if(!transaction) {
		if(!ok || !tmp->Commit()) {
			tmp->Rollback();
			ok = false;
		} else {
			ok = true;
		}
		delete tmp;
	}

	return ok;
}
