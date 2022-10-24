#ifndef DS_SQLITE_DATABASE_ENTITY_H_
#define DS_SQLITE_DATABASE_ENTITY_H_

#include <wx/wx.h>
#include "DSClassInfo.h"
#include "DSDatabaseEntity.h"
#include "DSSQLiteDatabase.h"

#define DS_SQLITE_DATABASE_ENTITY_NAME		_N("DSSQLiteDatabaseEntity")
#define DS_SQLITE_DATABASE_ENTITY_VERSION	_N("0.0.1")
#define DS_SQLITE_DATABASE_ENTITY_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSQLiteDatabaseEntity : public DSDatabaseEntity {

		public:
			DSSQLiteDatabaseEntity(
				DSSQLiteDatabase *db,
				const bool getAutoSequence = true
			);
			DSSQLiteDatabaseEntity(
				DSSQLiteDatabase *db,
				const wxString &name,
				const wxString &primaryKey,
				const bool getAutoSequence   = true,
				const wxString &foreignKey   = wxEmptyString,
				const wxString &foreignTable = wxEmptyString,
				const unsigned int reference = REFERENCE_NO
			);
			virtual ~DSSQLiteDatabaseEntity();

			DSClassInfo GetClassInfo();

			DSEntityInternalType GetInternalType() const;

			void SetDatabase(DSSQLiteDatabase *db);
			DSSQLiteDatabase *GetDatabase() const;

			virtual wxString CreateInsertQuery(const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateUpdateQuery(const wxString &where = wxEmptyString, const bool withoutPrimaryKey = true, wxArrayString *withoutFields = NULL);
			virtual wxString CreateDeleteQuery(const wxString &where = wxEmptyString);

			bool ExecInsertQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecUpdateQuery(const wxString &query, DSQuery *queryObject = NULL);
			bool ExecDeleteQuery(const wxString &query, DSQuery *queryObject = NULL);

			bool ExecQuery(const wxString &query, DSQuery *queryObject, const unsigned int kind);

		protected:	
			DSSQLiteDatabase *db;

	};

}

#endif /* DS_SQLITE_DATABASE_ENTITY_H_ */
