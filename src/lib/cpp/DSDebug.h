#ifndef DS_DEBUG_H_
#define DS_DEBUG_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_DEBUG_VERSION	_N("1.0.1")
#define DS_DEBUG_NAME		_N("DSDebug")
#define DS_DEBUG_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_DEBUG_FILE		_N("debug.txt")

#define DBW(value) DSDebug((value))

namespace DynSoft {

	class DSDebug : public DSLib {
	
		public:
			DSDebug();
			DSDebug(const wxString &message);
			DSDebug(
				const wxString &message,
				const bool error,
				const wxString &value
			);

			DSClassInfo GetClassInfo();
			static bool Write(
				wxString message,
				const bool = true,
				const wxString &value = wxEmptyString,
				const bool withoutErrorMasking = false
			);
	
	};

}

#endif /* DS_DEBUG_H_ */
