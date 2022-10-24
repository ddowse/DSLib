#ifndef DS_PAYPAL_CART_H_
#define DS_PAYPAL_CART_H_

#define DS_PAYPAL_CART_VERSION _N("0.0.1")
#define DS_PAYPAL_CART_NAME    _N("DSPayPalCart")
#define DS_PAYPAL_CART_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_PAYPAL_DEFAULT_CURRENCY_CODE _N("EUR")

#include "DSType.h"
#include "DSTemplateContainer.h"
#include "DSPayPalCartItem.h"

namespace DynSoft {

	class DSPayPalCart : public DSType {

		public:
			DSPayPalCart(
				const DSCurrency shippingPrice,
				const wxString &currencyCode = DS_PAYPAL_DEFAULT_CURRENCY_CODE,
				const wxString &sellerPayPalAccountId = wxEmptyString,
				const wxString &paymentRequestId = wxEmptyString
			);
			~DSPayPalCart();

			static DSPayPalCart *New(
				const DSCurrency shippingPrice,
				const wxString &currencyCode = DS_PAYPAL_DEFAULT_CURRENCY_CODE
			);

			DSClassInfo GetClassInfo();

			DSPayPalCartItem *AddCartItem(DSPayPalCartItem *item);
			DSPayPalCartItem *AddCartItem(
				const wxString &name,
				const wxString &description,
				const DSCurrency price
			);
			unsigned int GetCartItemCount() const;
			DSPayPalCartItem *GetCartItem(const unsigned int number);

			void SetShippingPrice(const DSCurrency shippingPrice);
			DSCurrency GetShippingPrice() const;

			DSCurrency GetCartPrice();
			DSCurrency GetPrice();

			void SetCurrencyCode(const wxString &currencyCode);
			wxString GetCurrencyCode() const;

			void SetSellerPayPalAccountId(const wxString &sellerPayPalAccountId);
			wxString GetSellerPayPalAccountId() const;

			void SetPaymentRequestId(const wxString &paymentRequestId);
			wxString GetPaymentRequestId() const;

			wxString ToSetExpressCheckout(const unsigned int paymentNumber);
			wxString ToDoExpressCheckoutPayment(const unsigned int paymentNumber);

			wxString ToString();

		protected:
			DSTemplateContainer<DSPayPalCartItem *> items;
			DSCurrency shippingPrice;
			wxString currencyCode;
			wxString sellerPayPalAccountId;
			wxString paymentRequestId;
	
	};

}

#endif /* DS_PAYPAL_CART_H_ */
