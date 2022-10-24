#include "DSDatabase.h"

DynSoft::DSDatabase::DSDatabase() : DSLib() {
}

DynSoft::DSDatabase::DSDatabase(
	const wxString &filename,
	const wxString &username,
	const wxString &password
) : DSLib() {
	this->filename = filename;
	this->username = username;
	this->password = password;
}

DynSoft::DSDatabase::DSDatabase(
	const wxString &hostname,
	const wxString &database,
	const wxString &username,
	const wxString &password,
	const wxString &port
) : DSLib() {
	this->hostname = hostname;
	this->database = database;
	this->username = username;
	this->password = password;
	this->port     = port;
}

DynSoft::DSDatabase::~DSDatabase() {
}

DynSoft::DSClassInfo DynSoft::DSDatabase::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DATABASE_NAME,
		DS_DATABASE_VERSION,
		DS_DATABASE_AUTHOR
	);
}

void DynSoft::DSDatabase::SetFilename(const wxString &filename) {
	this->filename = filename;
}

wxString DynSoft::DSDatabase::GetFilename() const {
	return filename;
}

void DynSoft::DSDatabase::SetHostname(const wxString &hostname) {
	this->hostname = hostname;
}

wxString DynSoft::DSDatabase::GetHostname() const {
	return hostname;
}

void DynSoft::DSDatabase::SetDatabase(const wxString &database) {
	this->database = database;
}

wxString DynSoft::DSDatabase::GetDatabase() const {
	return database;
}

void DynSoft::DSDatabase::SetUsername(const wxString &username) {
	this->username = username;
}

wxString DynSoft::DSDatabase::GetUsername() const {
	return username;
}

void DynSoft::DSDatabase::SetPassword(const wxString &password) {
	this->password = password;
}

wxString DynSoft::DSDatabase::GetPassword() const {
	return password;
}

void DynSoft::DSDatabase::SetPort(const wxString &port) {
	this->port = port;
}

wxString DynSoft::DSDatabase::GetPort() const {
	return port;
}

