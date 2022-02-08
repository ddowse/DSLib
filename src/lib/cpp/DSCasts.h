#ifndef DS_CASTS_H_
#define DS_CASTS_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSCurrency.h"
#include "DSDateTime.h"

#define DS_CASTS_VERSION	_N("0.3.5")
#define DS_CASTS_NAME		_N("DSCasts")
#define DS_CASTS_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCasts : public DSLib {

		public:
			DSCasts();
			DSCasts(const wxString &value);
			DSCasts(const bool value);
			DSCasts(const short value);
			DSCasts(const unsigned short value);
			DSCasts(const int value);
			DSCasts(const unsigned int value);
			DSCasts(const long value);
			DSCasts(const unsigned long value);
			DSCasts(const float value);
			DSCasts(const double value);
			DSCasts(const char *value);
			DSCasts(DSCurrency value);
			DSCasts(DSDateTime value);

			DSClassInfo GetClassInfo();

			static DSCasts Convert(const wxString &value);
			static DSCasts Convert(const short value);
			static DSCasts Convert(const unsigned short value);
			static DSCasts Convert(const int value);
			static DSCasts Convert(const unsigned int value);
			static DSCasts Convert(const long value);
			static DSCasts Convert(const unsigned long value);
			static DSCasts Convert(const float value);
			static DSCasts Convert(const double value);
			static DSCasts Convert(const char *value);
			static DSCasts Convert(DSCurrency value);
			static DSCasts Convert(DSDateTime value);

			char *ToChar();
			short ToShort();
			unsigned short ToUnsignedShort();
			int ToInt();
			unsigned int ToUnsignedInt();
			long ToLong();
			unsigned long ToUnsignedLong();
			float ToFloat();
			double ToDouble();
			bool ToBool();
			wxString ToString();
			DSCurrency ToCurrency();
			DSDateTime ToDateTime(const wxChar separator = '-');

			static char *ToChar(const wxString &value);
			static char *ToChar(const unsigned short value);
			static char *ToChar(const int value);
			static char *ToChar(const unsigned int value);
			static char *ToChar(const long value);
			static char *ToChar(const unsigned long value);
			static char *ToChar(const float value);
			static char *ToChar(const double value);
			static char *ToChar(DSCurrency value);
			static char *ToChar(DSDateTime value);

			static short ToShort(const wxString &value);
			static short ToShort(const unsigned short value);
			static short ToShort(const int value);
			static short ToShort(const unsigned int value);
			static short ToShort(const long value);
			static short ToShort(const unsigned long value);
			static short ToShort(const float value);
			static short ToShort(const double value);
			static short ToShort(const char *value);
			static short ToShort(DSCurrency value);

			static unsigned short ToUnsignedShort(const wxString &value);
			static unsigned short ToUnsignedShort(const short value);
			static unsigned short ToUnsignedShort(const int value);
			static unsigned short ToUnsignedShort(const unsigned int value);
			static unsigned short ToUnsignedShort(const long value);
			static unsigned short ToUnsignedShort(const unsigned long value);
			static unsigned short ToUnsignedShort(const float value);
			static unsigned short ToUnsignedShort(const double value);
			static unsigned short ToUnsignedShort(const char *value);
			static unsigned short ToUnsignedShort(DSCurrency value);

			static int ToInt(const wxString &value);
			static int ToInt(const short value);
			static int ToInt(const unsigned short value);
			static int ToInt(const unsigned int value);
			static int ToInt(const long value);
			static int ToInt(const unsigned long value);
			static int ToInt(const float value);
			static int ToInt(const double value);
			static int ToInt(const char *value);
			static int ToInt(DSCurrency value);

			static unsigned int ToUnsignedInt(const wxString &value);
			static unsigned int ToUnsignedInt(const short value);
			static unsigned int ToUnsignedInt(const unsigned short value);
			static unsigned int ToUnsignedInt(const int value);
			static unsigned int ToUnsignedInt(const long value);
			static unsigned int ToUnsignedInt(const unsigned long value);
			static unsigned int ToUnsignedInt(const float value);
			static unsigned int ToUnsignedInt(const double value);
			static unsigned int ToUnsignedInt(const char *value);
			static unsigned int ToUnsignedInt(DSCurrency value);

			static long ToLong(const wxString &value);
			static long ToLong(const short value);
			static long ToLong(const unsigned short value);
			static long ToLong(const int value);
			static long ToLong(const unsigned int value);
			static long ToLong(const unsigned long value);
			static long ToLong(const float value);
			static long ToLong(const double value);
			static long ToLong(const char *value);
			static long ToLong(DSCurrency value);

			static unsigned long ToUnsignedLong(const wxString &value);
			static unsigned long ToUnsignedLong(const short value);
			static unsigned long ToUnsignedLong(const unsigned short value);
			static unsigned long ToUnsignedLong(const int value);
			static unsigned long ToUnsignedLong(const unsigned int value);
			static unsigned long ToUnsignedLong(const long value);
			static unsigned long ToUnsignedLong(const float value);
			static unsigned long ToUnsignedLong(const double value);
			static unsigned long ToUnsignedLong(const char *value);
			static unsigned long ToUnsignedLong(DSCurrency value);

			static float ToFloat(const wxString &value);
			static float ToFloat(const short value);
			static float ToFloat(const unsigned short value);
			static float ToFloat(const int value);
			static float ToFloat(const unsigned int value);
			static float ToFloat(const long value);
			static float ToFloat(const unsigned long value);
			static float ToFloat(const double value);
			static float ToFloat(const char *value);
			static float ToFloat(DSCurrency value);

			static double ToDouble(wxString value);
			static double ToDouble(const short value);
			static double ToDouble(const unsigned short value);
			static double ToDouble(const int value);
			static double ToDouble(const unsigned int value);
			static double ToDouble(const long value);
			static double ToDouble(const unsigned long value);
			static double ToDouble(const float value);
			static double ToDouble(const char *value);
			static double ToDouble(DSCurrency value);

			static bool ToBool(wxString value);
			static bool ToBool(const char *value);

			static wxString ToString(const short value);
			static wxString ToString(const unsigned short value);
			static wxString ToString(const int value);
			static wxString ToString(const unsigned int value);
			static wxString ToString(const long value);
			static wxString ToString(const unsigned long value);
			static wxString ToString(const float value);
			static wxString ToString(const double value);
			static wxString ToString(const bool value, const bool upperCase = false, const bool shortResult = false);
			static wxString ToString(const char *value);
			static wxString ToString(DSCurrency value);
			static wxString ToString(DSDateTime value);

		protected:
			wxString value;

	};

}

#endif /* DS_CASTS_H_ */
