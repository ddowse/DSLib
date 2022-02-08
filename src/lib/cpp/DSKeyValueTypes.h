#ifndef DS_KEY_VALUE_TYPES_H_
#define DS_KEY_VALUE_TYPES_H_

#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSTemplateContainer.h"
#include "DSCasts.h"
#include "DSKeyValueType.h"

#define DS_KEY_VALUE_TYPES_VERSION        _N("0.0.1")
#define DS_KEY_VALUE_TYPES_NAME           _N("DSKeyValueTypes")
#define DS_KEY_VALUE_TYPES_AUTHOR         _N("Thorsten Geppert (tgeppert@gug-it.de)")

namespace DynSoft {

	class DSKeyValueTypes : public DSTemplateContainer<DSKeyValueType *> {

		public:
			DSKeyValueTypes(const bool autoCleanUp = true);
			~DSKeyValueTypes();

			DSClassInfo GetClassInfo();

			void SetAutoCleanUp(const bool autoCleanUp);
			bool IsAutoCleanUp() const;

			unsigned int Count();

			DSKeyValueType *GetOrCreate(const wxString &key, const wxString &value = wxEmptyString);

			void Push(const wxString &key, DSCasts value);
			void Push(const wxString &key, const wxString &value);
			void Push(const wxString &key, const bool value);
			void Push(const wxString &key, const short value);
			void Push(const wxString &key, const unsigned short value);
			void Push(const wxString &key, const int value);
			void Push(const wxString &key, const unsigned int value);
			void Push(const wxString &key, const long value);
			void Push(const wxString &key, const unsigned long value);
			void Push(const wxString &key, const float value);
			void Push(const wxString &key, const double value);
			void Push(const wxString &key, const char *value);
			void Push(const wxString &key, DSCurrency value);
			void Push(const wxString &key, DSDateTime value);
			DSCasts Pull(const wxString &key);
			DSCasts Pull(const unsigned int index);
			bool Delete(const wxString &key);
			bool Delete(const unsigned int index);

			bool PushDSKeyValueType(DSKeyValueType *keyValueType, const bool deleteIfAlreadyExists = true);
			DSKeyValueType *PullDSKeyValueType(const wxString &key);
			DSKeyValueType *PullDSKeyValueType(const unsigned int index);

			wxString ToString(const wxString &delimiter = _N("\n"));
			wxString NonEmptyToString(
				const wxString &keyDelimiter = _N(": "),
				const wxString &delimiter = _N("\n")
			);

			bool Exists(const wxString &key);
		
		protected:
			bool autoCleanUp;

	};

}

#endif /* DS_KEY_VALUE_TYPES_H_ */
