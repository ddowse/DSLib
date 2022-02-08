#ifndef DS_POSTGRESQL_DATABASE_ENTITY_H_
#define DS_POSTGRESQL_DATABASE_ENTITY_H_

#include <wx/wx.h>
#include "DSClassInfo.h"
#include "DSDatabaseEntity.h"
#include "DSPostgreSQLDatabase.h"
#include "DSQuery.h"

#define DS_POSTGRESQL_DATABASE_ENTITY_NAME			_N("DSPostgreSQLDatabaseEntity")
#define DS_POSTGRESQL_DATABASE_ENTITY_VERSION		_N("0.0.3")
#define DS_POSTGRESQL_DATABASE_ENTITY_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSPostgreSQLDatabaseEntity : public DSDatabaseEntity {

		public:
			DSPostgreSQLDatabaseEntity(
				DSPostgreSQLDatabase *db,
				const bool getAutoSequence = true
			);
			DSPostgreSQLDatabaseEntity(
				DSPostgreSQLDatabase *db,
				const wxString &name,
				const wxString &primaryKey   = wxEmptyString,
				const bool getAutoSequence   = true,
				const wxString &foreignKey   = wxEmptyString,
				const wxString &foreignTable = wxEmptyString,
				const unsigned int reference = REFERENCE_NO
			);
			virtual ~DSPostgreSQLDatabaseEntity();

			DSClassInfo GetClassInfo();

			DSEntityInternalType GetInternalType() const;

			void SetDatabase(DSPostgreSQLDatabase *db);
			DSPostgreSQLDatabase *GetDatabase() const;

			virtual wxString CreateInsertQuery(const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateUpdateQuery(const wxString &where = wxEmptyString, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateDeleteQuery(const wxString &where = wxEmptyString);

			bool ExecInsertQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecUpdateQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecDeleteQuery(const wxString &query, DSQuery *queryObject = NULL);

			bool ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind);

		protected:	
			DSPostgreSQLDatabase *db;
	
	};

}

#endif /* DS_POSTGRESQL_DATABASE_ENTITY_H_ */
