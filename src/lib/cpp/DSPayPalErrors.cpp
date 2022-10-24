#include "DSPayPalErrors.h"
#include "DSCasts.h"

DynSoft::DSPayPalErrors::DSPayPalErrors() : DSType(
) {
}

DynSoft::DSPayPalErrors::~DSPayPalErrors() {
	CleanErrors();
}

DynSoft::DSClassInfo DynSoft::DSPayPalErrors::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_ERRORS_NAME,
        DS_PAYPAL_ERRORS_VERSION,
        DS_PAYPAL_ERRORS_AUTHOR
    );
}

DynSoft::DSPayPalError *DynSoft::DSPayPalErrors::AddError(
	const int errorCode,
	const wxString &severityCode,
	const wxString &shortMessage,
	const wxString &longMessage
) {
	DSPayPalError *payPalError = new DSPayPalError(errorCode, severityCode, shortMessage, longMessage);
	errors.Add(payPalError);
	return payPalError;
}

void DynSoft::DSPayPalErrors::AddError(DynSoft::DSPayPalError *payPalError) {
	errors.Add(payPalError);
}

unsigned int DynSoft::DSPayPalErrors::GetErrorCount() const {
	return errors.GetCount();
}

DynSoft::DSPayPalError *DynSoft::DSPayPalErrors::GetError(const unsigned int number) {
	return errors.Get(number);
}

unsigned int DynSoft::DSPayPalErrors::ParseErrorHashMap(DSStringHashMap &errorHashMap) {
	unsigned int result = 0;
	wxString number;

	for(bool found = true; found; result++) {
		number = DynSoft::DSCasts::ToString(result);
		if(!errorHashMap[_N("L_ERRORCODE") + number].IsEmpty()) {
			AddError(
				DynSoft::DSCasts::ToUnsignedInt(errorHashMap[_N("L_ERRORCODE") + number]),
				errorHashMap[_N("L_SEVERITYCODE") + number],
				errorHashMap[_N("L_SHORTMESSAGE") + number],
				errorHashMap[_N("L_LONGMESSAGE") + number]
			);
		} else {
			found = false;
		}
	}

	return result;
}

bool DynSoft::DSPayPalErrors::HasErrors() const {
	return GetErrorCount() > 0;
}

void DynSoft::DSPayPalErrors::CleanErrors() {
	errors.Clear(true);
}

wxString DynSoft::DSPayPalErrors::ToString() {
	wxString result;

	const unsigned int count = GetErrorCount();
	for(unsigned int i = 0; i < count; i++) {
		result += GetError(i)->ToString();
		if(i + 1 < count)
			result += _N("\n");
	}

	return result;
}
