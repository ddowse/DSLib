#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_DATEPICKERCTRL_H_
#define DS_DATEPICKERCTRL_H_

#include <wx/wx.h>
#include <wx/datectrl.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_DATEPICKERCTRL_VERSION        _N("0.0.1")
#define DS_DATEPICKERCTRL_NAME           _N("DSDatePickerCtrl")
#define DS_DATEPICKERCTRL_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSDatePickerCtrl : public wxDatePickerCtrl, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSDatePickerCtrl)

		public:
			DSDatePickerCtrl(bool *changed = NULL);
			DSDatePickerCtrl(
				wxWindow *parent,
				wxWindowID id,
				const wxDateTime &dt = wxDefaultDateTime,
				bool *changed = NULL,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = wxDP_DEFAULT | wxDP_SHOWCENTURY,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxDatePickerCtrlNameStr
			);

			DSClassInfo GetClassInfo();

		protected:
			DECLARE_EVENT_TABLE()

			void ChangeEvent(wxCommandEvent &event);

	};

}

#endif /* DATEPICKERCTRL */

#endif /* DS_WITH_GUI */
