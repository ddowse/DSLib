#include "DSTranslation.h"
#include "DSFile.h"
#include "DSConstants.h"

DynSoft::DSTranslation::DSTranslation(const wxString &path, const wxString &languageFile) {
	this->translation = new DSStringHashMap;
	SetPath(path);

	ReadLanguageFile(languageFile);
}

DynSoft::DSTranslation::~DSTranslation() {
	if(translation) {
		delete translation;
		translation = NULL;
	}
}

DynSoft::DSClassInfo DynSoft::DSTranslation::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TRANSLATION_NAME,
		DS_TRANSLATION_VERSION,
		DS_TRANSLATION_AUTHOR
	);
}

void DynSoft::DSTranslation::SetPath(const wxString &path) {
	this->path = path;
}

wxString DynSoft::DSTranslation::GetPath() const {
	return this->path;
}

DSStringHashMap *DynSoft::DSTranslation::GetTranslation() {
	return translation;
}

void DynSoft::DSTranslation::ReadLanguageFile(const wxString &languageFile) {
	wxString tmpPath(languageFile);
	if(!GetPath().IsEmpty())
		tmpPath = GetPath() + DS_PATH_SEPARATOR + languageFile;

	if(DSFile::ExistsFile(tmpPath)) {
		DSFile f(tmpPath, _N("r"));
		if(f.IsOpened()) {
			wxArrayString file;
			file = f.ReadToArrayString();
			wxString line;
			bool msgid = false;
			bool msgstr = false;
			wxString msgidString;
			wxString msgstrString;
			for(unsigned int i = 0; i < file.GetCount(); i++) {
				line = file[i];

				if(line.StartsWith(_N("msgid \""), &line)) {
					msgid = true;
					msgstr = false;
					msgidString = line.Mid(0, line.Length() - 1);
					//DS_PL(line + _N(" > ") + line.Mid(0, line.Length() -1));
					continue;
				}

				if(line.StartsWith(_N("msgstr \""), &line)) {
					msgstr = true;
					msgid = false;
					msgstrString = line.Mid(0, line.Length() - 1);
					//DS_PL(line + _N(" > ") + line.Mid(0, line.Length() -1));
					continue;
				}

				if(line.IsEmpty()) {
					msgid = false;
					msgstr = false;
					if(!msgidString.IsEmpty() && !msgstrString.IsEmpty()) {
						(*translation)[msgidString] = msgstrString;
						//DS_PL(msgidString + _N(" > ") + msgstrString);
					}
					msgstrString.Clear();
					msgidString.Clear();
					continue;
				}
			
				if(msgid) {
					msgidString += line.Mid(1, line.Length() - 2);
					//DS_PL(line + _N(" > ") + line.Mid(1, line.Length() -2));
				}

				if(msgstr) {
					msgstrString += line.Mid(1, line.Length() - 2);
					//DS_PL(line + _N(" > ") + line.Mid(1, line.Length() -2));
				}
			}
		}
	}
}
