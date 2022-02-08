#include "DSQueryParser.h"
#include "DSCasts.h"

DynSoft::DSQueryParser::DSQueryParser(const wxString &query) : DSLib() {
	this->query = query;
}

DynSoft::DSClassInfo DynSoft::DSQueryParser::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_QUERY_PARSER_NAME,
		DS_QUERY_PARSER_VERSION,
		DS_QUERY_PARSER_AUTHOR
	);
}

void DynSoft::DSQueryParser::Prepare(const wxString &query) {
	this->query = query;
	ExtractFields();
}

void DynSoft::DSQueryParser::PrepareByResource(const wxString &resource) {
	Prepare(GetResourceByName(resource));
}

bool DynSoft::DSQueryParser::Bind(
	const wxString &field,
	wxString value,
	const bool delimiters,
	const bool escape
) {
	if(!FindInArrayString(fields, field))
		return false;

	if(escape)
		EscapeReference(value);
	if(delimiters)
		value = _N("'") + value + _N("'");
	
	keyValues[field] = value;

	return true;
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const short value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const unsigned short value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const int value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const unsigned int value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const long value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const unsigned long value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const float value) {
	wxString tmp(DSCasts::ToString(value));
	tmp.Replace(_N(","), _N("."));
	return Bind(field, tmp, false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const double value) {
	wxString tmp(DSCasts::ToString(value));
	tmp.Replace(_N(","), _N("."));
	return Bind(field, tmp, false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, const bool value) {
	return Bind(field, DSCasts::ToString(value), false, false);
}

bool DynSoft::DSQueryParser::Bind(const wxString &field, DSCurrency value) {
	return Bind(field, value.ToDouble());
}

bool DynSoft::DSQueryParser::Bind(
	const wxString &field,
	const char *value,
	const bool delimiters,
	const bool escape
) {
	return Bind(field, DSCasts::ToString(value), delimiters, escape);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, wxString value) {
	const bool empty = value.IsEmpty();
	return Bind(field, empty ? wxString(_N("NULL")) : value, !empty);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const short value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const unsigned short value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const int value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const unsigned int value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const long value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const unsigned long value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, const double value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field, DSCurrency value) {
	return value == 0 ? BindNull(field) : Bind(field, value);
}

bool DynSoft::DSQueryParser::BindNull(const wxString &field) {
	return Bind(field, _N("NULL"), false);
}

bool DynSoft::DSQueryParser::UnBind(const wxString &field) {
	bool found = false;
	for(unsigned long i = 0; i < fields.GetCount(); i++) {
		if(fields[i] == field) {
			fields.RemoveAt(i);
			keyValues.erase(field);
			found = true;
		}
	}

	return found;
}

wxString &DynSoft::DSQueryParser::GetQuery() {
	return query;
}

wxString DynSoft::DSQueryParser::GetParsedQuery() {
	if(fields.GetCount() == 0)
		return query;
	
	wxString tmp(query);
	wxString tmpField;
	
	size_t pos = 0;
	for(unsigned int i = 0; i < fields.GetCount(); i++) {
		tmpField = _N(":") + fields[i] + _N(":");

		pos = tmp.find(tmpField, pos);
		if(pos != wxString::npos) {
			tmp.replace(
				pos,
				tmpField.Length(),
				keyValues[fields[i]],
				0,
				keyValues[fields[i]].Length()
			);

			pos += keyValues[fields[i]].Length() + 1;
		}
	}

	return tmp;
}

int DynSoft::DSQueryParser::ExtractFields() {
	fields.Clear();

	if(query.Length() == 0)
		return 0;
	
	bool in = false;
	wxString tmp;
	wxChar c;
	int i = 0;
	for(; i < (int) query.Length(); i++) {
		c = query[i];

		if(c == ':' && in) {
			in = false;
			fields.Add(tmp);
			keyValues[tmp] = wxEmptyString;
			tmp.Clear();
		} else if(c == ':' && !in) {
			in = true;
			continue;
		}

		if(in)
			tmp.Append(c);
	}

	return i;
}

unsigned long DynSoft::DSQueryParser::RemoveFields() {
	unsigned long count = fields.GetCount();
	fields.Clear();
	return count;
}

bool DynSoft::DSQueryParser::FindInArrayString(const wxArrayString &array, const wxString &field) const {
	for(unsigned int i = 0; i < array.GetCount(); i++)
		if(array[i] == field)
			return true;
	return false;
}

wxString DynSoft::DSQueryParser::Escape(wxString value) {
	value.Replace(_N("\\"), _N("\\\\"));
	value.Replace(_N("'"), _N("''"));
	return value;
}

wxString &DynSoft::DSQueryParser::EscapeReference(wxString &value) {
	value.Replace(_N("\\"), _N("\\\\"));
	value.Replace(_N("'"), _N("''"));
	return value;
}

