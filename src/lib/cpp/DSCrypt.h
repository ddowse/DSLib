#ifndef DS_CRYPT_H_
#define DS_CRYPT_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_CRYPT_VERSION _N("0.0.1")
#define DS_CRYPT_NAME    _N("DSCrypt")
#define DS_CRYPT_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCrypt : public DSLib {
	
		public:
			enum Methods { STREAM, ECB, CBC, CFB, OFB, NOFB, NCFB, CTR };
			enum Algorithms {
				DES,
				TRIPPLEDES,
				CAST128,
				CAST256,
				XTEA,
				THREEWAY,
				SKIPJACK,
				BLOWFISH,
				TWOFISH,
				LOKI97,
				RC2,
				ARCFOUR,
				RC6,
				RIJNDAEL128,
				RIJNDAEL192,
				RIJNDAEL256,
				MARS,
				PANAMA,
				WAKE,
				SERPENT,
				IDEA,
				ENIGMA,
				GOST,
				SAFERK64,
				SAFERK128,
				SAFERSK64,
				SAFERSK128,
				SAFERPLUS
			};

			DSCrypt(
				const unsigned int algorithm  = RIJNDAEL256,
				const wxString &algorithmPath = wxEmptyString,
				const unsigned int method     = CBC,
				const wxString &methodPath    = wxEmptyString
			);
			~DSCrypt();

			DSClassInfo GetClassInfo();

			wxString GetAlgorithmString(const unsigned int algorithm);
			wxString GetMethodString(const unsigned int method);

			void SetAlgorithm(const unsigned int algorithm);
			unsigned int GetAlgorithm() const;
			void SetAlgorithmPath(const wxString &algorithmPath);
			wxString GetAlgorithmPath() const;

			void SetMethod(const unsigned int method);
			unsigned int GetMethod() const;
			void SetMethodPath(const wxString &methodPath);
			wxString GetMethodPath() const;

			void SetPassword(const wxString &password);
			wxString GetPassword() const;

			void SetIV(const wxString &iv);
			wxString GetIV() const;

			bool Encrypt(void *buffer, int bufferLength);
			bool Decrypt(void *buffer, int bufferLength);

			char *EncryptString(const wxString &content, int &length);
			wxString DecryptString(char *buffer, const int length);

			int GetBlockSize();

			void PrintCipher(void *buffer, const int bufferLength);

		protected:
			unsigned int algorithm;
			wxString algorithmPath;
			unsigned int method;
			wxString methodPath;
			wxString password;
			wxString iv;
			unsigned int passwordLength;

			char *tmpAlgorithm;
			char *tmpAlgorithmPath;
			char *tmpMethod;
			char *tmpMethodPath;
			char *tmpIv;
			char *tmpPassword;

			bool Crypt(void *buffer, int bufferLength, const bool encrypt);

	};

}

#endif /* DS_CRYPT_H_ */
