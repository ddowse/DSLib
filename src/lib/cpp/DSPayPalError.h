#ifndef DS_PAYPAL_ERROR_H_
#define DS_PAYPAL_ERROR_H_

#define DS_PAYPAL_ERROR_VERSION _N("0.0.1")
#define DS_PAYPAL_ERROR_NAME    _N("DSPayPalError")
#define DS_PAYPAL_ERROR_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSTemplateContainer.h"
#include "DSPayPalCart.h"

namespace DynSoft {

	class DSPayPalError : public DSType {

		public:
			DSPayPalError();
			DSPayPalError(
				const int errorCode,
				const wxString &severityCode,
				const wxString &shortMessage,
				const wxString &longMessage
			);
			~DSPayPalError();

			DSClassInfo GetClassInfo();

			void SetErrorCode(const int errorCode);
			int GetErrorCode();

			void SetSeverityCode(const wxString &severityCode);
			wxString GetSeverityCode() const;

			void SetShortMessage(const wxString &shortMessage);
			wxString GetShortMessage() const;

			void SetLongMessage(const wxString &longMessage);
			wxString GetLongMessage() const;

			wxString ToString();

		protected:
			int errorCode;
			wxString severityCode;
			wxString shortMessage;
			wxString longMessage;
	
	};

}

#endif /* DS_PAYPAL_CART_H_ */
