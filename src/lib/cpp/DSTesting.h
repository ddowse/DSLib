#ifndef DS_TESTING_H_
#define DS_TESTING_H_

#include <wx/wx.h>
#include "DSTemplateContainer.h"
#include "DSClassInfo.h"
#include "DSTest.h"

#define DS_TESTING_VERSION	_N("0.0.5")
#define DS_TESTING_NAME		_N("DSTesting")
#define DS_TESTING_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de")

namespace DynSoft {

	class DSTesting : public DSTemplateContainer<DSTest *> {

		public:
			static const unsigned int TEXT = 0;
			static const unsigned int CSV  = 1;
			static const unsigned int HTML = 2;
			static const unsigned int NONE = 3; // Means no saving of results

			DSTesting();
			~DSTesting();

			unsigned int Save(
				const unsigned int format = NONE,
				const wxString &filename = wxEmptyString,
				bool *saved = nullptr
			);

			DSClassInfo GetClassInfo();

		protected:
			wxString message;

			void SetHeaderFooter(const unsigned int format);
			void Switcher(const wxString &text, const unsigned int format);
			void Switcher(DSTest::DSTestEntity *entity, const unsigned int format);

			void SaveAsText(const wxString &text);
			void SaveAsCSV(const wxString &text);
			void SaveAsHTML(const wxString &text);

			void SaveAsText(DSTest::DSTestEntity *entity);
			void SaveAsCSV(DSTest::DSTestEntity *entity);
			void SaveAsHTML(DSTest::DSTestEntity *entity);

	};

}

#endif /* DS_TESTING_H_ */
