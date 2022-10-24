#include "DSTable.h"

DynSoft::DSTable::DSTable() : DSLib() {
	rows = new DSTemplateContainer<DSTableRow *>();
}

DynSoft::DSTable::~DSTable() {
	Reset();
	delete rows;
}

void DynSoft::DSTable::Reset() {
	for(unsigned int i = 0; i < GetRowCount(); i++)
		GetRow(i)->Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSTable::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TABLE_NAME,
		DS_TABLE_VERSION,
		DS_TABLE_AUTHOR
	);
}

unsigned int DynSoft::DSTable::AppendRow() {
	rows->Add(new DSTableRow(GetColumnCount()));
	return GetRowCount();
}

unsigned int DynSoft::DSTable::InsertRow(unsigned int position) {
	if(position < GetRowCount()) {
		rows->Insert(new DSTableRow(GetColumnCount()), position);
	} else {
		position -= (GetRowCount() - 1);
		for(unsigned int i = 0; i < position; i++)
			AppendRow();
	}
	return GetRowCount();
}

bool DynSoft::DSTable::RemoveRow(unsigned int position) {
	if(position < GetRowCount()) {
		rows->Remove(position, true);
		return true;
	}

	return false;
}

unsigned int DynSoft::DSTable::GetRowCount() const {
	return rows->GetCount();
}

DynSoft::DSTable::DSTableRow *DynSoft::DSTable::GetRow(unsigned int position) const {
	return rows->Get(position);
}

unsigned int DynSoft::DSTable::AppendColumn() {
	if(GetRowCount() < 1)
		AppendRow();
	for(unsigned int i = 0; i < GetRowCount(); i++)
		GetRow(i)->Add(new DSTableColumn);	
	
	return GetColumnCount();
}

void DynSoft::DSTable::InsertColumn(unsigned int position) {
	if(GetRowCount() == 0)
		AppendRow();

	if(position < GetColumnCount()) {
		for(unsigned int i = 0; i < GetRowCount(); i++)
			GetRow(i)->Insert(new DSTableColumn, position);
	} else {
		position -= (GetColumnCount() - 1);
		for(unsigned int i = 0; i < GetRowCount(); i++) {
			for(unsigned j = 0; j < position; j++)
				GetRow(i)->Add(new DSTableColumn);
		}
	}
}

bool DynSoft::DSTable::RemoveColumn(unsigned int position) {
	if(position < GetColumnCount()) {
		for(unsigned int i = 0; i < GetRowCount(); i++)
			GetRow(i)->Remove(position, true);
		return true;
	}

	return false;
}

unsigned int DynSoft::DSTable::GetColumnCount() const {
	if(GetRowCount() > 0)
		return GetRow(0)->GetCount();
	return 0;
}

int DynSoft::DSTable::GetColumnPosition(unsigned int row, const wxString &content) {
	for(unsigned int i = 0; i < GetColumnCount(); i++)
		if(GetCell(row, i)->GetContent() == content)
			return i;

	return -1;
}

DynSoft::DSTable::DSTableColumn *DynSoft::DSTable::GetCell(
	const unsigned int row,
	const unsigned int column
) const {
	if(row >= GetRowCount() || column >= GetColumnCount()) {
		return (DSTableColumn *) NULL;
	}
	
	return GetRow(row)->Get(column);
}

wxString DynSoft::DSTable::GetContent(
	const unsigned int row,
	const wxString &column
) {
	return GetContent(row, GetColumnPosition(0, column));
}

wxString DynSoft::DSTable::GetContent(
	const unsigned int row,
	const unsigned int column
) {
	DSTableColumn *tmp = GetCell(row, column);
	if(tmp)
		return tmp->GetContent();
	return wxEmptyString;
}
