#ifndef DS_SQLITE_DATABASE_H_
#define DS_SQLITE_DATABASE_H_

#include <wx/wx.h>
#include <sqlite3.h>
#include "DSDatabase.h"
#include "DSClassInfo.h"

#define DS_SQLITE_DATABASE_VERSION	_N("0.0.2")
#define DS_SQLITE_DATABASE_NAME		_N("DSSQLiteDatabase")
#define DS_SQLITE_DATABASE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSQLiteDatabase : public DSDatabase {
	
		public:
			DSSQLiteDatabase();
			DSSQLiteDatabase(const wxString &filename);
			virtual ~DSSQLiteDatabase();

			DSClassInfo GetClassInfo();

			virtual bool Connect();
			virtual bool IsConnected();
			virtual bool Reconnect();
			virtual bool Disconnect();

			sqlite3 *GetConnection() const;

		protected:
			sqlite3 *connection;
			bool isConnected;

			wxString filename;
	
	};

}

#endif /* DS_SQLITE_DATABASE_H_ */
