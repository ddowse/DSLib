#include "DSPosixSocket.h"
#include "DSCasts.h"
#include <stdlib.h>

DynSoft::DSPosixSocket::DSPosixSocket(short family) {
	this->family    = family;
	connection      = 0;
	seconds         = 0;
	microseconds    = 0;
	timeoutSetted   = false;
}

DynSoft::DSClassInfo DynSoft::DSPosixSocket::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_POSIXSOCKET_NAME,
		DS_POSIXSOCKET_VERSION,
		DS_POSIXSOCKET_AUTHOR
	);
}

bool DynSoft::DSPosixSocket::CheckIpSection(const wxString &section) {
	if(section.Length() == 0 || section.Length() > 3)
		return false;
	int tmp = DSCasts::ToInt(section);
	if(tmp == 0 && (section == _N("0") || section == _N("00") || section == _N("000")))
		return true;
	return tmp >= 0 && tmp <= 255;
}

bool DynSoft::DSPosixSocket::IsIp(const wxString &address) {
	wxArrayString as(Split(address, '.'));
	if(as.GetCount() != 4)
		return false;
	
	long tmp;
	for(unsigned int i = 0; i < as.GetCount(); i++)
		if(!as[i].ToLong(&tmp))
			return false;

	return CheckIpSection(as[0]) &&
		   CheckIpSection(as[1]) &&
		   CheckIpSection(as[2]) &&
		   CheckIpSection(as[3]);
}

bool DynSoft::DSPosixSocket::SetAddress(
	const wxString &host,
	unsigned int port,
	int type,
	int protocol
) {
	const char *tmpHost = DSCasts::ToChar(host);

/*
	if(!IsIp(host)) {
		struct hostent *hp = gethostbyname(tmpHost);
		if(hp == NULL)
			return false;
		bcopy(hp->h_addr, &address.sin_addr.s_addr, hp->h_length);
	} else {
		inet_aton(tmpHost, &address.sin_addr);
	}
*/
	struct hostent *hp = NULL;

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

	return true;
}

bool DynSoft::DSPosixSocket::Connect() {
	connection = socket(GetFamily(), GetType(), GetProtocol());
	if(connection <= 0)
		return false;

	SetOptions(SOL_SOCKET, SO_REUSEADDR);

	return connect(
		connection,
		(struct sockaddr *) &address,
		sizeof(address)
	) == 0;
}

bool DynSoft::DSPosixSocket::Bind() {
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

// TODO what are we doing here?
bool DynSoft::DSPosixSocket::SetOptions(int level, int name, void *value, int length) {
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

bool DynSoft::DSPosixSocket::Listen(int tries) {
	return listen(connection, tries) == 0;
}

DynSoft::DSPosixSocket *DynSoft::DSPosixSocket::Accept() {
	socklen_t length = sizeof(struct sockaddr_in);
	DynSoft::DSPosixSocket *socket = new DynSoft::DSPosixSocket(*this);
	int tmpConnection = accept(
		connection,
		(struct sockaddr *) &address,
		&length
	);

	if(tmpConnection > 0) {
		socket->SetConnection(tmpConnection);
		#ifdef __WINDOWS__
			memcpy(&address, socket->GetAddressStruct(), length);
		#else
			bcopy(&address, socket->GetAddressStruct(), length);
		#endif
	} else {
		delete socket;
		socket = NULL;
	}

	return socket;
}

bool DynSoft::DSPosixSocket::Disconnect() {
	return close(connection) == 0;
}

ssize_t DynSoft::DSPosixSocket::Receive(void *buffer, size_t length, int flags) {
	#ifdef __WINDOWS__
		return recv(connection, (char *) buffer, length, flags);
	#else
		return recv(connection, buffer, length, flags);
	#endif
}

ssize_t DynSoft::DSPosixSocket::Send(void *buffer, size_t length, int flags) {
	#ifdef __WINDOWS__
		return send(connection, (char *) buffer, length, flags);
	#else
		return send(connection, buffer, length, flags);
	#endif
}

ssize_t DynSoft::DSPosixSocket::Receive(wxString *buffer, char stop) {
	/*buffer->Clear();
	int size = 0;
	int lastSize = -1;
	char tmp;
	while(size != lastSize && !TimedOut()) {
		lastSize = size;
		size += Receive(&tmp, 1);
		if(tmp == stop)
			break;
		if(size > lastSize)
			buffer->Append(tmp);
	}*/

	buffer->Clear();
	unsigned int count = 0;
	ssize_t size = 0;
	ssize_t lastSize = -1;
	char tmp;
	char *tmpBuffer = NULL;
	while(size != lastSize && !TimedOut()) {
		lastSize = size;
		size += Receive(&tmp, 1);
		if(tmp == stop)
			break;
		if(size > lastSize) {
			tmpBuffer = (char *) realloc(tmpBuffer, sizeof(char) * ++count);
			tmpBuffer[count - 1] = tmp;
		}
	}

	if(tmpBuffer) {
		tmpBuffer = (char *) realloc(tmpBuffer, sizeof(char) * (count + 1));
		tmpBuffer[count] = '\0';
		*buffer = DSCasts::ToString(tmpBuffer);
		free(tmpBuffer);
	}

	return size;
}

ssize_t DynSoft::DSPosixSocket::Send(const wxString &buffer, const bool removeTermination) {
	const char *tmp = DSCasts::ToChar(buffer);
	int size = Send((void *) tmp, strlen(tmp) + (removeTermination ? 0 : 1));
	delete [] tmp;
	tmp = NULL;
	return size;
}


wxString DynSoft::DSPosixSocket::GetIp() const {
	return DSCasts::ToString(inet_ntoa(address.sin_addr));
}

void DynSoft::DSPosixSocket::SetConnection(const int connection) {
	this->connection = connection;
}

int DynSoft::DSPosixSocket::GetConnection() const {
	return connection;
}

void DynSoft::DSPosixSocket::SetTimeout(long seconds, long microseconds) {
	this->seconds      = seconds;
	this->microseconds = microseconds;
	timeoutSetted      = true;
}

bool DynSoft::DSPosixSocket::GetTimeout(long *seconds, long *microseconds) const {
	if(seconds != NULL)
		*seconds = this->seconds;
	if(microseconds != NULL)
		*microseconds = this->microseconds;
	return timeoutSetted;
}

bool DynSoft::DSPosixSocket::TimedOut() {
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

void DynSoft::DSPosixSocket::SetFamily(short family) {
	this->family = family;
}

short DynSoft::DSPosixSocket::GetFamily() const {
	return family;
}

bool DynSoft::DSPosixSocket::GetAddress(
	wxString *ip,
	unsigned int *port
) {
	if(ip != NULL)
		*ip = GetIp();
	if(port != NULL)
		*port = ntohs(address.sin_port);
	
	return connection > 0;
}

void DynSoft::DSPosixSocket::SetProtocol(const int protocol) {
	this->protocol = protocol;
}

int DynSoft::DSPosixSocket::GetProtocol() const {
	return protocol;
}

void DynSoft::DSPosixSocket::SetType(const int type) {
	this->type = type;
}

int DynSoft::DSPosixSocket::GetType() const {
	return type;
}

struct sockaddr *DynSoft::DSPosixSocket::GetAddressStruct() {
	return (sockaddr *) &address;
}

bool DynSoft::DSPosixSocket::IsConnected() const {
	sockaddr *tmpName   = new sockaddr;
	socklen_t tmpLength = 0;
	const bool result   = getpeername(GetConnection(), tmpName, &tmpLength) == 0;
	delete tmpName;
	return result;
}

bool DynSoft::DSPosixSocket::Shutdown(const int how, int *errorNumber) {
	int tmpErrorNumber = shutdown(GetConnection(), how);
	if(errorNumber)
		*errorNumber = tmpErrorNumber;
	return tmpErrorNumber == 0;
}
