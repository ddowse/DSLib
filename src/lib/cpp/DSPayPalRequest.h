#ifndef DS_PAYPAL_REQUEST_H_
#define DS_PAYPAL_REQUEST_H_

#define DS_PAYPAL_REQUEST_VERSION _N("0.0.1")
#define DS_PAYPAL_REQUEST_NAME    _N("DSPayPalRequest")
#define DS_PAYPAL_REQUEST_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSLib.h"
#include "DSStringHashMap.h"
#include "DSPayPalConnectionType.h"
#include "DSPayPalCarts.h"
#include "DSPayPalResponse.h"
#include "DSPayPalMethod.h"
#include "DSPayPalToken.h"

// FIXME
const unsigned int BUFFER_SIZE = 64;

namespace DynSoft {

	class DSPayPalRequest : public DSLib {

		public:
			DSPayPalRequest();
			~DSPayPalRequest();

			DSClassInfo GetClassInfo();

			DSPayPalResponse *Request(
				DSPayPalConnectionType &connection,
				DSPayPalMethod &method,
				DSPayPalToken &token,
				DSPayPalCarts &carts
			);

		protected:
			DSStringHashMap Request(
				DSPayPalConnectionType &connection,
				const wxString &request
			);
	
	};

}

#endif /* DS_PAYPAL_REQUEST_H_ */
