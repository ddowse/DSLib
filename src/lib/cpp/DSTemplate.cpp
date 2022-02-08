#include "DSTemplate.h"
#include "DSConstants.h"
#include "DSCasts.h"
#include "DSDateTime.h"
#include <wx/ffile.h>
#if ! defined __WXMSW__ && ! defined __WXMAC__
	#include "DSCgi.h"
	#include <fcgi_stdio.h>
#endif

DynSoft::DSTemplate::DSTemplate(const wxString &root) : DSLib() {
	this->root = root;
	if(this->root.Length() > 0)
		if(this->root[this->root.Length() - 1] != DS_PATH_SEPARATOR)
			this->root.Append(DS_PATH_SEPARATOR);
	FillInternVariables();
}

void DynSoft::DSTemplate::FillInternVariables() {
	DSDateTime dt;
	SetInternVariable(_N("date"), dt.ToDatabaseDate());
	SetInternVariable(_N("time"), dt.ToDatabaseTime());
	SetInternVariable(_N("datetime"), dt.ToDatabaseDateTime());
}

wxString DynSoft::DSTemplate::GetRoot() const {
	return root;
}

void DynSoft::DSTemplate::SetContent(const wxString &content) {
	this->content = content;
}

int DynSoft::DSTemplate::SetFile(const wxString &filename) {
	this->filename = filename;
	wxFFile file(root + filename, _N("r"));
	if(!file.IsOpened())
		return DS_FILE_NOT_OPEN;
	
	int result = DS_OK;
	if(!file.ReadAll(&content))
		result = DS_FILE_NOT_READ;
	file.Close();

	return result;
}

wxString &DynSoft::DSTemplate::GetContent() {
	return content;
}

wxString DynSoft::DSTemplate::GetContentCopy() const {
	return content;
}

wxString DynSoft::DSTemplate::GetFilename() const {
	return filename;
}

wxString &DynSoft::DSTemplate::Get() {
	return parsedContent;
}

wxString DynSoft::DSTemplate::GetCopy() const {
	return parsedContent;
}

void DynSoft::DSTemplate::SetVariable(
	const wxString &key,
	const wxString &value,
	const bool htmlSpecialChars
) {
	#if ! defined __WXMSW__ && ! defined __WXMAC__
		variables[key] = htmlSpecialChars ? DSCgi::HtmlSpecialChars(value) : value;
	#else
		variables[key] = value;
	#endif
}

wxString DynSoft::DSTemplate::GetVariable(const wxString &key) {
	return variables[key];
}

void DynSoft::DSTemplate::SetInternVariable(
	const wxString &key,
	const wxString &value,
	const bool htmlSpecialChars
) {
	#if ! defined __WXMSW__ && ! defined __WXMAC__
		intern[key] = htmlSpecialChars ? DSCgi::HtmlSpecialChars(value) : value;
	#else
		intern[key] = value;
	#endif
}

wxString DynSoft::DSTemplate::GetInternVariable(const wxString &key) {
	return intern[key];
}

DSStringHashMap DynSoft::DSTemplate::GetInternVariables() const {
	return intern;
}

void DynSoft::DSTemplate::SetDynamicVariable(
	const wxString &key,
	const wxString &value,
	const bool htmlSpecialChars
) {
	#if ! defined __WXMSW__ && ! defined __WXMAC__
		dynamic[key] = htmlSpecialChars ? DSCgi::HtmlSpecialChars(value) : value;
	#else
		dynamic[key] = value;
	#endif
}

wxString DynSoft::DSTemplate::GetDynamicVariable(const wxString &key) {
	return dynamic[key];
}

wxString DynSoft::DSTemplate::Parse() {
	wxString tmp(content);

	DSStringHashMap::iterator it;
	for(it = variables.begin(); it != variables.end(); ++it)
		tmp.Replace(_N("{s:") + it->first + _N("}"), it->second);
	for(it = intern.begin(); it != intern.end(); ++it)
		tmp.Replace(_N("{i:") + it->first + _N("}"), it->second);
	for(it = dynamic.begin(); it != dynamic.end(); ++it)
		tmp.Replace(_N("{d:") + it->first + _N("}"), it->second);
	parsedContent.Append(tmp);

	return tmp;
}

void DynSoft::DSTemplate::Show(const wxString &header) const {
	const char *tmpHeader = DSCasts::ToChar(header);
	const char *tmpContent = DSCasts::ToChar(parsedContent);
	printf(
		"%s%s\n",
		tmpHeader,
		tmpContent
	);
	delete [] tmpContent;
	delete [] tmpHeader;
}

DynSoft::DSClassInfo DynSoft::DSTemplate::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TEMPLATE_NAME,
		DS_TEMPLATE_VERSION,
		DS_TEMPLATE_AUTHOR
	);
}

void DynSoft::DSTemplate::ClearParsed() {
	parsedContent.Clear();
}

void DynSoft::DSTemplate::SetEntity(DynSoft::DSEntity *entity) {
	if(!entity)
		return;
	
	DynSoft::DSEntity::DSEntityType *entityType = NULL;
	const unsigned int count = entity->GetCount();
	for(unsigned int i = 0; i < count; i++) {
		entityType = entity->Get(i);
		if(entityType)
			SetVariable(entityType->GetKey(), entityType->ToString(), true);
	}
}
