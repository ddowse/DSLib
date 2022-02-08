#include "DSFile.h"
#include <wx/filename.h>

DynSoft::DSFile::DSFile(
	DSDatabase *db
) : DSLib(
	db
) {
}

DynSoft::DSFile::DSFile(
	const wxString &filename,
	const wxString &mode
) : wxFFile(
	filename,
	mode
) {
}

DynSoft::DSClassInfo DynSoft::DSFile::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_FILE_NAME,
		DS_FILE_VERSION,
		DS_FILE_AUTHOR
	);
}

wxArrayString DynSoft::DSFile::ReadToArrayString(wxMBConv &conv) {
	wxString tmp;
	ReadAll(&tmp, conv);
	tmp.Replace(_N("\r\n"), _N("\n"));
	tmp.Replace(_N("\r"), _N("\n"));
	return DSLib::Split(tmp, '\n');
}

wxString DynSoft::DSFile::Concat(const wxString &first, const wxString &second) {
	const wxChar sep = wxFileName::GetPathSeparator();
	const unsigned int length = first.Length();
	if(length > 0 && first[length - 1] != sep)
		return first + sep + second;
	return first + second;
}

bool DynSoft::DSFile::ExistsFile(const wxString &file) {
	FILE *f = fopen(file.mb_str(wxConvUTF8), "r");
	if(f) {
		fclose(f);
		return true;
	}

	return false;
}
