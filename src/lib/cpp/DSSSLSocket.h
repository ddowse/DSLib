#ifndef DS_SSLSOCKET_H_
#define DS_SSLSOCKET_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define DS_SSLSOCKET_VERSION	_N("0.0.2")
#define DS_SSLSOCKET_NAME		_N("DSSSLSocket")
#define DS_SSLSOCKET_AUTHOR	    _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSSLSocket : public DSLib {

		public:
			DSSSLSocket(
				const bool sslInitialize          = true,
				const bool sslLoadErrorStrings    = true,
				const bool bioLoadErrorStrings    = true,
				const bool cryptoLoadErrorStrings = true,
				const bool addAllAlgorithms       = true
			);
			~DSSSLSocket();

			DSClassInfo GetClassInfo();

			void SslInitialize();
			bool SslInitialize() const;

			void SslLoadErrorStrings();
			bool SslLoadErrorStringsLoaded() const;

			void BioLoadErrorStrings();
			bool BioLoadErrorStringsLoaded() const;

			void CryptoLoadErrorStrings();
			bool CryptoLoadErrorStringsLoaded() const;

			void AddAllAlgorithms();
			bool AllAlgorithmsAdded() const;

			BIO *GetConnection() const;

			void SetAddress(const wxString &hostname, const unsigned int port);
			void GetAddress(wxString *hostname, unsigned int *port) const;

			wxString GetHostname() const;
			unsigned int GetPort() const;

			bool Connect();
			void Disconnect();
			bool VerifySsl();

			int Send(const char *message, unsigned int length);
			int Send(const wxString &message);

			int Receive(void *buffer, unsigned int length);
			int Receive(wxString *buffer);

			long SetCtxTimeout(const long seconds);
			void SetTimeout(long seconds, long microseconds = 0);
			bool GetTimeout(long *seconds, long *microseconds = NULL) const;
			bool TimedOut();

		protected:
			bool sslInitialized;
			bool sslLoadErrorStringsLoaded;
			bool bioLoadErrorStringsLoaded;
			bool cryptoLoadErrorStringsLoaded;
			bool allAlgorithmsAdded;

			BIO *connection;
			SSL_CTX *ctx;
			SSL *ssl;
			wxString hostname;
			unsigned int port;

			long seconds, microseconds;
			bool timeoutSetted;

			wxString CreateAddress() const;
	
	};

}

#endif /* DS_SSLSOCKET_H_ */
