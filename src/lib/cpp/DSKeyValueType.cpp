#include "DSKeyValueType.h"

DynSoft::DSKeyValueType::DSKeyValueType() {
	SetDataType(UNKNOWN);
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, DynSoft::DSCasts value) {
	SetKey(key); SetValue(value);
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const wxString &value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const bool value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const short value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const unsigned short value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const int value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const unsigned int value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const long value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const unsigned long value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const float value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const double value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, const char *value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, DynSoft::DSCurrency value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSKeyValueType::DSKeyValueType(const wxString &key, DynSoft::DSDateTime value) {
	SetKey(key); SetValue(DSCasts(value));
}

DynSoft::DSClassInfo DynSoft::DSKeyValueType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_KEY_VALUE_TYPE_NAME,
		DS_KEY_VALUE_TYPE_VERSION,
		DS_KEY_VALUE_TYPE_AUTHOR
	);
}

void DynSoft::DSKeyValueType::SetKey(const wxString &key) {
	this->key = key;
}

wxString DynSoft::DSKeyValueType::GetKey() const {
	return key;
}

void DynSoft::DSKeyValueType::SetValue(DynSoft::DSCasts value) {
	this->value = value;
	SetDataType(UNKNOWN);
}

void DynSoft::DSKeyValueType::SetValue(const wxString &value) {
	this->value = DSCasts(value);
	SetDataType(WXSTRING);
}

void DynSoft::DSKeyValueType::SetValue(const bool value) {
	this->value = DSCasts(value);
	SetDataType(BOOL);
}

void DynSoft::DSKeyValueType::SetValue(const short value) {
	this->value = DSCasts(value);
	SetDataType(SHORT);
}

void DynSoft::DSKeyValueType::SetValue(const unsigned short value) {
	this->value = DSCasts(value);
	SetDataType(UNSIGNED_SHORT);
}

void DynSoft::DSKeyValueType::SetValue(const int value) {
	this->value = DSCasts(value);
	SetDataType(INT);
}

void DynSoft::DSKeyValueType::SetValue(const unsigned int value) {
	this->value = DSCasts(value);
	SetDataType(UNSIGNED_INT);
}

void DynSoft::DSKeyValueType::SetValue(const long value) {
	this->value = DSCasts(value);
	SetDataType(LONG);
}

void DynSoft::DSKeyValueType::SetValue(const unsigned long value) {
	this->value = DSCasts(value);
	SetDataType(UNSIGNED_LONG);
}

void DynSoft::DSKeyValueType::SetValue(const float value) {
	this->value = DSCasts(value);
	SetDataType(FLOAT);
}

void DynSoft::DSKeyValueType::SetValue(const double value) {
	this->value = DSCasts(value);
	SetDataType(DOUBLE);
}

void DynSoft::DSKeyValueType::SetValue(const char *value) {
	this->value = DSCasts(value);
	SetDataType(CHAR_P);
}

void DynSoft::DSKeyValueType::SetValue(DynSoft::DSCurrency value) {
	this->value = DSCasts(value);
	SetDataType(DSCURRENCY);
}

void DynSoft::DSKeyValueType::SetValue(DynSoft::DSDateTime value) {
	this->value = DSCasts(value);
	SetDataType(DSDATETIME);
}

DynSoft::DSCasts DynSoft::DSKeyValueType::GetValue() {
	return value;
}

wxString DynSoft::DSKeyValueType::ToString() {
	return _N("\"") + GetKey() + _N("\" => \"") + GetValue().ToString() + _N("\"");
}

void DynSoft::DSKeyValueType::SetDataType(DynSoft::DSKeyValueType::DataType dataType) {
	this->dataType = dataType;
}

DynSoft::DSKeyValueType::DataType DynSoft::DSKeyValueType::GetDataType() const {
	return dataType;
}
