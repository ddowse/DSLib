#ifndef DS_JSON_TYPE_H_
#define DS_JSON_TYPE_H_

#include "DSType.h"
#include "DSClassInfo.h"
#include <wx/jsonval.h>

#define DS_JSON_TYPE_VERSION        _N("0.0.1")
#define DS_JSON_TYPE_NAME           _N("DSKeyValueType")
#define DS_JSON_TYPE_AUTHOR         _N("Thorsten Geppert (tgeppert@gug-it.de)")

namespace DynSoft {

	class DSJSONType : public wxJSONValue, public DSType {

		public:
			DSJSONType();
			DSJSONType(DSJSONType &type);
			DSJSONType(wxJSONValue value);
			DSJSONType(int i);
			DSJSONType(unsigned int i);
			DSJSONType(short i);
			DSJSONType(unsigned short i);
			DSJSONType(long int i);
			DSJSONType(unsigned long int i);
			DSJSONType(wxInt64 i);
			DSJSONType(wxUint64 ui);
			DSJSONType(bool b);
			DSJSONType(double d);
			DSJSONType(const wxChar *str);
			DSJSONType(const wxString &str);
			DSJSONType(const DSJSONType &other);

			DSClassInfo GetClassInfo();

			wxString ToString() const;
			void Print() const;

	};

}

#endif /* DS_JSON_TYPE_H_ */
