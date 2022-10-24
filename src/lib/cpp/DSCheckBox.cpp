#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSCheckBox.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSCheckBox, wxCheckBox)

BEGIN_EVENT_TABLE(DynSoft::DSCheckBox, wxCheckBox)
	EVT_CHECKBOX(wxID_ANY, DSCheckBox::ChangeEvent)
END_EVENT_TABLE()

DynSoft::DSCheckBox::DSCheckBox(bool *changed) : wxCheckBox(), DynSoft::DSChangeInterface(changed) {
}

DynSoft::DSCheckBox::DSCheckBox(
	wxWindow* parent,
	wxWindowID id,
	const wxString &value,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxCheckBox(
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
}

DynSoft::DSClassInfo DynSoft::DSCheckBox::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CHECKBOX_NAME,
		DS_CHECKBOX_VERSION,
		DS_CHECKBOX_AUTHOR
	);
}

void DynSoft::DSCheckBox::ChangeEvent(wxCommandEvent &event) {
	SetChanged(true);
	event.Skip();
}

#endif
