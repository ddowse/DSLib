#ifndef DS_PAYPAL_PERSIST_H_
#define DS_PAYPAL_PERSIST_H_

#define DS_PAYPAL_PERSIST_VERSION _N("0.0.1")
#define DS_PAYPAL_PERSIST_NAME    _N("DSPayPalPersist")
#define DS_PAYPAL_PERSIST_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSLib.h"
#include "DSPayPalToken.h"
#include "DSPayPalCarts.h"

namespace DynSoft {

	class DSPayPalPersist : public DSLib {

		public:
			DSPayPalPersist();
			~DSPayPalPersist();

			DSClassInfo GetClassInfo();

			virtual bool Persist(DSPayPalToken &token, DSPayPalCarts &carts, const wxString &transactionId = wxEmptyString) = 0;
			virtual bool Restore(DSPayPalToken &token, DSPayPalCarts &carts, wxString *transactionId = NULL)                = 0;
			virtual bool Remove(DSPayPalToken &token)                                                                       = 0;

	};

}

#endif /* DS_PAYPAL_PERSIST_H_ */
