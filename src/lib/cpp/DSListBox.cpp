#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSListBox.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSListBox, wxListBox)

BEGIN_EVENT_TABLE(DynSoft::DSListBox, wxListBox)
	EVT_LISTBOX(wxID_ANY, DSListBox::ChangeEvent)
END_EVENT_TABLE()

DynSoft::DSListBox::DSListBox(bool *changed) : wxListBox(), DynSoft::DSChangeInterface(changed) {
}

DynSoft::DSListBox::DSListBox(
	wxWindow *parent,
	wxWindowID id,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	int n,
	const wxString choices[],
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxListBox(
	parent,
	id,
	pos,
	size,
	n,
	choices,
	style,
	validator,
	name
), DynSoft::DSChangeInterface(
	changed
) {
}

DynSoft::DSListBox::DSListBox(
	wxWindow *parent,
	wxWindowID id,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	const wxArrayString &choices,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxListBox(
	parent,
	id,
	pos,
	size,
	choices,
	style,
	validator,
	name
), DynSoft::DSChangeInterface(
	changed
) {
}

DynSoft::DSClassInfo DynSoft::DSListBox::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_LISTBOX_NAME,
		DS_LISTBOX_VERSION,
		DS_LISTBOX_AUTHOR
	);
}

void DynSoft::DSListBox::ChangeEvent(wxCommandEvent &event) {
	SetChanged(true);
	event.Skip();
}

#endif
