#ifndef DS_SOCKET_H_
#define DS_SOCKET_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_SOCKET_VERSION	_N("0.0.1")
#define DS_SOCKET_NAME		_N("DSSocket")
#define DS_SOCKET_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSocket : public DSLib {

		public:
			DSSocket();

			DSClassInfo GetClassInfo();
	
	};

}

#endif /* DS_SOCKET_H_ */
