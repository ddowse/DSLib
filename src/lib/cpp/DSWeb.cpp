#include "DSWeb.h"

DynSoft::DSWeb::DSWeb(
	const wxString &contentType,
	const bool useUnicode,
	const unsigned int mode,
	const wxString &uploadDirectory
) : DSLib(
), cgi(
	useUnicode,
	uploadDirectory
) {
	this->useUnicode = useUnicode;
	SetContentType(contentType);
	SetMode(mode);
	SetGetCookies(NULL);
}

DynSoft::DSWeb::~DSWeb() {
	delete getCookies;
}

DynSoft::DSClassInfo DynSoft::DSWeb::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_WEB_NAME,
		DS_WEB_VERSION,
		DS_WEB_AUTHOR
	);
}

void DynSoft::DSWeb::SetUploadDirectory(const wxString &uploadDirectory) {
	GetCgi()->SetUploadDirectory(uploadDirectory);
}

wxString DynSoft::DSWeb::GetUploadDirectory() {
	return GetCgi()->GetUploadDirectory();
}

void DynSoft::DSWeb::SetMode(const unsigned int mode) {
	this->mode = mode;
}

unsigned int DynSoft::DSWeb::GetMode() const {
	return mode;
}

void DynSoft::DSWeb::SetContentType(const wxString &contentType) {
	this->contentType = contentType;
}

wxString DynSoft::DSWeb::GetContentType() const {
	return contentType;
}

DynSoft::DSCgi *DynSoft::DSWeb::GetCgi() {
	return &cgi;
}

wxString DynSoft::DSWeb::GetDefaultContentType() {
	return _N("Content-type: text/html\r\n");
}

void DynSoft::DSWeb::AddCookie(DSCookieType *cookieType) {
	setCookies.Add(cookieType);
}

void DynSoft::DSWeb::ClearCookies() {
	setCookies.Clear(true);
}

void DynSoft::DSWeb::SetGetCookies(DynSoft::DSCookiesType *getCookies) {
	this->getCookies = getCookies;
}

DynSoft::DSCookiesType *DynSoft::DSWeb::GetSetCookies() {
	return &setCookies;
}

DynSoft::DSCookiesType *DynSoft::DSWeb::GetGetCookies() const {
	return getCookies;
}

wxString DynSoft::DSWeb::GetHeader() {
	wxString header(GetContentType());

	DSCookieType *cookie      = NULL;
	DSCookiesType *setCookies = GetSetCookies();
	const unsigned int count  = setCookies->GetCount();
	for(unsigned int i = 0; i < count; i++) {
		cookie = setCookies->Get(i);
		if(cookie)
			header += cookie->GetCookieString() + _N("\r\n");
	}

	return header;
}

void DynSoft::DSWeb::SetStringContent(const wxString &stringContent) {
	this->stringContent = stringContent;
}

wxString DynSoft::DSWeb::GetStringContent() const {
	return stringContent;
}

void DynSoft::DSWeb::ClearStringContent() {
	stringContent.Clear();
}
