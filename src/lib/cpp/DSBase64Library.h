// Konvertierung von wxWidgets 3.1 (Thorsten Geppert, 16.03.2017)

///////////////////////////////////////////////////////////////////////////////
// Name:        src/common/base64.cpp
// Purpose:     implementation of BASE64 encoding/decoding functions
// Author:      Charles Reimers, Vadim Zeitlin
// Created:     2007-06-18
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef DS_BASE_64_LIBRARY_H_
#define DS_BASE_64_LIBRARY_H_

#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_BASE_64_LIBRARY_VERSION        _N("0.0.1")
#define DS_BASE_64_LIBRARY_NAME           _N("DSDSBase64Library")
#define DS_BASE_64_LIBRARY_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSBase64Library : DSLib {

		public:
			enum wxBase64DecodeMode {
				// normal behaviour: stop at any invalid characters
				wxBase64DecodeMode_Strict,

				// skip whitespace characters
				wxBase64DecodeMode_SkipWS,

				// the most lenient behaviour: simply ignore all invalid characters
				wxBase64DecodeMode_Relaxed
			};

			DSBase64Library();
			~DSBase64Library();

			DSClassInfo GetClassInfo();

			size_t wxBase64Encode(char *dst, size_t dstLen, const void *src_, size_t srcLen);
			size_t wxBase64Decode(void *dst_, size_t dstLen, const char *src, size_t srcLen, wxBase64DecodeMode mode, size_t *posErr);
			wxMemoryBuffer wxBase64Decode(const char *src, size_t srcLen, wxBase64DecodeMode mode, size_t *posErr);

			inline size_t wxBase64DecodedSize(size_t srcLen);
			inline size_t wxBase64EncodedSize(size_t len);

			wxString wxBase64Encode(const void *src, size_t srcLen);
			wxString wxBase64Encode(const wxMemoryBuffer& buf);
			size_t wxBase64Decode(void *dst, size_t dstLen, const wxString& src, wxBase64DecodeMode mode = wxBase64DecodeMode_Strict, size_t *posErr = NULL);
			wxMemoryBuffer wxBase64Decode(const wxString &src, wxBase64DecodeMode mode = wxBase64DecodeMode_Strict, size_t *posErr = NULL);

			bool FileToBase64(const wxString &filename, wxString &base64String);
			bool Base64ToFile(const wxString &filename, const wxString &base64String);
			wxString Base64ToTemporaryFile(const wxString &base64String, wxString directory = wxEmptyString);
		
	};

}

#endif /* DS_BASE_64_LIBRARY_H_ */
