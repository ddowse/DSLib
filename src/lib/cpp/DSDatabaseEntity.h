#ifndef DS_DATABASE_ENTITY_H_
#define DS_DATABASE_ENTITY_H_

#include <wx/wx.h>
#include "DSClassInfo.h"
#include "DSEntity.h"
#include "DSDatabase.h"
#include "DSQuery.h"
#include "DSTemplateContainer.h"

#define DS_DATABASE_ENTITY_NAME			_N("DSDatabaseEntity")
#define DS_DATABASE_ENTITY_VERSION		_N("0.0.4")
#define DS_DATABASE_ENTITY_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSDatabaseEntity : public DSEntity {

		public:
			static const unsigned int INSERT                 = 0;
			static const unsigned int UPDATE                 = 1;
			static const unsigned int REMOVE                 = 2;
			static const unsigned int SELECT                 = 3;
			static const unsigned int REFERENCE_NO           = 0;
			static const unsigned int REFERENCE_ONE_TO_ONE   = 1;
			static const unsigned int REFERENCE_ONE_TO_MANY  = 2;
			static const unsigned int REFERENCE_MANY_TO_ONE  = 3;
			static const unsigned int REFERENCE_MANY_TO_MANY = 4;

			DSDatabaseEntity(
				const bool getAutoSequence = true
			);
			DSDatabaseEntity(
				const wxString &name,
				const wxString &primaryKey   = wxEmptyString,
				const bool getAutoSequence   = true,
				const wxString &foreignKey   = wxEmptyString,
				const wxString &foreignTable = wxEmptyString,
				const unsigned int reference = REFERENCE_NO
			);
			virtual ~DSDatabaseEntity();

			DSClassInfo GetClassInfo();

			DSEntityInternalType GetInternalType() const;
			
			virtual wxString CreateInsertQuery(const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL)                                        = 0;
			virtual wxString CreateUpdateQuery(const wxString &where = wxEmptyString, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL) = 0;
			virtual wxString CreateDeleteQuery(const wxString &where = wxEmptyString)                                                                           = 0;
			virtual bool ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind)                                                        = 0;

			void SetTable(const wxString &table);
			wxString GetTable() const;

			void SetForeignTable(const wxString &foreignTable);
			wxString GetForeignTable() const;

			void SetReference(const unsigned int &reference);
			unsigned int GetReference() const;

			void SetGetAutoSequence(const bool getAutoSequence);
			bool GetGetAutoSequence() const;

			wxString GetLastParsedQuery() const;

			DSTemplateContainer<DSDatabaseEntity *> *GetReferences();

		protected:
			bool getAutoSequence;
			wxString foreignTable;
			unsigned int reference;
			wxString lastParsedQuery;

			DSTemplateContainer<DSDatabaseEntity *> references;

			wxString BuildInsertQuery(
				const bool withoutPrimaryKey = true,
				const wxString &prefix        = wxEmptyString,
				const wxString &suffix        = wxEmptyString,
				wxArrayString *withoutFields  = NULL
			);

			wxString BuildUpdateQuery(
				wxString where               = wxEmptyString,
				const bool withoutPrimaryKey = true,
				const wxString &prefix       = wxEmptyString,
				const wxString &suffix       = wxEmptyString,
				wxArrayString *withoutFields = NULL
			);

			wxString BuildDeleteQuery(
				wxString where         = wxEmptyString,
				const wxString &prefix = wxEmptyString,
				const wxString &suffix = wxEmptyString
			);

			unsigned int BuildKeysValues(
				wxString *keys,
				wxString *values,
				const wxString &prefix        = wxEmptyString,
				const wxString &suffix        = wxEmptyString,
				const bool withoutPrimaryKey = false,
				wxArrayString *withoutFields  = NULL
			);

			unsigned int BuildKeysValuesPairs(
				wxString *pairs,
				const wxString &prefix,
				const wxString &suffix,
				const bool withoutPrimaryKey = true,
				wxArrayString *withoutFields = NULL
			);

			wxString BindValues(const wxString &query, unsigned int *bounded = NULL);

	};

}

#endif /* DS_DATABASE_ENTITY_H_ */
