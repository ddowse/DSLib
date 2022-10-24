#ifndef DS_DIRECTORY_TYPE_H_
#define DS_DIRECTORY_TYPE_H_

#include "DSType.h"
#include "DSClassInfo.h"

#define DS_DIRECTORY_TYPE_VERSION	_N("0.0.1")
#define DS_DIRECTORY_TYPE_NAME		_N("DSDirectoryType")
#define DS_DIRECTORY_TYPE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSDirectoryType : public DSType {

		public:
			DSDirectoryType(
				wxString name,
				const wxString &full,
				const wxString &path,
				const wxString &withoutBase,
				wxULongLong size
			);

			DSClassInfo GetClassInfo();

			void SetName(const wxString &name);
			wxString GetName() const;

			void SetFull(const wxString &full);
			wxString GetFull() const;

			void SetPath(const wxString &path);
			wxString GetPath() const;

			void SetWithoutBase(const wxString &withoutBase);
			wxString GetWithoutBase() const;

			void SetSize(const wxULongLong size);
			wxULongLong GetSize() const;

			static wxString GetParent(wxString path);
			static wxArrayString SplitPath(const wxString &path);

			wxString ToString();
		
		protected:
			wxString name;
			wxString full;
			wxString path;
			wxString withoutBase;
			wxULongLong size;

	};

}

#endif /* DS_DIRECTORY_TYPE_H_ */
