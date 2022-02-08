#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_CHECKBOX_H_
#define DS_CHECKBOX_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_CHECKBOX_VERSION        _N("0.0.1")
#define DS_CHECKBOX_NAME           _N("DSCheckBox")
#define DS_CHECKBOX_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCheckBox : public wxCheckBox, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSCheckBox)

		public:
			DSCheckBox(bool *changed = NULL);
			DSCheckBox(
				wxWindow *parent,
				wxWindowID id,
				const wxString &value = wxEmptyString,
				bool *changed = NULL,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxCheckBoxNameStr
			);

			DSClassInfo GetClassInfo();

		protected:
			DECLARE_EVENT_TABLE()

			void ChangeEvent(wxCommandEvent &event);

	};

}

#endif /* CHECKBOX */

#endif /* DS_WITH_GUI */
