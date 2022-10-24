#include "DSCsv.h"
#include "DSFile.h"

DynSoft::DSCsv::DSCsv(
	const wxChar fieldSeparator,
	const wxChar textSeparator
) : DSLib(
) {
	this->fieldSeparator = fieldSeparator;
	this->textSeparator  = textSeparator;
	this->row            = 0;
}

DynSoft::DSCsv::~DSCsv() {
}

DynSoft::DSClassInfo DynSoft::DSCsv::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CSV_NAME,
		DS_CSV_VERSION,
		DS_CSV_AUTHOR
	);
}

bool DynSoft::DSCsv::SetFile(const wxString &filename) {
	DynSoft::DSFile file(filename, _("r"));
	if(file.IsOpened()) {
		wxString content;
		file.ReadAll(&content);
		file.Close();

		return SetContent(content);
	}

	return false;
}

bool DynSoft::DSCsv::SetContent(wxString &content) {
	if(content.IsEmpty())
		return false;

	row  = 0;
	rows = 0;
	lines.Clear();

	content.Replace(_("\r\n"), _("\n"));
	content.Replace(_("\r"), _("\n"));

	size_t last         = 0;
	long in             = 0;
	const size_t length = content.Length();
	wxChar c;
	for(size_t i = 0; i < length; i++) {
		c = content[i];

		if(c == textSeparator && !in)
			in++;
		else if(c == textSeparator && in)
			in--;
		
		if(in == 0 && (c == '\n' || i == length - 1)) {
			lines.Add(content.Mid(last, i - last));
			last = i + 1;
		}
	}

	rows = lines.GetCount();

	return true;
}

bool DynSoft::DSCsv::GetFields(wxArrayString &fields) {
	if(row == rows)
		return false;

	fields.Clear();
	
	wxString line(lines[row++]);
	wxString field;
	wxChar c;
	long in = 0;

	const size_t length = line.Length();
	for(size_t i = 0; i < length; i++) {
		c = line[i];

		if(c == textSeparator && !in)
			in++;
		else if(c == textSeparator && in)
			in--;

		field += c;
		if(in == 0 && ((i + 1 < length && line[i + 1] == fieldSeparator) || i == length - 1)) {
			if(field.Left(1) == textSeparator && field.Right(1) == textSeparator)
				field = field.Mid(1, field.Length() - 2);
			field.Replace(wxString(textSeparator) + wxString(textSeparator), wxString(textSeparator));
			fields.Add(field);
			field.Clear();
			i++;
		}
	}

	return true;
}

unsigned DynSoft::DSCsv::GetRows() const {
	return rows;
}

unsigned int DynSoft::DSCsv::GetRow() const {
	return row;
}

wxString DynSoft::DSCsv::GetLine(const unsigned row) {
	if(row < rows)
		return lines[row];
	return wxEmptyString;
}
