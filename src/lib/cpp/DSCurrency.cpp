#include "DSCurrency.h"
#include "DSCasts.h"
#include <math.h>

DynSoft::DSCurrency DynSoft::DSCurrency::Round() {
	const bool small = value < 0;
	if(small)
		value *= -1;

	value = value * 1000;
	long long tmpValue = (long long) value;
	value = tmpValue;
	value = value / 10;

	value = value + 0.5;

	value = floor(value);
	value = value / 100;

	if(small)
		value *= -1;

	return DSCurrency(value);
}

double DynSoft::DSCurrency::ToDouble() {
	Round();
	return value;
}

wxString DynSoft::DSCurrency::ToString() {
	wxString format(_N("%.2f"));
	wxString tmp(wxString::Format(format, ToDouble()));
	tmp.Replace(_N("."), _N(","));
	return tmp;
}

wxString DynSoft::DSCurrency::ToGermanString() {
	return ToString();
}

wxString DynSoft::DSCurrency::ToAmericanString() {
	wxString tmp(ToString());
	tmp.Replace(_N(","), _N("."));
	return tmp;
}

DynSoft::DSCurrency::DSCurrency(const long double value) {
	this->value = value;
}

DynSoft::DSCurrency::DSCurrency(const wxString &value) {
	this->value = DSCasts::ToDouble(value);
}

DynSoft::DSClassInfo DynSoft::DSCurrency::GetClassInfo() {
	return DSClassInfo(
		DS_CURRENCY_NAME,
		DS_CURRENCY_VERSION,
		DS_CURRENCY_AUTHOR
	);
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const DSCurrency value) {
	if(this != &value)
		this->value = value.value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const wxString &value) {
	this->value = DSCasts::ToDouble(value);
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const int value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const unsigned int value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const double value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const long double value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const long value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator=(const unsigned long value) {
	this->value = value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const DSCurrency value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value.value;
	return f;
}


DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const int value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const unsigned int value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const double value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const long double value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const long value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+(const unsigned long value) {
	DynSoft::DSCurrency f;
	f.value = this->value + value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const DSCurrency value) {
	this->value += value.value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const int value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const unsigned int value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const double value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const long double value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const long value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator+=(const unsigned long value) {
	this->value += value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const DSCurrency value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value.value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const int value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const unsigned int value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const double value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const long double value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const long value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-(const unsigned long value) {
	DynSoft::DSCurrency f;
	f.value = this->value - value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const DSCurrency value) {
	this->value -= value.value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const int value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const unsigned int value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const double value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const long double value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const long value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator-=(const unsigned long value) {
	this->value -= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const DSCurrency value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value.value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const int value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const unsigned int value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const double value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const long double value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const long value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*(const unsigned long value) {
	DynSoft::DSCurrency f;
	f.value = this->value * value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const DSCurrency value) {
	this->value *= value.value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const int value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const unsigned int value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const double value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const long double value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const long value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator*=(const unsigned long value) {
	this->value *= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const DSCurrency value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value.value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const int value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const unsigned int value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const double value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const long double value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const long value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/(const unsigned long value) {
	DynSoft::DSCurrency f;
	f.value = this->value / value;
	return f;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const DSCurrency value) {
	this->value /= value.value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const int value) {
	this->value /= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const unsigned int value) {
	this->value /= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const double value) {
	this->value /= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const long double value) {
	this->value /= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const long value) {
	this->value /= value;
	return *this;
}

DynSoft::DSCurrency DynSoft::DSCurrency::operator/=(const unsigned long value) {
	this->value /= value;
	return *this;
}

bool DynSoft::DSCurrency::operator<(const DynSoft::DSCurrency value) {
	return this->value < value.value;
}

bool DynSoft::DSCurrency::operator<(const long double value) {
	return this->value < value;
}

bool DynSoft::DSCurrency::operator>(const long double value) {
	return this->value > value;
}

bool DynSoft::DSCurrency::operator>(const DynSoft::DSCurrency value) {
	return this->value > value.value;
}

bool DynSoft::DSCurrency::operator<=(const DynSoft::DSCurrency value) {
	return this->value <= value.value;
}

bool DynSoft::DSCurrency::operator<=(const long double value) {
	return this->value <= value;
}

bool DynSoft::DSCurrency::operator>=(const DynSoft::DSCurrency value) {
	return this->value >= value.value;
}

bool DynSoft::DSCurrency::operator>=(const long double value) {
	return this->value >= value;
}

bool DynSoft::DSCurrency::operator!=(const DynSoft::DSCurrency value) {
	return this->value != value.value;
}

bool DynSoft::DSCurrency::operator==(const long double value) {
	return this->value == value;
}

bool DynSoft::DSCurrency::operator==(const DynSoft::DSCurrency value) {
	return this->value == value.value;
}
