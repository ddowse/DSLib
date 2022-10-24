#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSDatePickerCtrl.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSDatePickerCtrl, wxDatePickerCtrl)

BEGIN_EVENT_TABLE(DynSoft::DSDatePickerCtrl, wxDatePickerCtrl)
	//EVT_DATE_CHANGED(wxID_ANY, DSDatePickerCtrl::ChangeEvent) // TODO
END_EVENT_TABLE()

DynSoft::DSDatePickerCtrl::DSDatePickerCtrl(bool *changed) : wxDatePickerCtrl() {
	SetChange(changed);
}

DynSoft::DSDatePickerCtrl::DSDatePickerCtrl(
	wxWindow *parent,
	wxWindowID id,
	const wxDateTime &dt,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxDatePickerCtrl(
	parent,
	id,
	dt,
	pos,
	size,
	style,
	validator,
	name
), DynSoft::DSChangeInterface(
	changed
) {
}

DynSoft::DSClassInfo DynSoft::DSDatePickerCtrl::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DATEPICKERCTRL_NAME,
		DS_DATEPICKERCTRL_VERSION,
		DS_DATEPICKERCTRL_AUTHOR
	);
}

void DynSoft::DSDatePickerCtrl::ChangeEvent(wxCommandEvent &event) {
	SetChanged(true);
	event.Skip();
}

#endif
