#include "DSPayPalConnectionType.h"
#include "DSCasts.h"

DynSoft::DSPayPalConnectionType::DSPayPalConnectionType() : DSType(
) {
	SetVersion(DS_PAYPAL_CONNECTION_TYPE_DEFAULT_VERSION);
}

DynSoft::DSPayPalConnectionType::DSPayPalConnectionType(
	const wxString &hostname,
	const unsigned int port,
	const unsigned int timeout,
	const wxString &username,
	const wxString &password,
	const wxString &signature,
	const wxString &returnURL,
	const wxString &cancelURL,
	const wxString &callURL,
	const wxString &localeCode,
	const wxString &callableFile
) {
	SetHostname(hostname);
	SetPort(port);
	SetTimeout(timeout);
	SetUsername(username);
	SetPassword(password);
	SetSignature(signature);
	SetReturnURL(returnURL);
	SetCancelURL(cancelURL);
	SetCallURL(callURL);
	SetLocaleCode(localeCode);
	SetCallableFile(callableFile);

	SetVersion(DS_PAYPAL_CONNECTION_TYPE_DEFAULT_VERSION);
}

DynSoft::DSPayPalConnectionType::~DSPayPalConnectionType() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalConnectionType::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_CONNECTION_TYPE_NAME,
        DS_PAYPAL_CONNECTION_TYPE_VERSION,
        DS_PAYPAL_CONNECTION_TYPE_AUTHOR
    );
}

void DynSoft::DSPayPalConnectionType::SetHostname(const wxString &hostname) {
	this->hostname = hostname;
}

wxString DynSoft::DSPayPalConnectionType::GetHostname() const {
	return hostname;
}

void DynSoft::DSPayPalConnectionType::SetPort(const unsigned int port) {
	this->port = port;
}

unsigned int DynSoft::DSPayPalConnectionType::GetPort() const {
	return port;
}

void DynSoft::DSPayPalConnectionType::SetUsername(const wxString &username) {
	this->username = username;
}

wxString DynSoft::DSPayPalConnectionType::GetUsername() const {
	return username;
}

void DynSoft::DSPayPalConnectionType::SetPassword(const wxString &password) {
	this->password = password;
}

wxString DynSoft::DSPayPalConnectionType::GetPassword() const {
	return password;
}

void DynSoft::DSPayPalConnectionType::SetSignature(const wxString &signature) {
	this->signature = signature;
}

wxString DynSoft::DSPayPalConnectionType::GetSignature() const {
	return signature;
}

void DynSoft::DSPayPalConnectionType::SetReturnURL(const wxString &returnURL) {
	this->returnURL = returnURL;
}

wxString DynSoft::DSPayPalConnectionType::GetReturnURL() const {
	return returnURL;
}

void DynSoft::DSPayPalConnectionType::SetCancelURL(const wxString &cancelURL) {
	this->cancelURL = cancelURL;
}

wxString DynSoft::DSPayPalConnectionType::GetCancelURL() const {
	return cancelURL;
}

void DynSoft::DSPayPalConnectionType::SetCallURL(const wxString &callURL) {
	this->callURL = callURL;
}

wxString DynSoft::DSPayPalConnectionType::GetCallURL() const {
	return callURL;
}

wxString DynSoft::DSPayPalConnectionType::GetFullCallURL(
	DynSoft::DSPayPalToken &token
) const {
	return GetCallURL() + _N("/cgi-bin/webscr?cmd=_express-checkout&token=") + token.GetToken();
}

void DynSoft::DSPayPalConnectionType::SetLocaleCode(const wxString &localeCode) {
	this->localeCode = localeCode;
}

wxString DynSoft::DSPayPalConnectionType::GetLocaleCode() const {
	return localeCode;
}

void DynSoft::DSPayPalConnectionType::SetCallableFile(const wxString &callableFile) {
	this->callableFile = callableFile;
}

wxString DynSoft::DSPayPalConnectionType::GetCallableFile() const {
	return callableFile;
}

wxString DynSoft::DSPayPalConnectionType::GetVersion() const {
	return version;
}

void DynSoft::DSPayPalConnectionType::SetTimeout(const unsigned int timeout) {
	this->timeout = timeout;
}

unsigned int DynSoft::DSPayPalConnectionType::GetTimeout() const {
	return timeout;
}

void DynSoft::DSPayPalConnectionType::SetVersion(const wxString &version) {
	this->version = version;
}

wxString DynSoft::DSPayPalConnectionType::ToUrlString() {
	wxString url;

	url  = _N("USER=")       + GetUsername()  + _N("&");
	url += _N("PWD=")        + GetPassword()  + _N("&");
	url += _N("SIGNATURE=")  + GetSignature() + _N("&");
	url += _N("VERSION=")    + GetVersion()   + _N("&");
	url += _N("RETURNURL=")  + GetReturnURL() + _N("&");
	url += _N("CANCELURL=")  + GetCancelURL() + _N("&");
	url += _N("LOCALECODE=") + GetLocaleCode();

	return url;
}

wxString DynSoft::DSPayPalConnectionType::ToCallableString() {
	return GetCallableFile() + _N("?") + ToUrlString();
}

wxString DynSoft::DSPayPalConnectionType::ToString() {
	wxString result;
	
	result += _N("                       Hostname: ") + GetHostname() + _N("\n");
	result += _N("                           Port: ") + DynSoft::DSCasts::ToString(GetPort()) + _N("\n");
	result += _N("                       Username: ") + GetUsername() + _N("\n");
	result += _N("                       Password: ") + GetPassword() + _N("\n");
	result += _N("                      Signature: ") + GetSignature() + _N("\n");
	result += _N("                     Return URL: ") + GetReturnURL() + _N("\n");
	result += _N("                     Cancel URL: ") + GetCancelURL() + _N("\n");
	result += _N("                    Locale code: ") + GetLocaleCode() + _N("\n");
	result += _N("                  Callable file: ") + GetCallableFile() + _N("\n");
	result += _N("                        Timeout: ") + DynSoft::DSCasts::ToString(GetTimeout()) + _N("\n");
	result += _N("                        Version: ") + GetVersion();

	return result;
}
