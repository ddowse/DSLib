#ifndef DS_POSTGRESQL_DATABASE_H_
#define DS_POSTGRESQL_DATABASE_H_

#include <wx/wx.h>
#include <libpq-fe.h>
#include "DSDatabase.h"
#include "DSClassInfo.h"
//#include "dsPostgreSQL.h"

#define DS_POSTGRESQL_DATABASE_VERSION	_N("0.7.1")
#define DS_POSTGRESQL_DATABASE_NAME		_N("DSPostgreSQLDatabase")
#define DS_POSTGRESQL_DATABASE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {
	
	class DSPostgreSQLDatabase : public DSDatabase {

		public:
			DSPostgreSQLDatabase();

			DSPostgreSQLDatabase(
				const wxString &hostname,
				const wxString &database,
				const wxString &username,
				const wxString &password,
				const wxString &port
			);

	//		DSPostgreSQLDatabase(dsPostgreSQL *db);

			virtual ~DSPostgreSQLDatabase();

			DSClassInfo GetClassInfo();

			virtual bool Connect();
			virtual bool IsConnected();
			virtual bool Reconnect();
			virtual bool Disconnect();

			void SetFlags(char *flags = NULL);
			char *GetFlags() const;

			void SetTty(char *tty = NULL);
			char *GetTty() const;

			PGconn *GetConnection() const;
			void SetConnection(PGconn *connection);

		protected:
			PGconn *connection;

			char *tty;
			char *flags;

	};

}

#endif /* DS_POSTGRESQL_DATABASE_H_ */
