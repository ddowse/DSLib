#include "DSBase64Library.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "DSCasts.h"

using namespace DynSoft;

///////////////////////////////////////////////////////////////////////////////
// Name:        src/common/base64.cpp
// Purpose:     implementation of BASE64 encoding/decoding functions
// Author:      Charles Reimers, Vadim Zeitlin
// Created:     2007-06-18
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

DynSoft::DSBase64Library::DSBase64Library(
) : DSLib(
) {
}

DynSoft::DSBase64Library::~DSBase64Library() {
}

size_t DynSoft::DSBase64Library::wxBase64Encode(char *dst, size_t dstLen, const void *src_, size_t srcLen) {
    wxCHECK_MSG( src_, wxCONV_FAILED, wxT("NULL input buffer") );

    const unsigned char *src = static_cast<const unsigned char *>(src_);

    static const char b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


    size_t encLen = 0;

    // encode blocks of 3 bytes into 4 base64 characters
    for ( ; srcLen >= 3; srcLen -= 3, src += 3 )
    {
        encLen += 4;
        if ( dst )
        {
            if ( encLen > dstLen )
                return wxCONV_FAILED;

            *dst++ = b64[src[0] >> 2];
            *dst++ = b64[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
            *dst++ = b64[((src[1] & 0x0f) << 2) | ((src[2] & 0xc0) >> 6)];
            *dst++ = b64[src[2] & 0x3f];
        }
    }

    // finish with the remaining characters
    if ( srcLen )
    {
        encLen += 4;
        if ( dst )
        {
            if ( encLen > dstLen )
                return wxCONV_FAILED;

            // we have definitely one and maybe two bytes remaining
            unsigned char next = srcLen == 2 ? src[1] : 0;
            *dst++ = b64[src[0] >> 2];
            *dst++ = b64[((src[0] & 0x03) << 4) | ((next & 0xf0) >> 4)];
            *dst++ = srcLen == 2 ? b64[((next & 0x0f) << 2)] : '=';
            *dst = '=';
        }
    }

    return encLen;
}

size_t DynSoft::DSBase64Library::wxBase64Decode(void *dst_, size_t dstLen, const char *src, size_t srcLen, wxBase64DecodeMode mode, size_t *posErr) {
    wxCHECK_MSG( src, wxCONV_FAILED, wxT("NULL input buffer") );

    unsigned char *dst = static_cast<unsigned char *>(dst_);

    size_t decLen = 0;

    if ( srcLen == wxNO_LEN )
        srcLen = strlen(src);

    // this table contains the values, in base 64, of all valid characters and
    // special values WSP or INV for white space and invalid characters
    // respectively as well as a special PAD value for '='
    enum
    {
        WSP = 200,
        INV,
        PAD
    };

    static const unsigned char decode[256] =
    {
        WSP,INV,INV,INV,INV,INV,INV,INV,INV,WSP,WSP,INV,WSP,WSP,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        WSP,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,076,INV,INV,INV,077,
        064,065,066,067,070,071,072,073,074,075,INV,INV,INV,PAD,INV,INV,
        INV,000,001,002,003,004,005,006,007,010,011,012,013,014,015,016,
        017,020,021,022,023,024,025,026,027,030,031,INV,INV,INV,INV,INV,
        INV,032,033,034,035,036,037,040,041,042,043,044,045,046,047,050,
        051,052,053,054,055,056,057,060,061,062,063,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
        INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,INV,
    };

    // we decode input by groups of 4 characters but things are complicated by
    // the fact that there can be whitespace and other junk in it too so keep
    // record of where exactly we're inside the current quartet in this var
    int n = 0;
    unsigned char in[4];                    // current quartet
    bool end = false;                       // set when we find padding
    size_t padLen = 0;                      // length lost to padding
    const char *p;
    for ( p = src; srcLen; p++, srcLen-- )
    {
        const unsigned char c = decode[static_cast<unsigned char>(*p)];
        switch ( c )
        {
            case WSP:
                if ( mode == wxBase64DecodeMode_SkipWS )
                    continue;

            case INV:
                if ( mode == wxBase64DecodeMode_Relaxed )
                    continue;

                // force the loop to stop and an error to be returned
                n = -1;
                srcLen = 1;
                break;

            case PAD:
                // set the flag telling us that we're past the end now
                end = true;

                // there can be either a single '=' at the end of a quartet or
                // "==" in positions 2 and 3
                if ( n == 3 )
                {
                    padLen = 1;
                    in[n++] = '\0';
                }
                else if ( (n == 2) && (--srcLen && *++p == '=') )
                {
                    padLen = 2;
                    in[n++] = '\0';
                    in[n++] = '\0';
                }
                else // invalid padding
                {
                    // force the loop terminate with an error
                    n = -1;
                    srcLen = 1;
                }
                break;

            default:
                if ( end )
                {
                    // nothing is allowed after the end so provoke error return
                    n = -1;
                    srcLen = 1;
                    break;
                }

                in[n++] = c;
        }

        if ( n == 4 )
        {
            // got entire block, decode
            decLen += 3 - padLen;
            if ( dst )
            {
                if ( decLen > dstLen )
                    return wxCONV_FAILED;

                // undo the bit shifting done during encoding
                *dst++ = in[0] << 2 | in[1] >> 4;

                // be careful to not overwrite the output buffer with NUL pad
                // bytes
                if ( padLen != 2 )
                {
                    *dst++ = in[1] << 4 | in[2] >> 2;
                    if ( !padLen )
                        *dst++ = in[2] << 6 | in[3];
                }
            }

            n = 0;
        }
    }

    if ( n )
    {
        if ( posErr )
        {
            // notice that the error was on a previous position as we did one
            // extra "p++" in the loop line after it
            *posErr = p - src - 1;
        }

        return wxCONV_FAILED;
    }

    return decLen;
}

wxMemoryBuffer DynSoft::DSBase64Library::wxBase64Decode(const char *src, size_t srcLen, wxBase64DecodeMode mode, size_t *posErr) {
    wxMemoryBuffer buf;
    wxCHECK_MSG( src, buf, wxT("NULL input buffer") );

    if ( srcLen == wxNO_LEN )
        srcLen = strlen(src);

    size_t len = wxBase64DecodedSize(srcLen);
    len = wxBase64Decode(buf.GetWriteBuf(len), len, src, srcLen, mode, posErr);
    if ( len == wxCONV_FAILED )
        len = 0;

    buf.SetDataLen(len);

    return buf;
}

size_t DynSoft::DSBase64Library::wxBase64DecodedSize(size_t srcLen) {
	return 3 * srcLen / 4;
}

size_t DynSoft::DSBase64Library::wxBase64EncodedSize(size_t len) {
	return 4 * ((len + 2) / 3);
}

wxString DynSoft::DSBase64Library::wxBase64Encode(const void *src, size_t srcLen)
{
    const size_t dstLen = wxBase64EncodedSize(srcLen);
    //wxCharBuffer dst(dstLen);
	char *dst = new char[dstLen];
    wxBase64Encode(dst, dstLen, src, srcLen);
	const wxString tmp(dst, wxConvUTF8, dstLen);
	delete [] dst;

    return tmp;
}

wxString DynSoft::DSBase64Library::wxBase64Encode(const wxMemoryBuffer& buf)
{
    return wxBase64Encode(buf.GetData(), buf.GetDataLen());
}

size_t DynSoft::DSBase64Library::wxBase64Decode(void *dst, size_t dstLen, const wxString& src, wxBase64DecodeMode mode, size_t *posErr)
{
    // don't use str.length() here as the ASCII buffer is shorter than it for
    // strings with embedded NULs
    return wxBase64Decode(dst, dstLen, src.ToAscii(), wxNO_LEN, mode, posErr);
}

// decode the contents of the given string; the returned buffer is empty if an
// error occurs during decoding

wxMemoryBuffer DynSoft::DSBase64Library::wxBase64Decode(const wxString& src, wxBase64DecodeMode mode, size_t *posErr)
{
    // don't use str.length() here as the ASCII buffer is shorter than it for
    // strings with embedded NULs
    return wxBase64Decode(src.ToAscii(), wxNO_LEN, mode, posErr);
}

bool DynSoft::DSBase64Library::FileToBase64(const wxString &filename, wxString &base64String) {
	FILE *file = fopen(static_cast<const char *>(filename.mb_str(wxConvUTF8)), "r");
	if(!file)
		return false;
	
	fseek(file, 0, SEEK_END);
	const long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *content = static_cast<char *>(malloc(sizeof(char) * size));
	fread(content, size, sizeof(char), file);
	fclose(file);

	base64String = wxBase64Encode(content, size);

	free(content);

	return true;
}

bool DynSoft::DSBase64Library::Base64ToFile(const wxString &filename, const wxString &base64String) {
	FILE *file = fopen(static_cast<const char *>(filename.mb_str(wxConvUTF8)), "w");
	if(!file)
		return false;

	wxMemoryBuffer memoryBuffer(wxBase64Decode(base64String));
	fwrite(memoryBuffer.GetData(), memoryBuffer.GetDataLen(), sizeof(char), file);
	fclose(file);
	
	return true;
}

wxString DynSoft::DSBase64Library::Base64ToTemporaryFile(const wxString &base64String, wxString directory) {
	if(directory.IsEmpty()) {
		const wxString sep(wxFileName::GetPathSeparator());
		wxStandardPaths standardPaths = wxStandardPaths::Get();
		directory = standardPaths.GetTempDir();
		if(directory.Len() > 0 && directory[directory.Len() - 1] != sep)
			directory.Append(sep);
	}

	wxString fullPath;
	long i = 0;
	do {
		fullPath = directory + DSCasts::ToString(i++);
	} while(wxFileExists(fullPath));

	return Base64ToFile(fullPath, base64String) ? fullPath : wxString();
}

DynSoft::DSClassInfo DynSoft::DSBase64Library::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_BASE_64_LIBRARY_NAME,
		DS_BASE_64_LIBRARY_VERSION,
		DS_BASE_64_LIBRARY_AUTHOR
	);
}
