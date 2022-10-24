#ifndef DS_MYSQL_DATABASE_H_
#define DS_MYSQL_DATABASE_H_

#include <wx/wx.h>
#include <algorithm>

#ifdef __WIN32__
	#include <windows.h>
#endif

#include <mysql.h>
#include "DSDatabase.h"

#define DS_MYSQL_DATABASE_VERSION	_N("0.4.1")
#define DS_MYSQL_DATABASE_NAME		_N("DSMySQLDatabase")
#define DS_MYSQL_DATABASE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSMySQLDatabase : public DSDatabase {
	
		public:
			DSMySQLDatabase();

			DSMySQLDatabase(
				const wxString &hostname,
				const wxString &database,
				const wxString &username,
				const wxString &password,
				const wxString &port
			);

			DSClassInfo GetClassInfo();

			virtual bool Connect();
			virtual bool IsConnected();
			virtual bool Reconnect();
			virtual bool Disconnect();

			void SetSocketName(char *socketName = NULL);
			char *GetSocketName() const;

			void SetFlags(unsigned int flags = 0);
			unsigned int GetFlags() const;

			void SetEncoding(const wxString &encoding = _("utf8"));
			wxString GetEncoding() const;

			MYSQL *GetConnection() const;

		protected:
			MYSQL *connection;
			char *socketName;
			unsigned int flags;
			wxString encoding;
	
	};

}

#endif /* DS_MYSQL_DATABASE_H_ */
