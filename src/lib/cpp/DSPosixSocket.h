#ifndef DS_POSIXSOCKET_H_
#define DS_POSIXSOCKET_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


#define DS_POSIXSOCKET_VERSION	_N("0.0.7")
#define DS_POSIXSOCKET_NAME		_N("DSPosixSocket")
#define DS_POSIXSOCKET_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSPosixSocket : public DSLib {
	
		public:
			DSPosixSocket(short family = AF_INET);

			DSClassInfo GetClassInfo();

			bool Connect();
			bool Bind();
			bool SetOptions(int level = SOL_SOCKET, int name = SO_REUSEADDR, void *value = NULL, int length = 1);
			bool Listen(int tries = 5);
			DSPosixSocket *Accept();
			bool Disconnect();
			bool TimedOut();
			ssize_t Receive(void *buffer, size_t length = 1, int flags = 0);
			ssize_t Send(void *buffer, size_t length, int flags = 0);
			ssize_t Receive(wxString *buffer, char stop = '\0');
			ssize_t Send(const wxString &buffer, const bool removeTermination = false);

			wxString GetIp() const;
			void SetConnection(const int connection);
			int GetConnection() const;
			bool IsConnected() const;
			void SetTimeout(long seconds, long microseconds = 0);
			bool GetTimeout(long *seconds, long *microseconds = NULL) const;
			void SetFamily(short family = AF_INET);
			short GetFamily() const;
			bool SetAddress(
				const wxString &host,
				unsigned int port,
				int type     = SOCK_STREAM,
				int protocol = 0
			);
			bool GetAddress(
				wxString *ip,
				unsigned int *port
			);
			void SetProtocol(const int protocol = 0);
			int GetProtocol() const;
			void SetType(const int type = SOCK_STREAM);
			int GetType() const;
			static bool IsIp(const wxString &address);

			bool Shutdown(const int how = SHUT_RDWR, int *errorNumber = NULL);

		protected:
			int connection;
			short family;
			int protocol;
			int type;
			struct sockaddr_in address;
			long seconds, microseconds;
			bool timeoutSetted;

			static bool CheckIpSection(const wxString &section);
			struct sockaddr *GetAddressStruct();
	
	};

}

#endif /* DS_POSIXSOCKET_H_ */
