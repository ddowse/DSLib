#include "DSCasts.h"

DynSoft::DSCasts::DSCasts() : DSLib() {
}

DynSoft::DSCasts::DSCasts(const wxString &value) : DSLib() {
	this->value = value;
}

DynSoft::DSCasts::DSCasts(const bool value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const short value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const unsigned short value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const int value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const unsigned int value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const long value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const unsigned long value) {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const float value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const double value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(const char *value) : DSLib() {
	this->value = ToString(value);
}

DynSoft::DSCasts::DSCasts(DSCurrency value) {
	this->value = value.ToString();
}

DynSoft::DSCasts::DSCasts(DSDateTime value) {
	this->value = value.ToDatabaseDateTime();
}

DynSoft::DSClassInfo DynSoft::DSCasts::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CASTS_NAME,
		DS_CASTS_VERSION,
		DS_CASTS_AUTHOR
	);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const wxString &value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const short value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const unsigned short value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const int value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const unsigned int value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const long value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const unsigned long value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const float value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const double value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(const char *value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(DSCurrency value) {
	return DSCasts(value);
}

DynSoft::DSCasts DynSoft::DSCasts::Convert(DSDateTime value) {
	return DSCasts(value);
}

char *DynSoft::DSCasts::ToChar() {
	return ToChar(value);
}

short DynSoft::DSCasts::ToShort() {
	return ToShort(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort() {
	return ToUnsignedShort(value);
}

int DynSoft::DSCasts::ToInt() {
	return ToInt(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt() {
	return ToUnsignedInt(value);
}

long DynSoft::DSCasts::ToLong() {
	return ToLong(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong() {
	return ToUnsignedLong(value);
}

float DynSoft::DSCasts::ToFloat() {
	return ToFloat(value);
}

double DynSoft::DSCasts::ToDouble() {
	return ToDouble(value);
}

bool DynSoft::DSCasts::ToBool() {
	return ToBool(value);
}

wxString DynSoft::DSCasts::ToString() {
	return value;
}

DynSoft::DSCurrency DynSoft::DSCasts::ToCurrency() {
	return DynSoft::DSCurrency(ToDouble(value));
}


char *DynSoft::DSCasts::ToChar(const wxString &value) {
	int length = strlen((const char *) value.mb_str(wxConvUTF8));
	char *result = new char[length + 1];
	strncpy(result, (const char *) value.mb_str(wxConvUTF8), length);
	result[length] = '\0';
	return result;
}

char *DynSoft::DSCasts::ToChar(const unsigned short value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const int value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const unsigned int value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const long value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const unsigned long value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const float value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(const double value) {
	return ToChar(ToString(value));
}

char *DynSoft::DSCasts::ToChar(DynSoft::DSCurrency value) {
	return ToChar(value.ToString());
}

char *DynSoft::DSCasts::ToChar(DSDateTime value) {
	return ToChar(value.ToDatabaseDateTime());
}


short DynSoft::DSCasts::ToShort(const wxString &value) {
	long result = 0;
	value.ToLong(&result);
	return ToShort(result);
}

short DynSoft::DSCasts::ToShort(const unsigned short value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const int value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const unsigned int value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const long value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const unsigned long value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const float value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const double value) {
	return static_cast<short>(value);
}

short DynSoft::DSCasts::ToShort(const char *value) {
	return ToShort(ToString(value));
}

short DynSoft::DSCasts::ToShort(DynSoft::DSCurrency value) {
	return ToShort(value.ToString());
}


unsigned short DynSoft::DSCasts::ToUnsignedShort(const wxString &value) {
	unsigned long result = 0;
	value.ToULong(&result);
	return ToUnsignedShort(result);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const short value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const int value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const unsigned int value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const long value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const unsigned long value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const float value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const double value) {
	return static_cast<unsigned short>(value);
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(const char *value) {
	return ToUnsignedShort(ToString(value));
}

unsigned short DynSoft::DSCasts::ToUnsignedShort(DynSoft::DSCurrency value) {
	return ToUnsignedShort(value.ToString());
}


int DynSoft::DSCasts::ToInt(const wxString &value) {
	long result = 0;
	value.ToLong(&result);
	return ToInt(result);
}

int DynSoft::DSCasts::ToInt(const short value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const unsigned short value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const unsigned int value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const long value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const unsigned long value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const float value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const double value) {
	return static_cast<int>(value);
}

int DynSoft::DSCasts::ToInt(const char *value) {
	return ToInt(ToString(value));
}

int DynSoft::DSCasts::ToInt(DynSoft::DSCurrency value) {
	return ToInt(value.ToString());
}


unsigned int DynSoft::DSCasts::ToUnsignedInt(const wxString &value) {
	unsigned long result = 0;
	value.ToULong(&result);
	return ToUnsignedInt(result);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const short value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const unsigned short value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const int value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const long value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const unsigned long value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const float value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const double value) {
	return static_cast<unsigned int>(value);
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(const char *value) {
	return ToUnsignedInt(ToString(value));
}

unsigned int DynSoft::DSCasts::ToUnsignedInt(DynSoft::DSCurrency value) {
	return ToUnsignedInt(value.ToString());
}


long DynSoft::DSCasts::ToLong(const wxString &value) {
	long result = 0;
	value.ToLong(&result);
	return result;
}

long DynSoft::DSCasts::ToLong(const short value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const unsigned short value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const int value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const unsigned int value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const unsigned long value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const float value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const double value) {
	return static_cast<long>(value);
}

long DynSoft::DSCasts::ToLong(const char *value) {
	return ToLong(ToString(value));
}

long DynSoft::DSCasts::ToLong(DynSoft::DSCurrency value) {
	return ToLong(value.ToString());
}


unsigned long DynSoft::DSCasts::ToUnsignedLong(const wxString &value) {
	unsigned long result = 0;
	value.ToULong(&result);
	return result;
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const short value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const unsigned short value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const int value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const unsigned int value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const long value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const float value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const double value) {
	return static_cast<unsigned long>(value);
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(const char *value) {
	return ToUnsignedLong(ToString(value));
}

unsigned long DynSoft::DSCasts::ToUnsignedLong(DynSoft::DSCurrency value) {
	return ToUnsignedLong(value.ToString());
}


float DynSoft::DSCasts::ToFloat(const wxString &value) {
	double result = 0.00;
	value.ToDouble(&result);
	return ToFloat(result);
}

float DynSoft::DSCasts::ToFloat(const short value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const unsigned short value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const int value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const unsigned int value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const long value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const unsigned long value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const double value) {
	return static_cast<float>(value);
}

float DynSoft::DSCasts::ToFloat(const char *value) {
	return ToFloat(ToString(value));
}

float DynSoft::DSCasts::ToFloat(DynSoft::DSCurrency value) {
	return ToFloat(value.ToString());
}


double DynSoft::DSCasts::ToDouble(wxString value) {
	double result = 0.00;
	value.Replace(_N("."), _N(","));
	value.ToDouble(&result);
	
	wxString tmp(ToString(result));
	tmp.Replace(_N("."), _N(","));
	if(tmp.Mid(0, value.Length()) == value)
		return result;

	value.Replace(_N(","), _N("."));
	value.ToDouble(&result);

	return result;
}

double DynSoft::DSCasts::ToDouble(const short value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const unsigned short value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const int value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const unsigned int value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const long value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const unsigned long value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const float value) {
	return static_cast<double>(value);
}

double DynSoft::DSCasts::ToDouble(const char *value) {
	return ToDouble(ToString(value));
}

double DynSoft::DSCasts::ToDouble(DynSoft::DSCurrency value) {
	return ToDouble(value.ToString());
}

bool DynSoft::DSCasts::ToBool(wxString value) {
	value.LowerCase();
	return value == _N("t")    ||
		   value == _N("true") ||
		   value == _N("yes")  ||
		   value == _N("y")    ||
		   value == _N("j")    ||
		   value == _N("ja")   ||
		   value == _N("on")   ||
		   value == _N("ok");
}

bool DynSoft::DSCasts::ToBool(const char *value) {
	return ToBool(ToString(value));
}

wxString DynSoft::DSCasts::ToString(const short value) {
	return wxString::Format(_N("%hd"), value);
}

wxString DynSoft::DSCasts::ToString(const unsigned short value) {
	return wxString::Format(_N("%hd"), value);
}

wxString DynSoft::DSCasts::ToString(const int value) {
	return wxString::Format(_N("%i"), value);
}

wxString DynSoft::DSCasts::ToString(const unsigned int value) {
	return wxString::Format(_N("%u"), value);
}

wxString DynSoft::DSCasts::ToString(const long value) {
	return wxString::Format(_N("%ld"), value);
}

wxString DynSoft::DSCasts::ToString(const unsigned long value) {
	return wxString::Format(_N("%ld"), value);
}

wxString DynSoft::DSCasts::ToString(const float value) {
	return wxString::Format(_N("%f"), value);
}

wxString DynSoft::DSCasts::ToString(const double value) {
	return wxString::Format(_("%lf"), value);
}

wxString DynSoft::DSCasts::ToString(const bool value, const bool upperCase, const bool shortResult) {
	wxString t(shortResult ? _N("t") : _N("true"));
	wxString f(shortResult ? _N("f") : _N("false"));

	if(upperCase) {
		t.MakeUpper();
		f.MakeUpper();
	}

	return value ? t : f;
}

wxString DynSoft::DSCasts::ToString(const char *value) {
	if(!value)
		return wxEmptyString;

	return wxString(value, wxConvUTF8);
}

wxString DynSoft::DSCasts::ToString(DynSoft::DSCurrency value) {
	return value.ToString();
}

wxString DynSoft::DSCasts::ToString(DynSoft::DSDateTime value) {
	return value.ToDatabaseDateTime();
}

DynSoft::DSDateTime DynSoft::DSCasts::ToDateTime(const wxChar separator) {
	return DSDateTime(value, separator);
}
