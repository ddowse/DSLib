#ifndef DS_PAYPAL_CONNECTION_TYPE_H_
#define DS_PAYPAL_CONNECTION_TYPE_H_

#define DS_PAYPAL_CONNECTION_TYPE_VERSION _N("0.0.1")
#define DS_PAYPAL_CONNECTION_TYPE_NAME    _N("DSPayPalConnectionType")
#define DS_PAYPAL_CONNECTION_TYPE_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_PAYPAL_CONNECTION_TYPE_DEFAULT_VERSION          _N("109")
#define DS_PAYPAL_CONNECTION_TYPE_DEFAULT_LOCALE_CODE      _N("de_DE")
#define DS_PAYPAL_CONNECTION_TYPE_DEFAULT_CALLABLE_FILE    _N("/nvp")
#define DS_PAYPAL_CONNECTION_TYPE_DEFAULT_CALL_URL         _N("https://www.paypal.com")

#include "DSType.h"
#include "DSPayPalToken.h"

namespace DynSoft {

	class DSPayPalConnectionType : public DSType {

		public:
			DSPayPalConnectionType();
			DSPayPalConnectionType(
				const wxString &hostname,
				const unsigned int port,
				const unsigned int timeout,
				const wxString &username,
				const wxString &password,
				const wxString &signature,
				const wxString &returnURL,
				const wxString &cancelURL,
				const wxString &callURL        = DS_PAYPAL_CONNECTION_TYPE_DEFAULT_CALL_URL,
				const wxString &localeCode     = DS_PAYPAL_CONNECTION_TYPE_DEFAULT_LOCALE_CODE,
				const wxString &callableFile   = DS_PAYPAL_CONNECTION_TYPE_DEFAULT_CALLABLE_FILE
			);
			~DSPayPalConnectionType();

			DSClassInfo GetClassInfo();

			void SetHostname(const wxString &hostname);
			wxString GetHostname() const;

			void SetPort(const unsigned int port);
			unsigned int GetPort() const;

			void SetUsername(const wxString &username);
			wxString GetUsername() const;
			
			void SetPassword(const wxString &password);
			wxString GetPassword() const;
			
			void SetSignature(const wxString &signature);
			wxString GetSignature() const;
			
			void SetReturnURL(const wxString &returnURL);
			wxString GetReturnURL() const;
			
			void SetCancelURL(const wxString &cancelURL);
			wxString GetCancelURL() const;

			void SetCallURL(const wxString &callURL);
			wxString GetCallURL() const;

			wxString GetFullCallURL(
				DynSoft::DSPayPalToken &token
			) const;
			
			void SetLocaleCode(const wxString &localeCode);
			wxString GetLocaleCode() const;

			void SetCallableFile(const wxString &callableFile);
			wxString GetCallableFile() const;

			void SetTimeout(const unsigned int timeout);
			unsigned int GetTimeout() const;

			wxString GetVersion() const;

			wxString ToUrlString();
			wxString ToCallableString();
			wxString ToString();

		protected:
			wxString hostname;
			unsigned int port;
			wxString username;
			wxString password;
			wxString signature;
			wxString returnURL;
			wxString cancelURL;
			wxString callURL;
			wxString localeCode;
			wxString version;
			unsigned int timeout;
			wxString callableFile;

			void SetVersion(const wxString &version);
	
	};

}

#endif /* DS_PAYPAL_CONNECTION_TYPE_H_ */
