#ifndef DS_CLASS_INFO_H_
#define DS_CLASS_INFO_H_

#include <wx/wx.h>

#define DS_CLASS_INFO_NAME		_N("DSClassInfo")
#define DS_CLASS_INFO_VERSION	_N("1.0.1")
#define DS_CLASS_INFO_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSClassInfo {

		public:
			DSClassInfo(
				const wxString &name,
				const wxString &version,
				const wxString &author
			);

			DSClassInfo GetClassInfo();

			void SetName(const wxString &name);
			wxString GetName() const;

			void SetVersion(const wxString &version);
			wxString GetVersion() const;

			void SetAuthor(const wxString &author);
			wxString GetAuthor() const;

		protected:
			wxString name;
			wxString version;
			wxString author;
	
	};

}

#endif /* DS_CLASS_INFO_H_ */
