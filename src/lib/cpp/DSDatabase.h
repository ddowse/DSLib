#ifndef DS_DATABASE_H_
#define DS_DATABASE_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_DATABASE_VERSION	_N("0.4.1")
#define DS_DATABASE_NAME	_N("DSDatabase")
#define DS_DATABASE_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSDatabase : public DSLib {

		public:
			DSDatabase();

			DSDatabase(
				const wxString &filename,
				const wxString &username,
				const wxString &password
			);

			DSDatabase(
				const wxString &hostname,
				const wxString &database,
				const wxString &username,
				const wxString &password,
				const wxString &port
			);

			virtual ~DSDatabase();

			DSClassInfo GetClassInfo();

			virtual bool Connect()     = 0;
			virtual bool IsConnected() = 0;
			virtual bool Reconnect()   = 0;
			virtual bool Disconnect()  = 0;

			void SetFilename(const wxString &filename);
			wxString GetFilename() const;

			void SetHostname(const wxString &hostname);
			wxString GetHostname() const;

			void SetDatabase(const wxString &database);
			wxString GetDatabase() const;

			void SetUsername(const wxString &username);
			wxString GetUsername() const;

			void SetPassword(const wxString &password);
			wxString GetPassword() const;

			void SetPort(const wxString &port);
			wxString GetPort() const;
		
		protected:
			wxString filename;
			wxString hostname;
			wxString database;
			wxString username;
			wxString password;
			wxString port;

	};

}

#endif /* DS_DATABASE_H_ */
