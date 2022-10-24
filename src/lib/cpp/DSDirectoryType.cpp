#include "DSDirectoryType.h"
#include <wx/filename.h>

DynSoft::DSDirectoryType::DSDirectoryType(
	wxString name,
	const wxString &full,
	const wxString &path,
	const wxString &withoutBase,
	wxULongLong size
) : DSType(
) {
	SetName(name);
	SetFull(full);
	SetPath(path);
	SetWithoutBase(withoutBase);
	SetSize(size);
}

DynSoft::DSClassInfo DynSoft::DSDirectoryType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DIRECTORY_TYPE_NAME,
		DS_DIRECTORY_TYPE_VERSION,
		DS_DIRECTORY_TYPE_AUTHOR
	);
}

void DynSoft::DSDirectoryType::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSDirectoryType::GetName() const {
	return name;
}

void DynSoft::DSDirectoryType::SetFull(const wxString &full) {
	this->full = full;
}

wxString DynSoft::DSDirectoryType::GetFull() const {
	return full;
}

void DynSoft::DSDirectoryType::SetPath(const wxString &path) {
	this->path = path;
}

wxString DynSoft::DSDirectoryType::GetPath() const {
	return path;
}

void DynSoft::DSDirectoryType::SetSize(const wxULongLong size) {
	this->size = size;
}

wxULongLong DynSoft::DSDirectoryType::GetSize() const {	
	return size;
}

wxString DynSoft::DSDirectoryType::ToString() {
	return
		_N("      Name: ") + GetName() + _N("\n") +
		_N("      Full: ") + GetFull() + _N("\n") +
		_N("      Path: ") + GetPath() + _N("\n") +
		_N("      Size: ") + GetSize().ToString()
	;
}

void DynSoft::DSDirectoryType::SetWithoutBase(const wxString &withoutBase) {
	this->withoutBase = withoutBase;
}

wxString DynSoft::DSDirectoryType::GetWithoutBase() const {
	return withoutBase;
}

wxString DynSoft::DSDirectoryType::GetParent(wxString path) {
	const int position = path.Find(wxFileName::GetPathSeparator(), true);
	if(position == wxNOT_FOUND)
		return wxEmptyString;

	return path.Mid(0, position);
}

wxArrayString DynSoft::DSDirectoryType::SplitPath(const wxString &path) {
	return Split(path, wxFileName::GetPathSeparator());
}
