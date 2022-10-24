#ifndef DS_ENTITY_H_
#define DS_ENTITY_H_

#include <wx/wx.h>
#include "DSCasts.h"
#include "DSClassInfo.h"
#include "DSTemplateContainer.h"

#define DS_ENTITY_NAME			_N("DSEntity")
#define DS_ENTITY_VERSION		_N("0.0.8")
#define DS_ENTITY_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_ENTITY_TYPE_NAME		_N("DSEntityType")
#define DS_ENTITY_TYPE_VERSION	_N("0.0.3")
#define DS_ENTITY_TYPE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSEntity : public DSLib {
	
		public:
			class DSEntityType : public DSCasts {
				
				public:
					typedef unsigned int DSResultType;
					static const DSResultType DS_RESULT_TYPE_WXSTRING       =  0;
					static const DSResultType DS_RESULT_TYPE_SHORT          =  1;
					static const DSResultType DS_RESULT_TYPE_UNSIGNED_SHORT =  2;
					static const DSResultType DS_RESULT_TYPE_INT            =  3;
					static const DSResultType DS_RESULT_TYPE_UNSIGNED_INT   =  4;
					static const DSResultType DS_RESULT_TYPE_LONG           =  5;
					static const DSResultType DS_RESULT_TYPE_UNSIGNED_LONG  =  6;
					static const DSResultType DS_RESULT_TYPE_FLOAT          =  7;
					static const DSResultType DS_RESULT_TYPE_DOUBLE         =  8;
					static const DSResultType DS_RESULT_TYPE_CHAR_POINTER   =  9;
					static const DSResultType DS_RESULT_TYPE_DSCURRENCY     = 10;
					static const DSResultType DS_RESULT_TYPE_BOOL           = 11;
					static const DSResultType DS_RESULT_TYPE_DSDATETIME     = 12;

				public:
					DSEntityType(const wxString &key, const wxString &value, const bool delimeters = true, const bool escape = true, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const bool value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const short value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const unsigned short value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const int value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const unsigned int value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const long value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const unsigned long value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const float value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const double value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, const char *value, const bool delimeters = true, const bool escape = true, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, DSCurrency value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
					DSEntityType(const wxString &key, DSDateTime value, const bool delimeters = true, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);

					void SetKey(const wxString &key);
					wxString GetKey() const;

					void SetDelimiters(const bool delimeters);
					bool GetDelimiters() const;

					void SetEscape(const bool escape);
					bool GetEscape() const;

					void SetField(const wxString &field);
					wxString GetField() const;

					void SetLength(const unsigned int length);
					unsigned int GetLength() const;

					void SetNull(const bool null);
					bool GetNull() const;

					void SetType(const DSResultType type);
					DSResultType GetType() const;

				protected:
					void SetParameters(
						const wxString &key,
						const bool delimeters,
						const bool escape,
						const wxString &field,
						const unsigned int length,
						const bool null,
						const DSResultType type
					);

					wxString key;
					bool delimeters;
					bool escape;
					wxString field;
					unsigned int length;
					bool null;
					DSResultType type;
				
			};

		public:
			DSEntity();
			DSEntity(
				const wxString &name,
				const wxString &primaryKey,
				const wxString &foreignKey = wxEmptyString
			);
			virtual ~DSEntity();

			DSClassInfo GetClassInfo();

			typedef enum {
				DS_ENTITY = 0,
				DS_DATABASE_ENTITY,
				DS_POSTGRESQL_DATABASE_ENTITY,
				DS_MYSQL_DATABASE_ENTITY,
				DS_SQLITE_DATABASE_ENTITY
			} DSEntityInternalType;

			DSEntityInternalType GetInternalType() const;

			void Set(const wxString &key, const wxString &value = wxEmptyString, const bool delimeters = true, const bool escape = true, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const bool value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const short value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const unsigned short value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const int value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const unsigned int value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const long value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const unsigned long value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const float value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const double value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, const char *value, const bool delimeters = true, const bool escape = true, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, DSCurrency value, const bool delimeters = false, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);
			void Set(const wxString &key, DSDateTime value, const bool delimeters = true, const bool escape = false, const wxString &field = wxEmptyString, const unsigned int length = 0, const bool null = true);

			bool SetValue(const wxString &key, const wxString &value = wxEmptyString);
			bool SetValue(const wxString &key, const bool value);
			bool SetValue(const wxString &key, const short value);
			bool SetValue(const wxString &key, const unsigned short value);
			bool SetValue(const wxString &key, const int value);
			bool SetValue(const wxString &key, const unsigned int value);
			bool SetValue(const wxString &key, const long value);
			bool SetValue(const wxString &key, const unsigned long value);
			bool SetValue(const wxString &key, const float value);
			bool SetValue(const wxString &key, const double value);
			bool SetValue(const wxString &key, const char *value);
			bool SetValue(const wxString &key, DSCurrency value);
			bool SetValue(const wxString &key, DSDateTime value);

			void SetName(const wxString &name);
			wxString GetName() const;

			DSEntityType *Get(const wxString &key);
			DSEntityType *Get(const unsigned int index);
			bool Equals(DSEntity *entity);
			bool Remove(const wxString &key);

			void SetPrimaryKey(const wxString &primaryKey);
			wxString GetPrimaryKey() const;
			void SetForeignKey(const wxString &foreignKey);
			wxString GetForeignKey() const;

			unsigned int GetCount() const;

			wxString ToString();
			wxString ToCsv(
				const bool columns,
				wxString fieldDelimiter,
				const wxString &textDelimiter,
				const wxString &replaceLineFeedWith = wxEmptyString,
				const bool replaceLineFeed = false
			);

		protected:
			wxString name;
			wxString primaryKey;
			wxString foreignKey;
			DSTemplateContainer<DSEntity::DSEntityType *> entities;
	
	};

}


#endif /* DS_ENTITY_H_ */
