#include "DSLib.h"
#include "DSCasts.h"
#include "DSFile.h"
#include <wx/tokenzr.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DynSoft::DSLib::DSLib(DSDatabase *db) {
	this->db = db;
}

DynSoft::DSLib::~DSLib() {
}

DynSoft::DSClassInfo DynSoft::DSLib::GetInfo() {
	return DynSoft::DSClassInfo(
		DS_LIB_NAME,
		DS_LIB_VERSION,
		DS_LIB_AUTHOR
	);
}

void DynSoft::DSLib::SetDatabase(DSDatabase *db) {
	this->db = db;
}

DynSoft::DSDatabase *DynSoft::DSLib::GetDatabase() const {
	return db;
}

wxArrayString DynSoft::DSLib::Split(const wxString &string, wxChar delimiter) {
	wxArrayString splitted;

	wxStringTokenizer tkz(string, delimiter, wxTOKEN_RET_EMPTY_ALL);
	while(tkz.HasMoreTokens())
		splitted.Add(tkz.GetNextToken());

	return splitted;
}

unsigned int DynSoft::DSLib::ParseSearchWords(
	const wxString &search,
	wxArrayString *relations,
	wxArrayString *words
) {
	unsigned int counter = 0;

	if(relations == NULL || words == NULL)
		return counter;

	wxString tmp;
	wxChar c;
	unsigned int describer = 0;

	for(unsigned int i = 0; i < search.Length(); i++) {
		c = search[i];

		if(c == '+' || c == '-' || c == ' ' || i == 0) {
			if(i == 0 && c != '+' && c != '-') {
				describer = DS_LIB_DESCRIBER_OR;
			} else {
				describer = c;
				continue;
			}
		}
	
		for(; i < search.Length(); i++) {
			c = search[i];
			if(c == '+' || c == '-' || c == ' ') {
				if(i > 0)
					i--;
				break;
			} else if(c == '"') {
				i++;
				for(; i < search.Length(); i++) {
					c = search[i];
					if(c == '"' && search[i - i] != '\\')
						break;
					tmp.Append(c);
				}
			} else {
				tmp.Append(c);
			}
		}

		if(!tmp.IsEmpty()) {
			switch(describer) {
				case DS_LIB_DESCRIBER_AND:
					relations->Add(_N("AND"));
					break;
				case DS_LIB_DESCRIBER_NOT:
					relations->Add(_N("NOT"));
					break;
				case DS_LIB_DESCRIBER_OR:
				default:
					relations->Add(_N("OR"));
					break;
			}

			words->Add(tmp);
		}
		tmp.Clear();

		counter++;
	}
	
	return counter;
}

bool DynSoft::DSLib::PrintArrayString(wxArrayString *messages) {
	if(messages != NULL) {
		for(unsigned int i = 0; i < messages->GetCount(); i++)
			PrintLine((*messages)[i]);
		return true;
	}

	return false;
}

void DynSoft::DSLib::Print(wxString message) {
	std::cout << (const char *) message.mb_str(wxConvUTF8) << std::flush;
}

void DynSoft::DSLib::Print(const char *message) {
	std::cout << message << std::flush;
}

void DynSoft::DSLib::PrintLine(wxString message) {
	std::cout << static_cast<const char *>(message.mb_str(wxConvUTF8)) << std::endl;
}

void DynSoft::DSLib::PrintLineError(wxString message) {
	std::cerr << static_cast<const char *>(message.mb_str(wxConvUTF8)) << std::endl;
}

void DynSoft::DSLib::PrintLine(const char *message) {
	std::cout << message << std::endl;
}

void DynSoft::DSLib::PrintLineError(const char *message) {
	std::cerr << message << std::endl;
}

wxString DynSoft::DSLib::ReadLine(const wxString &input) {
	if(!input.IsEmpty())
		Print(input);

	char c = 0;
	int counter = 1;
	char *tmp = (char *) malloc(sizeof(char *));
	tmp[0] = '\0';
	while((c = fgetc(stdin)) != '\n') {
		tmp = (char *) realloc(tmp, sizeof(char *) * ++counter);
		strncat(tmp, &c, 1);
	}
	wxString result;
	result = DSCasts::ToString(tmp);
	free(tmp);
	tmp = NULL;

	return result;
}

int DynSoft::DSLib::LoadResource(const wxString &filename) {
	return LoadResourceFile(filename, &resource);
}

int DynSoft::DSLib::AppendResource(const wxString &filename) {
	ClearResource();
	return LoadResourceFile(filename, &resource);
}

unsigned int DynSoft::DSLib::ClearResource() {
	unsigned int size = (unsigned int) resource.size();
	resource.clear();
	return size;
}

DSStringHashMap *DynSoft::DSLib::GetResource() {
	return &resource;
}

wxString DynSoft::DSLib::GetResourceByName(const wxString &name) {
	return resource[name];
}

wxString DynSoft::DSLib::res(const wxString &name) {
	return GetResourceByName(name);
}

int DynSoft::DSLib::LoadResourceFile(const wxString &filename, DSStringHashMap *resource) {
	int result = OK;
	DynSoft::DSFile file(filename, _N("r"));
	if(file.IsOpened()) {
		wxArrayString lines(file.ReadToArrayString());
	
		wxString identifier;
		wxString line;
		wxString tmp;
		const unsigned int count = lines.GetCount();
		const unsigned int stop  = count - 2;
		for(unsigned int i = 0; i < count; i++) {
			line = lines[i];
			if(!line.IsEmpty()) {
				if(line[0] != '\t' || i == stop) {
					if(i == stop)
						tmp.Append(line.Remove(0, 1) + _N("\n"));
					if(!identifier.IsEmpty()) {
						identifier.Replace(_N("\r"), _N(""));
						identifier.Replace(_N("\n"), _N(""));
						(*resource)[identifier] = tmp;
						tmp.Clear();
						result++;
					}
					identifier = line;
				} else {
					tmp.Append(line.Remove(0, 1) + _N("\n"));
				}
			}
		}

		file.Close();
	} else {
		result = ERROR_FILE;
	}

	return result;
}

wxString DynSoft::DSLib::VersionToString(
	const unsigned int major,
	const unsigned int minor,
	const unsigned int patch
) {
	return wxString::Format(_N("%i.%i.%i"), major, minor, patch);
}

bool DynSoft::DSLib::IsGreaterVersion(const wxString &first, const wxString &second) {
	return CompareVersion(first, second, GREATER);
}

bool DynSoft::DSLib::IsEqualVersion(const wxString &first, const wxString &second) {
	return CompareVersion(first, second, EQUAL);
}

bool DynSoft::DSLib::IsLesserVersion(const wxString &first, const wxString &second) {
	return CompareVersion(first, second, LESSER);
}

bool DynSoft::DSLib::CompareVersion(const wxString &first, const wxString &second, const int flag) {
	unsigned int firstMajor = 0, firstMinor = 0, firstPatch = 0;
	unsigned int secondMajor = 0, secondMinor = 0, secondPatch = 0;
	if(
		!SplitVersion(first, firstMajor, firstMinor, firstPatch) || 
		!SplitVersion(second, secondMajor, secondMinor, secondPatch)
	) {
		return false;
	}
	bool result = false;
	switch(flag) {
		case EQUAL:
			result = firstMajor == secondMajor && firstMinor == secondMinor && firstPatch == secondPatch;
			break;
		case GREATER:
			if(firstMajor > secondMajor) {
				result = true;
			 } else {
			 	if(firstMinor > secondMinor && firstMajor >= secondMajor) {
					result = true;
				} else {
					if(firstPatch > secondPatch && firstMinor >= secondMinor && firstMajor >= secondMajor) {
						result = true;
					}
				}
			 }
			break;
		case LESSER:
			if(firstMajor < secondMajor) {
				result = true;
			 } else {
			 	if(firstMinor < secondMinor && firstMajor <= secondMajor) {
					result = true;
				} else {
					if(firstPatch < secondPatch && firstMinor <= secondMinor && firstMajor <= secondMajor) {
						result = true;
					}
				}
			 }
			break;
	};
	return result;
}

bool DynSoft::DSLib::SplitVersion(
	const wxString &version, 
	unsigned int &major,
	unsigned int &minor,
	unsigned int &patch
) {
	if(IsValidVersion(version)) {
		wxArrayString splittedVersion(DynSoft::DSLib::Split(version, '.'));
		major = DynSoft::DSCasts::ToUnsignedInt(splittedVersion[0]);
		minor = DynSoft::DSCasts::ToUnsignedInt(splittedVersion[1]);
		patch = DynSoft::DSCasts::ToUnsignedInt(splittedVersion[2]);
		return true;
	}

	return false;
}

bool DynSoft::DSLib::IsValidVersion(const wxString &version) {
	const unsigned int count = version.Length();
	unsigned int dots = 0;
	wxChar c;
	for(unsigned int i = 0; i < count; ++i) {
		c = version[i];
		if(c == '.' && i > 0 && i < count - 1) {
			if(++dots > 2)
				return false;
		} else if(c < '0' || c > '9') {
			return false;
		}
	}

	return true;
}

wxString DynSoft::DSLib::HtmlSpecialChars(wxString html) {
	html.Replace(_N("&"), _N("&amp;"));
	html.Replace(_N("\""), _N("&quot;"));
	html.Replace(_N("'"), _N("&#039;"));
	html.Replace(_N("<"), _N("&lt;"));
	html.Replace(_N(">"), _N("&gt;"));

	return html;
}

wxString DynSoft::DSLib::nl2br(wxString str) {
	str.Replace(_N("\r\n"), _N("<br />"));
	str.Replace(_N("\r"), _N("<br />"));
	str.Replace(_N("\n"), _N("<br />"));
	return str;
}
