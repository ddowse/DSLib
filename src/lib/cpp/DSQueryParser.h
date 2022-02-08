#ifndef DS_QUERY_PARSER_H_
#define DS_QUERY_PARSER_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSCurrency.h"

#define DS_QUERY_PARSER_NAME		_N("DSQueryParser")
#define DS_QUERY_PARSER_VERSION		_N("1.0.3")
#define DS_QUERY_PARSER_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSQueryParser : public DSLib {
	
		public:
			DSQueryParser(const wxString &query = wxEmptyString);

			DSClassInfo GetClassInfo();

			void Prepare(const wxString &query);
			void PrepareByResource(const wxString &resource);
			
			bool Bind(
				const wxString &field,
				wxString value,
				const bool delimiters = true,
				const bool escape = true
			);
			bool Bind(const wxString &field, const short value);
			bool Bind(const wxString &field, const unsigned short value);
			bool Bind(const wxString &field, const int value);
			bool Bind(const wxString &field, const unsigned int value);
			bool Bind(const wxString &field, const long value);
			bool Bind(const wxString &field, const unsigned long value);
			bool Bind(const wxString &field, const float value);
			bool Bind(const wxString &field, const double value);
			bool Bind(const wxString &field, const bool value);
			bool Bind(const wxString &field, DSCurrency value);
			bool Bind(
				const wxString &field,
				const char *value,
				const bool delimiters = true,
				const bool escape = true
			);
			bool BindNull(const wxString &field, wxString value);
			bool BindNull(const wxString &field);


			bool BindNull(const wxString &field, const short value);
			bool BindNull(const wxString &field, const unsigned short value);
			bool BindNull(const wxString &field, const int value);
			bool BindNull(const wxString &field, const unsigned int value);
			bool BindNull(const wxString &field, const long value);
			bool BindNull(const wxString &field, const unsigned long value);
			bool BindNull(const wxString &field, const float value);
			bool BindNull(const wxString &field, const double value);
			bool BindNull(const wxString &field, DSCurrency value);

			bool UnBind(const wxString &field);
			
			wxString &GetQuery();
			wxString GetParsedQuery();
			
			static wxString Escape(wxString value);
			static wxString &EscapeReference(wxString &value);

		protected:
			WX_DECLARE_STRING_HASH_MAP(wxString, KeyValues);

			int ExtractFields();
			unsigned long RemoveFields();
			bool FindInArrayString(const wxArrayString &array, const wxString &field) const;

			wxString query;
			KeyValues keyValues;
			wxArrayString fields;
			bool storeResult;
	
	};

}

#endif /* DS_QUERY_PARSER_H_ */
