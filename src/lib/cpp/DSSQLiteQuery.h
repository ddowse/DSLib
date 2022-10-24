#ifndef DS_SQLITE_QUERY_H_
#define DS_SQLITE_QUERY_H_

#include <wx/wx.h>
#include <sqlite3.h>
#include "DSQuery.h"
#include "DSSQLiteDatabase.h"
#include "DSClassInfo.h"

#define DS_SQLITE_QUERY_VERSION	_N("0.0.4")
#define DS_SQLITE_QUERY_NAME	_N("DSSQLiteQuery")
#define DS_SQLITE_QUERY_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSQLiteQuery : public DSQuery {

		public:
			DSSQLiteQuery(DSSQLiteDatabase *db);

			DSClassInfo GetClassInfo();

			virtual bool Exec(const bool storeResult = true);
			virtual DSCasts GetField(const wxString &field, const bool caseSensitive = true);
			virtual DSCasts GetField(const int column);
			virtual DSCasts GetColumn(const int column);
			virtual bool IsNull(const wxString &field);
			virtual bool IsNull(const int column);
			virtual unsigned int GetRowCount() const;
			virtual unsigned int GetColumnCount() const;
			virtual bool Begin();
			virtual bool Commit();
			virtual bool Rollback();
			virtual bool NextRecord();
			virtual void FreeResult();

		protected:
			sqlite3 *connection;
			unsigned int row;
			int rowCount;
			int columnCount;
			char *errorMessage;
			char **result;
			wxArrayString columns;

	};

}

#endif /* DS_SQLITE_QUERY_H_ */
