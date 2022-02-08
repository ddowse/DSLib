#ifndef DS_WEB_H_
#define DS_WEB_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSCgi.h"
#include "DSCasts.h"
#include "DSCookieType.h"
#include "DSCookiesType.h"
#include "DSDebug.h"
#include <fcgi_stdio.h>

#define DS_WEB_VERSION			_N("0.0.8")
#define DS_WEB_NAME				_N("DSWeb")
#define DS_WEB_AUTHOR			_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_WEB_AUTOHEADER 0
#define DS_WEB_SELFHEADER 1

#define IMPLEMENT_WEB(className, objectName) \
	className objectName; \
	\
	int main(int argc, char **argv) { \
		wxEntryStart(argc, argv); \
		\
		int result = objectName.Init(); \
		if(result != 0) \
			return result; \
		\
		int fcgiResult = 0; \
		while((fcgiResult = FCGI_Accept()) >= 0) { \
			objectName.ClearStringContent(); \
			\
			objectName.GetCgi()->MakeRequests(); \
			\
			switch(objectName.GetMode()) { \
				case DS_WEB_AUTOHEADER: \
					{\
						const char *header = DSCasts::ToChar(objectName.GetContentType() + _N("\r\n")); \
						printf("%s", header); \
						delete [] header; \
						break; \
					} \
				case DS_WEB_SELFHEADER: \
					{ \
						objectName.SetGetCookies(objectName.GetCgi()->GetCookies()); \
						break; \
					} \
			} \
			\
			result = objectName.Run(); \
			\
			if(objectName.GetMode() == DS_WEB_SELFHEADER) { \
				const char *content= DSCasts::ToChar(objectName.GetHeader() + _N("\r\n") + objectName.GetStringContent()); \
				printf("%s", content); \
				delete [] content; \
				delete objectName.GetGetCookies(); \
				objectName.SetGetCookies(NULL); \
				objectName.GetSetCookies()->Clear(true); \
				\
			} \
			\
			if(result != 0) \
				break; \
		} \
		\
		if(fcgiResult < 0) \
			return fcgiResult; \
		\
		return result < 0 ? 0 : result; \
	}

namespace DynSoft {

	class DSWeb : public DSLib {
	
		public:
			DSWeb(
				const wxString &contentType = _N("Content-type: text/html\r\n"),
				const bool useUnicode = true,
				const unsigned int mode = DS_WEB_AUTOHEADER,
				const wxString &uploadDirectory = wxEmptyString
			);
			~DSWeb();

			DSClassInfo GetClassInfo();

			void SetContentType(const wxString &contentType);
			wxString GetContentType() const;

			void SetMode(const unsigned int mode);
			unsigned int GetMode() const;

			void SetUploadDirectory(const wxString &uploadDirectory);
			wxString GetUploadDirectory();

			DSCgi *GetCgi();
			wxString GetDefaultContentType();

			// Everything other than zero will stop the program
			virtual int Init() = 0;
			// A negative value will stop the program with the result of zero,
			// a positive value will stop the program with the result value.
			// A zero value will run the next loop
			virtual int Run()  = 0;

			void SetGetCookies(DSCookiesType *getCookies);
			DSCookiesType *GetSetCookies();
			DSCookiesType *GetGetCookies() const;

			void AddCookie(DSCookieType *cookieType);
			void ClearCookies();

			wxString GetHeader();

			void SetStringContent(const wxString &stringContent);
			wxString GetStringContent() const;
			void ClearStringContent();

		protected:
			wxString contentType;
			bool useUnicode;
			DSCgi cgi;
			unsigned int mode;
			DSCookiesType setCookies;
			DSCookiesType *getCookies;
			wxString stringContent;
	
	};

}

#endif /* DS_WEB_H_ */
