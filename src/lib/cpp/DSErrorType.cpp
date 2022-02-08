#include "DSErrorType.h"

DynSoft::DSErrorType::DSErrorType() : DSContainerType() {
}

DynSoft::DSErrorType::DSErrorType(
	const int number,
	const wxString &module,
	const wxString &description,
	const wxString &message,
	const DSDateTime &date
) : DSContainerType(
) {
	SetNumber(number);
	SetModule(module);
	SetDescription(description);
	SetMessage(message);
	SetDate(date);
}

DynSoft::DSClassInfo DynSoft::DSErrorType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_ERROR_TYPE_NAME,
		DS_ERROR_TYPE_VERSION,
		DS_ERROR_TYPE_AUTHOR
	);
}

void DynSoft::DSErrorType::SetNumber(const int number) {
	this->number = number;
}

int DynSoft::DSErrorType::GetNumber() const {
	return number;
}


void DynSoft::DSErrorType::SetModule(const wxString &module) {
	this->module = module;
}

wxString DynSoft::DSErrorType::GetModule() const {
	return module;
}


void DynSoft::DSErrorType::SetDescription(const wxString &description) {
	this->description = description;
}

wxString DynSoft::DSErrorType::GetDescription() const {
	return description;
}


void DynSoft::DSErrorType::SetMessage(const wxString &message) {
	this->message = message;
}

wxString DynSoft::DSErrorType::GetMessage() const {
	return message;
}


void DynSoft::DSErrorType::SetDate(const DynSoft::DSDateTime &date) {
	this->date = date;
}

DynSoft::DSDateTime DynSoft::DSErrorType::GetDate() const {
	return date;
}

