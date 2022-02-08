#include "DSCookieType.h"
#include "DSCookiesType.h"

DynSoft::DSCookiesType::DSCookiesType(
) : DSTemplateContainer<DSCookieType *>(
) {
}

DynSoft::DSCookiesType::~DSCookiesType() {
	Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSCookiesType::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_COOKIES_TYPE_NAME,
		DS_COOKIES_TYPE_VERSION,
		DS_COOKIES_TYPE_AUTHOR
	);
}

DynSoft::DSCookieType *DynSoft::DSCookiesType::GetCookie(const wxString &name) {
	DSCookieType *cookie = NULL;

	const unsigned int count = GetCount();
	for(unsigned int i = 0; i < count; i++) {
		cookie = Get(i);
		if(cookie && cookie->GetName() == name)
			return cookie;
	}

	return NULL;;
}

wxString DynSoft::DSCookiesType::GetCookieValue(const wxString &name) {
	DSCookieType *cookie = GetCookie(name);
	if(cookie)
		return cookie->GetValue();
	return wxEmptyString;
}
