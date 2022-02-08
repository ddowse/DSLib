#ifndef DS_CONFIGURATION_H_
#define DS_CONFIGURATION_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSStringHashMap.h"
#include "DSCasts.h"

#define DS_CONFIGURATION_VERSION	_N("0.0.4")
#define DS_CONFIGURATION_NAME		_N("DSConfiguration")
#define DS_CONFIGURATION_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSConfiguration : public DSLib {

		public:
			DSConfiguration(const wxString &commentChars = _N("#"), const bool commentsOnlyFromLineStart = false);

			virtual DSClassInfo GetClassInfo();

			bool Load(const wxString &filename);
			bool Save(const wxString &filename, const wxString &lineBreak = _N("\n"));

			DSCasts Get(const wxString &key, const wxString &valueIfEmpty = wxEmptyString);
			void Set(const wxString &key, const wxString &value);
			void Set(const wxString &key, DSCasts &value);

			void SetCommentChars(const wxString &commentChars);
			wxString GetCommentChars() const;

			void SetCommentsOnlyFromLineStart(const bool commentsOnlyFromLineStart);
			bool GetCommentsOnlyFromLineStart() const;

			wxString RemoveComment(const wxString &line);

		protected:
			DSStringHashMap configuration;

			void SplitLine(wxString line, wxString *key, wxString *value) const;

			wxString commentChars;
			bool commentsOnlyFromLineStart;
	
	};

}

#endif /* DS_CONFIGURATION_H_ */
