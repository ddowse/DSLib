#ifndef DS_TYPE_H_
#define DS_TYPE_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_TYPE_VERSION	_N("1.0.1")
#define DS_TYPE_NAME	_N("DSType")
#define DS_TYPE_AUTHOR	_N("Thorsten Geppert (thorsten@dynsoft.com")

namespace DynSoft {

	class DSType : public DSLib {
	
		public:
			DSType();

			DSClassInfo GetClassInfo();
	
	};

}

#endif /* DS_TYPE_H_ */
