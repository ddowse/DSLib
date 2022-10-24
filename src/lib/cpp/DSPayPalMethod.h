#ifndef DS_PAYPAL_METHOD_H_
#define DS_PAYPAL_METHOD_H_

#define DS_PAYPAL_METHOD_VERSION _N("0.0.1")
#define DS_PAYPAL_METHOD_NAME    _N("DSPayPalMethod")
#define DS_PAYPAL_METHOD_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"

namespace DynSoft {

	class DSPayPalMethod : public DSType {

		public:
			static const unsigned int INVALID                  = 0;
			static const unsigned int NONE                     = 1;
			static const unsigned int SETEXPRESSCHECKOUT       = 2;
			static const unsigned int DOEXPRESSCHECKOUTPAYMENT = 3;

			DSPayPalMethod(const unsigned int method = NONE);
			~DSPayPalMethod();

			DSClassInfo GetClassInfo();

			void SetMethod(const unsigned int method);
			unsigned int GetMethod() const;
			wxString GetMethodString() const;

			bool IsValid() const;
			bool IsOk() const;

			wxString ToUrlString() const;
			wxString ToString() const;

		protected:
			wxArrayString names;
			unsigned int method;

	};

}

#endif /* DS_PAYPAL_METHOD_H_ */
