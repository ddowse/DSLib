#ifndef DS_PAYPAL_CARTS_H_
#define DS_PAYPAL_CARTS_H_

#define DS_PAYPAL_CARTS_VERSION _N("0.0.1")
#define DS_PAYPAL_CARTS_NAME    _N("DSPayPalCarts")
#define DS_PAYPAL_CARTS_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSTemplateContainer.h"
#include "DSPayPalCart.h"

namespace DynSoft {

	class DSPayPalCarts : public DSType {

		public:
			DSPayPalCarts();
			~DSPayPalCarts();

			DSClassInfo GetClassInfo();

			DSPayPalCart *AddCart(const DSCurrency shippingPrice);
			void AddCart(DSPayPalCart *cart);
			unsigned int GetCartCount() const;
			DSPayPalCart *GetCart(const unsigned int number);

			wxString ToSetExpressCheckout();
			wxString ToDoExpressCheckoutPayment();
			wxString ToString();

		protected:
			DSTemplateContainer<DSPayPalCart *> carts;

	};

}

#endif /* DS_PAYPAL_CART_H_ */
