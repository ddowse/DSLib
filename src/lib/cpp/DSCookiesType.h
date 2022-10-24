#ifndef DS_COOKIES_TYPE_H_
#define DS_COOKIES_TYPE_H_

#include <wx/wx.h>
#include "DSCookieType.h"
#include "DSTemplateContainer.h"

#define DS_COOKIES_TYPE_VERSION	_N("0.0.1")
#define DS_COOKIES_TYPE_NAME		_N("DSCookieType")
#define DS_COOKIES_TYPE_AUTHOR	_N("Dietrich Haag (dietrich@haagit.com), Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCookiesType : public DSTemplateContainer<DSCookieType *> {

		public:
			DSCookiesType();
			~DSCookiesType();

			DSClassInfo GetClassInfo();

			DSCookieType *GetCookie(const wxString &name);
			wxString GetCookieValue(const wxString &name);

	};

}

#endif /* DS_COOKIES_TYPE_H_ */
