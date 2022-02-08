#include "DSEntityData.h"

DynSoft::DSEntityData::DSEntityData(
	DSQuery *query,
	const wxString &table,
	const wxString &primaryKey,
	const wxString &orderByField,
	const unsigned int order,
	const bool cleanUp
) : DSData(
	query,
	cleanUp
) {
	this->table        = table;
	this->primaryKey   = primaryKey;

	SetOrderBy(orderByField, order);
}

DynSoft::DSEntityData::~DSEntityData() {
}

DynSoft::DSClassInfo DynSoft::DSEntityData::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_ENTITY_DATA_NAME,
		DS_ENTITY_DATA_VERSION,
		DS_ENTITY_DATA_AUTHOR
	);
}

void DynSoft::DSEntityData::SetOrderBy(const wxString &orderByField, const unsigned int order) {
	this->orderByField = orderByField;
	this->order        = order == DESC ? _N("DESC") : _N("ASC");
}

void DynSoft::DSEntityData::GetOrderBy(wxString *orderByField, unsigned int *order) {
	if(orderByField)
		*orderByField = this->orderByField;
	if(order)
		*order = this->order == _N("DESC") ? 0 : 1;
}

void DynSoft::DSEntityData::Get(DSEntity *entity, const wxString &prefix, const wxString &suffix) {
	if(!entity)
		return;
	
	// TODO this is not the fastest way
	// but I don't know (at this time)
	// how to make it better in a few times
	DSEntity::DSEntityType *entry = NULL;
	unsigned int count = entity->GetCount();
	wxArrayString keys;
	for(unsigned int i = 0; i < count; i++) {
		entry = entity->Get(i);
		if(entry)
			keys.Add(entry->GetKey());
	}

	wxString key;
	count = keys.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entry = entity->Get(keys[i]);
		if(!entry)
			continue;

		//key = prefix + entry->GetKey() + suffix;
		key = entry->GetKey();

		if(query->ExistsColumn(entry->GetKey())) {
			switch(entry->GetType()) {
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_SHORT:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToShort());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_SHORT:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToUnsignedShort());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_INT:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToInt());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_INT:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToUnsignedInt());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_LONG:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToLong());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_LONG:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToUnsignedLong());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_FLOAT:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToFloat());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DOUBLE:
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DSCURRENCY:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToDouble());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_CHAR_POINTER:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToChar());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_BOOL:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToBool());
					break;
				case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_WXSTRING:
				default:
					entity->SetValue(entry->GetKey(), query->GetField(key).ToString());
					break;
			}
		}
	}
}

bool DynSoft::DSEntityData::Insert(DSDatabaseEntity *entity, const bool withoutPrimaryKey, wxArrayString *withoutFields, DSQuery *queryObject) {
	lastParsedQuery = entity->CreateInsertQuery(withoutPrimaryKey, withoutFields);
	return entity->ExecQuery(lastParsedQuery, queryObject, DSDatabaseEntity::INSERT);
}

bool DynSoft::DSEntityData::Update(DSDatabaseEntity *entity, const wxString &where, const bool withoutPrimaryKey, wxArrayString *withoutFields, DSQuery *queryObject) {
	lastParsedQuery = entity->CreateUpdateQuery(where, withoutPrimaryKey, withoutFields);
	return entity->ExecQuery(lastParsedQuery, queryObject, DSDatabaseEntity::UPDATE);
}

bool DynSoft::DSEntityData::InsertOrUpdate(DSDatabaseEntity *entity, wxArrayString *withoutFields, DSQuery *queryObject) {
	if(Exists(entity->GetPrimaryKey(), entity->Get(entity->GetPrimaryKey())->ToString()))
		return Update(entity, wxEmptyString, entity->GetGetAutoSequence(), withoutFields, queryObject);
	return Insert(entity, entity->GetGetAutoSequence(), withoutFields, queryObject);
}

bool DynSoft::DSEntityData::Delete(DSDatabaseEntity *entity, const wxString &where, DSQuery *queryObject) {
	lastParsedQuery = entity->CreateDeleteQuery(where);
	return entity->ExecQuery(lastParsedQuery, queryObject, DSDatabaseEntity::REMOVE);
}

wxString DynSoft::DSEntityData::GetLastParsedQuery() const {
	return lastParsedQuery;
}

void DynSoft::DSEntityData::SetTable(const wxString &table) {
	this->table = table;
}

wxString DynSoft::DSEntityData::GetTable() const {
	return table;
}

bool DynSoft::DSEntityData::Persist(DSDatabaseEntity *entity, DSQuery *queryObject) {
	if(!InsertOrUpdate(entity, NULL, queryObject))
		return false;
	
	DSDatabaseEntity *nextEntity = NULL;
	DSTemplateContainer<DSDatabaseEntity *> *entities = entity->GetReferences();
	const unsigned int count = entities->GetCount();
	for(unsigned int i = 0; i < count; i++) {
		nextEntity = entities->Get(i);

		switch(entity->Get(entity->GetPrimaryKey())->GetType()) {
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_SHORT:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToShort());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_SHORT:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToUnsignedShort());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_INT:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToInt());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_INT:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToUnsignedInt());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_LONG:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToLong());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_LONG:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToUnsignedLong());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_FLOAT:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToFloat());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DOUBLE:
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DSCURRENCY:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToDouble());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_CHAR_POINTER:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToChar());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_BOOL:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToBool());
				break;
			case DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_WXSTRING:
			default:
				nextEntity->SetValue(nextEntity->GetForeignKey(), entity->Get(entity->GetPrimaryKey())->ToString());
				break;
		}

		if(!Persist(nextEntity, queryObject))
			return false;
	}

	return true;
}

