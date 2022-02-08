#include "DSSetup.h"

#ifdef DS_WITH_GUI
#include "DSBind.h"
#include "DSDateTime.h"

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindType::DSBindType(const wxString &key, const unsigned int kind) : DSType() {
	this->key  = key;
	this->kind = kind;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_TYPE_NAME,
		DS_BIND_TYPE_VERSION,
		DS_BIND_TYPE_AUTHOR
	);
}

wxString DynSoft::DSBind::DSBindType::GetKey() const {
	return key;
}

unsigned int DynSoft::DSBind::DSBindType::GetKind() const {
	return kind;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindTextCtrlType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindTextCtrlType::DSBindTextCtrlType(const wxString &key, wxTextCtrl *value) : DSBindType(key) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindTextCtrlType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_TEXTCTRL_TYPE_NAME,
		DS_BIND_TEXTCTRL_TYPE_VERSION,
		DS_BIND_TEXTCTRL_TYPE_AUTHOR
	);
}

wxTextCtrl *DynSoft::DSBind::DSBindTextCtrlType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindComboBoxType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindComboBoxType::DSBindComboBoxType(const wxString &key, wxComboBox *value, const unsigned int kind) : DSBindType(key, kind) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindComboBoxType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_COMBOBOX_TYPE_NAME,
		DS_BIND_COMBOBOX_TYPE_VERSION,
		DS_BIND_COMBOBOX_TYPE_AUTHOR
	);
}

wxComboBox *DynSoft::DSBind::DSBindComboBoxType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindListBoxType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindListBoxType::DSBindListBoxType(const wxString &key, wxListBox *value, const unsigned int kind) : DSBindType(key, kind) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindListBoxType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_LISTBOX_TYPE_NAME,
		DS_BIND_LISTBOX_TYPE_VERSION,
		DS_BIND_LISTBOX_TYPE_AUTHOR
	);
}

wxListBox *DynSoft::DSBind::DSBindListBoxType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindSpinCtrlType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindSpinCtrlType::DSBindSpinCtrlType(const wxString &key, wxSpinCtrl *value) : DSBindType(key) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindSpinCtrlType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_SPINCTRL_TYPE_NAME,
		DS_BIND_SPINCTRL_TYPE_VERSION,
		DS_BIND_SPINCTRL_TYPE_AUTHOR
	);
}

wxSpinCtrl *DynSoft::DSBind::DSBindSpinCtrlType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindCheckBoxType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindCheckBoxType::DSBindCheckBoxType(const wxString &key, wxCheckBox *value) : DSBindType(key) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindCheckBoxType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_CHECKBOX_TYPE_NAME,
		DS_BIND_CHECKBOX_TYPE_VERSION,
		DS_BIND_CHECKBOX_TYPE_AUTHOR
	);
}

wxCheckBox *DynSoft::DSBind::DSBindCheckBoxType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBindDatePickerCtrlType
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBindDatePickerCtrlType::DSBindDatePickerCtrlType(const wxString &key, wxDatePickerCtrl *value) : DSBindType(key) {
	this->value = value;
}

DynSoft::DSClassInfo DynSoft::DSBind::DSBindDatePickerCtrlType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_DATEPICKERCTRL_TYPE_NAME,
		DS_BIND_DATEPICKERCTRL_TYPE_VERSION,
		DS_BIND_DATEPICKERCTRL_TYPE_AUTHOR
	);
}

wxDatePickerCtrl *DynSoft::DSBind::DSBindDatePickerCtrlType::GetValue() {
	return value;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////
//// DSBind
////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

DynSoft::DSBind::DSBind(DSEntity *entity) : DSLib() {
	this->entity = entity;
}

DynSoft::DSBind::~DSBind() {
	textCtrlContainer.Clear();
	comboBoxContainer.Clear();
	listBoxContainer.Clear();
	spinCtrlContainer.Clear();
	checkBoxContainer.Clear();
	datePickerCtrlContainer.Clear();
}

DynSoft::DSClassInfo DynSoft::DSBind::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BIND_NAME,
		DS_BIND_VERSION,
		DS_BIND_AUTHOR
	);
}

void DynSoft::DSBind::Bind(const wxString &key, wxTextCtrl *value) {
	Get(key, true);
	textCtrlContainer.Add(new DSBindTextCtrlType(key, value));
}

void DynSoft::DSBind::Bind(const wxString &key, wxComboBox *value, const unsigned int kind) {
	Get(key, true);
	comboBoxContainer.Add(new DSBindComboBoxType(key, value, kind));
}

void DynSoft::DSBind::Bind(const wxString &key, wxListBox *value, const unsigned int kind) {
	Get(key, true);
	listBoxContainer.Add(new DSBindListBoxType(key, value, kind));
}

void DynSoft::DSBind::Bind(const wxString &key, wxSpinCtrl *value) {
	Get(key, true);
	spinCtrlContainer.Add(new DSBindSpinCtrlType(key, value));
}

void DynSoft::DSBind::Bind(const wxString &key, wxCheckBox *value) {
	Get(key, true);
	checkBoxContainer.Add(new DSBindCheckBoxType(key, value));
}

void DynSoft::DSBind::Bind(const wxString &key, wxDatePickerCtrl *value) {
	Get(key, true);
	datePickerCtrlContainer.Add(new DSBindDatePickerCtrlType(key, value));
}

wxControl *DynSoft::DSBind::Get(const wxString &key, const bool removeIfFound) {
	// TextCtrl
	DynSoft::DSBind::DSBindTextCtrlType *textCtrlType = NULL;
	unsigned int count = textCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		textCtrlType = textCtrlContainer.Get(i);
		if(textCtrlType && textCtrlType->GetKey() == key) {
			wxTextCtrl *tmp = textCtrlType->GetValue();
			if(removeIfFound)
				textCtrlContainer.Remove(i);
			return tmp;
		}
	}

	// ComboBox
	DynSoft::DSBind::DSBindComboBoxType *comboBoxType = NULL;
	count = comboBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		comboBoxType = comboBoxContainer.Get(i);
		if(comboBoxType && comboBoxType->GetKey() == key) {
			wxComboBox *tmp = comboBoxType->GetValue();
			if(removeIfFound)
				comboBoxContainer.Remove(i);
			return tmp;
		}
	}

	// ListBox
	DynSoft::DSBind::DSBindListBoxType *listBoxType = NULL;
	count = listBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		listBoxType = listBoxContainer.Get(i);
		if(listBoxType && listBoxType->GetKey() == key) {
			wxListBox *tmp = listBoxType->GetValue();
			if(removeIfFound)
				listBoxContainer.Remove(i);
			return tmp;
		}
	}

	// SpinCtrl
	DynSoft::DSBind::DSBindSpinCtrlType *spinCtrlType = NULL;
	count = spinCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		spinCtrlType = spinCtrlContainer.Get(i);
		if(spinCtrlType && spinCtrlType->GetKey() == key) {
			wxSpinCtrl *tmp = spinCtrlType->GetValue();
			if(removeIfFound)
				spinCtrlContainer.Remove(i);
			return tmp;
		}
	}

	// CheckBox
	DynSoft::DSBind::DSBindCheckBoxType *checkBoxType = NULL;
	count = checkBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		checkBoxType = checkBoxContainer.Get(i);
		if(checkBoxType && checkBoxType->GetKey() == key) {
			wxCheckBox *tmp = checkBoxType->GetValue();
			if(removeIfFound)
				checkBoxContainer.Remove(i);
			return tmp;
		}
	}

	// DatePickerCtrl
	DynSoft::DSBind::DSBindDatePickerCtrlType *datePickerCtrlType = NULL;
	count = datePickerCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		datePickerCtrlType = datePickerCtrlContainer.Get(i);
		if(datePickerCtrlType && datePickerCtrlType->GetKey() == key) {
			wxDatePickerCtrl *tmp = datePickerCtrlType->GetValue();
			if(removeIfFound)
				datePickerCtrlContainer.Remove(i);
			return tmp;
		}
	}

	return NULL;
}

void DynSoft::DSBind::Push() {
	// TextCtrl
	DynSoft::DSBind::DSBindTextCtrlType *textCtrlType = NULL;
	unsigned int count = textCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		textCtrlType = textCtrlContainer.Get(i);
		if(textCtrlType && textCtrlType->GetValue() && entity->Get(textCtrlType->GetKey())) {
			if(entity->Get(textCtrlType->GetKey())->GetType() == DSEntity::DSEntityType::DS_RESULT_TYPE_DSCURRENCY)
				textCtrlType->GetValue()->SetValue(entity->Get(textCtrlType->GetKey())->ToCurrency().ToString());
			else
				textCtrlType->GetValue()->SetValue(entity->Get(textCtrlType->GetKey())->ToString());
		}
	}

	// ComboBox
	DynSoft::DSBind::DSBindComboBoxType *comboBoxType = NULL;
	count = comboBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		comboBoxType = comboBoxContainer.Get(i);
		if(comboBoxType && comboBoxType->GetValue() && entity->Get(comboBoxType->GetKey())) {
			switch(comboBoxType->GetKind()) {
				case VALUE:
					comboBoxType->GetValue()->SetValue(entity->Get(comboBoxType->GetKey())->ToString());
					break;
				case SELECTION:
					comboBoxType->GetValue()->SetSelection(entity->Get(comboBoxType->GetKey())->ToInt());
					break;
				case STRING:
					comboBoxType->GetValue()->SetStringSelection(entity->Get(comboBoxType->GetKey())->ToString());
					break;
			}
		}
	}

	// ListBox
	DynSoft::DSBind::DSBindListBoxType *listBoxType = NULL;
	count = listBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		listBoxType = listBoxContainer.Get(i);
		if(listBoxType && listBoxType->GetValue() && entity->Get(listBoxType->GetKey())) {
			switch(listBoxType->GetKind()) {
				case SELECTION:
					listBoxType->GetValue()->SetSelection(entity->Get(listBoxType->GetKey())->ToInt());
					break;
				case STRING:
					listBoxType->GetValue()->SetStringSelection(entity->Get(listBoxType->GetKey())->ToString());
					break;
			}
		}
	}

	// SpinCtrl
	DynSoft::DSBind::DSBindSpinCtrlType *spinCtrlType = NULL;
	count = spinCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		spinCtrlType = spinCtrlContainer.Get(i);
		if(spinCtrlType && spinCtrlType->GetValue() && entity->Get(spinCtrlType->GetKey()))
			spinCtrlType->GetValue()->SetValue(entity->Get(spinCtrlType->GetKey())->ToInt());
	}

	// CheckBox
	DynSoft::DSBind::DSBindCheckBoxType *checkBoxType = NULL;
	count = checkBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		checkBoxType = checkBoxContainer.Get(i);
		if(checkBoxType && checkBoxType->GetValue() && entity->Get(checkBoxType->GetKey()))
			checkBoxType->GetValue()->SetValue(entity->Get(checkBoxType->GetKey())->ToBool());
	}

	// DatePickerCtrl
	DSDateTime dateTime;
	wxString timestamp;
	DynSoft::DSBind::DSBindDatePickerCtrlType *datePickerCtrlType = NULL;
	count = datePickerCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		datePickerCtrlType = datePickerCtrlContainer.Get(i);
		if(datePickerCtrlType && datePickerCtrlType->GetValue() && entity->Get(datePickerCtrlType->GetKey())) {
			dateTime.SetAmericanDate(entity->Get(datePickerCtrlType->GetKey())->ToString());
			datePickerCtrlType->GetValue()->SetValue(dateTime.GetWxDateTime());
		}
	}
}

void DynSoft::DSBind::Pull() {
	// TextCtrl
	DynSoft::DSBind::DSBindTextCtrlType *textCtrlType = NULL;
	unsigned int count = textCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		textCtrlType = textCtrlContainer.Get(i);
		if(textCtrlType && textCtrlType->GetValue() && entity->Get(textCtrlType->GetKey()))
			entity->SetValue(textCtrlType->GetKey(), textCtrlType->GetValue()->GetValue());
	}

	// ComboBox
	DynSoft::DSBind::DSBindComboBoxType *comboBoxType = NULL;
	count = comboBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		comboBoxType = comboBoxContainer.Get(i);
		if(comboBoxType && comboBoxType->GetValue() && entity->Get(comboBoxType->GetKey())) {
			switch(comboBoxType->GetKind()) {
				case VALUE:
					entity->SetValue(comboBoxType->GetKey(), comboBoxType->GetValue()->GetValue());
					break;
				case SELECTION:
					entity->SetValue(comboBoxType->GetKey(), comboBoxType->GetValue()->GetSelection());
					break;
				case STRING:
					entity->SetValue(comboBoxType->GetKey(), comboBoxType->GetValue()->GetStringSelection());
					break;
			}
		}
	}

	// ListBox
	DynSoft::DSBind::DSBindListBoxType *listBoxType = NULL;
	count = listBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		listBoxType = listBoxContainer.Get(i);
		if(listBoxType && listBoxType->GetValue() && entity->Get(listBoxType->GetKey())) {
			switch(listBoxType->GetKind()) {
				case SELECTION:
					entity->SetValue(listBoxType->GetKey(), listBoxType->GetValue()->GetSelection());
					break;
				case STRING:
					entity->SetValue(listBoxType->GetKey(), listBoxType->GetValue()->GetStringSelection());
					break;
			}
		}
	}

	// SpinCtrl
	DynSoft::DSBind::DSBindSpinCtrlType *spinCtrlType = NULL;
	count = spinCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		spinCtrlType = spinCtrlContainer.Get(i);
		if(spinCtrlType && spinCtrlType->GetValue() && entity->Get(spinCtrlType->GetKey()))
			entity->SetValue(spinCtrlType->GetKey(), spinCtrlType->GetValue()->GetValue());
	}

	// CheckBox
	DynSoft::DSBind::DSBindCheckBoxType *checkBoxType = NULL;
	count = checkBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		checkBoxType = checkBoxContainer.Get(i);
		if(checkBoxType && checkBoxType->GetValue() && entity->Get(checkBoxType->GetKey()))
			entity->SetValue(checkBoxType->GetKey(), checkBoxType->GetValue()->GetValue());
	}

	// DatePickerCtrl
	DSDateTime dateTime;
	DynSoft::DSBind::DSBindDatePickerCtrlType *datePickerCtrlType = NULL;
	count = datePickerCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		datePickerCtrlType = datePickerCtrlContainer.Get(i);
		if(datePickerCtrlType && datePickerCtrlType->GetValue() && entity->Get(datePickerCtrlType->GetKey())) {
			dateTime.SetWxDateTime(datePickerCtrlType->GetValue()->GetValue());
			entity->SetValue(datePickerCtrlType->GetKey(), dateTime.ToDatabaseDateTime());
		}
	}
}

DynSoft::DSEntity *DynSoft::DSBind::GetEntity() const {
	return entity;
}

void DynSoft::DSBind::EnableAll(const bool enable) {
	// TextCtrl
	DynSoft::DSBind::DSBindTextCtrlType *textCtrlType = NULL;
	unsigned int count = textCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		textCtrlType = textCtrlContainer.Get(i);
		if(textCtrlType && textCtrlType->GetValue())
			textCtrlType->GetValue()->Enable(enable);
	}

	// ComboBox
	DynSoft::DSBind::DSBindComboBoxType *comboBoxType = NULL;
	count = comboBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		comboBoxType = comboBoxContainer.Get(i);
		if(comboBoxType && comboBoxType->GetValue())
			comboBoxType->GetValue()->Enable(enable);
	}

	// ListBox
	DynSoft::DSBind::DSBindListBoxType *listBoxType = NULL;
	count = listBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		listBoxType = listBoxContainer.Get(i);
		if(listBoxType && listBoxType->GetValue())
			listBoxType->GetValue()->Enable(enable);
	}

	// SpinCtrl
	DynSoft::DSBind::DSBindSpinCtrlType *spinCtrlType = NULL;
	count = spinCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		spinCtrlType = spinCtrlContainer.Get(i);
		if(spinCtrlType && spinCtrlType->GetValue())
			spinCtrlType->GetValue()->Enable(enable);
	}

	// CheckBox
	DynSoft::DSBind::DSBindCheckBoxType *checkBoxType = NULL;
	count = checkBoxContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		checkBoxType = checkBoxContainer.Get(i);
		if(checkBoxType && checkBoxType->GetValue())
			checkBoxType->GetValue()->Enable(enable);
	}

	// DatePickerCtrl
	DSDateTime dateTime;
	DynSoft::DSBind::DSBindDatePickerCtrlType *datePickerCtrlType = NULL;
	count = datePickerCtrlContainer.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		datePickerCtrlType = datePickerCtrlContainer.Get(i);
		if(datePickerCtrlType && datePickerCtrlType->GetValue())
			datePickerCtrlType->GetValue()->Enable(enable);
	}
}

#endif
