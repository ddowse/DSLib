#ifndef DS_CURRENCY_H_
#define DS_CURRENCY_H_

//#ifndef TFLOAT_H_
//	#define TFLOAT_H_
//#endif

//#define TFloat DSCurrency

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSType.h"

#define DS_CURRENCY_VERSION _N("0.8.7")
#define DS_CURRENCY_NAME    _N("DSCurrency")
#define DS_CURRENCY_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCurrency : public DSType {

		public:
			DSClassInfo GetClassInfo();

			DSCurrency(const long double value = 0.00);
			DSCurrency(const wxString &value);

			// FIXME DSBind
			double ToDouble();
			wxString ToString();
			wxString ToGermanString();
			wxString ToAmericanString();
			DSCurrency Round();

			DSCurrency operator=(const DSCurrency value);
			DSCurrency operator=(const wxString &value);
			DSCurrency operator=(const int value);
			DSCurrency operator=(const unsigned int value);
			DSCurrency operator=(const double value);
			DSCurrency operator=(const long double value);
			DSCurrency operator=(const long value);
			DSCurrency operator=(const unsigned long value);
			DSCurrency operator+(const DSCurrency value);
			DSCurrency operator+(const int value);
			DSCurrency operator+(const unsigned int value);
			DSCurrency operator+(const double value);
			DSCurrency operator+(const long double value);
			DSCurrency operator+(const long value);
			DSCurrency operator+(const unsigned long value);
			DSCurrency operator+=(const DSCurrency value);
			DSCurrency operator+=(const int value);
			DSCurrency operator+=(const unsigned int value);
			DSCurrency operator+=(const double value);
			DSCurrency operator+=(const long double value);
			DSCurrency operator+=(const long value);
			DSCurrency operator+=(const unsigned long value);
			DSCurrency operator-(const DSCurrency value);
			DSCurrency operator-(const int value);
			DSCurrency operator-(const unsigned int value);
			DSCurrency operator-(const double value);
			DSCurrency operator-(const long double value);
			DSCurrency operator-(const long value);
			DSCurrency operator-(const unsigned long value);
			DSCurrency operator-=(const DSCurrency value);
			DSCurrency operator-=(const int value);
			DSCurrency operator-=(const unsigned int value);
			DSCurrency operator-=(const double value);
			DSCurrency operator-=(const long double value);
			DSCurrency operator-=(const long value);
			DSCurrency operator-=(const unsigned long value);
			DSCurrency operator*(const DSCurrency value);
			DSCurrency operator*(const int value);
			DSCurrency operator*(const unsigned int value);
			DSCurrency operator*(const double value);
			DSCurrency operator*(const long double value);
			DSCurrency operator*(const long value);
			DSCurrency operator*(const unsigned long value);
			DSCurrency operator*=(const DSCurrency value);
			DSCurrency operator*=(const int value);
			DSCurrency operator*=(const unsigned int value);
			DSCurrency operator*=(const double value);
			DSCurrency operator*=(const long double value);
			DSCurrency operator*=(const long value);
			DSCurrency operator*=(const unsigned long value);
			DSCurrency operator/(const DSCurrency value);
			DSCurrency operator/(const int value);
			DSCurrency operator/(const unsigned int value);
			DSCurrency operator/(const double value);
			DSCurrency operator/(const long double value);
			DSCurrency operator/(const long value);
			DSCurrency operator/(const unsigned long value);
			DSCurrency operator/=(const DSCurrency value);
			DSCurrency operator/=(const int value);
			DSCurrency operator/=(const unsigned int value);
			DSCurrency operator/=(const double value);
			DSCurrency operator/=(const long double value);
			DSCurrency operator/=(const long value);
			DSCurrency operator/=(const unsigned long value);
			bool operator<(const DSCurrency value);
			bool operator<(const long double value);
			bool operator>(const DSCurrency value);
			bool operator>(const long double value);
			bool operator<=(const DSCurrency value);
			bool operator<=(const long double value);
			bool operator>=(const DSCurrency value);
			bool operator>=(const long double value);
			bool operator!=(const DSCurrency value);
			bool operator==(const long double value);
			bool operator==(const DSCurrency value);

		protected:
			long double value;
			unsigned int places;

	};

}

#endif /* DS_CURRENCY_H_ */
