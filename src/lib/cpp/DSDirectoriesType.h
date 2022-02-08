#ifndef DS_DIRECTORIES_TYPE_H_
#define DS_DIRECTORIES_TYPE_H_

#include "DSType.h"
#include "DSClassInfo.h"
#include "DSTemplateContainer.h"
#include "DSDirectoryType.h"
#include "DSFileType.h"

#define DS_DIRECTORIES_TYPE_VERSION		_N("0.0.1")
#define DS_DIRECTORIES_TYPE_NAME		_N("DSDirectoriesType")
#define DS_DIRECTORIES_TYPE_AUTHOR	 	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSDirectoriesType : public DSType {

		public:
			DSDirectoriesType(const bool autoClean = true);
			~DSDirectoriesType();

			DSClassInfo GetClassInfo();

			void SetAutoClean(const bool autoClean);
			bool GetAutoClean() const;

			void AddDirectory(DSDirectoryType *directory);
			unsigned int GetDirectoryCount() const;
			DSDirectoryType *GetDirectory(const unsigned int index);

			void AddFile(DSFileType *file);
			unsigned int GetFileCount() const;
			DSFileType *GetFile(const unsigned int index);
		
		protected:
			DSTemplateContainer<DSDirectoryType *> directories;
			DSTemplateContainer<DSFileType *> files;
			bool autoClean;

	};

}

#endif /* DS_DIRECTORIES_TYPE_H_ */
