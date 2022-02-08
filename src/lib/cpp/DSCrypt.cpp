#include "DSCrypt.h"
#include "DSCasts.h"
#include <mcrypt.h>

DynSoft::DSCrypt::DSCrypt(
	const unsigned int algorithm,
	const wxString &algorithmPath,
	const unsigned int method,
	const wxString &methodPath
) {
	tmpAlgorithm     = NULL;
	tmpAlgorithmPath = NULL;
	tmpMethod        = NULL;
	tmpMethodPath    = NULL;
	tmpIv            = NULL;
	tmpPassword      = NULL;
	passwordLength   = 0;

	SetAlgorithm(algorithm);
	SetAlgorithmPath(algorithmPath);
	SetMethod(method);
	SetMethodPath(methodPath);
}

DynSoft::DSCrypt::~DSCrypt() {
	delete [] tmpAlgorithm;
	delete [] tmpAlgorithmPath;
	delete [] tmpMethod;
	delete [] tmpMethodPath;
	delete [] tmpIv;
	delete [] tmpPassword;
}

DynSoft::DSClassInfo DynSoft::DSCrypt::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CRYPT_VERSION,
		DS_CRYPT_NAME,
		DS_CRYPT_AUTHOR
	);
}

wxString DynSoft::DSCrypt::GetAlgorithmString(const unsigned int algorithm) {
	wxString algorithmString;

	switch(algorithm) {
		case DES:         algorithmString = _N("des");          break;
		case TRIPPLEDES:  algorithmString = _N("3des");         break;
		case CAST128:     algorithmString = _N("cast-128");     break;
		case CAST256:     algorithmString = _N("cast-256");     break;
		case XTEA:        algorithmString = _N("xtea");         break;
		case THREEWAY:    algorithmString = _N("3-way");        break;
		case SKIPJACK:    algorithmString = _N("skipjack");     break;
		case BLOWFISH:    algorithmString = _N("blowfish");     break;
		case TWOFISH:     algorithmString = _N("twofish");      break;
		case LOKI97:      algorithmString = _N("loki97");       break;
		case RC2:         algorithmString = _N("rc2");          break;
		case ARCFOUR:     algorithmString = _N("arcfour");      break;
		case RC6:         algorithmString = _N("rc6");          break;
		case RIJNDAEL128: algorithmString = _N("rijndael-128"); break;
		case RIJNDAEL192: algorithmString = _N("rijndael-192"); break;
		case RIJNDAEL256: algorithmString = _N("rijndael-256"); break;
		case MARS:        algorithmString = _N("mars");         break;
		case PANAMA:      algorithmString = _N("panama");       break;
		case WAKE:        algorithmString = _N("wake");         break;
		case SERPENT:     algorithmString = _N("serpent");      break;
		case IDEA:        algorithmString = _N("idea");         break;
		case ENIGMA:      algorithmString = _N("enigma");       break;
		case GOST:        algorithmString = _N("gost");         break;
		case SAFERK64:    algorithmString = _N("safer k-64");   break;
		case SAFERK128:   algorithmString = _N("safer k-128");  break;
		case SAFERSK64:   algorithmString = _N("safer sk-64");  break;
		case SAFERSK128:  algorithmString = _N("safer sk-128"); break;
		case SAFERPLUS:   algorithmString = _N("safer+");       break;
	}

	return algorithmString;
}

wxString DynSoft::DSCrypt::GetMethodString(const unsigned int method) {
	wxString methodString;

	switch(method) {
		case STREAM: methodString = _N("stream"); break;
		case ECB:    methodString = _N("ecb");    break;
		case CBC:    methodString = _N("cbc");    break;
		case CFB:    methodString = _N("cfb");    break;
		case OFB:    methodString = _N("ofb");    break;
		case NOFB:   methodString = _N("nofb");   break;
		case NCFB:   methodString = _N("ncfb");   break;
		case CTR:    methodString = _N("ctr");    break;
	}

	return methodString;
}

void DynSoft::DSCrypt::SetAlgorithm(const unsigned int algorithm) {
	this->algorithm = algorithm;

	delete [] tmpAlgorithmPath;
	tmpAlgorithm = (char *) DynSoft::DSCasts::ToChar(GetAlgorithmString(algorithm));
}

unsigned int DynSoft::DSCrypt::GetAlgorithm() const {
	return algorithm;
}

void DynSoft::DSCrypt::SetAlgorithmPath(const wxString &algorithmPath) {
	this->algorithmPath = algorithmPath;

	delete [] tmpAlgorithmPath;
	tmpAlgorithmPath = algorithmPath.IsEmpty() ? NULL : (char *) DynSoft::DSCasts::ToChar(algorithmPath);
}

wxString DynSoft::DSCrypt::GetAlgorithmPath() const {
	return algorithmPath;
}

void DynSoft::DSCrypt::SetMethod(const unsigned int method) {
	this->method = method;

	delete [] tmpMethod;
	tmpMethod = (char *) DynSoft::DSCasts::ToChar(GetMethodString(method));
}

unsigned int DynSoft::DSCrypt::GetMethod() const {
	return method;
}

void DynSoft::DSCrypt::SetMethodPath(const wxString &methodPath) {
	this->methodPath = methodPath;

	delete [] tmpMethodPath;
	tmpMethodPath = methodPath.IsEmpty() ? NULL : (char *) (GetMethodPath().IsEmpty() ? NULL : DynSoft::DSCasts::ToChar(GetMethodPath()));
}

wxString DynSoft::DSCrypt::GetMethodPath() const {
	return methodPath;
}

void DynSoft::DSCrypt::SetPassword(const wxString &password) {
	this->password = password;

	delete [] tmpPassword;
	tmpPassword    = (char *) DynSoft::DSCasts::ToChar(GetPassword());
	passwordLength = password.Length();
}

wxString DynSoft::DSCrypt::GetPassword() const {
	return password;
}

void DynSoft::DSCrypt::SetIV(const wxString &iv) {
	this->iv = iv;

	delete [] tmpIv;
	tmpIv = (char *) DynSoft::DSCasts::ToChar(GetIV());
}

wxString DynSoft::DSCrypt::GetIV() const {
	return iv;
}

bool DynSoft::DSCrypt::Encrypt(void *buffer, int bufferLength) {
	return Crypt(buffer, bufferLength, true);
}

bool DynSoft::DSCrypt::Decrypt(void *buffer, int bufferLength) {
	return Crypt(buffer, bufferLength, false);
}

bool DynSoft::DSCrypt::Crypt(void *buffer, int bufferLength, const bool encrypt) {
	if(!buffer)
		return false;

	MCRYPT td = mcrypt_module_open(tmpAlgorithm, tmpAlgorithmPath, tmpMethod, tmpMethodPath);
	if(bufferLength % mcrypt_enc_get_block_size(td) != 0)
		return false;

	char *IV = (char *) malloc(mcrypt_enc_get_iv_size(td));
	strncpy(IV, tmpIv, mcrypt_enc_get_iv_size(td));
	mcrypt_generic_init(td, tmpPassword, passwordLength, IV);
	free(IV);
	if(encrypt)
		mcrypt_generic(td, buffer, bufferLength);
	else
		mdecrypt_generic(td, buffer, bufferLength);

	mcrypt_generic_deinit(td);
	mcrypt_module_close(td);

	return true;	
}

void DynSoft::DSCrypt::PrintCipher(void *buffer, const int bufferLength) {
	for(int v = 0; v < bufferLength; v++) {
		printf("%d ", ((char *)buffer)[v]);
	}
	printf("\n");
}

char *DynSoft::DSCrypt::EncryptString(const wxString &content, int &length) {
	const char *tmpContent = DSCasts::ToChar(content); // Fucking !Unicode
	const int blocksize    = GetBlockSize();
	const int realLength   = strlen(tmpContent) + 1;
	length                 = realLength + (blocksize - (realLength % blocksize));
	char *buffer           = new char [length];
	strncpy(buffer, tmpContent, length);
	delete [] tmpContent;
	
	if(!Crypt(buffer, length, true)) {
		delete [] buffer;
		return NULL;
	}

	return buffer;
}

wxString DynSoft::DSCrypt::DecryptString(char *buffer, const int length) {
	if(!buffer)
		return wxEmptyString;

	Decrypt(buffer, length);
	
	return DynSoft::DSCasts::ToString(buffer);
}

int DynSoft::DSCrypt::GetBlockSize() {
	MCRYPT td = mcrypt_module_open(tmpAlgorithm, tmpAlgorithmPath, tmpMethod, tmpMethodPath);
	const int blocksize = mcrypt_enc_get_block_size(td);
	mcrypt_module_close(td);
	return blocksize;
}
