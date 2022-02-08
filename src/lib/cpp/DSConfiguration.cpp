#include "DSConfiguration.h"
#include "DSFile.h"

DynSoft::DSConfiguration::DSConfiguration(
	const wxString &commentChars,
	const bool commentsOnlyFromLineStart
) : DSLib(
) {
	SetCommentChars(commentChars);
	SetCommentsOnlyFromLineStart(commentsOnlyFromLineStart);
}

DynSoft::DSClassInfo DynSoft::DSConfiguration::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CONFIGURATION_NAME,
		DS_CONFIGURATION_VERSION,
		DS_CONFIGURATION_AUTHOR
	);
}

bool DynSoft::DSConfiguration::Load(const wxString &filename) {
	if(!DSFile::ExistsFile(filename))
		return false;

	DSFile file(filename, _N("r"));
	if(!file.IsOpened())
		return false;
	
	wxArrayString lines(file.ReadToArrayString());
	file.Close();

	wxString key, value;
	const unsigned int count = lines.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		if(lines[i].IsEmpty())
			continue;

		SplitLine(RemoveComment(lines[i]), &key, &value);
		if(!key.IsEmpty())
			Set(key, value);
	}

	return true;
}

bool DynSoft::DSConfiguration::Save(const wxString &filename, const wxString &lineBreak) {
	DSFile file(filename, _N("w"));
	if(!file.IsOpened())
		return false;

	DSStringHashMap::iterator it;
	for(it = configuration.begin(); it != configuration.end(); ++it) {
		if(!file.Write(it->first + _N(" ") + it->second + lineBreak)) {
			file.Close();
			return false;
		}
	}

	file.Close();

	return true;
}

wxString DynSoft::DSConfiguration::RemoveComment(const wxString &line) {
	const int position = line.Find(GetCommentChars());
	if(position == wxNOT_FOUND)
		return line;
	
	if(GetCommentsOnlyFromLineStart() && position > 0)
		return line;

	return line.Mid(0, position);
}

void DynSoft::DSConfiguration::SplitLine(wxString line, wxString *key, wxString *value) const {
	if(key)
		key->Clear();
	if(value)
		value->Clear();

	line.Trim();
	line.Trim(true);
	if(line.IsEmpty())
		return;

	const int positionSpace = line.Find(_N(" "));
	const int positionTab   = line.Find(_N("\t"));
	int position            = wxNOT_FOUND;
	if(positionSpace != wxNOT_FOUND && positionTab != wxNOT_FOUND)
		position = positionSpace > positionTab ? positionTab: positionSpace;
	else if(positionSpace == wxNOT_FOUND)
		position = positionTab;
	else
		position = positionSpace;

	if(position == wxNOT_FOUND) {
		if(key)
			*key = line;
		return;
	}

	if(key)
		*key = line.Mid(0, position);
	if(!value)
		return;

	*value = line.Mid(position + 1);
	unsigned int i = 0;
	const unsigned int length = value->Length();
	for(; i < length; i++)
		if((*value)[i] != '\t' && (*value)[i] != ' ')
			break;

	*value = value->Mid(i);
}

DynSoft::DSCasts DynSoft::DSConfiguration::Get(const wxString &key, const wxString &valueIfEmpty) {
	return DSCasts(configuration[key].IsEmpty() ? valueIfEmpty : configuration[key]);
}

void DynSoft::DSConfiguration::Set(const wxString &key, const wxString &value) {
	configuration[key] = value;
}

void DynSoft::DSConfiguration::Set(const wxString &key, DSCasts &value) {
	Set(key, value.ToString());
}

void DynSoft::DSConfiguration::SetCommentChars(const wxString &commentChars) {
	this->commentChars = commentChars;
}

wxString DynSoft::DSConfiguration::GetCommentChars() const {
	return commentChars;
}

void DynSoft::DSConfiguration::SetCommentsOnlyFromLineStart(const bool commentsOnlyFromLineStart) {
	this->commentsOnlyFromLineStart = commentsOnlyFromLineStart;
}

bool DynSoft::DSConfiguration::GetCommentsOnlyFromLineStart() const {
	return commentsOnlyFromLineStart;
}
