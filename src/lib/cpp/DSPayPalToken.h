#ifndef DS_PAYPAL_TOKEN_H_
#define DS_PAYPAL_TOKEN_H_

#define DS_PAYPAL_TOKEN_VERSION _N("0.0.1")
#define DS_PAYPAL_TOKEN_NAME    _N("DSPayPalToken")
#define DS_PAYPAL_TOKEN_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"

namespace DynSoft {

	class DSPayPalToken : public DSType {

		public:
			DSPayPalToken();
			DSPayPalToken(
				const wxString &token,
				const wxString &payerId = wxEmptyString
			);
			~DSPayPalToken();

			DSClassInfo GetClassInfo();

			void SetToken(const wxString &token);
			wxString GetToken() const;

			void SetPayerId(const wxString &payerId);
			wxString GetPayerId() const;

			void ParseTokenHashMap(DSStringHashMap &tokenHashMap);

			wxString ToUrlString() const;
			wxString ToString() const;

		protected:
			wxString token;
			wxString payerId;

	};

}

#endif /* DS_PAYPAL_TOKEN_H_ */
