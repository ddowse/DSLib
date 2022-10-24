#ifndef DS_COOKIE_TYPE_H_
#define DS_COOKIE_TYPE_H_

#include <wx/wx.h>
#include "DSType.h"
#include "DSDateTime.h"

#define DS_COOKIE_TYPE_VERSION	_N("0.0.1")
#define DS_COOKIE_TYPE_NAME		_N("DSCookieType")
#define DS_COOKIE_TYPE_AUTHOR	_N("Dietrich Haag (dietrich@haagit.com), Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCookieType : public DSType {
		
		public:
			DSCookieType();
			DSCookieType(
				const wxString &name,
				const wxString &value = wxEmptyString,
				const DynSoft::DSDateTime &expiration = DSDateTime(0, 0, 0, 0), // should be earliert than "Now" in Method GetCookieString
				const wxString &domain = wxEmptyString,
				const wxString &path = wxEmptyString,
				const bool &secure = false,
				const bool &httpOnly = false
			);

			DSClassInfo GetClassInfo();

			void SetName(const wxString &name); // Name for Cookies > Specialchars URL-ENCODED
			wxString GetName() const;

			void SetValue(const wxString &value); // Wert for Cookies > Specialchars URL-ENCODED
			wxString GetValue() const;

			void SetExpiration(const DynSoft::DSDateTime &expires); // "Wednesday, 09-Nov-99 00:00:00 GMT"
			DynSoft::DSDateTime GetExpiration() const;
			void UnsetExpiration();

			void SetDomain(const wxString &domain); // ".dynsoft.com" = everything on dynsoft.com or "www.dynsoft.com" = only everything on www.dynsoft.com
			wxString GetDomain() const;

			void SetPath(const wxString &path); // "/gna/bla/index.rnd" or "/gna/bla/"
			wxString GetPath() const;

			void SetSecure(const bool &secure = false); // "secure" as last attribute = only https
			bool GetSecure() const;

			void SetHttpOnly(const bool &httpOnly = true); // 
			bool GetHttpOnly() const;

			wxString GetCookieString() const;

//	print "Set-Cookie: ";
//	print ($name, "=", $value, "; expires=", $expiration, "; path=", $path, "; domain=", $domain, "; ", $secure, "\n");

		protected:
			wxString name;
			wxString value;
			DynSoft::DSDateTime expires;
			wxString domain;
			wxString path;
			bool secure;
			bool httpOnly;
			bool expiresSetted;
	};

}

#endif /* DS_COOKIE_TYPE_H_ */
