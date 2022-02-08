#include "DSOpenSSLSocket.h"
#include "DSCasts.h"

DynSoft::DSOpenSSLSocket::DSOpenSSLSocket(
	const bool autoInit,
	short family
) : DSLib(
) {
	SetFamily(family);

	bio = NULL;
	ssl = NULL;

	context                          = false;
	connection                       = 0;
	seconds                          = 0;
	microseconds                     = 0;
	timeoutSetted                    = false;

	initialized                      = false;
	initializedSSLVersion            = false;
	initializedCertificationFilename = false;
	initializedKeyFilename           = false;
	initializedMode                  = false;
	initializedVerify                = false;
	initializedVerifyDepth           = false;
	initializedAddress               = false;

	ctx                              = NULL;

	if(autoInit) {
		SetSSLVersion(AUTO);
		SetMode(SSL_MODE_AUTO_RETRY);
		SetVerify(SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
		SetVerifyDepth(1);
	}
}

DynSoft::DSOpenSSLSocket::~DSOpenSSLSocket() {
	if(!context && ctx)
		SSL_CTX_free(ctx);
}

DynSoft::DSClassInfo DynSoft::DSOpenSSLSocket::GetClassInfo() {
	return DSClassInfo(
		DS_OPENSSLSOCKET_VERSION,
		DS_OPENSSLSOCKET_NAME,
		DS_OPENSSLSOCKET_AUTHOR
	);
}

void DynSoft::DSOpenSSLSocket::SetSSLVersion(const DynSoft::DSOpenSSLSocket::DSOpenSSLSocketMethodType sslVersion) {
	this->sslVersion      = sslVersion;
	initializedSSLVersion = true;
}

DynSoft::DSOpenSSLSocket::DSOpenSSLSocketMethodType DynSoft::DSOpenSSLSocket::GetSSLMethod() const {
	return sslVersion;
}

void DynSoft::DSOpenSSLSocket::SetCaFilename(const wxString &caFilename) {
	this->caFilename      = caFilename;
}

wxString DynSoft::DSOpenSSLSocket::GetCaFilename() const {
	return caFilename;
}

void DynSoft::DSOpenSSLSocket::SetCertificateFilename(const wxString &certificateFilename) {
	this->certificateFilename        = certificateFilename;
	initializedCertificationFilename = true;
}

wxString DynSoft::DSOpenSSLSocket::GetCertificateFilename() const {
	return certificateFilename;
}

void DynSoft::DSOpenSSLSocket::SetKeyFilename(const wxString &keyFilename) {
	this->keyFilename      = keyFilename;
	initializedKeyFilename = true;
}

wxString DynSoft::DSOpenSSLSocket::GetKeyFilename() const {
	return keyFilename;
}

void DynSoft::DSOpenSSLSocket::SetMode(const long mode) {
	this->mode      = mode;
	initializedMode = true;
}

long DynSoft::DSOpenSSLSocket::GetMode() const {
	return mode;
}

void DynSoft::DSOpenSSLSocket::SetVerify(const int verify) {
	this->verify      = verify;
	initializedVerify = true;
}

int DynSoft::DSOpenSSLSocket::GetVerify() const {
	return verify;
}

void DynSoft::DSOpenSSLSocket::SetVerifyDepth(const int verifyDepth) {
	this->verifyDepth      = verifyDepth;
	initializedVerifyDepth = true;
}

int DynSoft::DSOpenSSLSocket::GetVerifyDepth() const {
	return verifyDepth;
}

DynSoft::DSOpenSSLSocket::DSOpenSSLSocketErrorType DynSoft::DSOpenSSLSocket::Initialize() {
	if(initialized)
		return ALREADY_INITIALIZED;
	else if(!initializedSSLVersion)
		return NOT_INITIALIZED_SSL_VERSION;
	else if(!initializedCertificationFilename)
		return NOT_INITIALIZED_CERTIFICATION_FILENAME;
	else if(!initializedKeyFilename)
		return NOT_INITIALIZED_KEY_FILENAME;
	else if(!initializedMode)
		return NOT_INITIALIZED_MODE;
	else if(!initializedVerify)
		return NOT_INITIALIZED_VERIFY;
	else if(!initializedVerifyDepth)
		return NOT_INITIALIZED_VERIFY_DEPTH;
	else if(!initializedAddress)
		return NOT_INITIALIZED_ADDRESS;
	
	SSL_load_error_strings();
	SSL_library_init();

	const SSL_METHOD *sslMethod;

	switch(GetSSLMethod()) {
		case AUTO:           sslMethod = TLSv1_2_method();         break;
		case AUTO_SERVER:    sslMethod = TLSv1_2_server_method();  break;
		case AUTO_CLIENT:    sslMethod = TLSv1_2_client_method();  break;
		case TLSv12:         sslMethod = TLSv1_2_method();         break;
		case TLSv12_SERVER:  sslMethod = TLSv1_2_server_method();  break;
		case TLSv12_CLIENT:  sslMethod = TLSv1_2_client_method();  break;
		case UNKNOWN:
		default:
			sslMethod = NULL;
			break;
	}

	if(!sslMethod)
		return UNKNOWN_SSL_METHOD;

	ctx = SSL_CTX_new(sslMethod);
	if(ctx) {
		DSOpenSSLSocketErrorType error = NONE;
		if(!SSL_CTX_load_verify_locations(ctx, GetCaFilename().mb_str(wxConvUTF8), NULL)) {
			error = ERROR_LOAD_VERIFY;
		} else {
			SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file(GetCaFilename().mb_str(wxConvUTF8)));

			if(!SSL_CTX_use_certificate_file(ctx, GetCertificateFilename().mb_str(wxConvUTF8), SSL_FILETYPE_PEM)) {
				error = ERROR_USE_CERTIFICATE_FILE;
			} else if(!SSL_CTX_use_PrivateKey_file(ctx, GetKeyFilename().mb_str(wxConvUTF8), SSL_FILETYPE_PEM)) {
				error = ERROR_USE_KEY_FILE;
			} else if(!SSL_CTX_check_private_key(ctx)) {
				error = ERROR_CHECK_KEY;
			} else {
				SSL_CTX_set_mode(ctx, GetMode());
				SSL_CTX_set_verify(ctx, GetVerify(), NULL);
				SSL_CTX_set_verify_depth(ctx, GetVerifyDepth());
			}
		}

		if(error != NONE) {
			SSL_CTX_free(ctx);
			return error;
		} else {
			initialized = true;
		}
	} else {
		return ERROR_CTX;
	}

	return NONE;
}

bool DynSoft::DSOpenSSLSocket::SetAddress(
	const wxString &host,
	unsigned int port,
	int type,
	int protocol
) {
	const char *tmpHost = DSCasts::ToChar(host);
	struct hostent *hp  = NULL;

#ifndef __WINDOWS__
	if(!inet_aton(tmpHost, &address.sin_addr)) {
		hp = gethostbyname(tmpHost);
		delete [] tmpHost;
		if(!hp)
			return false;
		address.sin_addr = *(struct in_addr *) hp->h_addr;
	}
#else
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
		return false;

	hp = gethostbyname(tmpHost);
	delete [] tmpHost;
	if(!hp)
		return false;
	address.sin_addr = *((struct in_addr*) (hp->h_addr_list[0]));
#endif

	address.sin_family = family;
	address.sin_port   = htons(port);

	SetProtocol(protocol);
	SetType(type);
	SetFamily(family);

	initializedAddress = true;

	return true;
}

void DynSoft::DSOpenSSLSocket::GetAddress(
	wxString *ip,
	unsigned int *port
) {
	if(ip != NULL)
		*ip = GetIp();
	if(port != NULL)
		*port = ntohs(address.sin_port);
}

wxString DynSoft::DSOpenSSLSocket::GetIp() const {
	return DSCasts::ToString(inet_ntoa(address.sin_addr));
}

void DynSoft::DSOpenSSLSocket::SetFamily(short family) {
	this->family = family;
}

short DynSoft::DSOpenSSLSocket::GetFamily() const {
	return family;
}

void DynSoft::DSOpenSSLSocket::SetProtocol(const int protocol) {
	this->protocol = protocol;
}

int DynSoft::DSOpenSSLSocket::GetProtocol() const {
	return protocol;
}

void DynSoft::DSOpenSSLSocket::SetType(const int type) {
	this->type = type;
}

int DynSoft::DSOpenSSLSocket::GetType() const {
	return type;
}

bool DynSoft::DSOpenSSLSocket::SetOptions(int level, int name, void *value, int length) {
	const int tmp = 1;
	return setsockopt(
		connection,
		level,
		name,
		#ifdef __WINDOWS__
			value == NULL ? (char *) &tmp : (char *) value,
		#else
			value == NULL ? (void *) &tmp : value,
		#endif
		value == NULL ? sizeof(tmp) : length
	) == 0;
}

bool DynSoft::DSOpenSSLSocket::Bind() {
	connection = socket(GetFamily(), GetType(), GetProtocol());
	if(connection <= 0)
		return false;

	SetOptions(SOL_SOCKET, SO_REUSEADDR);

	return bind(
		connection,
		(struct sockaddr *) &address,
		sizeof(address)
	) == 0;
}

bool DynSoft::DSOpenSSLSocket::Listen(int tries) {
	return listen(connection, tries) == 0;
}

DynSoft::DSOpenSSLSocket *DynSoft::DSOpenSSLSocket::Accept(DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType *error) {
	socklen_t length = sizeof(struct sockaddr_in);
	DynSoft::DSOpenSSLSocket *socket = new DynSoft::DSOpenSSLSocket(*this);
	int tmpConnection = accept(
		connection,
		(struct sockaddr *) &address,
		&length
	);

	if(tmpConnection > 0) {
		DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType tmpError = socket->SetConnection(tmpConnection, ctx);
		if(error)
			*error = tmpError;
		if(tmpError == DSOpenSSLSocket::CONNECTED) {
			#ifdef __WINDOWS__
				memcpy(&address, socket->GetAddressStruct(), length);
			#else
				bcopy(&address, socket->GetAddressStruct(), length);
			#endif
		} else {
			delete socket;
			socket = NULL;
		}
	} else {
		delete socket;
		socket = NULL;
	}

	return socket;
}

DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType DynSoft::DSOpenSSLSocket::SetConnection(const int connection, SSL_CTX *ctx) {
	context = true;

	DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType error = CONNECTED;

	if(ssl) {
		SSL_free(ssl);
		ssl = NULL;
	}

	bio = BIO_new_socket(connection, BIO_NOCLOSE);
	if(bio) {
		ssl = SSL_new(ctx);
		if(ssl) {
			SSL_set_bio(ssl, bio, bio);

			if(SSL_accept(ssl) == -1) {
				error = ERROR_SSL_ACCEPT;
			} else {
				this->connection = connection;
			}
		} else {
			error = ERROR_SSL_NEW;
		}
	} else {
		error = ERROR_BIO_NEW_SOCKET;
	}

	if(error != CONNECTED) {
		if(ssl) {
			SSL_free(ssl);
			ssl = NULL;
		}
	}

	return error;
}

int DynSoft::DSOpenSSLSocket::GetConnection() const {
	return connection;
}

struct sockaddr *DynSoft::DSOpenSSLSocket::GetAddressStruct() {
	return (sockaddr *) &address;
}

void DynSoft::DSOpenSSLSocket::SetTimeout(long seconds, long microseconds) {
	this->seconds      = seconds;
	this->microseconds = microseconds;
	timeoutSetted      = true;
}

bool DynSoft::DSOpenSSLSocket::GetTimeout(long *seconds, long *microseconds) const {
	if(seconds != NULL)
		*seconds = this->seconds;
	if(microseconds != NULL)
		*microseconds = this->microseconds;
	return timeoutSetted;
}

void DynSoft::DSOpenSSLSocket::SetAutoTimeout(long seconds, long microseconds) {
	this->autoSeconds = seconds;
	this->autoMicroseconds = microseconds;
	this->autoTimeoutSetted = true;
}

bool DynSoft::DSOpenSSLSocket::GetAutoTimeout(long *seconds, long *microseconds) const {
	if(seconds != NULL)
		*seconds = this->autoSeconds;
	if(microseconds != NULL)
		*microseconds = this->autoMicroseconds;
	return autoTimeoutSetted;
}

bool DynSoft::DSOpenSSLSocket::TimedOut() {
	if(!timeoutSetted)
		return false;
	
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(static_cast<unsigned int>(connection), &fds);

	struct timeval timeout;
	timeout.tv_sec  = seconds;
	timeout.tv_usec = microseconds;

	return select(connection + 1, &fds, NULL, NULL, &timeout) <= 0;
}

bool DynSoft::DSOpenSSLSocket::Disconnect() {
	if(ssl) {
		SSL_free(ssl);
		ssl = NULL;
	}

	return close(connection) == 0;
}

int DynSoft::DSOpenSSLSocket::Receive(void *buffer, int length) {
	return SSL_read(ssl, buffer, length);
}

int DynSoft::DSOpenSSLSocket::Send(void *buffer, int length) {
	return SSL_write(ssl, buffer, length);
}

DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType DynSoft::DSOpenSSLSocket::Connect() {
	connection = socket(GetFamily(), GetType(), GetProtocol());
	if(connection <= 0)
		return ERROR_CONNECTION;

	SetOptions(SOL_SOCKET, SO_REUSEADDR);

	if(GetAutoTimeout(NULL, NULL)) {
		struct timeval tv;
		tv.tv_sec = seconds;
		tv.tv_usec = microseconds;

		setsockopt(
			GetConnection(),
			SOL_SOCKET,
			SO_RCVTIMEO,
			(char *) &tv,
			sizeof(struct timeval)
		);
	}

	int tmp = connect(
		connection,
		(struct sockaddr *) &address,
		sizeof(address)
	);

	if(tmp != 0)
		return ERROR_CONNECT;
	
	DynSoft::DSOpenSSLSocket::DSOpenSSLSocketConnectionErrorType error = CONNECTED;

	if(ssl) {
		SSL_free(ssl);
		ssl = NULL;
	}

	ssl = SSL_new(ctx);
	if(ssl) {
		bio = BIO_new_socket(connection, BIO_NOCLOSE);
		if(bio) {
			SSL_set_bio(ssl, bio, bio);

			if(SSL_connect(ssl) > 0) {
				if(SSL_get_verify_result(ssl) != X509_V_OK)
					error = ERROR_SSL_VERIFY;
			} else {
				error = ERROR_SSL_CONNECT;
			}
		} else {
			error = ERROR_BIO_NEW_SOCKET;
		}
	} else {
		error = ERROR_SSL_NEW;
	}

	if(error != CONNECTED) {
		if(ssl) {
			SSL_free(ssl);
			ssl = NULL;
		}
	}

	return error;
}

bool DynSoft::DSOpenSSLSocket::IsConnected() const {
	sockaddr *tmpName   = new sockaddr;
	socklen_t tmpLength = 0;
	const bool result   = getpeername(GetConnection(), tmpName, &tmpLength) == 0;
	delete tmpName;
	return result;
}
