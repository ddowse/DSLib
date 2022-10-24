#ifndef DS_ENTITY_DATA_H_
#define DS_ENTITY_DATA_H_

#include <wx/wx.h>
#include "DSData.h"
#include "DSClassInfo.h"
#include "DSQuery.h"
#include "DSEntity.h"
#include "DSDatabaseEntity.h"

#define DS_ENTITY_DATA_NAME			_N("DSEntityData")
#define DS_ENTITY_DATA_VERSION		_N("0.0.10")
#define DS_ENTITY_DATA_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSEntityData : public DSData {
	
		public:
			static const unsigned int DESC = 0;
			static const unsigned int ASC  = 1;

			DSEntityData(
				DSQuery *query,
				const wxString &table        = wxEmptyString,
				const wxString &primaryKey   = wxEmptyString,
				const wxString &orderByField = wxEmptyString,
				const unsigned int order     = ASC,
				const bool cleanUp           = true
			);
			virtual ~DSEntityData();

			DSClassInfo GetClassInfo();

			void SetOrderBy(const wxString &orderByField, const unsigned int order);
			void GetOrderBy(wxString *orderByField, unsigned int *order);

			void Get(DSEntity *entity, const wxString &prefix, const wxString &suffix);

			virtual void Get()                                                                           = 0;
			virtual void Get(const unsigned int primaryKey)                                              = 0;
			virtual void Get(const wxString &primaryKey, const bool delimiters = false)                  = 0;
			virtual void Get(const wxString &field, const wxString &value, const bool delimiters = true) = 0;
			virtual bool Exists(
				const wxString &field,
				const wxString &value,
				const wxString &oldValue = wxEmptyString,
				const bool separators    = true,
				const bool escape        = true
			) = 0;

			bool Insert(DSDatabaseEntity *entity, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL, DSQuery *queryObject = NULL);
			bool Update(DSDatabaseEntity *entity, const wxString &where = wxEmptyString, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL, DSQuery *queryObject = NULL);
			bool InsertOrUpdate(DSDatabaseEntity *entity, wxArrayString *withoutFields = NULL, DSQuery *queryObject = NULL);
			bool Delete(DSDatabaseEntity *entity, const wxString &where = wxEmptyString, DSQuery *queryObject = NULL);
			bool Persist(DSDatabaseEntity *entity, DSQuery *queryObject);
			
			wxString GetLastParsedQuery() const;
			void SetTable(const wxString &table);
			wxString GetTable() const;

		protected:	
			wxString table;
			wxString primaryKey;
			wxString orderByField;
			wxString order;
			wxString lastParsedQuery;

	};

}

#endif /* DS_ENTITY_DATA_H_ */
