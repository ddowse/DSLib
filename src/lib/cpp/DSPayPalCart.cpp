#include "DSPayPalCart.h"
#include "DSCasts.h"
#include "DSCgi.h"

DynSoft::DSPayPalCart::DSPayPalCart(
	const DSCurrency shippingPrice,
	const wxString &currencyCode,
	const wxString &sellerPayPalAccountId,
	const wxString &paymentNumber
) : DSType(
) {
	SetShippingPrice(shippingPrice);
	SetCurrencyCode(currencyCode);
	SetSellerPayPalAccountId(sellerPayPalAccountId);
	SetPaymentRequestId(paymentNumber);
}

DynSoft::DSPayPalCart::~DSPayPalCart() {
	items.Clear(true);
}

DynSoft::DSPayPalCart *DynSoft::DSPayPalCart::New(
	const DSCurrency shippingPrice,
	const wxString &currencyCode
) {
	return new DSPayPalCart(shippingPrice, currencyCode);
}

DynSoft::DSClassInfo DynSoft::DSPayPalCart::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_CART_NAME,
        DS_PAYPAL_CART_VERSION,
        DS_PAYPAL_CART_AUTHOR
    );
}

DynSoft::DSPayPalCartItem *DynSoft::DSPayPalCart::AddCartItem(DSPayPalCartItem *item) {
	items.Add(item);
	return item;
}

DynSoft::DSPayPalCartItem *DynSoft::DSPayPalCart::AddCartItem(
	const wxString &name,
	const wxString &description,
	const DSCurrency price
) {
	DynSoft::DSPayPalCartItem *item = new DSPayPalCartItem(
		name,
		description,
		price
	);
	items.Add(item);
	return item;
}

void DynSoft::DSPayPalCart::SetShippingPrice(const DSCurrency shippingPrice) {
	this->shippingPrice = shippingPrice;
}

DynSoft::DSCurrency DynSoft::DSPayPalCart::GetShippingPrice() const {
	return shippingPrice;
}

unsigned int DynSoft::DSPayPalCart::GetCartItemCount() const {
	return items.GetCount();
}

DynSoft::DSPayPalCartItem *DynSoft::DSPayPalCart::GetCartItem(const unsigned int number) {
	return items.Get(number);
}

DynSoft::DSCurrency DynSoft::DSPayPalCart::GetCartPrice() {
	DSCurrency price;	
	DSPayPalCartItem *cartItem = NULL;
	
	const unsigned int count = GetCartItemCount();
	for(unsigned int i = 0; i < count; i++) {
		cartItem = GetCartItem(i);
		if(cartItem)
			price += cartItem->GetPrice();
	}

	return price;
}

DynSoft::DSCurrency DynSoft::DSPayPalCart::GetPrice() {
	return GetCartPrice() + GetShippingPrice();
}

void DynSoft::DSPayPalCart::SetCurrencyCode(const wxString &currencyCode) {
	this->currencyCode = currencyCode;
}

wxString DynSoft::DSPayPalCart::GetCurrencyCode() const {
	return currencyCode;
}

void DynSoft::DSPayPalCart::SetSellerPayPalAccountId(const wxString &sellerPayPalAccountId) {
	this->sellerPayPalAccountId = sellerPayPalAccountId;
}

wxString DynSoft::DSPayPalCart::GetSellerPayPalAccountId() const {
	return sellerPayPalAccountId;
}

void DynSoft::DSPayPalCart::SetPaymentRequestId(const wxString &paymentRequestId) {
	this->paymentRequestId = paymentRequestId;
}

wxString DynSoft::DSPayPalCart::GetPaymentRequestId() const {
	return paymentRequestId;
}

wxString DynSoft::DSPayPalCart::ToSetExpressCheckout(const unsigned int paymentNumber) {
	const wxString tmpPaymentNumber(DSCasts::ToString(paymentNumber));

	wxString url;

	url  = _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_AMT=") + GetPrice().ToAmericanString() + _N("&");
	url += _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_CURRENCYCODE=") + DSCgi::UrlEncode(GetCurrencyCode()) + _N("&");
	url += _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_ITEMAMT=") + GetCartPrice().ToAmericanString() + _N("&");
	url += _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_SHIPPINGAMT=") + GetShippingPrice().ToAmericanString();

	if(!GetSellerPayPalAccountId().IsEmpty())
		url += _N("&PAYMENTREQUEST_") + tmpPaymentNumber + _N("_SELLERPAYPALACCOUNTID=") + GetSellerPayPalAccountId();
	if(!GetPaymentRequestId().IsEmpty())
		url += _N("&PAYMENTREQUEST_") + tmpPaymentNumber + _N("_PAYMENTREQUESTID=") + GetPaymentRequestId();

	DSPayPalCartItem *item = NULL;
	const unsigned int count = GetCartItemCount();
	for(unsigned int i = 0; i < count; i++) {
		item = GetCartItem(i);
		if(item)
			url += _N("&") + item->ToSetExpressCheckout(paymentNumber, i);
	}

	return url;
}

wxString DynSoft::DSPayPalCart::ToDoExpressCheckoutPayment(const unsigned int paymentNumber) {
	const wxString tmpPaymentNumber(DSCasts::ToString(paymentNumber));

	wxString url;

	url  = _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_AMT=") + GetPrice().ToAmericanString() + _N("&");
	url += _N("PAYMENTREQUEST_") + tmpPaymentNumber + _N("_CURRENCYCODE=") + DSCgi::UrlEncode(GetCurrencyCode());

	return url;
}

wxString DynSoft::DSPayPalCart::ToString() {
	const unsigned int count = GetCartItemCount();

	wxString result;

	result += _N("                 Shipping price: ") + GetShippingPrice().ToString() + _N("\n");
	result += _N("                     Cart price: ") + GetCartPrice().ToString() + _N("\n");
	result += _N("                          Price: ") + GetPrice().ToString() + _N("\n");
	result += _N("                  Currency code: ") + GetCurrencyCode() + _N("\n");
	result += _N("       Seller PayPal account id: ") + GetSellerPayPalAccountId() + _N("\n");
	result += _N("             Payment request id: ") + GetPaymentRequestId() + _N("\n");
	result += _N("                Cart item count: ") + DynSoft::DSCasts::ToString(count);

	DSPayPalCartItem *item = NULL;
	for(unsigned int i = 0; i < count; i++) {
		item = GetCartItem(i);
		if(item) {
			result += _N("\n................................................................................\n");
			result += item->ToString();
		}
	}

	return result;
}
