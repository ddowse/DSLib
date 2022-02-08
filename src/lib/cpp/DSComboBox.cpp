#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSComboBox.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSComboBox, wxComboBox)

//#if wxMAJOR_VERSION < 3
	BEGIN_EVENT_TABLE(DynSoft::DSComboBox, wxComboBox)
		EVT_TEXT(wxID_ANY, DSComboBox::ChangeEvent)
		EVT_COMBOBOX(wxID_ANY, DSComboBox::ChangeEvent)
	END_EVENT_TABLE()
//#endif

DynSoft::DSComboBox::DSComboBox(bool *changed) : wxComboBox(), DynSoft::DSChangeInterface(changed) {
	#if wxMAJOR_VERSION < 3
		SetMaxLength(0);
	#endif
}

DynSoft::DSComboBox::DSComboBox(
	wxWindow *parent,
	wxWindowID id,
	const wxString &value,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	int n,
	const wxString choices[],
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxComboBox(
	parent,
	id,
	value,
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
	#if wxMAJOR_VERSION < 3
		SetMaxLength(0);
	#endif
}

DynSoft::DSComboBox::DSComboBox(
	wxWindow *parent,
	wxWindowID id,
	const wxString &value,
	bool *changed,
	const wxPoint &pos,
	const wxSize &size,
	const wxArrayString &choices,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxComboBox(
	parent,
	id,
	value,
	pos,
	size,
	choices,
	style,
	validator,
	name
), DynSoft::DSChangeInterface(
	changed
) {
	#if wxMAJOR_VERSION < 3
		SetMaxLength(0);
	#endif
}

DynSoft::DSClassInfo DynSoft::DSComboBox::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_COMBOBOX_NAME,
		DS_COMBOBOX_VERSION,
		DS_COMBOBOX_AUTHOR
	);
}

#if wxMAJOR_VERSION < 3
	void DynSoft::DSComboBox::ChangeEvent(wxCommandEvent &event) {
		bool ok = true;

		if(maxLength != 0) {
			wxString temp(GetValue() + event.GetString());
			if(temp.Length() > maxLength)
				ok = false;
		}

		if(ok)
			SetChanged(true);

		event.Skip();
	}

	void DynSoft::DSComboBox::SetMaxLength(const unsigned int maxLength) {
		this->maxLength = maxLength;
	}

	unsigned int DynSoft::DSComboBox::GetMaxLength() const {
		return maxLength;
	}
#else
	void DynSoft::DSComboBox::ChangeEvent(wxCommandEvent &event) {
		SetChanged(true);
		event.Skip();
	}
#endif

#endif
