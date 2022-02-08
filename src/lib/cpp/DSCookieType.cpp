#include "DSCookieType.h"
#include "DSCgi.h"
#include <wx/datetime.h>
#include "DSDebug.h"
#include "DSCasts.h"

DynSoft::DSCookieType::DSCookieType() : DSType() {
	expiresSetted = false;
	httpOnly = true;
	secure = false;
}

DynSoft::DSCookieType::DSCookieType(
	const wxString &name,
	const wxString &value,
	const DynSoft::DSDateTime &expiration,
	const wxString &domain,
	const wxString &path,
	const bool &secure,
	const bool &httpOnly
) : DSType() {
	SetName(name);
	SetValue(value);
	SetExpiration(expiration);
	SetDomain(domain);
	SetPath(path);
	SetSecure(secure);
	SetHttpOnly(httpOnly);
}

DynSoft::DSClassInfo DynSoft::DSCookieType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_COOKIE_TYPE_NAME,
		DS_COOKIE_TYPE_VERSION,
		DS_COOKIE_TYPE_AUTHOR
	);
}

void DynSoft::DSCookieType::SetName(const wxString &name) {
	this->name = name;
}

wxString DynSoft::DSCookieType::GetName() const {
	return name;
}

void DynSoft::DSCookieType::SetValue(const wxString &value) {
	this->value = value;
}

wxString DynSoft::DSCookieType::GetValue() const {
	return value;
}

void DynSoft::DSCookieType::SetExpiration(const DynSoft::DSDateTime &expires) {
	this->expires = expires;
	expiresSetted = true;
}

DynSoft::DSDateTime DynSoft::DSCookieType::GetExpiration() const {
	return expires;
}

void DynSoft::DSCookieType::UnsetExpiration() {
	expiresSetted = false;
}

void DynSoft::DSCookieType::SetDomain(const wxString &domain) {
	this->domain = domain;
}

wxString DynSoft::DSCookieType::GetDomain() const {
	return domain;
}

void DynSoft::DSCookieType::SetPath(const wxString &path) {
	this->path = path;
}

wxString DynSoft::DSCookieType::GetPath() const {
	return path;
}

void DynSoft::DSCookieType::SetSecure(const bool &secure) {
	this->secure = secure;
}

bool DynSoft::DSCookieType::GetSecure() const {
	return secure;
}

void DynSoft::DSCookieType::SetHttpOnly(const bool &httpOnly) {
	this->httpOnly = httpOnly;
}

bool DynSoft::DSCookieType::GetHttpOnly() const {
	return httpOnly;
}

wxString DynSoft::DSCookieType::GetCookieString() const {
	wxString cookieString(_N("Set-Cookie: "));

	cookieString += DSCgi::CookieEncode(GetName()) + _N("=") + DSCgi::CookieEncode(GetValue()) + _N(";");
	
	wxString dateString(GetExpiration().ToCookieDateTime());

	if(GetExpiration() < DSDateTime::Now())
		dateString = _N("0");

	if(expiresSetted)
		cookieString += _N("expires") + _N("=") + dateString;

	if(!GetDomain().IsEmpty())
		cookieString += _N(";domain") + _N("=") + GetDomain();

	if(!GetPath().IsEmpty())
		cookieString += _N(";path") + _N("=") + GetPath();

	if(GetSecure())
		cookieString += _N(";secure");

	if(GetHttpOnly())
		cookieString += _N(";HttpOnly");

	return cookieString;
}
