#include "DSSocket.h"

DynSoft::DSSocket::DSSocket() {
}

DynSoft::DSClassInfo DynSoft::DSSocket::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SOCKET_NAME,
		DS_SOCKET_VERSION,
		DS_SOCKET_AUTHOR
	);
}

