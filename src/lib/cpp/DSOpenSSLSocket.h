#ifndef DS_OPENSSLSOCKET_H_
#define DS_OPENSSLSOCKET_H_

#include "DSLib.h"
#include <openssl/ssl.h>

#ifdef __WINDOWS__
	#include <winsock.h>
	#define socklen_t int
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
#endif

#define DS_OPENSSLSOCKET_VERSION	_N("0.0.3")
#define DS_OPENSSLSOCKET_NAME		_N("DSOpenSSLSocket")
#define DS_OPENSSLSOCKET_AUTHOR		_N("Thorsten Geppert (thorsten@gug-it.de)")

namespace DynSoft {

	class DSOpenSSLSocket : public DSLib {
	
		public:
			typedef enum {
				UNKNOWN = 0,
				AUTO,
				AUTO_SERVER,
				AUTO_CLIENT,
				TLSv12,
				TLSv12_SERVER,
				TLSv12_CLIENT
			} DSOpenSSLSocketMethodType;

			typedef enum { BOTH = 0, SERVER, CLIENT } DSOpenSSLSocketKindType;

			typedef enum {
				NONE = 0,
				ALREADY_INITIALIZED,
				NOT_INITIALIZED_SSL_VERSION,
				NOT_INITIALIZED_CERTIFICATION_FILENAME,
				NOT_INITIALIZED_KEY_FILENAME,
				NOT_INITIALIZED_MODE,
				NOT_INITIALIZED_VERIFY,
				NOT_INITIALIZED_VERIFY_DEPTH,
				NOT_INITIALIZED_ADDRESS,
				UNKNOWN_SSL_METHOD,
				ERROR_CTX,
				ERROR_LOAD_VERIFY,
				ERROR_USE_CERTIFICATE_FILE,
				ERROR_USE_KEY_FILE,
				ERROR_CHECK_KEY

			} DSOpenSSLSocketErrorType;

			typedef enum {
				CONNECTED = 0,
				ERROR_BIO_NEW_SOCKET,
				ERROR_SSL_NEW,
				ERROR_SSL_ACCEPT,
				ERROR_CONNECTION,
				ERROR_CONNECT,
				ERROR_SSL_CONNECT,
				ERROR_SSL_VERIFY
			} DSOpenSSLSocketConnectionErrorType;

			DSOpenSSLSocket(const bool autoInit = true, short family = AF_INET);
			~DSOpenSSLSocket();

			DSClassInfo GetClassInfo();

			void SetSSLVersion(const DSOpenSSLSocketMethodType sslVersion);
			DSOpenSSLSocketMethodType GetSSLMethod() const;

			void SetCaFilename(const wxString &caFilename);
			wxString GetCaFilename() const;

			void SetCertificateFilename(const wxString &certificateFilename);
			wxString GetCertificateFilename() const;

			void SetKeyFilename(const wxString &keyFilename);
			wxString GetKeyFilename() const;

			void SetMode(const long mode);
			long GetMode() const;

			void SetVerify(const int verify);
			int GetVerify() const;

			void SetVerifyDepth(const int verifyDepth);
			int GetVerifyDepth() const;

			DSOpenSSLSocketErrorType Initialize();

			bool SetAddress(
				const wxString &host,
				unsigned int port,
				int type     = SOCK_STREAM,
				int protocol = 0
			);

			void GetAddress(
				wxString *ip,
				unsigned int *port
			);

			wxString GetIp() const;
			void SetFamily(short family = AF_INET);
			short GetFamily() const;
			void SetProtocol(const int protocol = 0);
			int GetProtocol() const;
			void SetType(const int type = SOCK_STREAM);
			int GetType() const;
			bool SetOptions(int level = SOL_SOCKET, int name = SO_REUSEADDR, void *value = NULL, int length = 1);

			DSOpenSSLSocketConnectionErrorType SetConnection(const int connection, SSL_CTX *ctx);
			int GetConnection() const;

			void SetTimeout(long seconds, long microseconds = 0);
			bool GetTimeout(long *seconds, long *microseconds = NULL) const;
			bool TimedOut();
			void SetAutoTimeout(long seconds, long microseconds = 0);
			bool GetAutoTimeout(long *seconds, long *microseconds = NULL) const;

			bool Bind();
			bool Listen(int tries = 5);
			DSOpenSSLSocket *Accept(DSOpenSSLSocketConnectionErrorType *error = NULL);
			bool Disconnect();

			int Receive(void *buffer, int length);
			int Send(void *buffer, int length);

			DSOpenSSLSocketConnectionErrorType Connect();

			bool IsConnected() const;

		protected:
			DSOpenSSLSocketMethodType sslVersion;
			wxString caFilename;
			wxString certificateFilename;
			wxString keyFilename;
			long mode;
			int verify;
			int verifyDepth;

			bool initialized;
			bool initializedSSLVersion;
			bool initializedCertificationFilename;
			bool initializedKeyFilename;
			bool initializedMode;
			bool initializedVerify;
			bool initializedVerifyDepth;
			bool initializedAddress;

			SSL_CTX *ctx;
			int connection;
			short family;
			int protocol;
			int type;
			struct sockaddr_in address;

			struct sockaddr *GetAddressStruct();

			long seconds, microseconds;
			bool timeoutSetted;
			long autoSeconds, autoMicroseconds;
			bool autoTimeoutSetted;

			BIO *bio;
			SSL *ssl;
			
			bool context;

	};

}

#endif /* DS_OPENSSLSOCKET_H_ */
