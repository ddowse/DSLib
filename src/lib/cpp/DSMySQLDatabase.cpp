#include "DSMySQLDatabase.h"
#include "DSMySQLQuery.h"
#include "DSCasts.h"

#include <fcgi_stdio.h>

DynSoft::DSMySQLDatabase::DSMySQLDatabase() : DSDatabase() {
	SetFlags(0);
	SetSocketName(NULL);
	connection = mysql_init(NULL);
	SetEncoding(_N("utf8"));
}

DynSoft::DSMySQLDatabase::DSMySQLDatabase(
	const wxString &hostname,
	const wxString &database,
	const wxString &username,
	const wxString &password,
	const wxString &port
) : DynSoft::DSDatabase(
	hostname,
	database,
	username,
	password,
	port
) {
	SetFlags(0);
	SetSocketName(NULL);
	connection = mysql_init(NULL);
	SetEncoding(_N("utf8"));
}

DynSoft::DSClassInfo DynSoft::DSMySQLDatabase::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_MYSQL_DATABASE_NAME,
		DS_MYSQL_DATABASE_VERSION,
		DS_MYSQL_DATABASE_AUTHOR
	);
}

bool DynSoft::DSMySQLDatabase::Connect() {
	if(GetConnection() == NULL)
		return false;

	const char *hostname = DSCasts::ToChar(GetHostname());
	const char *database = DSCasts::ToChar(GetDatabase());
	const char *username = DSCasts::ToChar(GetUsername());
	const char *password = DSCasts::ToChar(GetPassword());

	bool result = mysql_real_connect(
		GetConnection(),
		hostname,
		username,
		password,
		database,
		DSCasts::ToUnsignedInt(GetPort()),
		GetSocketName(),
		GetFlags()
	) != NULL;

	delete [] hostname;
	delete [] database;
	delete [] username;
	delete [] password;
	
	return result;
}

bool DynSoft::DSMySQLDatabase::IsConnected() {
	return mysql_ping(GetConnection()) == 0;
}

bool DynSoft::DSMySQLDatabase::Reconnect() {
	return IsConnected();
}

bool DynSoft::DSMySQLDatabase::Disconnect() {
	mysql_close(GetConnection());
	return true;
}

MYSQL *DynSoft::DSMySQLDatabase::GetConnection() const {
	return connection;
}

void DynSoft::DSMySQLDatabase::SetFlags(unsigned int flags) {
	this->flags = flags;
}

unsigned int DynSoft::DSMySQLDatabase::GetFlags() const {
	return flags;
}

void DynSoft::DSMySQLDatabase::SetEncoding(const wxString &encoding) {
	this->encoding = encoding;
}

wxString DynSoft::DSMySQLDatabase::GetEncoding() const {
	return encoding;
}

void DynSoft::DSMySQLDatabase::SetSocketName(char *socketName) {
	this->socketName = socketName;
}

char *DynSoft::DSMySQLDatabase::GetSocketName() const {
	return socketName;
}
