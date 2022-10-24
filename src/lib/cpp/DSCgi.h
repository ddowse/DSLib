#ifndef DS_CGI_H_
#define DS_CGI_H_

#include <wx/wx.h>
#include <wx/hashmap.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSCookiesType.h"

#define DS_CGI_VERSION				_N("0.2.9")
#define DS_CGI_NAME					_N("DSCgi")
#define DS_CGI_AUTHOR				_N("Thorsten Geppert (thorsten@dynsoft.com)")
#define DS_CGI_METHOD_UNKNOWN		-1
#define DS_CGI_METHOD_GET			0
#define DS_CGI_METHOD_POST			1
#define DS_CGI_SENDMAIL				"/usr/sbin/sendmail -t -i"
#define DS_CGI_REGEX_MAIL			_N("([^@]+)@([[:alnum:].-_].)+([[:alnum:]-]+)")
#define DS_CGI_MULTIPLE_SEPERATOR	'\23'
#define DS_CGI_MAIL_MIME			_N("MIME-Version: 1.0\r\nContent-Type: text/plain; charset=\"utf-8\"\r\nContent-Transfer-Encoding: 8bit\"")

WX_DECLARE_STRING_HASH_MAP(wxString, DSCgiHash);

namespace DynSoft {

	class DSCgi : public DSLib {
	
		public:
			DSCgi(const bool useUnicode = true, const wxString &uploadDirectory = wxEmptyString);

			DSClassInfo GetClassInfo();

			void SetUploadDirectory(const wxString &uploadDirectory);
			wxString GetUploadDirectory() const;

			int GetMethod();
			DSCgiHash rq;
			static wxString GetVariable(const wxString &str);
			// Those two methods are very very dirty
			// We got to write a hex2ascii and ascii2hex transformator
			// by time
			static wxString Hex2Ascii(wxString &hex);
			static wxString UrlDecode(wxString str); // depracated
			static wxString UrlEncode(wxString str); // depracated
			static wxString CookieDecode(wxString str);
			static wxString CookieEncode(wxString str);
			static wxString nl2br(wxString str);
			static int Mail(
				const wxString &to,
				const wxString &subject,
				const wxString &message,
				const wxString &headers
			);
			wxString GetLineBreak(const wxString &string);
			static wxString StripTags(wxString html);
			static bool IsEmail(const wxString &email, const wxString &expression = DS_CGI_REGEX_MAIL);
			void MakeRequests(); // Starts the Post or Get method

			void SetHeaderExtend(const wxString &headerExtend);
			void AddToHeader(const wxString &headerExtend);
			wxString GetHeaderExtend() const;
			DSCookiesType *GetCookies(DSCookiesType *cookies = NULL);

			wxArrayString GetMultipleRequest(const wxString &field, const wxChar separator = DS_CGI_MULTIPLE_SEPERATOR);
			bool IsMultipleRequest(const wxString &field, const wxChar separator = DS_CGI_MULTIPLE_SEPERATOR);

			wxString CreateRandomFilename();
			bool FileExists(const wxString &filename);

			static wxString Escape(const wxString &url);
			static wxString Unescape(const wxString &url);

		protected:
			wxString headerExtend;
			wxString uploadDirectory;

			void MakeRequestGet(); // Creates the query string for get
			void MakeRequestPost(); // Creates the query string for post
			void MakeRequest(const wxString &request, const wxString &token); // Fills the hashmap
			void MakeRequestMultiform(char *postContent, int size); // Creates the query string for multiform post
			char *AddWindowsLinebreak(
				char *content,
				int size,
				int *newSize
			);
			char *GetDelimeter(
				char *content
			);
			char *ExtractField(
				char *content,
				const char *find
			);
			char *SplitHeaderContent(
				char *str,
				int length,
				int delimiterLength,
				size_t *newLength,
				size_t start
			);
			char *Split(
				char *content,
				int contentSize,
				char *delimiter,
				int *position,
				int *newSize
			);
			bool StripContentType(
				const wxString &contentType,
				wxString &id
			);
			static char Convert(char *hex);

			bool useUnicode;

	};

}

#endif /* DS_CGI_H_ */
