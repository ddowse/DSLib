#include "DSPayPalToken.h"

DynSoft::DSPayPalToken::DSPayPalToken() : DSType(
) {
}

DynSoft::DSPayPalToken::DSPayPalToken(
	const wxString &token,
	const wxString &payerId
) {
	SetToken(token);
	SetPayerId(payerId);
}

DynSoft::DSPayPalToken::~DSPayPalToken() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalToken::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_TOKEN_NAME,
        DS_PAYPAL_TOKEN_VERSION,
        DS_PAYPAL_TOKEN_AUTHOR
    );
}

void DynSoft::DSPayPalToken::SetToken(const wxString &token) {
	this->token = token;
}

wxString DynSoft::DSPayPalToken::GetToken() const {
	return token;
}

void DynSoft::DSPayPalToken::SetPayerId(const wxString &payerId) {
	this->payerId = payerId;
}

wxString DynSoft::DSPayPalToken::GetPayerId() const {
	return payerId;
}

void DynSoft::DSPayPalToken::ParseTokenHashMap(DSStringHashMap &tokenHashMap) {
	SetToken(tokenHashMap[_N("TOKEN")]);
	SetPayerId(tokenHashMap[_N("PAYERID")]);
}

wxString DynSoft::DSPayPalToken::ToUrlString() const {
	wxString url;

	if(!GetToken().IsEmpty())
		url += _N("TOKEN=") + GetToken();
	if(!GetPayerId().IsEmpty()) {
		if(!url.IsEmpty())
			url += _N("&");
		url += _N("PAYERID=") + GetPayerId();
	}

	return url;
}

wxString DynSoft::DSPayPalToken::ToString() const {
	wxString result;

	result += _N("                          Token: ") + GetToken() + _N("\n");
	result += _N("                       Payer id: ") + GetPayerId();

	return result;
}
