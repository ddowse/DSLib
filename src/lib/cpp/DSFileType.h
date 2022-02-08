#ifndef DS_FILE_TYPE_H_
#define DS_FILE_TYPE_H_

#include "DSType.h"
#include "DSClassInfo.h"

#define DS_FILE_TYPE_VERSION	_N("0.0.1")
#define DS_FILE_TYPE_NAME		_N("DSFileType")
#define DS_FILE_TYPE_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSFileType : public DSType {

		public:
			DSFileType(
				const wxString &fullname,
				const wxString &name = wxEmptyString,
				const wxString &extension = wxEmptyString,
				const wxString &full = wxEmptyString,
				const wxString &path = wxEmptyString,
				const wxULongLong size = 0,
				const wxString &humanSize = wxEmptyString,
				const bool executable = false,
				const bool readable = false,
				const bool writeable = false,
				const wxString &mimetype = wxEmptyString
			);

			DSClassInfo GetClassInfo();

			void SetName(const wxString &name);
			wxString GetName() const;

			void SetFullname(const wxString &fullname);
			wxString GetFullname() const;

			void SetFull(const wxString &full);
			wxString GetFull() const;

			void SetPath(const wxString &path);
			wxString GetPath() const;

			void SetExtension(const wxString &extension);
			wxString GetExtension() const;

			void SetSize(const wxULongLong size);
			wxULongLong GetSize() const;

			void SetHumanSize(const wxString &humanSize);
			wxString GetHumanSize() const;

			void SetExecutable(const bool executable);
			bool IsExecutable() const;

			void SetReadable(const bool readable);
			bool IsReadable() const;

			void SetWriteable(const bool writeable);
			bool IsWriteable() const;

			void SetMimetype(const wxString &mimetype);
			wxString GetMimetype() const;

			wxString ToString();
		
		protected:
			wxString name;
			wxString fullname;
			wxString extension;
			wxString full;
			wxString path;
			wxULongLong size;
			wxString humanSize;
			bool executable;
			bool readable;
			bool writeable;
			wxString mimetype;

	};

}

#endif /* DS_FILE_TYPE_H_ */
