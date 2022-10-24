#ifndef DSTRANSLATION_H_
#define DSTRANSLATION_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSStringHashMap.h"

#define DS_TRANSLATION_VERSION	_N("0.0.2")
#define DS_TRANSLATION_NAME		_N("DSTranslation")
#define DS_TRANSLATION_AUTHOR	_N("Dietrich Haag (dietrich@haagit.com)")

namespace DynSoft {

	class DSTranslation : public DSLib {

		public:
			DSTranslation(const wxString &path, const wxString &translationFile);
			~DSTranslation();

			DSClassInfo GetClassInfo();

			DSStringHashMap *GetTranslation();
			void SetPath(const wxString &path);
			wxString GetPath() const;

		private:
			void ReadLanguageFile(const wxString &languageFile);

			DSStringHashMap *translation;
			wxString path;

	};
}

#endif /* DSTRANSLATION_H_ */
