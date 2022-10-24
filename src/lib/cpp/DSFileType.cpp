#include "DSFileType.h"

DynSoft::DSFileType::DSFileType(
	const wxString &fullname,
	const wxString &name,
	const wxString &extension,
	const wxString &full,
	const wxString &path,
	const wxULongLong size,
	const wxString &humanSize,
	const bool executable,
	const bool readable,
	const bool writeable,
	const wxString &mimetype
) : DSType(
) {
	SetFullname(fullname);
	SetName(name);
	SetExtension(extension);
	SetFull(full);
	SetPath(path);
	SetSize(size);
	SetHumanSize(humanSize);
	SetExecutable(executable);
	SetReadable(readable);
	SetWriteable(writeable);
	SetMimetype(mimetype);
}

DynSoft::DSClassInfo DynSoft::DSFileType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_FILE_TYPE_NAME,
		DS_FILE_TYPE_VERSION,
		DS_FILE_TYPE_AUTHOR
	);
}

void DynSoft::DSFileType::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSFileType::GetName() const {
	return name;
}

void DynSoft::DSFileType::SetFullname(const wxString &fullname) {
	this->fullname = fullname;
}

wxString DynSoft::DSFileType::GetFullname() const {
	return fullname;
}

void DynSoft::DSFileType::SetFull(const wxString &full) {
	this->full = full;
}

wxString DynSoft::DSFileType::GetFull() const {
	return full;
}

void DynSoft::DSFileType::SetPath(const wxString &path) {
	this->path = path;
}

wxString DynSoft::DSFileType::GetPath() const {
	return path;
}

void DynSoft::DSFileType::SetExtension(const wxString &extension) {
	this->extension = extension;
}

wxString DynSoft::DSFileType::GetExtension() const {
	return extension;
}

void DynSoft::DSFileType::SetSize(const wxULongLong size) {
	this->size = size;
}

wxULongLong DynSoft::DSFileType::GetSize() const {
	return size;
}

void DynSoft::DSFileType::SetHumanSize(const wxString &humanSize) {
	this->humanSize = humanSize;
}

wxString DynSoft::DSFileType::GetHumanSize() const {
	return humanSize;
}

void DynSoft::DSFileType::SetExecutable(const bool executable) {
	this->executable = executable;
}

bool DynSoft::DSFileType::IsExecutable() const {
	return executable;
}

void DynSoft::DSFileType::SetReadable(const bool readable) {
	this->readable = readable;
}

bool DynSoft::DSFileType::IsReadable() const {
	return readable;
}

void DynSoft::DSFileType::SetWriteable(const bool writeable) {
	this->writeable = writeable;
}

bool DynSoft::DSFileType::IsWriteable() const {
	return writeable;
}

void DynSoft::DSFileType::SetMimetype(const wxString &mimetype) {
	this->mimetype = mimetype;
}

wxString DynSoft::DSFileType::GetMimetype() const {
	return mimetype;
}

wxString DynSoft::DSFileType::ToString() {
	return
		_N("  Fullname: ") + GetFullname() + _N("\n") +
		_N("      Name: ") + GetName() + _N("\n") +
		_N(" Extension: ") + GetExtension() + _N("\n") +
		_N("      Full: ") + GetFull() + _N("\n") +
		_N("      Path: ") + GetPath() + _N("\n") +
		_N("      Size: ") + GetSize().ToString() + _N("\n") +
		_N("Human size: ") + GetHumanSize() + _N("\n") +
		_N("Executable: ") + (IsExecutable() ? _N("YES") : _N("NO")) + _N("\n") +
		_N("  Readable: ") + (IsReadable() ? _N("YES") : _N("NO")) + _N("\n") +
		_N(" Writeable: ") + (IsWriteable() ? _N("YES") : _N("NO")) + _N("\n") +
		_N("  Mimetype: ") + GetMimetype() + _N("\n")
	;
}
