#include "DSLogType.h"

DynSoft::DSLogType::DSLogType() : DSErrorType() {
}

DynSoft::DSLogType::DSLogType(
	const int number,
	const wxString &username,
	const wxString &module,
	const wxString &description,
	const wxString &message,
	const DSDateTime &date
) : DSErrorType(
	number,
	module,
	description,
	message,
	date
) {
	SetUsername(username);
}

DynSoft::DSClassInfo DynSoft::DSLogType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_LOG_TYPE_NAME,
		DS_LOG_TYPE_VERSION,
		DS_LOG_TYPE_AUTHOR
	);
}

void DynSoft::DSLogType::SetUsername(const wxString &username) {
	this->username = username;
}

wxString DynSoft::DSLogType::GetUsername() const {
	return username;
}
