#ifndef DS_KEY_VALUE_TYPE_H_
#define DS_KEY_VALUE_TYPE_H_

#include "DSType.h"
#include "DSClassInfo.h"
#include "DSCasts.h"

#define DS_KEY_VALUE_TYPE_VERSION        _N("0.0.1")
#define DS_KEY_VALUE_TYPE_NAME           _N("DSKeyValueType")
#define DS_KEY_VALUE_TYPE_AUTHOR         _N("Thorsten Geppert (tgeppert@gug-it.de)")

namespace DynSoft {

	class DSKeyValueType : public DSType {

		public:
			typedef enum {
				UNKNOWN = 0,
				WXSTRING,
				BOOL,
				SHORT,
				UNSIGNED_SHORT,
				INT,
				UNSIGNED_INT,
				LONG,
				UNSIGNED_LONG,
				FLOAT,
				DOUBLE,
				CHAR_P,
				DSCURRENCY,
				DSDATETIME
			} DataType;

			DSKeyValueType();
			DSKeyValueType(const wxString &key, DSCasts value);
			DSKeyValueType(const wxString &key, const wxString &value);
			DSKeyValueType(const wxString &key, const bool value);
			DSKeyValueType(const wxString &key, const short value);
			DSKeyValueType(const wxString &key, const unsigned short value);
			DSKeyValueType(const wxString &key, const int value);
			DSKeyValueType(const wxString &key, const unsigned int value);
			DSKeyValueType(const wxString &key, const long value);
			DSKeyValueType(const wxString &key, const unsigned long value);
			DSKeyValueType(const wxString &key, const float value);
			DSKeyValueType(const wxString &key, const double value);
			DSKeyValueType(const wxString &key, const char *value);
			DSKeyValueType(const wxString &key, DSCurrency value);
			DSKeyValueType(const wxString &key, DSDateTime value);

			DSClassInfo GetClassInfo();

			void SetKey(const wxString &key);
			wxString GetKey() const;

			void SetValue(DSCasts value);
			void SetValue(const wxString &value);
			void SetValue(const bool value);
			void SetValue(const short value);
			void SetValue(const unsigned short value);
			void SetValue(const int value);
			void SetValue(const unsigned int value);
			void SetValue(const long value);
			void SetValue(const unsigned long value);
			void SetValue(const float value);
			void SetValue(const double value);
			void SetValue(const char *value);
			void SetValue(DSCurrency value);
			void SetValue(DSDateTime value);
			DSCasts GetValue();

			wxString ToString();

			void SetDataType(DataType dataType);
			DataType GetDataType() const;

		protected:
			wxString key;
			DSCasts value;
			DataType dataType;

	};

}

#endif /* DS_KEY_VALUE_TYPE_H_ */
