#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_SPINCTRL_H_
#define DS_SPINCTRL_H_

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_SPINCTRL_VERSION        _N("0.0.1")
#define DS_SPINCTRL_NAME           _N("DSSpinCtrl")
#define DS_SPINCTRL_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSpinCtrl : public wxSpinCtrl, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSSpinCtrl)

		public:
			DSSpinCtrl(bool *changed = NULL);
			DSSpinCtrl(
				wxWindow *parent,
				wxWindowID id = -1,
				const wxString &value = wxEmptyString,
				bool *changed = NULL,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = wxSP_ARROW_KEYS,
				int min = 0,
				int max = 100,
				int initial = 0,
				const wxString &name = _N("wxSpinCtrl")
			);

			DSClassInfo GetClassInfo();

		protected:
			DECLARE_EVENT_TABLE()

			void ChangeEvent(wxSpinEvent &event);

	};

}

#endif /* SPINCTRL */

#endif /* DS_WITH_GUI */
