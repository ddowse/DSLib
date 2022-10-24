#ifndef DS_TEMPLATE_H_
#define DS_TEMPLATE_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSStringHashMap.h"
#include "DSEntity.h"

#define DS_TEMPLATE_VERSION	_N("2.0.0")
#define DS_TEMPLATE_NAME	_N("DSTemplate")
#define DS_TEMPLATE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSTemplate : public DSLib {
	
		public:
			DSTemplate(const wxString &root = wxEmptyString);
			wxString GetRoot() const;
			void SetContent(const wxString &content);
			int SetFile(const wxString &filename);
			wxString &GetContent();
			wxString GetContentCopy() const;
			wxString GetFilename() const;
			wxString &Get();
			wxString GetCopy() const;

			void SetVariable(
				const wxString &key,
				const wxString &value,
				const bool htmlSpecialChars = false
			);
			wxString GetVariable(const wxString &key);

			void SetDynamicVariable(
				const wxString &key,
				const wxString &value,
				const bool htmlSpecialChars = false
			);
			wxString GetDynamicVariable(const wxString &key);

			void SetInternVariable(
				const wxString &key,
				const wxString &value,
				const bool htmlSpecialChars = false
			);
			wxString GetInternVariable(const wxString &key);
			DSStringHashMap GetInternVariables() const;

			wxString Parse();
			void Show(const wxString &header = wxEmptyString) const;
			void ClearParsed();

			DSClassInfo GetClassInfo();

			void SetEntity(DSEntity *entity);

		protected:
			wxString root;
			wxString content;
			wxString parsedContent;
			wxString filename;

			DSStringHashMap intern;
			DSStringHashMap dynamic;
			DSStringHashMap variables;

			void FillInternVariables();

	};

}

#endif /* DS_TEMPLATE_H_ */
