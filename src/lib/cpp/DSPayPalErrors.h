#ifndef DS_PAYPAL_ERRORS_H_
#define DS_PAYPAL_ERRORS_H_

#define DS_PAYPAL_ERRORS_VERSION _N("0.0.1")
#define DS_PAYPAL_ERRORS_NAME    _N("DSPayPalErrors")
#define DS_PAYPAL_ERRORS_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSTemplateContainer.h"
#include "DSStringHashMap.h"
#include "DSPayPalError.h"

namespace DynSoft {

	class DSPayPalErrors : public DSType {

		public:
			DSPayPalErrors();
			~DSPayPalErrors();

			DSClassInfo GetClassInfo();

			DSPayPalError *AddError(
				const int errorCode,
				const wxString &severityCode,
				const wxString &shortMessage,
				const wxString &longMessage
			);
			void AddError(DSPayPalError *error);
			unsigned int GetErrorCount() const;
			DSPayPalError *GetError(const unsigned int number);
			bool HasErrors() const;
			void CleanErrors();

			unsigned int ParseErrorHashMap(DSStringHashMap &errorHashMap);

			wxString ToString();
			
		protected:
			DSTemplateContainer<DSPayPalError *> errors;
	
	};

}

#endif /* DS_PAYPAL_CART_H_ */
