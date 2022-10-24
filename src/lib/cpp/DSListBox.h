#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_LISTBOX_H_
#define DS_LISTBOX_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_LISTBOX_VERSION        _N("0.0.1")
#define DS_LISTBOX_NAME           _N("DSListBox")
#define DS_LISTBOX_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSListBox : public wxListBox, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSListBox)

		public:
			DSListBox(bool *changed = NULL);
			DSListBox(
				wxWindow *parent,
				wxWindowID id,
				bool *changed = NULL,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				int n = 0,
				const wxString choices[] = NULL,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxListBoxNameStr
			);

			DSListBox(
				wxWindow *parent,
				wxWindowID id,
				bool *changed,
				const wxPoint &pos,
				const wxSize &size,
				const wxArrayString &choices,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxListBoxNameStr
			);

			DSClassInfo GetClassInfo();

		protected:
			DECLARE_EVENT_TABLE()

			void ChangeEvent(wxCommandEvent &event);

	};

}

#endif /* LISTBOX */

#endif /* DS_WITH_GUI */
