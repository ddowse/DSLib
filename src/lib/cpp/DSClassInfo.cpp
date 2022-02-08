#include "DSClassInfo.h"
#include "DSLib.h"

DynSoft::DSClassInfo::DSClassInfo(
	const wxString &name,
	const wxString &version,
	const wxString &author
) {
	SetName(name);
	SetVersion(version);
	SetAuthor(author);
}

DynSoft::DSClassInfo DynSoft::DSClassInfo::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CLASS_INFO_NAME,
		DS_CLASS_INFO_VERSION,
		DS_CLASS_INFO_AUTHOR
	);
}

void DynSoft::DSClassInfo::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSClassInfo::GetName() const {
	return name;
}

void DynSoft::DSClassInfo::SetVersion(const wxString &version) {
	this->version = version;
}

wxString DynSoft::DSClassInfo::GetVersion() const {
	return version;
}

void DynSoft::DSClassInfo::SetAuthor(const wxString &author) {
	this->author = author;
}

wxString DynSoft::DSClassInfo::GetAuthor() const {
	return author;
}


