#include "DSPayPalMethod.h"
#include "DSCasts.h"

DynSoft::DSPayPalMethod::DSPayPalMethod(const unsigned int method) : DSType(
) {
	names.Add(_N("Invalid"));
	names.Add(_N("None"));
	names.Add(_N("SetExpressCheckout"));
	names.Add(_N("DoExpressCheckoutPayment"));

	SetMethod(method);
}

DynSoft::DSPayPalMethod::~DSPayPalMethod() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalMethod::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_METHOD_NAME,
        DS_PAYPAL_METHOD_VERSION,
        DS_PAYPAL_METHOD_AUTHOR
    );
}

void DynSoft::DSPayPalMethod::SetMethod(const unsigned int method) {
	if(method > 3)
		this->method = INVALID;
	else
		this->method = method;
}

unsigned int DynSoft::DSPayPalMethod::GetMethod() const {
	return method;
}

wxString DynSoft::DSPayPalMethod::GetMethodString() const {
	return names[GetMethod()];
}

bool DynSoft::DSPayPalMethod::IsValid() const {
	return GetMethod() != INVALID;
}

bool DynSoft::DSPayPalMethod::IsOk() const {
	return GetMethod() > 1;
}

wxString DynSoft::DSPayPalMethod::ToUrlString() const {
	return _N("METHOD=") + GetMethodString();
}

wxString DynSoft::DSPayPalMethod::ToString() const {
	wxString result;

	result += _N("             Internal method id: ") + DynSoft::DSCasts::ToString(GetMethod()) + _N("\n");
	result += _N("                         Method: ") + GetMethodString();

	return result;
}
