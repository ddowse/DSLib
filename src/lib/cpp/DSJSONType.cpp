#include "DSJSONType.h"
#include <wx/jsonwriter.h>

DynSoft::DSJSONType::DSJSONType() : wxJSONValue() {
}

DynSoft::DSJSONType::DSJSONType(wxJSONValue value) : wxJSONValue(value) {
}

DynSoft::DSJSONType::DSJSONType(DSJSONType &type) : wxJSONValue(type) {
}

DynSoft::DSJSONType::DSJSONType(int i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(unsigned int i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(short i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(unsigned short i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(long int i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(unsigned long int i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(wxInt64 i) : wxJSONValue(i) {
}

DynSoft::DSJSONType::DSJSONType(wxUint64 ui) : wxJSONValue(ui) {
}

DynSoft::DSJSONType::DSJSONType(bool b) : wxJSONValue(b) {
}

DynSoft::DSJSONType::DSJSONType(double d) : wxJSONValue(d) {
}

DynSoft::DSJSONType::DSJSONType(const wxChar *str) : wxJSONValue(str) {
}

DynSoft::DSJSONType::DSJSONType(const wxString &str) : wxJSONValue(str) {
}

DynSoft::DSJSONType::DSJSONType(const DSJSONType &other) : wxJSONValue(other) {
}

DynSoft::DSClassInfo DynSoft::DSJSONType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_JSON_TYPE_NAME,
		DS_JSON_TYPE_VERSION,
		DS_JSON_TYPE_AUTHOR
	);
}

wxString DynSoft::DSJSONType::ToString() const {
	wxString s;
	wxJSONWriter w;
	w.Write(*this, s);
	return s;
}

void DynSoft::DSJSONType::Print() const {
	DS_PL(ToString());
}
