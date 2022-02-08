#include "DSEntity.h"

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const wxString &value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_WXSTRING);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const bool value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_BOOL);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const short value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_SHORT);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const unsigned short value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_SHORT);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const int value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_INT);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const unsigned int value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_INT);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const long value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_LONG);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const unsigned long value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_UNSIGNED_LONG);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const float value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_FLOAT);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const double value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DOUBLE);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, const char *value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_CHAR_POINTER);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, DSCurrency value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DSCURRENCY);
}

DynSoft::DSEntity::DSEntityType::DSEntityType(const wxString &key, DSDateTime value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) : DynSoft::DSCasts(value) {
	SetParameters(key, delimeters, escape, field, length, null, DynSoft::DSEntity::DSEntityType::DS_RESULT_TYPE_DSDATETIME);
}

void DynSoft::DSEntity::DSEntityType::SetParameters(
	const wxString &key,
	const bool delimeters,
	const bool escape,
	const wxString &field,
	const unsigned int length,
	const bool null,
	const DynSoft::DSEntity::DSEntityType::DSResultType type
) {
	SetKey(key);
	SetDelimiters(delimeters);
	SetEscape(escape);
	SetField(field);
	SetLength(length);
	SetNull(null);
	SetType(type);
}

void DynSoft::DSEntity::DSEntityType::SetKey(const wxString &key) {
	this->key = key;
}

wxString DynSoft::DSEntity::DSEntityType::GetKey() const {
	return key;
}

void DynSoft::DSEntity::DSEntityType::SetDelimiters(const bool delimeters) {
	this->delimeters = delimeters;
}

bool DynSoft::DSEntity::DSEntityType::GetDelimiters() const {
	return delimeters;
}

void DynSoft::DSEntity::DSEntityType::SetEscape(const bool escape) {
	this->escape = escape;
}

bool DynSoft::DSEntity::DSEntityType::GetEscape() const {
	return escape;
}

void DynSoft::DSEntity::DSEntityType::SetField(const wxString &field) {
	this->field = field;
}

wxString DynSoft::DSEntity::DSEntityType::GetField() const {
	return field;
}

void DynSoft::DSEntity::DSEntityType::SetLength(const unsigned int length) {
	this->length = length;
}

unsigned int DynSoft::DSEntity::DSEntityType::GetLength() const {
	return length;
}

void DynSoft::DSEntity::DSEntityType::SetNull(const bool null) {
	this->null = null;
}

bool DynSoft::DSEntity::DSEntityType::GetNull() const {	
	return null;
}

void DynSoft::DSEntity::DSEntityType::SetType(DynSoft::DSEntity::DSEntityType::DSResultType type) {
	this->type = type;
}

DynSoft::DSEntity::DSEntityType::DSResultType DynSoft::DSEntity::DSEntityType::GetType() const {
	return type;
}


DynSoft::DSEntity::DSEntity() : DSLib() {
}

DynSoft::DSEntity::DSEntity(
	const wxString &name,
	const wxString &primaryKey,
	const wxString &foreignKey
) : DSLib() {
	SetName(name);
	SetPrimaryKey(primaryKey);
	SetForeignKey(foreignKey);
}

DynSoft::DSEntity::~DSEntity() {
	entities.Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSEntity::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_ENTITY_NAME,
		DS_ENTITY_VERSION,
		DS_ENTITY_AUTHOR
	);
}

DynSoft::DSEntity::DSEntityInternalType DynSoft::DSEntity::GetInternalType() const {
	return DynSoft::DSEntity::DS_ENTITY;
}

void DynSoft::DSEntity::Set(const wxString &key, const wxString &value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const bool value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const short value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const unsigned short value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const int value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const unsigned int value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const long value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const unsigned long value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const float value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const double value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, const char *value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, DSCurrency value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

void DynSoft::DSEntity::Set(const wxString &key, DSDateTime value, const bool delimeters, const bool escape, const wxString &field, const unsigned int length, const bool null) {
	Remove(key); entities.Add(new DynSoft::DSEntity::DSEntityType(key, value, delimeters, escape, field, length, null));
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const wxString &value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const bool value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const short value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const unsigned short value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const int value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const unsigned int value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const long value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const unsigned long value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const float value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const double value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, const char *value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, DSCurrency value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

bool DynSoft::DSEntity::SetValue(const wxString &key, DSDateTime value) {
	DSEntityType *entityType = Get(key);
	if(!entityType)
		return false;

	DSEntityType *newEntityType = new DynSoft::DSEntity::DSEntityType(key, value, entityType->GetDelimiters(), entityType->GetEscape(), entityType->GetField(), entityType->GetLength(), entityType->GetNull());
	newEntityType->SetType(entityType->GetType());
	Remove(key);
	entities.Add(newEntityType);
	return true;
}

DynSoft::DSEntity::DSEntityType *DynSoft::DSEntity::Get(const wxString &key) {
	DynSoft::DSEntity::DSEntityType *tmp = NULL;
	const unsigned int count = entities.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		tmp = entities.Get(i);
		if(tmp && tmp->GetKey() == key)
			break;
		tmp = NULL;
	}
	return tmp;
}

bool DynSoft::DSEntity::Equals(DSEntity *entity) {
	if(!entity || entity->GetCount() != GetCount()) {
		return false;
	}

	DynSoft::DSEntity::DSEntityType *tmp = NULL;
	const unsigned int count = entities.GetCount();
	unsigned int equalCount = 0;
	for(unsigned int i = 0; i < count; i++) {
		tmp = entities.Get(i);
		for(unsigned int j = 0; j < count; j++) {
			if(tmp->GetType() == entity->Get(j)->GetType()) {
				if(tmp->GetKey() == entity->Get(j)->GetKey()) {
					if(tmp->ToString() == entity->Get(j)->ToString()) {
						++equalCount;
					}
				}
			}
		}
	}
	
	return equalCount == count;
}

DynSoft::DSEntity::DSEntityType *DynSoft::DSEntity::Get(const unsigned int index) {
	return entities.Get(index);
}

void DynSoft::DSEntity::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSEntity::GetName() const {
	return name;
}

bool DynSoft::DSEntity::Remove(const wxString &key) {
	return entities.Remove(Get(key), true) > 0;
}

void DynSoft::DSEntity::SetPrimaryKey(const wxString &primaryKey) {
	this->primaryKey = primaryKey;
}

wxString DynSoft::DSEntity::GetPrimaryKey() const {
	return primaryKey;
}

void DynSoft::DSEntity::SetForeignKey(const wxString &foreignKey) {
	this->foreignKey = foreignKey;
}

wxString DynSoft::DSEntity::GetForeignKey() const {
	return foreignKey;
}

unsigned int DynSoft::DSEntity::GetCount() const {
	return entities.GetCount();
}

wxString DynSoft::DSEntity::ToString() {
	wxString tmp;
	DSEntityType *entry = NULL;
	const unsigned int count = GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entry = Get(i);
		if(entry) {
			tmp.Append(entry->GetKey());
			tmp.Append(_N(" => { "));
			tmp.Append(entry->ToString());
			tmp.Append(_N(" }"));

			if(i < count - 1)
				tmp.Append(_N("\n"));
		}
	}
	return tmp;
}


wxString DynSoft::DSEntity::ToCsv(
	const bool columns,
	wxString fieldDelimiter,
	const wxString &textDelimiter,
	const wxString &replaceLineFeedWith,
	const bool replaceLineFeed
) {
	if(fieldDelimiter == _N("{tab}"))
		fieldDelimiter = _N("\t");

	wxString tmp;
	DSEntityType *entry = NULL;
	wxString value;
	const unsigned int count = GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entry = Get(i);
		if(entry) {
			if(columns) {
				value = entry->GetKey();
				value.Replace(fieldDelimiter, _N("\\") + fieldDelimiter);
				value.Replace(textDelimiter, _N("\\") + textDelimiter);

				if(replaceLineFeed) {
					value.Replace(_N("\r\n"), replaceLineFeedWith);
					value.Replace(_N("\n"), replaceLineFeedWith);
					value.Replace(_N("\r"), replaceLineFeedWith);
				}

				tmp.Append(textDelimiter);
				tmp.Append(entry->GetKey());
				tmp.Append(textDelimiter);
				if(i < count - 1)
					tmp.Append(fieldDelimiter);
			} else {
				tmp.Append(textDelimiter);
				value = entry->ToString();
				value.Replace(fieldDelimiter, _N("\\") + fieldDelimiter);
				value.Replace(textDelimiter, _N("\\") + textDelimiter);

				if(replaceLineFeed) {
					value.Replace(_N("\r\n"), replaceLineFeedWith);
					value.Replace(_N("\n"), replaceLineFeedWith);
					value.Replace(_N("\r"), replaceLineFeedWith);
				}

				tmp.Append(value);
				tmp.Append(textDelimiter);

				if(i < count - 1)
					tmp.Append(fieldDelimiter);
			}
		}
	}
	return tmp;
}
