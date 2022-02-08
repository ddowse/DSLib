#include "DSSQLiteDatabase.h"
#include "DSCasts.h"

DynSoft::DSSQLiteDatabase::DSSQLiteDatabase(
) : DynSoft::DSDatabase(
) {
	connection  = NULL;
	isConnected = false;
}

DynSoft::DSSQLiteDatabase::DSSQLiteDatabase(
	const wxString &filename
) : DynSoft::DSDatabase(
	filename,
	wxEmptyString,
	wxEmptyString
) {
	connection  = NULL;
	isConnected = false;
}

DynSoft::DSSQLiteDatabase::~DSSQLiteDatabase() {
	Disconnect();
}

DynSoft::DSClassInfo DynSoft::DSSQLiteDatabase::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SQLITE_DATABASE_NAME,
		DS_SQLITE_DATABASE_VERSION,
		DS_SQLITE_DATABASE_AUTHOR
	);
}

bool DynSoft::DSSQLiteDatabase::Connect() {
	const char *filename = DSCasts::ToChar(GetFilename());
	int result = sqlite3_open(filename, &connection);
	delete [] filename;
	if(result) {
		Disconnect();
		isConnected = false;
	} else {
		isConnected = true;
	}

	return IsConnected();
}

bool DynSoft::DSSQLiteDatabase::IsConnected() {
	return isConnected;
}

bool DynSoft::DSSQLiteDatabase::Reconnect() {
	if(!IsConnected())
		return Connect();
	else
		return true;
}

bool DynSoft::DSSQLiteDatabase::Disconnect() {
	if(IsConnected()) {
		sqlite3_close(connection);
		connection = NULL;
		// FIXME -> Real result?
		return true;
	}

	return false;
}

sqlite3 *DynSoft::DSSQLiteDatabase::GetConnection() const {
	return connection;
}
