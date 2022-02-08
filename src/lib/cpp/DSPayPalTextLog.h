#ifndef DS_PAYPAL_TEXT_LOG_H_
#define DS_PAYPAL_TEXT_LOG_H_

#define DS_PAYPAL_TEXT_LOG_VERSION _N("0.0.1")
#define DS_PAYPAL_TEXT_LOG_NAME    _N("DSPayPalTextLog")
#define DS_PAYPAL_TEXT_LOG_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSLib.h"
#include "DSPayPalLog.h"
#include "DSPayPalConnectionType.h"
#include "DSPayPalMethod.h"
#include "DSPayPalToken.h"
#include "DSPayPalCarts.h"
#include "DSPayPalResponse.h"

namespace DynSoft {

	class DSPayPalTextLog : public DSPayPalLog {

		public:
			DSPayPalTextLog(const wxString &filename);
			~DSPayPalTextLog();

			DSClassInfo GetClassInfo();

			virtual bool Write(
				DSPayPalConnectionType *payPalConnectionType,
				DSPayPalMethod *payPalMethod,
				DSPayPalToken *payPalToken,
				DSPayPalCarts *payPalCarts,
				DSPayPalResponse *payPalResponse
			);

			void SetFilename(const wxString &filename);
			wxString GetFilename() const;

		protected:
			wxString filename;

			wxString GetDateTimeAsString() const;

	};

}

#endif /* DS_PAYPAL_TEXT_LOG_H_ */
