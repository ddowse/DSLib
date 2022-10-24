#include "DSPayPalCartItem.h"
#include "DSCasts.h"
#include "DSCgi.h"

DynSoft::DSPayPalCartItem::DSPayPalCartItem() : DSType(
) {
}

DynSoft::DSPayPalCartItem::DSPayPalCartItem(
	const wxString &name,
	const wxString &description,
	const DSCurrency price
) {
	SetName(name);
	SetDescription(description);
	SetPrice(price);
}

DynSoft::DSPayPalCartItem::~DSPayPalCartItem() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalCartItem::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_CART_ITEM_NAME,
        DS_PAYPAL_CART_ITEM_VERSION,
        DS_PAYPAL_CART_ITEM_AUTHOR
    );
}

void DynSoft::DSPayPalCartItem::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSPayPalCartItem::GetName() const {
	return name;
}

void DynSoft::DSPayPalCartItem::SetDescription(const wxString &description) {
	this->description = description;
}

wxString DynSoft::DSPayPalCartItem::GetDescription() const {
	return description;
}

void DynSoft::DSPayPalCartItem::SetPrice(const DSCurrency price) {
	this->price = price;
}

DynSoft::DSCurrency DynSoft::DSPayPalCartItem::GetPrice() const {
	return price;
}

wxString DynSoft::DSPayPalCartItem::ToSetExpressCheckout(
	const unsigned int paymentNumber,
	const unsigned int itemNumber
) {
	const wxString tmpPaymentNumber(DSCasts::ToString(paymentNumber));
	const wxString tmpItemNumber(DSCasts::ToString(itemNumber));

	wxString url;

	url  = _N("L_PAYMENTREQUEST_") + tmpPaymentNumber + _N("_NAME") + tmpItemNumber + _N("=") + DSCgi::Escape(GetName()) + _N("&");
	url += _N("L_PAYMENTREQUEST_") + tmpPaymentNumber + _N("_DESC") + tmpItemNumber + _N("=") + DSCgi::UrlEncode(GetDescription()) + _N("&");
	url += _N("L_PAYMENTREQUEST_") + tmpPaymentNumber + _N("_AMT")  + tmpItemNumber + _N("=") + GetPrice().ToAmericanString();

	return url;
}

wxString DynSoft::DSPayPalCartItem::ToString() {
	wxString result;

	result += _N("                           Name: ") + GetName() + _N("\n");
	result += _N("                    Description: ") + GetDescription() + _N("\n");
	result += _N("                          Price: ") + GetPrice().ToString();

	return result;
}
