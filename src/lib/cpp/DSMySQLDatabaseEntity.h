#ifndef DS_MYSQL_DATABASE_ENTITY_H_
#define DS_MYSQL_DATABASE_ENTITY_H_

#include <wx/wx.h>
#include "DSClassInfo.h"
#include "DSDatabaseEntity.h"
#include "DSMySQLDatabase.h"

#define DS_MYSQL_DATABASE_ENTITY_NAME		_N("DSMySQLDatabaseEntity")
#define DS_MYSQL_DATABASE_ENTITY_VERSION	_N("0.0.2")
#define DS_MYSQL_DATABASE_ENTITY_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSMySQLDatabaseEntity : public DSDatabaseEntity {

		public:
			DSMySQLDatabaseEntity(
				DSMySQLDatabase *db,
				const bool getAutoSequence = true
			);
			DSMySQLDatabaseEntity(
				DSMySQLDatabase *db,
				const wxString &name,
				const wxString &primaryKey   = wxEmptyString,
				const bool getAutoSequence   = true,
				const wxString &foreignKey   = wxEmptyString,
				const wxString &foreignTable = wxEmptyString,
				const unsigned int reference = REFERENCE_NO
			);
			virtual ~DSMySQLDatabaseEntity();

			DSClassInfo GetClassInfo();

			DSEntityInternalType GetInternalType() const;

			void SetDatabase(DSMySQLDatabase *db);
			DSMySQLDatabase *GetDatabase() const;

			virtual wxString CreateInsertQuery(const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateUpdateQuery(const wxString &where = wxEmptyString, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateDeleteQuery(const wxString &where = wxEmptyString);

			bool ExecInsertQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecUpdateQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecDeleteQuery(const wxString &query, DSQuery *queryObject = NULL);

			bool ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind);

		protected:	
			DSMySQLDatabase *db;

	};

}

#endif /* DS_MYSQL_DATABASE_ENTITY_H_ */
