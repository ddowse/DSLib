#include "DSPayPalError.h"
#include "DSCasts.h"

DynSoft::DSPayPalError::DSPayPalError() : DSType(
) {
	SetErrorCode(0);
}

DynSoft::DSPayPalError::DSPayPalError(
	const int errorCode,
	const wxString &severityCode,
	const wxString &shortMessage,
	const wxString &longMessage
) {
	SetErrorCode(errorCode);
	SetSeverityCode(severityCode);
	SetShortMessage(shortMessage);
	SetLongMessage(longMessage);
}

DynSoft::DSPayPalError::~DSPayPalError() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalError::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_ERROR_NAME,
        DS_PAYPAL_ERROR_VERSION,
        DS_PAYPAL_ERROR_AUTHOR
    );
}

void DynSoft::DSPayPalError::SetErrorCode(const int errorCode) {
	this->errorCode = errorCode;
}

int DynSoft::DSPayPalError::GetErrorCode() {
	return errorCode;
}

void DynSoft::DSPayPalError::SetSeverityCode(const wxString &severityCode) {
	this->severityCode = severityCode;
}

wxString DynSoft::DSPayPalError::GetSeverityCode() const {
	return severityCode;
}

void DynSoft::DSPayPalError::SetShortMessage(const wxString &shortMessage) {
	this->shortMessage = shortMessage;
}

wxString DynSoft::DSPayPalError::GetShortMessage() const {
	return shortMessage;
}

void DynSoft::DSPayPalError::SetLongMessage(const wxString &longMessage) {
	this->longMessage = longMessage;
}

wxString DynSoft::DSPayPalError::GetLongMessage() const {
	return longMessage;
}

wxString DynSoft::DSPayPalError::ToString() {
	wxString result;

	result += _N("                     Error code: ") + DynSoft::DSCasts::ToString(GetErrorCode()) + _N("\n");
	result += _N("                  Severity code: ") + GetSeverityCode() + _N("\n");
	result += _N("                  Short message: ") + GetShortMessage() + _N("\n");
	result += _N("                   Long message: ") + GetLongMessage();

	return result;
}
