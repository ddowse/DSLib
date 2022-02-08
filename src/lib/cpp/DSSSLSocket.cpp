#include "DSSSLSocket.h"
#include "DSCasts.h"

DynSoft::DSSSLSocket::DSSSLSocket(
	const bool sslInitialize,
	const bool sslLoadErrorStrings,
	const bool bioLoadErrorStrings,
	const bool cryptoLoadErrorStrings,
	const bool addAllAlgoritms
) {
	sslInitialized               = false;
	sslLoadErrorStringsLoaded    = false;
	bioLoadErrorStringsLoaded    = false;
	cryptoLoadErrorStringsLoaded = false;
	allAlgorithmsAdded           = false;

	if(sslInitialize)
		SslInitialize();
	if(sslLoadErrorStrings)
		SslLoadErrorStrings();
	if(bioLoadErrorStrings)
		BioLoadErrorStrings();
	if(cryptoLoadErrorStrings)
		CryptoLoadErrorStrings();
	if(addAllAlgoritms)
		AddAllAlgorithms();
	
	ctx           = SSL_CTX_new(SSLv23_client_method());
	connection    = NULL;
	port          = 0;
	timeoutSetted = false;
}

DynSoft::DSSSLSocket::~DSSSLSocket() {
//	if(ctx)
		//SSL_CTX_free(ctx);
		//SSL_free(ssl);
}

DynSoft::DSClassInfo DynSoft::DSSSLSocket::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SSLSOCKET_NAME,
		DS_SSLSOCKET_VERSION,
		DS_SSLSOCKET_AUTHOR
	);
}

void DynSoft::DSSSLSocket::SslInitialize() {
	SSL_library_init();
	sslInitialized = true;
}

bool DynSoft::DSSSLSocket::SslInitialize() const {
	return sslInitialized;
}

void DynSoft::DSSSLSocket::SslLoadErrorStrings() {
	SSL_load_error_strings();
	sslLoadErrorStringsLoaded = true;
}

bool DynSoft::DSSSLSocket::SslLoadErrorStringsLoaded() const {
	return sslLoadErrorStringsLoaded;
}

void DynSoft::DSSSLSocket::BioLoadErrorStrings() {
	ERR_load_BIO_strings();
	bioLoadErrorStringsLoaded = true;
}

bool DynSoft::DSSSLSocket::BioLoadErrorStringsLoaded() const {
	return bioLoadErrorStringsLoaded;
}

void DynSoft::DSSSLSocket::CryptoLoadErrorStrings() {
	ERR_load_crypto_strings();
	cryptoLoadErrorStringsLoaded = true;
}

bool DynSoft::DSSSLSocket::CryptoLoadErrorStringsLoaded() const {
	return cryptoLoadErrorStringsLoaded;
}

void DynSoft::DSSSLSocket::AddAllAlgorithms() {
	OpenSSL_add_all_algorithms();
	allAlgorithmsAdded = true;
}

bool DynSoft::DSSSLSocket::AllAlgorithmsAdded() const {
	return allAlgorithmsAdded;
}

BIO *DynSoft::DSSSLSocket::GetConnection() const {
	return connection;
}

void DynSoft::DSSSLSocket::SetAddress(const wxString &hostname, const unsigned int port) {
	this->hostname = hostname;
	this->port     = port;
}

void DynSoft::DSSSLSocket::GetAddress(wxString *hostname, unsigned int *port) const {
	if(hostname)
		*hostname = GetHostname();
	if(port)
		*port = GetPort();
}

wxString DynSoft::DSSSLSocket::GetHostname() const {
	return this->hostname;
}

unsigned int DynSoft::DSSSLSocket::GetPort() const {
	return port;
}

bool DynSoft::DSSSLSocket::Connect() {
	connection = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(connection, &ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	const char *url = DSCasts::ToChar(CreateAddress());
	BIO_set_conn_hostname(connection, url);
	delete [] url;
	return BIO_do_connect(connection) > 0;
}

bool DynSoft::DSSSLSocket::VerifySsl() {
	return SSL_get_verify_result(ssl) == X509_V_OK;
}

void DynSoft::DSSSLSocket::Disconnect() {
	if(connection) {
		BIO_reset(connection);
		BIO_free_all(connection);
	}
}

int DynSoft::DSSSLSocket::Send(const char *message, unsigned int length) {
	return BIO_write(connection, message, length);
}

int DynSoft::DSSSLSocket::Send(const wxString &message) {
	const char *tmp   = DSCasts::ToChar(message);
	const int result = Send(tmp, message.Length());
	delete [] tmp;
	return result;
}

int DynSoft::DSSSLSocket::Receive(void *buffer, unsigned int length) {
	if(!buffer)
		return 0;

	return BIO_read(connection, buffer, length);
}

int DynSoft::DSSSLSocket::Receive(wxString *buffer) {
	if(!buffer)
		return 0;
	
	unsigned int count = 0;
	char *tmp = NULL;
	char c;
	while(BIO_read(connection, &c, 1) > 0 && !TimedOut()) {
		tmp = (char *) realloc(tmp, sizeof(char) * (count + 2));
		tmp[count] = c;
		count++;
	}
	tmp[count] = '\0';

	buffer->Clear();
	*buffer = DSCasts::ToString(tmp);
	free(tmp);

	return count;
}

wxString DynSoft::DSSSLSocket::CreateAddress() const {
	return GetHostname() + wxString::Format(_N(":%u"), GetPort());
}

long DynSoft::DSSSLSocket::SetCtxTimeout(const long seconds) {
	return SSL_CTX_set_timeout(ctx, seconds);
}

void DynSoft::DSSSLSocket::SetTimeout(long seconds, long microseconds) {
	this->seconds      = seconds;
	this->microseconds = microseconds;
	timeoutSetted      = true;
}

bool DynSoft::DSSSLSocket::GetTimeout(long *seconds, long *microseconds) const {
	if(seconds != NULL)
		*seconds = this->seconds;
	if(microseconds != NULL)
		*microseconds = this->microseconds;
	return timeoutSetted;
}

bool DynSoft::DSSSLSocket::TimedOut() {
	if(!timeoutSetted)
		return false;
	
	int fdConnection = 0;
	if(BIO_get_fd(connection, &fdConnection) < 0) {
		DS_PL("Could not get fd");
		return false;
	}

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(fdConnection, &fds);

	struct timeval timeout;
	timeout.tv_sec  = seconds;
	timeout.tv_usec = microseconds;

	return select(fdConnection + 1, &fds, NULL, NULL, &timeout) <= 0;
}
