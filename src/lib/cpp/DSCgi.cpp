#include "DSCgi.h"
#include "DSCasts.h"
#include "DSDebug.h"
#include <wx/tokenzr.h>
#include <wx/file.h>
#include <wx/ffile.h>
#include <wx/regex.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <fcgi_stdio.h>
#include <wx/uri.h>

DynSoft::DSCgi::DSCgi(const bool useUnicode, const wxString &uploadDirectory) : DSLib() {
	this->useUnicode = useUnicode;
	SetUploadDirectory(uploadDirectory);
	MakeRequests();
}

DynSoft::DSClassInfo DynSoft::DSCgi::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CGI_NAME,
		DS_CGI_VERSION,
		DS_CGI_AUTHOR
	);
}

void DynSoft::DSCgi::SetUploadDirectory(const wxString &uploadDirectory) {
	if(uploadDirectory.IsEmpty()) {
		this->uploadDirectory = _N("/tmp/");
	} else {
		this->uploadDirectory = uploadDirectory;
		const unsigned int length = this->uploadDirectory.Length();
		if(length > 0 && this->uploadDirectory[length - 1] != '/')
		this->uploadDirectory += '/';
	}
}

wxString DynSoft::DSCgi::GetUploadDirectory() const {
	return uploadDirectory;
}

int DynSoft::DSCgi::GetMethod() {
	char *request = getenv("REQUEST_METHOD");
	if(request == NULL)
		return DS_CGI_METHOD_UNKNOWN;
	else if(strcmp(request, "GET") == 0)
		return DS_CGI_METHOD_GET;
	else if(strcmp(request, "POST") == 0)
		return DS_CGI_METHOD_POST;
	return DS_CGI_METHOD_UNKNOWN;
}

void DynSoft::DSCgi::MakeRequests() {
	rq.clear();
	switch(GetMethod()) {
		case DS_CGI_METHOD_GET:
			MakeRequestGet();
			break;
		case DS_CGI_METHOD_POST:
			MakeRequestPost();
			break;
	}
}

void DynSoft::DSCgi::MakeRequestGet() {
	char *get = getenv("QUERY_STRING");
	if(get != NULL)
		MakeRequest(DSCasts::ToString(get), _N("&;"));
}

void DynSoft::DSCgi::MakeRequestPost() {
	char *length = getenv("CONTENT_LENGTH");
	if(length == NULL)
		return;
	
	unsigned long size = DSCasts::ToUnsignedLong(length);
	if(size <= 0)
		return;
	
	char *post = NULL;
	int c;

	size = 0;
	while((c = getchar()) != EOF) {
		post = (char *) realloc(post, sizeof(char *) * (size + 1));
		post[size++] = (char) c;
	}

	wxString tmpId;
	if(StripContentType(GetVariable(_("CONTENT_TYPE")), tmpId)) {
		MakeRequestMultiform(post, size);
	} else {
		post = (char *) realloc(post, sizeof(char *) * (size + 1));
		post[size++] = '\0';

		MakeRequest(DSCasts::ToString(post), _N("&"));
	}

	free(post);

/*	char *length = getenv("CONTENT_LENGTH");
	if(length == NULL)
			return;

	unsigned long size = DSCasts::ToUnsignedLong(length);
	if(size <= 0)
			return;

	char post [size + 1];

	if(fgets(post, size + 1, stdin) != NULL) {
		FILE *f = fopen("/tmp/multipart.txt", "w");
		fwrite(post, size, sizeof(char), f);
		fclose(f);
		MakeRequest(DSCasts::ToString(post), _N("&"));
	}*/
}

void DynSoft::DSCgi::MakeRequest(const wxString &request, const wxString &token) {
	wxStringTokenizer stkAmp(request, token);

	wxString tmp;
	wxString tmp2;
	int pos = -1;
	while(stkAmp.HasMoreTokens()) {
		tmp = stkAmp.GetNextToken();
		pos = tmp.Find(_N("="));
		if(pos >= 0) {
			tmp2 = tmp.Mid(pos + 1);
			if(useUnicode) {
				if(!rq[tmp.Mid(0, pos)].IsEmpty()) {
					rq[tmp.Mid(0, pos)] += '\23';
					rq[tmp.Mid(0, pos)] += Hex2Ascii(tmp2);
				} else {
					rq[tmp.Mid(0, pos)] = Hex2Ascii(tmp2);
				}
			} else {
				wxURI uri(tmp2);
				if(!rq[tmp.Mid(0, pos)].IsEmpty()) {
					rq[tmp.Mid(0, pos)] += '\23';
					rq[tmp.Mid(0, pos)] += uri.BuildUnescapedURI();
				} else {
					rq[tmp.Mid(0, pos)] = uri.BuildUnescapedURI();
				}
			}
		}
	}
}

bool DynSoft::DSCgi::StripContentType(
	const wxString &contentType,
	wxString &id
) {
	if(contentType.StartsWith(_N("multipart/form-data;"), &id)) {
		id = id.AfterLast('-');
		return true;
	}

	return false;
}

wxString DynSoft::DSCgi::UrlDecode(wxString str) {
	str.Replace(_N("+"), _N(" "));
	str.Replace(_N("%09"), _N("\t"));
	str.Replace(_N("%20"), _N(" "));
	str.Replace(_N("%22"), _N("\""));
	str.Replace(_N("%23"), _N("#"));
	str.Replace(_N("%26"), _N("&"));
	str.Replace(_N("%28"), _N("("));
	str.Replace(_N("%29"), _N(")"));
	str.Replace(_N("%2B"), _N("+"));
	str.Replace(_N("%2C"), _N("'"));
	str.Replace(_N("%2E"), _N("."));
	str.Replace(_N("%2F"), _N("/"));
	str.Replace(_N("%3A"), _N(":"));
	str.Replace(_N("%3B"), _N(";"));
	str.Replace(_N("%3C"), _N("<"));
	str.Replace(_N("%3D"), _N("="));
	str.Replace(_N("%3E"), _N(">"));
	str.Replace(_N("%3F"), _N("?"));
	str.Replace(_N("%40"), _N("@"));
	str.Replace(_N("%5B"), _N("["));
	str.Replace(_N("%5C"), _N("\\"));
	str.Replace(_N("%5D"), _N("]"));
	str.Replace(_N("%5D"), _N("^"));
	str.Replace(_N("%60"), _N(","));
	str.Replace(_N("%78"), _N("{"));
	str.Replace(_N("%7C"), _N("|"));
	str.Replace(_N("%7D"), _N("}"));
	str.Replace(_N("%7E"), _N("~"));
	str.Replace(_N("%C3%BC"), _N("ü"));
	str.Replace(_N("%C3%A4"), _N("ä"));
	str.Replace(_N("%C3%B6"), _N("ö"));
	str.Replace(_N("%C3%9C"), _N("Ü"));
	str.Replace(_N("%C3%84"), _N("Ä"));
	str.Replace(_N("%C3%96"), _N("Ö"));
	str.Replace(_N("%C3%9F"), _N("ß"));
	str.Replace(_N("%25"), _N("%"));

	return str;
}

wxString DynSoft::DSCgi::UrlEncode(wxString str) {
	str.Replace(_N("%"), _N("%25"));
	str.Replace(_N("\t"), _N("%09"));
	str.Replace(_N(" "), _N("%20"));
	str.Replace(_N("\""), _N("%22"));
	str.Replace(_N("#"), _N("%23"));
	str.Replace(_N("&"), _N("%26"));
	str.Replace(_N("("), _N("%28"));
	str.Replace(_N(")"), _N("%29"));
	str.Replace(_N("+"), _N("%2B"));
	str.Replace(_N("'"), _N("%2C"));
	str.Replace(_N("."), _N("%2E"));
	str.Replace(_N("/"), _N("%2F"));
	str.Replace(_N(":"), _N("%3A"));
	str.Replace(_N(";"), _N("%3B"));
	str.Replace(_N("<"), _N("%3C"));
	str.Replace(_N("="), _N("%3D"));
	str.Replace(_N(">"), _N("%3E"));
	str.Replace(_N("?"), _N("%3F"));
	str.Replace(_N("@"), _N("%40"));
	str.Replace(_N("["), _N("%5B"));
	str.Replace(_N("\\"), _N("%5C"));
	str.Replace(_N("]"), _N("%5D"));
	str.Replace(_N("^"), _N("%5D"));
	str.Replace(_N(","), _N("%60"));
	str.Replace(_N("{"), _N("%78"));
	str.Replace(_N("|"), _N("%7C"));
	str.Replace(_N("}"), _N("%7D"));
	str.Replace(_N("~"), _N("%7E"));
	str.Replace(_N("ü"), _N("%C3%BC"));
	str.Replace(_N("ä"), _N("%C3%A4"));
	str.Replace(_N("ö"), _N("%C3%B6"));
	str.Replace(_N("Ü"), _N("%C3%9C"));
	str.Replace(_N("Ä"), _N("%C3%84"));
	str.Replace(_N("Ö"), _N("%C3%96"));
	str.Replace(_N("ß"), _N("%C3%9F"));

	return str;
}

wxString DynSoft::DSCgi::CookieDecode(wxString str) {
	str.Replace(_N("%20"), _N(" "));
	str.Replace(_N("%3B"), _N(";"));
	str.Replace(_N("%60"), _N(","));

	return str;
}

wxString DynSoft::DSCgi::CookieEncode(wxString str) {
	str.Replace(_N(" "), _N("%20"));
	str.Replace(_N(";"), _N("%3B"));
	str.Replace(_N(","), _N("%60"));

	return str;
}

wxString DynSoft::DSCgi::GetVariable(const wxString &str) {
	wxString tmp;
	const char *tmpStr = DSCasts::ToChar(str);
	char *result = getenv(tmpStr);
	if(result != NULL) {
		tmp = DSCasts::ToString(result);
	}
	delete tmpStr;
	return tmp;
}

wxString DynSoft::DSCgi::nl2br(wxString str) {
	str.Replace(_N("\r\n"), _N("<br />"));
	str.Replace(_N("\r"), _N("<br />"));
	str.Replace(_N("\n"), _N("<br />"));
	return str;
}

int DynSoft::DSCgi::Mail(const wxString &to, const wxString &subject, const wxString &message, const wxString &headers) {
	errno = 0;
	FILE *sendmail = popen(DS_CGI_SENDMAIL, "w");
	
	if(!sendmail)
		return 1;

	wxString tmpHeaders(headers);
	if(!tmpHeaders.IsEmpty())
		tmpHeaders += _N("\r\n");
	tmpHeaders += DS_CGI_MAIL_MIME;
	
	fprintf(sendmail, "To: %s\n", (const char *) to.mb_str(wxConvUTF8));
	fprintf(sendmail, "Subject: %s\n", (const char *) subject.mb_str(wxConvUTF8));
	if(headers.Length() > 0)
		fprintf(sendmail, "%s\n", (const char *) tmpHeaders.mb_str(wxConvUTF8));
	fprintf(sendmail, "\n%s\n", (const char *) message.mb_str(wxConvUTF8));

	return pclose(sendmail);
}

wxString DynSoft::DSCgi::GetLineBreak(const wxString &string) {
	if(string.First(_N("\r\n")) != wxNOT_FOUND)
		return _N("\r\n");
	if(string.First(_N("\r")) != wxNOT_FOUND)
		return _N("\r");
	return _N("\n");
}

char *DynSoft::DSCgi::Split(
	char *content,
	int contentSize,
	char *delimiter,
	int *position,
	int *newSize
) {
	for(*newSize = 0; *newSize < *position; (*newSize)++, content++);

	if(*position >= contentSize)
		return NULL;

	int delimiterSize = strlen(delimiter);
	int found = -1;
	char *result = NULL;
	char c;
	char *tmpContent, *tmpDelimiter;
	char tmpC, tmpD;
	int j = 0, k = 0;
	*newSize = 0;
	while(*position < contentSize - delimiterSize - 3) {
		c = *content;
		found = -1;

		if(c == delimiter[0]) {
			tmpContent   = content;
			tmpDelimiter = delimiter;
			found        = 0;
			j            = *position;
			k            = 0;
			while(j++ < contentSize && k++ < delimiterSize) {
				tmpC = *tmpContent++;
				tmpD = *tmpDelimiter++;

				if(tmpC != tmpD) {
					found = -1;
					break;
				}
			}
		}

		(*position)++;
		result = (char *) realloc(result, sizeof(char *) * (*newSize + 1));

		if(found == 0) {
			result[*newSize] = '\0';
			break;
		}

		result[*newSize] = (char) c;
		(*newSize)++;
		content++;
	}

	return result;
}

char *DynSoft::DSCgi::SplitHeaderContent(
	char *str,
	int length,
	int delimiterLength,
	size_t *newLength,
	size_t start
) {
	char *result = NULL;
	*newLength = 0;
	int i;
	char c;
	if(start > 0)
		length = length - 2;
	start += delimiterLength;

	for(i = start; i < length; i++) {
		c = str[i];

		if(c == '\r' && start - delimiterLength == 0) {
			if(i + 1 < length) {
				if(str[i + 1] == '\n') {
					if(i + 2 < length)
						if(str[i + 2] == '\r')
							if(i + 3 < length)
								if(str[i + 3] == '\n')
									break;
				}
			}
		}
		
		result = (char *) realloc(result, sizeof(char *) * (*newLength + 1));
		result[*newLength] = c;
		(*newLength)++;
	}

	result = (char *) realloc(result, sizeof(char *) * (*newLength + 1));
	result[*newLength] = '\0';

	return result;
}

char *DynSoft::DSCgi::ExtractField(
	char *content,
	const char *find
) {	
	char *result = NULL;
	int found = -1;
	char t;
	char *c;
	char tmpC, tmpF;
	int i = 0;
	while((t = *content)) {
		found = -1;
		if(t == *find) {
			c = content;
			const char *f = find;
			found = 0;

			while((tmpC = *c++) && (tmpF = *f++)) {
				if(tmpC != tmpF) {
					found = -1;
					break;
				}
			}

			if(found == 0) {
				while((tmpC = *c++)) {
					if(tmpC == '"' || tmpC == '\n' || tmpC == '\r')
						break;

					result = (char *) realloc(result, sizeof(char *) * (i + 1));
					result[i] = tmpC;
					i++;
				}

				break;
			}
		}

		content++;
	}

	result = (char *) realloc(result, sizeof(char *) * (i + 1));
	result[i] = '\0';

	return result;
}

char *DynSoft::DSCgi::GetDelimeter(
	char *content
) {
	char *tmp = content;
	while(*tmp != '\r' && *tmp != EOF)
		tmp++;

	const long size = tmp - content;
	char *result = (char *) calloc(size, sizeof(char) + 1);
	strncpy(result, content, size);
	return result;
}

void DynSoft::DSCgi::MakeRequestMultiform(
	char *postContent,
	int size
) {
	int c;
	char *post = NULL;

	int i;
	int tmpSize = 0;
	for(i = 0; i < size; i++) {
		c = postContent[i];
	//	if(c != '\r') {
			post = (char *) realloc(post, sizeof(char *) * (tmpSize + 1));
			post[tmpSize] = (char) c;
			tmpSize++;
	}

	size = tmpSize;

	char *delimiter = GetDelimeter(post);
	int delimiterLength = strlen(delimiter);

	int position = 1;
	char *tmp;
	int newSize;

	char *header;
	char *content;
	size_t splitSize;

	char *name, *filename, *contentType;
	/*wxFile f(_N("/tmp/test1.txt"), wxFile::write);
	f.Write(postContent, size);
	f.Close();*/

	wxString tmpName;
	while((tmp = Split(post, size, delimiter, &position, &newSize)) != NULL) {
		header      = SplitHeaderContent(tmp, newSize, delimiterLength, &splitSize, 0);
		content     = SplitHeaderContent(tmp, newSize, delimiterLength, &splitSize, splitSize + 4);
		name        = ExtractField(header, "name=");
		filename    = ExtractField(header, "filename=");
		contentType = ExtractField(header, "Content-Type:");

		tmpName = DSCasts::ToString(name);
		if(strlen(filename) > 0) {
			rq[tmpName + _N("_filename")]    = DSCasts::ToString(filename);
			rq[tmpName + _N("_contenttype")] = DSCasts::ToString(contentType);
			rq[tmpName + _N("_size")]        = DSCasts::ToString(splitSize);
			rq[tmpName + _N("_tmpfilename")] = CreateRandomFilename();
			rq[tmpName + _N("_error")]       = wxEmptyString;

			wxFFile f(rq[tmpName + _N("_tmpfilename")], _N("w"));
			if(f.IsOpened()) {
				if(f.Write(content, splitSize) != splitSize)
					rq[tmpName + _N("_error")] = _("Could not save file: ") + rq[tmpName + _N("_tmpfilename")];
				if(!f.Close())
					rq[tmpName + _N("_error")] = _("Could not close file: ") + rq[tmpName + _N("_tmpfilename")];
			} else {
				rq[tmpName + _N("_error")] = _("Could not open file: ") + rq[tmpName + _N("_tmpfilename")];
			}
		} else {
			if(!rq[tmpName].IsEmpty()) {
				rq[tmpName] += '\23';
				rq[tmpName] += UrlDecode(DSCasts::ToString(content));//uri.BuildUnescapedURI();
			} else {
				rq[tmpName] = UrlDecode(DSCasts::ToString(content));
			}
		}

		free(header);      header      = NULL;
		free(content);     content     = NULL;
		free(name);        name        = NULL;
		free(filename);    filename    = NULL;
		free(contentType); contentType = NULL;
		free(tmp);         tmp         = NULL;
	}

	free(delimiter);
	free(post);
}

bool DynSoft::DSCgi::FileExists(const wxString &filename) {
	wxFFile file(filename, _N("r"));
	if(file.IsOpened()) {
		file.Close();
		return true;
	}
	return false;
}

wxString DynSoft::DSCgi::CreateRandomFilename() {
	char buffer [11];
	wxString filename;

	do {
		srandom(time(NULL));
		srandom(random());
		snprintf(buffer, 11, "%ld%ld", random(), random());
		filename = GetUploadDirectory() + DSCasts::ToString(buffer);
	} while(FileExists(filename));

	return filename;
}

wxString DynSoft::DSCgi::StripTags(wxString html) {
	bool in = false;
	wxChar c;
	wxString tmp;

	for(unsigned int i = 0; i < html.Length(); i++) {
		c = html[i];

		if(!in)
			in = c == '<';
		if(in) {
			if(c == '"' || c == '\'') {
				while(html[++i] != c && i < html.Length());
				continue;
			} else {
				if(c == '>') {
					in = false;
					continue;
				}
			}
		}
		
		if(!in)
			tmp.Append(c);
	}

	return tmp;
}

char DynSoft::DSCgi::Convert(char *hex) {
	char ascii;

	ascii = (hex[0] >= 'A' ? ((hex[0] & 0xdf) - 'A') + 10 : (hex[0] - '0'));
	ascii <<= 4;
	ascii += (hex[1] >= 'A' ? ((hex[1] & 0xdf) - 'A') + 10 : (hex[1] - '0'));

	return ascii;
}

wxString DynSoft::DSCgi::Hex2Ascii(wxString &hex) {
	//wxURI uri(hex);
	//return uri.BuildUnescapedURI();

	char *ascii = (char *) DSCasts::ToChar(hex);

	int x, y;
	for(x = 0, y = 0; ascii[y] != '\0'; ++x, ++y) {
		ascii[x] = ascii[y];
		if(ascii[x] == '%') {
			ascii[x] = Convert(&ascii[y + 1]);
			y += 2;
		} else if(ascii[x] == '+') {
			ascii[x] = ' ';
		}
	}
	ascii[x] = '\0';

	wxString tmp(DSCasts::ToString(ascii));
	delete [] ascii;

	return tmp;
}

bool DynSoft::DSCgi::IsEmail(const wxString &email, const wxString &expression) {
	wxRegEx re(expression);
	return re.Matches(email);
}

void DynSoft::DSCgi::SetHeaderExtend(const wxString &headerExtend) {
	this->headerExtend = headerExtend;
}

void DynSoft::DSCgi::AddToHeader(const wxString &headerExtend) {
	this->headerExtend += headerExtend;
}

wxString DynSoft::DSCgi::GetHeaderExtend() const {
	return this->headerExtend;
}

DynSoft::DSCookiesType *DynSoft::DSCgi::GetCookies(DSCookiesType *cookies) {
	if(cookies == NULL)
		cookies = new DSCookiesType();

	char *cookiesHeader = getenv("HTTP_COOKIE");
	if(cookiesHeader != NULL) {
		wxString cookiesString;
		wxArrayString cookiesArray, cookieArray;
		DSCookieType *cookie = NULL;

		cookiesString = DSCasts::ToString(cookiesHeader);
		cookiesString.Replace(_N("; "), _N(";"));
		cookiesArray = DSLib::Split(cookiesString, ';');

		unsigned int cookieArrayCount = 0;
		unsigned int cookiesArrayCount = cookiesArray.GetCount();
		for(unsigned int i = 0; i < cookiesArrayCount; i++) {
			cookieArray = DSLib::Split(cookiesArray[i], '=');

			cookieArrayCount = cookiesArray.GetCount();
			for(unsigned int j = 0; j < cookieArrayCount; j++) {
				cookie = new DSCookieType;
				cookie->SetName(CookieDecode(cookieArray[0]));
				cookie->SetValue(CookieDecode(cookieArray[1]));
				cookies->Add(cookie);
			}
		}
	}
		
	return cookies;
}

wxArrayString DynSoft::DSCgi::GetMultipleRequest(const wxString &field, const wxChar separator) {
	return DSLib::Split(rq[field], separator);
}

bool DynSoft::DSCgi::IsMultipleRequest(const wxString &field, const wxChar separator) {
	return rq[field].Find(separator) != wxNOT_FOUND;
}

wxString DynSoft::DSCgi::Escape(const wxString &url) {
	wxURI uri(url);

	wxString tmp(uri.BuildURI());
	tmp.Replace(_N("+"), _N("%2B"));

	return tmp;
}

wxString DynSoft::DSCgi::Unescape(const wxString &url) {
	wxURI uri(url);
	wxString tmp(uri.BuildUnescapedURI());
	tmp.Replace(_N("%2B"), _N("+"));
	return tmp;
}
