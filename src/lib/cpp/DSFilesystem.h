#ifndef DS_FILESYSTEM_H_
#define DS_FILESYSTEM_H_

#include "DSLib.h"
#include "DSDirectoriesType.h"

#define DS_FILESYSTEM_VERSION	_N("0.0.1")
#define DS_FILESYSTEM_NAME		_N("DSFilesystem")
#define DS_FILESYSTEM_AUTHOR 	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSFilesystem : public DSLib {

		public:
			typedef enum {
				ERROR_NO,
				ERROR_SECURE,
				ERROR_DIRECTORY_EXISTS,
				ERROR_DIRECTORY_NOT_EXISTS,
				ERROR_DIRECTORY_CREATE,
				ERROR_DIRECTORY_OPEN,
				ERROR_DIRECTORY_REMOVE,
				ERROR_FILE_EXISTS,
				ERROR_FILE_NOT_EXISTS,
				ERROR_FILE_COPY,
				ERROR_FILE_MOVE,
				ERROR_FILE_REMOVE
			} ErrorType;

			DSFilesystem();
			DSFilesystem(const wxString &baseDirectory);

			DSClassInfo GetClassInfo();

			void SetBaseDirectory(const wxString &baseDirectory);
			wxString GetBaseDirectory() const;

			DSDirectoriesType *Get(
				wxString directory,
				ErrorType *error = NULL,
				const bool autoClean = true
			);

			bool IsDirectorySecure(const wxString &directory);
			wxString NormalizeDirectory(wxString directory);
			static wxString Concat(const wxString &path1, wxString path2);

			ErrorType CreateDirectory(wxString directory);
			ErrorType RemoveDirectory(wxString directory);
			ErrorType CopyFile(wxString fromFilename, wxString toFilename, const bool overwrite = true);
			ErrorType MoveFile(wxString fromFilename, wxString toFilename, const bool overwrite = true);
			ErrorType RemoveFile(wxString filename);

			static wxString ErrorToString(const ErrorType error);

			wxString StripBaseDirectory(wxString path);

		protected:
			wxString baseDirectory;

	};

}

#endif /* DS_FILESYSTEM_H_ */
