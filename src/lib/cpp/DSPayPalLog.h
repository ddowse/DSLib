#ifndef DS_PAYPAL_LOG_H_
#define DS_PAYPAL_LOG_H_

#define DS_PAYPAL_LOG_VERSION _N("0.0.1")
#define DS_PAYPAL_LOG_NAME    _N("DSPayPalLog")
#define DS_PAYPAL_LOG_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSLib.h"
#include "DSPayPalConnectionType.h"
#include "DSPayPalMethod.h"
#include "DSPayPalToken.h"
#include "DSPayPalCarts.h"
#include "DSPayPalResponse.h"

namespace DynSoft {

	class DSPayPalLog : public DSLib {

		public:
			DSPayPalLog();
			~DSPayPalLog();

			DSClassInfo GetClassInfo();

			virtual bool Write(
				DSPayPalConnectionType *payPalConnectionType,
				DSPayPalMethod *payPalMethod,
				DSPayPalToken *payPalToken,
				DSPayPalCarts *payPalCarts,
				DSPayPalResponse *payPalResponse
			) = 0;

	};

}

#endif /* DS_PAYPAL_LOG_H_ */
