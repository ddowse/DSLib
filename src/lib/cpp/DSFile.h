#ifndef DS_FILE_H_
#define DS_FILE_H_

#include <wx/wx.h>
#include <wx/ffile.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_FILE_VERSION		_N("0.0.3")
#define DS_FILE_NAME		_N("DSFile")
#define DS_FILE_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSFile : public wxFFile, public DSLib {
	
		public:
			DSFile(DSDatabase *db = NULL);
			DSFile(
				const wxString &filename,
				const wxString &mode = _N("r")
			);

			DSClassInfo GetClassInfo();

			wxArrayString ReadToArrayString(wxMBConv &conv = wxConvUTF8);

			static wxString Concat(const wxString &first, const wxString &second);
			static bool ExistsFile(const wxString &file); // wx console bug - error message loop
	
	};

}

#endif /* DS_FILE_H_ */
