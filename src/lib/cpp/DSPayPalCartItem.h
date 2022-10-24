#ifndef DS_PAYPAL_CART_ITEM_H_
#define DS_PAYPAL_CART_ITEM_H_

#define DS_PAYPAL_CART_ITEM_VERSION _N("0.0.1")
#define DS_PAYPAL_CART_ITEM_NAME    _N("DSPayPalCartItem")
#define DS_PAYPAL_CART_ITEM_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSCurrency.h"

namespace DynSoft {

	class DSPayPalCartItem : public DSType {

		public:
			DSPayPalCartItem();
			DSPayPalCartItem(
				const wxString &name,
				const wxString &description,
				const DSCurrency price
			);
			~DSPayPalCartItem();

			DSClassInfo GetClassInfo();

			void SetName(const wxString &name);
			wxString GetName() const;

			void SetDescription(const wxString &description);
			wxString GetDescription() const;

			void SetPrice(const DSCurrency price);
			DSCurrency GetPrice() const;

			wxString ToSetExpressCheckout(
				const unsigned int paymentNumber,
				const unsigned int itemNumber
			);

			wxString ToString();

		protected:
			wxString name;
			wxString description;
			DSCurrency price;

	};

}

#endif /* DS_PAYPAL_CART_ITEM_H_ */
