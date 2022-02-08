#include "DSSetup.h"

#ifdef DS_WITH_GUI
#include "DSListCtrl.h"

IMPLEMENT_DYNAMIC_CLASS(DynSoft::DSListCtrl, wxListCtrl)

BEGIN_EVENT_TABLE(DynSoft::DSListCtrl, wxListCtrl)
	EVT_LIST_DELETE_ITEM(wxID_ANY, DSListCtrl::ChangeEvent)
	EVT_LIST_DELETE_ALL_ITEMS(wxID_ANY, DSListCtrl::ChangeEvent)
END_EVENT_TABLE()

DynSoft::DSListCtrl::DSListCtrlRow::DSListCtrlRow() {
	SetPointer(NULL);
}

DynSoft::DSListCtrl::DSListCtrlRow::DSListCtrlRow(void *pointer) {
	SetPointer(pointer);
}

DynSoft::DSClassInfo DynSoft::DSListCtrl::DSListCtrlRow::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_LISTCTRLROW_NAME,
		DS_LISTCTRLROW_VERSION,
		DS_LISTCTRLROW_AUTHOR
	);
}

void DynSoft::DSListCtrl::DSListCtrlRow::SetPointer(void *pointer) {
	this->pointer = pointer;
}

void *DynSoft::DSListCtrl::DSListCtrlRow::GetPointer() const {
	return pointer;
}

void DynSoft::DSListCtrl::DSListCtrlRow::SetBackgroundColour(const wxColour &backgroundColour) {
	this->backgroundColour = backgroundColour;
}

wxColour DynSoft::DSListCtrl::DSListCtrlRow::GetBackgroundColour() const {
	return backgroundColour;
}

DynSoft::DSListCtrl::DSListCtrl(
) : wxListCtrl(
),  DynSoft::DSLib(
	NULL
) {
	SetChange(NULL);
}

DynSoft::DSListCtrl::DSListCtrl(
	wxWindow *parent,
	wxWindowID id,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxValidator &validator,
	const wxString &name
) : wxListCtrl(
	parent,
	id,
	pos,
	size,
	style,
	validator,
	name
),  DynSoft::DSLib(
	NULL
) {
	SetChange(NULL);
}

DynSoft::DSClassInfo DynSoft::DSListCtrl::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_LISTCTRL_NAME,
		DS_LISTCTRL_VERSION,
		DS_LISTCTRL_AUTHOR
	);
}

bool DynSoft::DSListCtrl::Append(DSListCtrl::DSListCtrlRow *row, const bool removePointer) {
	return Insert(GetItemCount(), row, removePointer);
}

bool DynSoft::DSListCtrl::Prepend(DSListCtrl::DSListCtrlRow *row, const bool removePointer) {
	return Insert(0, row, removePointer);
}

bool DynSoft::DSListCtrl::Insert(int position, DSListCtrl::DSListCtrlRow *row, const bool removePointer) {
	if(
		position < 0 ||
		position > GetItemCount() ||
		row == NULL ||
		row->GetCount() != (unsigned int) GetColumnCount()
	) {
		if(removePointer)
			delete row;
		return false;
	}
	
	wxListItem item;
	item.SetId(position);
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetText(row->GetCount() > 0 ? row->Item(0) : wxString());
	item.SetData(row->GetPointer());
	item.SetBackgroundColour(row->GetBackgroundColour());
	InsertItem(item);

	unsigned int count = GetColumnCount();
	for(unsigned int i = 1; i < count; i++)
		SetItem(position, i, row->Item(i));
	
	if(removePointer)
		delete row;
	
	SetChanged(true);

	return true;
}

long DynSoft::DSListCtrl::GetSingleSelectionPosition() {
	if(GetSelectedItemCount() == 0)
		return -1;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
	GetItem(item);

	return item.GetId();
}

bool DynSoft::DSListCtrl::Set(DSListCtrl::DSListCtrlRow *row, const bool removePointer) {
	bool result = false;
	if(row == NULL || row->GetPointer() == 0)
		return result;
	
	long position = GetPosition(row->GetPointer());
	if(position == wxNOT_FOUND) {
		result = Append(row, removePointer);
	} else {
		wxListItem item;
		item.SetId(position);
		item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
		item.SetText(row->GetCount() > 0 ? row->Item(0) : wxString());
		item.SetData(row->GetPointer());
		item.SetBackgroundColour(row->GetBackgroundColour());
		SetItem(item);

		unsigned int count = GetColumnCount();
		for(unsigned int i = 1; i < count; i++)
			SetItem(position, i, row->Item(i));
		
		if(removePointer)
			delete row;

		result = true;

		SetChanged(true);
	}

	return result;
}

DynSoft::DSListCtrl::DSListCtrlRow *DynSoft::DSListCtrl::GetSingleSelection() {
	DynSoft::DSListCtrl::DSListCtrlRow *row = NULL;
	if(GetSelectedItemCount() == 0)
		return row;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
	GetItem(item);

	row = new DynSoft::DSListCtrl::DSListCtrlRow((void *) item.GetData());

	const int count = GetColumnCount();
	for(int i = 0; i < count; i++) {
		item.SetColumn(i);
		GetItem(item);
		row->Add(item.GetText());
	}

	return row;
}

void *DynSoft::DSListCtrl::GetSingleSelectionPointer() {
	if(GetSelectedItemCount() == 0)
		return NULL;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
	GetItem(item);

	return (void *) item.GetData();
}

long DynSoft::DSListCtrl::GetPosition(void *pointer) {
	if(GetItemCount() == 0)
		return wxNOT_FOUND;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);

	unsigned long count = GetItemCount();
	for(unsigned long i = 0; i < count; i++) {
		item.SetId(i);
		GetItem(item);
		if((void *) item.GetData() == pointer)
			return (long) i;
	}

	return wxNOT_FOUND;
}

void DynSoft::DSListCtrl::CleanUp() {
	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);

	unsigned long count = GetItemCount();
	for(unsigned long i = 0; i < count; i++) {
		item.SetId(i);
		GetItem(item);
		delete (wxUIntPtr *) item.GetData();
	}
	DeleteAllItems();
}

bool DynSoft::DSListCtrl::SetText(const int row, const int col, const wxString &text) {
	if(!ExistField(row, col))
		return false;
	
	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(row);
	item.SetColumn(col);
	item.SetText(text);
	SetItem(item);

	return true;
}

wxString DynSoft::DSListCtrl::GetText(const int row, const int col, bool *found) {
	if(!ExistField(row, col)) {
		if(found != NULL)
			*found = false;
		return wxEmptyString;
	}

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(row);
	item.SetColumn(col);
	GetItem(item);

	return item.GetText();
}

bool DynSoft::DSListCtrl::SetPointer(const int row, const int col, void *pointer) {
	if(!ExistField(row, col))
		return false;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(row);
	item.SetColumn(col);
	item.SetData(pointer);
	SetItem(item);

	return true;
}

void *DynSoft::DSListCtrl::GetPointer(const int row, const int col) {
	if(!ExistField(row, col))
		return NULL;

	wxListItem item;
	item.SetMask(wxLIST_MASK_STATE | wxLIST_MASK_TEXT | wxLIST_MASK_IMAGE | wxLIST_MASK_DATA | wxLIST_MASK_WIDTH | wxLIST_MASK_FORMAT);
	item.SetId(row);
	item.SetColumn(col);
	GetItem(item);

	return (void *) item.GetData();
}

bool DynSoft::DSListCtrl::ExistField(const int row, const int col) {
	return row < GetItemCount() && col < GetColumnCount();
}

bool DynSoft::DSListCtrl::IsRowSelected(const int row) {
	if(row >= GetItemCount())
		return false;

	return GetItemState(row, wxLIST_STATE_SELECTED) != 0; 
}

void DynSoft::DSListCtrl::SelectAll(const bool all) {
	const unsigned int count = GetItemCount();
	for(unsigned int i = 0; i < count; i++)
		if(all)
			SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
		else
			SetItemState(i, 0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
}

void DynSoft::DSListCtrl::ChangeEvent(wxListEvent &event) {
	SetChanged(true);
}

void DynSoft::DSListCtrl::SetChange(bool *changed) {
	this->changed = changed;
}

bool *DynSoft::DSListCtrl::GetChange() const {
	return changed;
}

bool DynSoft::DSListCtrl::SetChanged(const bool changed) {
	const bool ok = GetChange() != NULL;
	if(ok)
		*this->changed = changed;
	return ok;
}

bool DynSoft::DSListCtrl::SelectedItemUp() {
	long position = GetSingleSelectionPosition();
	if(position == wxNOT_FOUND || position == 0)
		return false;
	
	DSListCtrl::DSListCtrlRow *row = GetSingleSelection();
	DeleteItem(position);

	position--;
	Insert(position, row);
	SetSelection(position);

	return true;
}

bool DynSoft::DSListCtrl::SelectedItemDown() {
	long position = GetSingleSelectionPosition();
	if(position == wxNOT_FOUND || position == GetItemCount() - 1)
		return false;
	
	DSListCtrl::DSListCtrlRow *row = GetSingleSelection();
	DeleteItem(position);

	position++;
	Insert(position, row);
	SetSelection(position);

	return true;
}

bool DynSoft::DSListCtrl::SetSelection(const int row) {
	return SetItemState(row, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

#endif /* DS_WITH_GUI */
