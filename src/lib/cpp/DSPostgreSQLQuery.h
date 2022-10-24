#ifndef DS_POSTGRESQL_QUERY_H_
#define DS_POSTGRESQL_QUERY_H_

#include <wx/wx.h>
#include <libpq-fe.h>
#include "DSQuery.h"
#include "DSPostgreSQLDatabase.h"
#include "DSClassInfo.h"
#include "dsPostgreSQL.h"

#define DS_POSTGRESQL_QUERY_VERSION	_N("0.8.2")
#define DS_POSTGRESQL_QUERY_NAME	_N("DSPostgreSQLQuery")
#define DS_POSTGRESQL_QUERY_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSPostgreSQLQuery : public DSQuery {

		public:
			DSPostgreSQLQuery(DSPostgreSQLDatabase *db);
			DSPostgreSQLQuery(dsPostgreSQL *db);

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

			static unsigned char *EscapeByteA(unsigned char *buffer, const size_t size, size_t &newSize);
			char *GetFieldByteA(const wxString &field, size_t &newSize);
			bool ExecWithoutResultByCString(const char *query);
			unsigned int ImportLargeObject(wxString filename, const unsigned int oid = 0);
			bool ExportLargeObject(const wxString &filename, const unsigned int oid);
			bool RemoveLargeObject(const unsigned int oid);
			bool ExistsLargeObject(const unsigned int oid);

		protected:
			PGconn *connection;
			PGresult *result;
			int rowsCount;

	};

}

#endif /* DS_POSTGRESQL_QUERY_H_ */
