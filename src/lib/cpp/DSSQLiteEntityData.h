#ifndef DS_SQLITE_ENTITY_DATA_H_
#define DS_SQLITE_ENTITY_DATA_H_

#include <wx/wx.h>
#include "DSEntityData.h"
#include "DSClassInfo.h"
#include "DSSQLiteDatabase.h"
#include "DSQueryParser.h"
#include "DSSQLiteDatabaseEntity.h"

#define DS_SQLITE_ENTITY_DATA_NAME			_N("DSSQLiteEntityData")
#define DS_SQLITE_ENTITY_DATA_VERSION		_N("0.0.3")
#define DS_SQLITE_ENTITY_DATA_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSQLiteEntityData : public DSEntityData {
	
		public:
			DSSQLiteEntityData(
				DSSQLiteDatabase *db,
				const wxString &table        = wxEmptyString,
				const wxString &primaryKey   = wxEmptyString,
				const wxString &orderByField = wxEmptyString,
				const unsigned int order     = ASC
			);

			DSClassInfo GetClassInfo();

			using DSEntityData::Get;
			void Get(DSSQLiteDatabaseEntity *entity);
			void Get();
			void Get(const unsigned int primaryKey);
			void Get(const wxString &primaryKey, const bool delimiters = false);
			void Get(const wxString &field, const wxString &value, const bool delimiters = true);
			bool Exists(
				const wxString &field,
				const wxString &value,
				const wxString &oldValue = wxEmptyString,
				const bool separators    = true,
				const bool escape        = true
			);

		protected:
			DSSQLiteDatabase *ndb;

	};

}

#endif /* DS_SQLITE_ENTITY_DATA_H_ */
