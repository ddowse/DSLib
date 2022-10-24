#include "DSPostgreSQLDatabase.h"
#include "DSCasts.h"

DynSoft::DSPostgreSQLDatabase::DSPostgreSQLDatabase() : DynSoft::DSDatabase() {
	SetTty(NULL);
	SetFlags(NULL);
	SetConnection(NULL);
}

DynSoft::DSPostgreSQLDatabase::DSPostgreSQLDatabase(
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
	SetTty(NULL);
	SetFlags(NULL);
	SetConnection(NULL);
}
/*
DynSoft::DSPostgreSQLDatabase::DSPostgreSQLDatabase(
	dsPostgreSQL *db
) : DynSoft::DSDatabase(
	db->getHostname(),
	db->getDatabase(),
	db->getUsername(),
	db->getPassword(),
	db->getPort()
) {
	SetTty(db->getTty());
	SetFlags(db->getFlags());
	SetConnection(db->dsConnection);
}*/

DynSoft::DSPostgreSQLDatabase::~DSPostgreSQLDatabase() {
	delete tty;
	delete flags;
}

DynSoft::DSClassInfo DynSoft::DSPostgreSQLDatabase::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_POSTGRESQL_DATABASE_NAME,
		DS_POSTGRESQL_DATABASE_VERSION,
		DS_POSTGRESQL_DATABASE_AUTHOR
	);
}

void DynSoft::DSPostgreSQLDatabase::SetConnection(PGconn *connection) {
	this->connection = connection;
}

bool DynSoft::DSPostgreSQLDatabase::Connect() {
	const char *hostname = DSCasts::ToChar(GetHostname());
	const char *database = DSCasts::ToChar(GetDatabase());
	const char *username = DSCasts::ToChar(GetUsername());
	const char *password = DSCasts::ToChar(GetPassword());
	const char *port     = DSCasts::ToChar(GetPort());

	connection = PQsetdbLogin(
		hostname,
		port,
		GetFlags(),
		GetTty(),
		database,
		username,
		password
	);

	delete [] hostname;
	delete [] database;
	delete [] username;
	delete [] password;
	delete [] port;

	if(PQstatus(connection) == CONNECTION_BAD)
		return false;

#if defined __WXMSW__
	//PQsetClientEncoding(connection, "LATIN9");
#endif

	return true;
}

bool DynSoft::DSPostgreSQLDatabase::IsConnected() {
	return PQstatus(connection) != CONNECTION_BAD;
}

bool DynSoft::DSPostgreSQLDatabase::Reconnect() {
	if(!IsConnected()) {
		return Connect();
	}
	return true;
}

bool DynSoft::DSPostgreSQLDatabase::Disconnect() {
	if(IsConnected()) {
		PQfinish(connection);
		return true;
	}

	return false;
}

void DynSoft::DSPostgreSQLDatabase::SetFlags(char *flags) {
	this->flags = flags;
}

char *DynSoft::DSPostgreSQLDatabase::GetFlags() const {
	return flags;
}

void DynSoft::DSPostgreSQLDatabase::SetTty(char *tty) {
	this->tty = tty;
}

char *DynSoft::DSPostgreSQLDatabase::GetTty() const {
	return tty;
}

PGconn *DynSoft::DSPostgreSQLDatabase::GetConnection() const {
	return connection;
}

