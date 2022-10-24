#ifndef DS_MYSQL_QUERY_H_
#define DS_MYSQL_QUERY_H_

#include <wx/wx.h>
#include <algorithm>

#ifdef __WIN32__
	#include <windows.h>
#endif

#include <mysql.h>
#include "DSQuery.h"
#include "DSMySQLDatabase.h"
#include "DSClassInfo.h"

#define DS_MYSQL_QUERY_VERSION	_N("0.4.2")
#define DS_MYSQL_QUERY_NAME		_N("DSMySQLQuery")
#define DS_MYSQL_QUERY_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSMySQLQuery : public DSQuery {
	
		public:
			DSMySQLQuery(DSMySQLDatabase *db);

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

			unsigned int GetLastInsertId() const;

			int GetFieldNumber(const wxString &field) const;

		protected:
			MYSQL *connection;
			MYSQL_RES *result;
			MYSQL_ROW row;
	
	};

}

#endif /* DS_MYSQL_QUERY_H_ */
