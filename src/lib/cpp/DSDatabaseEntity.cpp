#include "DSDatabaseEntity.h"
#include "DSQueryParser.h"

DynSoft::DSDatabaseEntity::DSDatabaseEntity(
	const bool getAutoSequence
) : DSEntity(
) {
	SetGetAutoSequence(getAutoSequence);
}

DynSoft::DSDatabaseEntity::DSDatabaseEntity(
	const wxString &name,
	const wxString &primaryKey,
	const bool getAutoSequence,
	const wxString &foreignKey,
	const wxString &foreignTable,
	const unsigned int reference
) : DSEntity(
	name,
	primaryKey,
	foreignKey
) {
	SetGetAutoSequence(getAutoSequence);
	SetForeignTable(foreignTable);
	SetReference(reference);
}

DynSoft::DSDatabaseEntity::~DSDatabaseEntity() {
	references.Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSDatabaseEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DATABASE_ENTITY_NAME,
		DS_DATABASE_ENTITY_VERSION,
		DS_DATABASE_ENTITY_AUTHOR
	);
}

DynSoft::DSDatabaseEntity::DSEntityInternalType DynSoft::DSDatabaseEntity::GetInternalType() const {
	return DynSoft::DSEntity::DS_DATABASE_ENTITY;
}

wxString DynSoft::DSDatabaseEntity::BuildInsertQuery(
	const bool withoutPrimaryKey,
	const wxString &prefix,
	const wxString &suffix,
	wxArrayString *withoutFields
) {
	wxString keys, values;
	BuildKeysValues(&keys, &values, prefix, suffix, withoutPrimaryKey, withoutFields);

	return wxString(_N("INSERT INTO ") + prefix + GetName() + suffix + _N(" (") + keys + _N(") VALUES (") + values + _N(")"));
}

wxString DynSoft::DSDatabaseEntity::BuildUpdateQuery(
	wxString where,
	const bool withoutPrimaryKey,
	const wxString &prefix,
	const wxString &suffix,
	wxArrayString *withoutFields
) {
	wxString pairs;
	BuildKeysValuesPairs(&pairs, prefix, suffix, withoutPrimaryKey, withoutFields);

	if(!where.IsEmpty())
		where = _N(" WHERE ") + prefix + where + suffix + _N(" = :") + where + _N(":");
	else if(!GetPrimaryKey().IsEmpty())
		where = _N(" WHERE ") + prefix + GetPrimaryKey() + suffix + _N(" = :") + GetPrimaryKey() + _N(":");

	return wxString(_N("UPDATE ") + prefix + GetName() + suffix + _N(" SET ") + pairs + where);
}

wxString DynSoft::DSDatabaseEntity::BuildDeleteQuery(
	wxString where,
	const wxString &prefix,
	const wxString &suffix
) {
	if(where.IsEmpty()) {
		wxString pk(GetPrimaryKey());
		if(!pk.IsEmpty())
			where = pk;
	}

	return wxString(_N("DELETE FROM ") + prefix + GetName() + suffix + _N(" WHERE ") + prefix +  where + suffix + _N(" = :") + where + _N(":"));
}

unsigned int DynSoft::DSDatabaseEntity::BuildKeysValues(
	wxString *keys,
	wxString *values,
	const wxString &prefix,
	const wxString &suffix,
	const bool withoutPrimaryKey,
	wxArrayString *withoutFields
) {
	wxString key;
	DSEntity::DSEntityType *entity = NULL;
	const wxString pk(GetPrimaryKey());
	const unsigned int count = entities.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entity = entities.Get(i);
		key    = entity->GetKey();
		if(withoutPrimaryKey && pk == key)
			continue;

		if(withoutFields && withoutFields->Index(key) != wxNOT_FOUND)
			continue;

		if(keys)
			keys->Append(prefix + key + suffix + _N(", "));
		if(values)
			values->Append(_N(":") + key + _N(":, "));
	}

	if(keys && keys->Length() > 2)
		*keys = keys->Mid(0, keys->Length() - 2);
	if(values && values->Length() > 2)
		*values = values->Mid(0, values->Length() - 2);

	return count;
}

unsigned int DynSoft::DSDatabaseEntity::BuildKeysValuesPairs(
	wxString *pairs,
	const wxString &prefix,
	const wxString &suffix,
	const bool withoutPrimaryKey,
	wxArrayString *withoutFields
) {
	if(!pairs)
		return 0;

	DSEntity::DSEntityType *entity = NULL;
	wxString key;
	const wxString pk(GetPrimaryKey());
	const unsigned int count = entities.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entity = entities.Get(i);
		key    = entity->GetKey();
		if(withoutPrimaryKey && pk == key)
			continue;
		if(withoutFields && withoutFields->Index(key) != wxNOT_FOUND)
			continue;
		pairs->Append(prefix + key + suffix + _N(" = :") + key + _(":, "));
	}
	
	if(pairs->Length() > 2)
		*pairs = pairs->Mid(0, pairs->Length() - 2);

	return count;
}

wxString DynSoft::DSDatabaseEntity::BindValues(const wxString &query, unsigned int *bounded) {
	DSEntity::DSEntityType *entity = NULL;
	DSQueryParser parser;
	parser.Prepare(query);

	if(bounded)
		*bounded = 0;
	
	bool isNull = false;
	wxString tmp;
	const unsigned int count = entities.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entity = entities.Get(i);
		tmp    = entity->ToString();
		isNull = entity->GetNull() && (tmp.IsEmpty() || (entity->GetType() != DSEntity::DSEntityType::DS_RESULT_TYPE_WXSTRING && tmp == _N("0")));

		if(isNull) {
			tmp = _N("NULL");
		} else {
			switch(entity->GetType()) {
				case DSEntityType::DS_RESULT_TYPE_FLOAT:
				case DSEntityType::DS_RESULT_TYPE_DOUBLE:
				case DSEntityType::DS_RESULT_TYPE_DSCURRENCY:
					tmp.Replace(_N(","), _N("."));
					break;
			}
		}

		if(parser.Bind(
			entity->GetKey(),
			tmp,
			isNull ? false : entity->GetDelimiters(),
			entity->GetEscape()
		)) {
			if(bounded)
				(*bounded)++;
		}
	}

	return parser.GetParsedQuery();
}

void DynSoft::DSDatabaseEntity::SetTable(const wxString &table) {
	this->name = table;
}

wxString DynSoft::DSDatabaseEntity::GetTable() const {
	return name;
}

void DynSoft::DSDatabaseEntity::SetForeignTable(const wxString &foreignTable) {
	this->foreignTable = foreignTable;
}

wxString DynSoft::DSDatabaseEntity::GetForeignTable() const {
	return foreignTable;
}

void DynSoft::DSDatabaseEntity::SetReference(const unsigned int &reference) {
	this->reference = reference;
}

unsigned int DynSoft::DSDatabaseEntity::GetReference() const {
	return reference;
}

void DynSoft::DSDatabaseEntity::SetGetAutoSequence(const bool getAutoSequence) {
	this->getAutoSequence = getAutoSequence;
}

bool DynSoft::DSDatabaseEntity::GetGetAutoSequence() const {
	return getAutoSequence;
}

wxString DynSoft::DSDatabaseEntity::GetLastParsedQuery() const {
	return lastParsedQuery;
}

DynSoft::DSTemplateContainer<DynSoft::DSDatabaseEntity *> *DynSoft::DSDatabaseEntity::GetReferences() {
	return &references;
}
