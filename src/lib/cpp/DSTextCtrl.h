#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_TEXTCTRL_H_
#define DS_TEXTCTRL_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSCurrency.h"
#include "DSChangeInterface.h"

#define DS_TEXTCTRL_VERSION        _N("0.0.6")
#define DS_TEXTCTRL_NAME           _N("DSTextCtrl")
#define DS_TEXTCTRL_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_TEXTCTRL_REGULAR_EXPRESSION_NONE     _N("^.*")
#define DS_TEXTCTRL_REGULAR_EXPRESSION_NUMBER   _N("^-?[0-9]*$")
//#define DS_TEXTCTRL_REGULAR_EXPRESSION_CURRENCY _N("^[0-9]{1}[0-9]*(,[0-9]{0,2}|[0-9]*)$")
#define DS_TEXTCTRL_REGULAR_EXPRESSION_CURRENCY _N("^-?[0-9]*(,[0-9]{0,2}|[0-9]*)$")
#define DS_TEXTCTRL_REGULAR_EXPRESSION_WEIGHT   _N("^-?[0-9]*(,[0-9]{0,3}|[0-9]*)$")
#define DS_TEXTCTRL_REGULAR_EXPRESSION_DOUBLE   _N("^-?[0-9]*(,[0-9]{0,8}|[0-9]*)$")

namespace DynSoft {

	class DSTextCtrl : public wxTextCtrl, public DSChangeInterface {

		DECLARE_DYNAMIC_CLASS(DSTextCtrl)
		
		public:
			DSTextCtrl(bool *changed = NULL);
			DSTextCtrl(
				wxWindow *parent,
				wxWindowID id,
				const wxString &value = wxEmptyString,
				bool *changed = NULL,
				const wxString regularExpression = DS_TEXTCTRL_REGULAR_EXPRESSION_NONE,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = 0,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxTextCtrlNameStr
			);

			DSClassInfo GetClassInfo();

			void SetCurrencyValue(DynSoft::DSCurrency value);
			DynSoft::DSCurrency GetCurrencyValue();

			void SetRegularExpression(const wxString regularExpression);
			wxString GetRegularExpression() const;

		protected:
			DECLARE_EVENT_TABLE()

			void InputEvent(wxCommandEvent &event);
			void SetFocusEvent(wxFocusEvent &event);
			void KillFocusEvent(wxFocusEvent &event);
			void DownEvent(wxKeyEvent &event);
			void UpEvent(wxKeyEvent &event);

			bool CheckText(const wxString &text);
			void FillUp(const unsigned int places = 2);

			wxString regularExpression;
			bool fireEvent;
			bool ctrl;
			
			wxString buffer;

	};

}

#endif /* DS_TEXTCTRL_H_ */

#endif /* DS_WITH_GUI */
