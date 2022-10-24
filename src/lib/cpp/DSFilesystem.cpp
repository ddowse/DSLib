#include "DSFilesystem.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/mimetype.h>

DynSoft::DSFilesystem::DSFilesystem() : DSLib() {
}

DynSoft::DSFilesystem::DSFilesystem(const wxString &baseDirectory) : DSLib() {
	SetBaseDirectory(baseDirectory);
}

DynSoft::DSClassInfo DynSoft::DSFilesystem::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_FILESYSTEM_NAME,
		DS_FILESYSTEM_VERSION,
		DS_FILESYSTEM_AUTHOR
	);
}

void DynSoft::DSFilesystem::SetBaseDirectory(const wxString &baseDirectory) {
	this->baseDirectory = NormalizeDirectory(baseDirectory);
}

wxString DynSoft::DSFilesystem::GetBaseDirectory() const {
	return baseDirectory;
}

DynSoft::DSDirectoriesType *DynSoft::DSFilesystem::Get(
	wxString directory,
	ErrorType *error,
	const bool autoClean
) {
	if(error)
		*error = ERROR_NO;
	
	if(!IsDirectorySecure(directory)) {
		if(error)
			*error = ERROR_SECURE;
		return NULL;
	}

	directory = Concat(GetBaseDirectory(), directory);

	if(!wxDirExists(directory)) {
		if(error)
			*error = ERROR_DIRECTORY_EXISTS;
		return NULL;
	}

	wxDir dir(directory);
	if(!dir.IsOpened()) {
		if(error)
			*error = ERROR_DIRECTORY_OPEN;
		return NULL;
	}

	DynSoft::DSDirectoriesType *directoriesType = new DynSoft::DSDirectoriesType(autoClean);

	wxULongLong size;
	wxString mimetype;
	wxFileType *filetype = NULL;
	wxMimeTypesManager mimeTypesManager;
	wxFileName filename;
	wxString name;
	bool next = dir.GetFirst(&name);
	while(next) {
		filename.Assign(directory, name);

		if(wxDirExists(filename.GetFullPath())) {
			size = dir.GetTotalSize(filename.GetFullPath());
			size = size == 4294967295 ? 0 : size;
			directoriesType->AddDirectory(new DynSoft::DSDirectoryType(
				filename.GetName(),
				filename.GetFullPath(),
				filename.GetPath(),
				StripBaseDirectory(filename.GetFullPath()),
				size
			));
		} else {
			filetype = mimeTypesManager.GetFileTypeFromExtension(filename.GetExt());
			if(filetype) {
				filetype->GetMimeType(&mimetype);
				delete filetype;
			} else {
				mimetype.Clear();
			}

			directoriesType->AddFile(new DynSoft::DSFileType(
				filename.GetFullName(),
				filename.GetName(),
				filename.GetExt(),
				filename.GetFullPath(),
				filename.GetPath(),
				filename.GetSize(),
				filename.GetHumanReadableSize(),
				filename.IsFileExecutable(),
				filename.IsFileReadable(),
				filename.IsFileWritable(),
				mimetype
			));
		}

		next = dir.GetNext(&name);
	}

	return directoriesType;
}

bool DynSoft::DSFilesystem::IsDirectorySecure(const wxString &directory) {
	if(directory.Find(_N("..")) != wxNOT_FOUND)
		return false;
	
	if(directory.Length() > 0 && directory[directory.Length() - 1] == '/')
		return false;
	
	return true;
}

wxString DynSoft::DSFilesystem::NormalizeDirectory(wxString directory) {
	directory.Trim().Trim(false);
	return directory;
}

wxString DynSoft::DSFilesystem::Concat(const wxString &path1, wxString path2) {
	const wxString sep(wxFileName::GetPathSeparator());

	const unsigned int path1Length = path1.Length();
	const unsigned int path2Length = path2.Length();

	while(path2Length > 0 && path2[0] == sep)
		path2 = path2.Mid(1);

	wxString concated(path1);
	if(path1Length > 0 && path1[path1Length - 1] != sep && path2Length > 0)
		concated += sep;
	
	if(path1Length == 0 && path2Length > 0 && path2[0] == sep)
		concated += path2.Mid(1);
	else
		concated += path2;
	
	return concated;
}

DynSoft::DSFilesystem::ErrorType DynSoft::DSFilesystem::CreateDirectory(wxString directory) {
	if(!IsDirectorySecure(directory))
		return ERROR_SECURE;
	
	directory = Concat(GetBaseDirectory(), directory);

	if(wxDirExists(directory))
		return ERROR_DIRECTORY_EXISTS;

	return wxMkdir(directory) ? ERROR_NO : ERROR_DIRECTORY_CREATE;
}

DynSoft::DSFilesystem::ErrorType DynSoft::DSFilesystem::RemoveDirectory(wxString directory) {
	if(!IsDirectorySecure(directory))
		return ERROR_SECURE;
	
	directory = Concat(GetBaseDirectory(), directory);

	if(!wxDirExists(directory))
		return ERROR_DIRECTORY_NOT_EXISTS;

#if wxMAJOR_VERSION == 3
	return wxFileName::Rmdir(directory, wxPATH_RMDIR_RECURSIVE) ? ERROR_NO : ERROR_DIRECTORY_REMOVE;
#else
	return wxFileName::Rmdir(directory) ? ERROR_NO : ERROR_DIRECTORY_REMOVE;
#endif
}

DynSoft::DSFilesystem::ErrorType DynSoft::DSFilesystem::CopyFile(wxString fromFilename, wxString toFilename, const bool overwrite) {
	if(!IsDirectorySecure(fromFilename) || !IsDirectorySecure(toFilename))
		return ERROR_SECURE;

	fromFilename = Concat(GetBaseDirectory(), fromFilename);
	if(!wxFileExists(fromFilename))
		return ERROR_FILE_NOT_EXISTS;

	toFilename = Concat(GetBaseDirectory(), toFilename);
	if(!overwrite && wxFileExists(toFilename))
		return ERROR_FILE_EXISTS;
	
	return wxCopyFile(fromFilename, toFilename, overwrite) ? ERROR_NO : ERROR_FILE_COPY;
}

DynSoft::DSFilesystem::ErrorType DynSoft::DSFilesystem::MoveFile(wxString fromFilename, wxString toFilename, const bool overwrite) {
	if(!IsDirectorySecure(fromFilename) || !IsDirectorySecure(toFilename))
		return ERROR_SECURE;

	fromFilename = Concat(GetBaseDirectory(), fromFilename);
	if(!wxFileExists(fromFilename))
		return ERROR_FILE_NOT_EXISTS;

	toFilename   = Concat(GetBaseDirectory(), toFilename);
	if(!overwrite && wxFileExists(toFilename))
		return ERROR_FILE_EXISTS;
	
	return wxRenameFile(fromFilename, toFilename, overwrite) ? ERROR_NO : ERROR_FILE_MOVE;
}

DynSoft::DSFilesystem::ErrorType DynSoft::DSFilesystem::RemoveFile(wxString filename) {
	if(!IsDirectorySecure(filename))
		return ERROR_SECURE;
	
	filename = Concat(GetBaseDirectory(), filename);

	if(!wxFileExists(filename))
		return ERROR_FILE_NOT_EXISTS;

	return wxRemoveFile(filename) ? ERROR_NO : ERROR_FILE_REMOVE;
}

wxString DynSoft::DSFilesystem::ErrorToString(const ErrorType error) {
	wxString result;

	switch(error) {
		case ERROR_NO:
			result = _("No error.");
			break;
		case ERROR_SECURE:
			result = _("The path is unsecure. Do not use absolute paths or double dots (.. or ../ or /.. or /../) in your path for security reasons.");
			break;
		case ERROR_DIRECTORY_EXISTS:
			result = _("The directory already exists.");
			break;
		case ERROR_DIRECTORY_NOT_EXISTS:
			result = _("The directory does not exist.");
			break;
		case ERROR_DIRECTORY_CREATE:
			result = _("Could not create the directory.");
			break;
		case ERROR_DIRECTORY_OPEN:
			result = _("Could not open the directory.");
			break;
		case ERROR_DIRECTORY_REMOVE:
			result = _("Could not remove the directory.");
			break;
		case ERROR_FILE_EXISTS:
			result = _("The file already exists.");
			break;
		case ERROR_FILE_NOT_EXISTS:
			result = _("The file does not exist.");
			break;
		case ERROR_FILE_COPY:
			result = _("Could not copy the file.");
			break;
		case ERROR_FILE_MOVE:
			result = _("Could not move or rename the file.");
			break;
		case ERROR_FILE_REMOVE:
			result = _("Could not remove the file.");
			break;
		default:
			result = _("Unknown error");
			break;
	}

	return result;
}

wxString DynSoft::DSFilesystem::StripBaseDirectory(wxString path) {
	const wxString base(GetBaseDirectory());
	const size_t length = base.Length();
	if(length == 0)
		return path;
	
	if(path.Length() < length)
		return path;
	
	if(path.Mid(0, length) == base)
		return path.Mid(length);

	return path;
}
