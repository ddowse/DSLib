#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSTextCtrl.h"
#include <wx/regex.h>
#include "DSCasts.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSTextCtrl, wxTextCtrl)

BEGIN_EVENT_TABLE(DynSoft::DSTextCtrl, wxTextCtrl)
	EVT_SET_FOCUS(DSTextCtrl::SetFocusEvent)
	EVT_KILL_FOCUS(DSTextCtrl::KillFocusEvent)
	EVT_TEXT(wxID_ANY, DSTextCtrl::InputEvent)
	EVT_KEY_DOWN(DSTextCtrl::DownEvent)
	EVT_KEY_UP(DSTextCtrl::UpEvent)
END_EVENT_TABLE()

DynSoft::DSTextCtrl::DSTextCtrl(bool *changed) : wxTextCtrl(), DynSoft::DSChangeInterface(changed) {
	this->fireEvent = true;
	this->ctrl = false;
	SetRegularExpression(DS_TEXTCTRL_REGULAR_EXPRESSION_NONE);
}

DynSoft::DSTextCtrl::DSTextCtrl(
	wxWindow* parent,
	wxWindowID id,
	const wxString &value,
	bool *changed,
	const wxString regularExpression,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxTextCtrl(
	parent,
	id,
	value,
	pos,
	size,
	style,
	validator,
	name
), DynSoft::DSChangeInterface(
	changed
) {
	SetRegularExpression(regularExpression);
	this->fireEvent = true;
	this->ctrl = false;
}

DynSoft::DSClassInfo DynSoft::DSTextCtrl::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TEXTCTRL_NAME,
		DS_TEXTCTRL_VERSION,
		DS_TEXTCTRL_AUTHOR
	);
}

void DynSoft::DSTextCtrl::DownEvent(wxKeyEvent &event) {
	if(event.ControlDown())
		ctrl = true;
	event.Skip();
}

void DynSoft::DSTextCtrl::UpEvent(wxKeyEvent &event) {
	ctrl = false;
	event.Skip();
}

void DynSoft::DSTextCtrl::InputEvent(wxCommandEvent &event) {
	if(ctrl) {
		event.Skip();
		return;
	}

	if(fireEvent && IsEditable()) {
		fireEvent = false;
		wxString tmp = event.GetString();

		long from = 0;
		long to   = 0;
		GetSelection(&from, &to);

		//if(to - from >= 0 && from >= 0 && to != from)
		//	tmp = tmp.Remove(from, to - from);

		from = 0; to = 0;
		
		int ip = GetInsertionPoint();

		if(CheckText(tmp))
			buffer = tmp;

//#ifdef __WXMAC__
		ChangeValue(buffer);
//#endif

		SetInsertionPoint(ip);

		SetChanged(true);

		fireEvent = true;
	}

	event.Skip();
}

void DynSoft::DSTextCtrl::SetFocusEvent(wxFocusEvent &event) {
	SetSelection(-1, -1);
	event.Skip();
}

void DynSoft::DSTextCtrl::KillFocusEvent(wxFocusEvent &event) {
	if(regularExpression == DS_TEXTCTRL_REGULAR_EXPRESSION_CURRENCY)
		FillUp(2);
	else if(regularExpression == DS_TEXTCTRL_REGULAR_EXPRESSION_WEIGHT)
		FillUp(3);
	event.Skip();
}

void DynSoft::DSTextCtrl::SetCurrencyValue(DynSoft::DSCurrency value) {
	SetValue(value.ToString());
}

DynSoft::DSCurrency DynSoft::DSTextCtrl::GetCurrencyValue() {
	return DynSoft::DSCurrency(DynSoft::DSCasts::ToDouble(GetValue()));
}

void DynSoft::DSTextCtrl::SetRegularExpression(const wxString regularExpression) {
	this->regularExpression = regularExpression;
	if(
		regularExpression == DS_TEXTCTRL_REGULAR_EXPRESSION_CURRENCY ||
		regularExpression == DS_TEXTCTRL_REGULAR_EXPRESSION_NUMBER
	) {
		SetWindowStyleFlag(GetWindowStyle() | wxTE_RIGHT);
	}
}

wxString DynSoft::DSTextCtrl::GetRegularExpression() const {
	return regularExpression;
}

bool DynSoft::DSTextCtrl::CheckText(const wxString &text) {
	if(text.IsEmpty())
		return true;

	wxRegEx re(regularExpression);
	return re.Matches(text);
}

void DynSoft::DSTextCtrl::FillUp(const unsigned int places) {
	wxString temp(GetValue());

	wxString second;
	if(temp.IsEmpty()) {
		for(unsigned int i = 0; i < places; i++)
			second += _N("0");
		SetValue(_("0,") + second);
		return;
	}
	
	int pos = temp.Find(_(","));
	if(pos == wxNOT_FOUND) {
		for(unsigned int i = 0; i < places; i++)
			second += _N("0");
		SetValue(temp + _N(",") + second);
	} else {
		wxArrayString as(DynSoft::DSLib::Split(temp, ','));
		second = as[1];
		unsigned int length = places - second.Length();
		if(length > places)
			return;
		for(unsigned int i = 0; i < length; i++)
			second += _N("0");
		SetValue(as[0] + _N(",") + second);
	}
}

#endif
