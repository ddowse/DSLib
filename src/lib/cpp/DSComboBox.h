#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_COMBOBOX_H_
#define DS_COMBOBOX_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_COMBOBOX_VERSION        _N("0.0.3")
#define DS_COMBOBOX_NAME           _N("DSComboBox")
#define DS_COMBOBOX_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSComboBox : public wxComboBox, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSComboBox)

		public:
			DSComboBox(bool *changed = NULL);
			DSComboBox(
				wxWindow *parent,
				wxWindowID id,
				const wxString &value = wxEmptyString,
				bool *changed = NULL,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				int n = 0,
				const wxString choices[] = NULL,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxComboBoxNameStr
			);
			DSComboBox(
				wxWindow *parent,
				wxWindowID id,
				const wxString &value,
				bool *changed,
				const wxPoint &pos,
				const wxSize &size,
				const wxArrayString &choices,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxComboBoxNameStr
			);

			DSClassInfo GetClassInfo();

			#if wxMAJOR_VERSION < 3
				void SetMaxLength(const unsigned int maxLength);
				unsigned int GetMaxLength() const;

				protected:
					DECLARE_EVENT_TABLE()

					void ChangeEvent(wxCommandEvent &event);

					unsigned int maxLength;
			#else
					DECLARE_EVENT_TABLE()

					void ChangeEvent(wxCommandEvent &event);
			#endif

	};

}

#endif /* COMBOBOX */

#endif /* DS_WITH_GUI */
