#include "DSPayPalCarts.h"
#include "DSCasts.h"

DynSoft::DSPayPalCarts::DSPayPalCarts() : DSType(
) {
}

DynSoft::DSPayPalCarts::~DSPayPalCarts() {
	carts.Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSPayPalCarts::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_CARTS_NAME,
        DS_PAYPAL_CARTS_VERSION,
        DS_PAYPAL_CARTS_AUTHOR
    );
}

DynSoft::DSPayPalCart *DynSoft::DSPayPalCarts::AddCart(const DSCurrency shippingPrice) {
	DynSoft::DSPayPalCart *cart = new DynSoft::DSPayPalCart(shippingPrice);
	carts.Add(cart);
	return cart;
}

void DynSoft::DSPayPalCarts::AddCart(DSPayPalCart *cart) {
	carts.Add(cart);
}

unsigned int DynSoft::DSPayPalCarts::GetCartCount() const {
	return carts.GetCount();
}

DynSoft::DSPayPalCart *DynSoft::DSPayPalCarts::GetCart(const unsigned int number) {
	return carts.Get(number);
}

wxString DynSoft::DSPayPalCarts::ToSetExpressCheckout() {
	wxString url;
	
	DSPayPalCart *cart = NULL;
	const unsigned int count = GetCartCount();
	for(unsigned int i = 0; i < count; i++) {
		cart = carts.Get(i);
		if(cart) {
			url += cart->ToSetExpressCheckout(i);
			if(i + 1 < count)
				url += _N("&");
		}
	}

	return url;
}

wxString DynSoft::DSPayPalCarts::ToDoExpressCheckoutPayment() {
	wxString url;
	
	DSPayPalCart *cart = NULL;
	const unsigned int count = GetCartCount();
	for(unsigned int i = 0; i < count; i++) {
		cart = carts.Get(i);
		if(cart) {
			url += cart->ToDoExpressCheckoutPayment(i);
			if(i + 1 < count)
				url += _N("&");
		}
	}

	return url;
}

wxString DynSoft::DSPayPalCarts::ToString() {
	wxString result;
	
	const unsigned int count = GetCartCount();

	result += _N("                     Cart count: ") + DynSoft::DSCasts::ToString(count);

	DSPayPalCart *cart = NULL;
	for(unsigned int i = 0; i < count; i++) {
		cart = carts.Get(i);
		if(cart) {
			result += _N("\n--------------------------------------------------------------------------------\n");
			result += cart->ToString();
		}
	}

	return result;
}
