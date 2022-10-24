#include "DSKeyValueTypes.h"
#include "DSCasts.h"

DynSoft::DSKeyValueTypes::DSKeyValueTypes(
	const bool autoCleanUp
) : DynSoft::DSTemplateContainer<DSKeyValueType *>(
) {
	SetAutoCleanUp(autoCleanUp);
}

DynSoft::DSKeyValueTypes::~DSKeyValueTypes() {
	if(IsAutoCleanUp())
		Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSKeyValueTypes::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_KEY_VALUE_TYPES_NAME,
		DS_KEY_VALUE_TYPES_VERSION,
		DS_KEY_VALUE_TYPES_AUTHOR
	);
}

void DynSoft::DSKeyValueTypes::SetAutoCleanUp(const bool autoCleanUp) {
	this->autoCleanUp = autoCleanUp;
}

bool DynSoft::DSKeyValueTypes::IsAutoCleanUp() const {
	return autoCleanUp;
}

unsigned int DynSoft::DSKeyValueTypes::Count() {
	return GetCount();
}

DynSoft::DSKeyValueType *DynSoft::DSKeyValueTypes::GetOrCreate(const wxString &key, const wxString &value) {
	DSKeyValueType *keyValueType = PullDSKeyValueType(key);
	if(!keyValueType) {
		keyValueType = new DSKeyValueType(key, value);
		PushDSKeyValueType(keyValueType);
	}

	return keyValueType;
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, DSCasts value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const wxString &value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const bool value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const short value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const unsigned short value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const int value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const unsigned int value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const long value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const unsigned long value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const float value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const double value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, const char *value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, DSCurrency value) {
	GetOrCreate(key)->SetValue(value);
}

void DynSoft::DSKeyValueTypes::Push(const wxString &key, DSDateTime value) {
	GetOrCreate(key)->SetValue(value);
}

DynSoft::DSCasts DynSoft::DSKeyValueTypes::Pull(const wxString &key) {
	DSKeyValueType *keyValueType = PullDSKeyValueType(key);
	return keyValueType ? keyValueType->GetValue() : wxString();
}

DynSoft::DSCasts DynSoft::DSKeyValueTypes::Pull(const unsigned int index) {
	DSKeyValueType *keyValueType = PullDSKeyValueType(index);
	return keyValueType ? keyValueType->GetValue() : wxString();
}

bool DynSoft::DSKeyValueTypes::Delete(const wxString &key) {
	return Remove(PullDSKeyValueType(key), IsAutoCleanUp()) > 0;
}

bool DynSoft::DSKeyValueTypes::Delete(const unsigned int index) {
	return Remove(PullDSKeyValueType(index), IsAutoCleanUp()) > 0;
}

bool DynSoft::DSKeyValueTypes::PushDSKeyValueType(DynSoft::DSKeyValueType *keyValueType, const bool deleteIfAlreadyExists) {
	if(!keyValueType)
		return false;
	
	if(PullDSKeyValueType(keyValueType->GetKey())) {
		if(deleteIfAlreadyExists)
			delete keyValueType;
		return false;
	}

	Add(keyValueType);

	return true;
}

DynSoft::DSKeyValueType *DynSoft::DSKeyValueTypes::PullDSKeyValueType(const wxString &key) {
	DSKeyValueType *keyValueType = NULL;
	
	const unsigned int count = Count();
	for(unsigned int i = 0; i < count; i++) {
		keyValueType = Get(i);
		if(keyValueType && keyValueType->GetKey() == key)
			break;
		else
			keyValueType = NULL;
	}

	return keyValueType;
}

DynSoft::DSKeyValueType *DynSoft::DSKeyValueTypes::PullDSKeyValueType(const unsigned int index) {
	return static_cast<DSKeyValueType *>(Get(index));
}

wxString DynSoft::DSKeyValueTypes::ToString(const wxString &delimiter) {
	wxString result;
	DSKeyValueType *keyValueType = NULL;

	const unsigned int count = Count();
	for(unsigned int i = 0; i < count; i++) {
		keyValueType = Get(i);
		if(keyValueType) {
			result += keyValueType->ToString();
			if(i + 1 < count)
				result += delimiter;
		}
	}

	return result;
}

bool DynSoft::DSKeyValueTypes::Exists(const wxString &key) {
	return PullDSKeyValueType(key) ? true : false;
}

wxString DynSoft::DSKeyValueTypes::NonEmptyToString(
	const wxString &keyDelimiter,
	const wxString &delimiter
) {
	wxString result;
	DSKeyValueType *keyValueType = NULL;

	const unsigned int count = Count();
	for(unsigned int i = 0; i < count; i++) {
		keyValueType = Get(i);
		if(keyValueType && !keyValueType->GetValue().ToString().IsEmpty())
			result += keyValueType->GetKey() + keyDelimiter + keyValueType->GetValue().ToString() + delimiter;
	}

	const size_t resultLen = result.Len();
	const size_t delimiterLen = delimiter.Len();

	if(resultLen >= delimiterLen)
		result = result.Mid(0, resultLen - delimiterLen);

	return result;
}
