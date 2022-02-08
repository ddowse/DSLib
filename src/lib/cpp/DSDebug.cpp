#include "DSDebug.h"
#include <wx/file.h>

DynSoft::DSDebug::DSDebug() : DSLib() {
}

DynSoft::DSClassInfo DynSoft::DSDebug::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DEBUG_NAME,
		DS_DEBUG_VERSION,
		DS_DEBUG_AUTHOR
	);
}

DynSoft::DSDebug::DSDebug(const wxString &message) {
	DynSoft::DSDebug::Write(message, false, wxEmptyString, true);
}

DynSoft::DSDebug::DSDebug(
	const wxString &message,
	const bool error,
	const wxString &value
) {
	DynSoft::DSDebug::Write(message, error, value);
}

bool DynSoft::DSDebug::Write(
	wxString message,
	const bool error,
	const wxString &value,
	const bool withoutErrorMasking
) {
	if(!withoutErrorMasking)
		message.Prepend(wxString((error ? _N("-") : _N("+"))) + _N(" "));
	message.Append(value + _N("\n"));

	wxFile file(DS_DEBUG_FILE, wxFile::write_append);
	if(!file.IsOpened())
		return false;

	file.Write(message);
	file.Close();

	return true;
}
