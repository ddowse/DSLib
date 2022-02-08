#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSSpinCtrl.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSSpinCtrl, wxSpinCtrl)

BEGIN_EVENT_TABLE(DynSoft::DSSpinCtrl, wxSpinCtrl)
	EVT_SPINCTRL(wxID_ANY, DSSpinCtrl::ChangeEvent)
END_EVENT_TABLE()

DynSoft::DSSpinCtrl::DSSpinCtrl(bool *changed) : wxSpinCtrl(), DynSoft::DSChangeInterface(changed) {
	SetChange(changed);
}

DynSoft::DSSpinCtrl::DSSpinCtrl(
	wxWindow *parent,
	wxWindowID id,
	const wxString &value,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	int min,
	int max,
	int initial,
	const wxString &name
) : wxSpinCtrl(
	parent,
	id,
	value,
	pos,
	size,
	style,
	min,
	max,
	initial,
	name
), DynSoft::DSChangeInterface(
	changed
) {
}

DynSoft::DSClassInfo DynSoft::DSSpinCtrl::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SPINCTRL_NAME,
		DS_SPINCTRL_VERSION,
		DS_SPINCTRL_AUTHOR
	);
}

void DynSoft::DSSpinCtrl::ChangeEvent(wxSpinEvent &event) {
	SetChanged(true);
	event.Skip();
}

#endif
