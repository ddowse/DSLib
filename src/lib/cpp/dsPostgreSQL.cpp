#include "dsPostgreSQL.h"
#include <wx/file.h>

dsPostgreSQL::dsPostgreSQL() {
	newDbObject = new DSPostgreSQLDatabase;
	isSetHostname = false;
	isSetDatabase = false;
	isSetUsername = false;
	isSetPassword = false;
	isSetPort = false;
	isSetFlags = false;
	isConnected = false;
	isSetTty = false;
}

dsPostgreSQL::~dsPostgreSQL() {
	delete newDbObject;
}

DSPostgreSQLDatabase *dsPostgreSQL::GetNewDbObject() {
	return newDbObject;
}

void dsPostgreSQL::setHostname(const wxString &_hostname) {
	hostname = _hostname;
	isSetHostname = true;
	newDbObject->SetHostname(_hostname);
}

void dsPostgreSQL::setDatabase(const wxString &_database) {
	database = _database;
	isSetDatabase = true;
	newDbObject->SetDatabase(_database);
}

void dsPostgreSQL::setUsername(const wxString &_username) {
	username = _username;
	isSetUsername = true;
	newDbObject->SetUsername(_username);
}

void dsPostgreSQL::setPassword(const wxString &_password) {
	password = _password;
	isSetPassword = true;
	newDbObject->SetPassword(_password);
}

void dsPostgreSQL::setPort(const wxString &_port) {
	port = _port;
	isSetPort = true;
	newDbObject->SetPort(_port);
}

void dsPostgreSQL::setFlags(char *_flags) {
	flags = _flags;
	isSetFlags = true;
	newDbObject->SetFlags(_flags);
}

void dsPostgreSQL::setTty(char *_tty) {
	tty = _tty;
	isSetTty = true;
	newDbObject->SetTty(_tty);
}

wxString dsPostgreSQL::getHostname() const {
	return hostname;
}

wxString dsPostgreSQL::getDatabase() const {
	return database;
}

wxString dsPostgreSQL::getUsername() const {
	return username;
}

wxString dsPostgreSQL::getPassword() const {
	return password;
}

wxString dsPostgreSQL::getPort() const {
	return port;
}

char *dsPostgreSQL::getTty() const {
	return tty;
}

char *dsPostgreSQL::getFlags() const {
	return flags;
}

bool dsPostgreSQL::connect() {
	if(!isSetHostname)		setHostname();
	if(!isSetDatabase)		setDatabase();
	if(!isSetUsername)		setUsername();
	if(!isSetPassword)		setPassword();
	if(!isSetPort)			setPort();
	if(!isSetTty)			setTty();
	if(!isSetFlags)			setFlags();
	
/*	char cHostname [hostname.length() + 2];
	char cDatabase [database.length() + 2];
	char cUsername [username.length() + 2];
	char cPassword [password.length() + 2];
	char cPort     [port.length() + 2];
	
	strcpy(cHostname, (char *) futf(hostname));
	strcpy(cDatabase, (char *) futf(database));
	strcpy(cUsername, (char *) futf(username));
	strcpy(cPassword, (char *) futf(password));
	strcpy(cPort,     (char *) futf(port));
*/

	//dsConnection = PQsetdbLogin(cHostname, cPort, flags, tty, cDatabase, cUsername, cPassword);
	dsConnection = PQsetdbLogin(futf(hostname), futf(port), flags, tty, futf(database), futf(username), futf(password));
	if(PQstatus(dsConnection) == CONNECTION_BAD) {
		isConnected = false;
		return false;
	} else {
		#ifdef __WXMSW__
			PQsetClientEncoding(dsConnection, "LATIN9");
		#endif

		isConnected = true;
		newDbObject->SetConnection(dsConnection);

		return true;
	}
}

void dsPostgreSQL::disconnect() {
	PQfinish(dsConnection);
	isConnected = false;
}

bool dsPostgreSQL::isConnect() {
	return isConnected;
}


dsPostgreSQLQuery::dsPostgreSQLQuery(dsPostgreSQL *_dps) {
	dps = _dps;
	isQuery = false;
}

unsigned int dsPostgreSQLQuery::numRows() {
	if(isQuery) return PQntuples(dsResult);
	else return 0;
}

unsigned int dsPostgreSQLQuery::numFields() {
	if(isQuery) return PQnfields(dsResult);
	else return 0;
}

bool dsPostgreSQLQuery::begin() {
	return query(_N("BEGIN"), false);	
}

bool dsPostgreSQLQuery::commit() {
	return query(_N("COMMIT"));
}

bool dsPostgreSQLQuery::rollback() {
	return query(_N("ROLLBACK"));
}

void dsPostgreSQLQuery::freeResult() {
	isQuery = false;
	PQclear(dsResult);
}

#ifndef wxUSE_UNICODE
bool dsPostgreSQLQuery::query(char *query, bool storeResult) {
	rowsCount = 0;
	if(dsResult = PQexec(dps->dsConnection, query)) {
		if(!dsResult) {
			isQuery = false;
			return false;
		} else {
			if(PQresultStatus(dsResult) == PGRES_TUPLES_OK) {
				if(!storeResult)
					PQclear(dsResult);
				isQuery = true;
				return true;
			} else {
				isQuery = false;
				return false;
			}
		}
	} else {
		isQuery = false;
		return false;
	}
}

void dsPostgreSQLQuery::bindValue(std::string key, std::string value, bool addCommas, bool escapeString) {
	if(escapeString) {
		char newValue [value.length() * 2 + 1];
		PQescapeString(newValue, value.c_str(), value.length());
		value = newValue;
	}

	if(addCommas) value = "'" + value + "'";
	if(sQuery.find((char*) key.c_str()) != std::string::npos)
		sQuery.replace(sQuery.find((char*) key.c_str()), std::strlen((char*) key.c_str()), value);
}

void dsPostgreSQLQuery::bindValueNull(std::string key, std::string value, bool addCommas, bool escapeString) {
	if(value.length() == 0)
		bindValue(key, "NULL", false, false);
	else
		bindValue(key, value, addCommas, escapeString);
}

void dsPostgreSQLQuery::bindValueInt(std::string key, int value) {
	char convert [12];
	sprintf(convert, "%i", value);
	
	bindValue(key, convert, false, false);
}

void dsPostgreSQLQuery::bindValueFloat(std::string key, float value) {
	char convert[50];
	sprintf(convert, "%f", value);
	
	bindValue(key, convert, false, false);
}

void dsPostgreSQLQuery::bindValueFloat(std::string key, std::string) {
	/*
	 * FIXME - Ersetzung
	 * char convert[50];
	sprintf(convert, "%f", value);
	
	bindValue(key, convert, false, false);*/
}

void dsPostgreSQLQuery::bindValueBool(std::string key, bool value) {
	bindValue(key, value ? "TRUE" : "FALSE", false, false);
}


bool dsPostgreSQLQuery::isNull(const char *_fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, PQfnumber(dsResult, _fieldValue)))
		return true;
	else
		return false;	
}

#ifdef USE_WXWIDGETS
	void dsPostgreSQLQuery::bindValue(const wxString &key, const wxString &value, bool addCommas, bool escapeString) {
		bindValue(key.c_str(), value.c_str(), addCommas, escapeString);
	}

	void dsPostgreSQLQuery::bindValueNull(const wxString &key, const wxString &value, bool addCommas, bool escapeString) {
		if(value.IsEmpty())
			bindValue(key, _N("NULL"), false, false);
		else
			bindValue(key, value, addCommas, escapeString);
	}
	
	void dsPostgreSQLQuery::bindValueInt(const wxString &key, int value) {
		bindValue(key, value, false, false);
	}
	
	void dsPostgreSQLQuery::bindValueFloat(const wxString &key, DSCurrency value) {
		wxString val(wxString::Format(_N("%.2f"), value.ToDouble()));
		val.Replace(_N(","), _N("."));
		bindValue(key, , false, false);
	}
	
	void dsPostgreSQLQuery::bindValueFloat(const wxString &key, wxString value) {
		value.Replace(_N(","), _N("."));
		if(value.Length() == 0)
			value = _N("0.00");
		bindValue(key, value, false, false);
	}

	void dsPostgreSQLQuery::bindValueBool(const wxString &key, bool value) {
		wxString newValue;
		if(value) newValue = _N("TRUE");
		else newValue = _N("FALSE");
		bindValue(key, newValue, false, false);
	}

	bool query(const wxString &_query, bool escape) {
		return query(_query.c_str(), escape);
	}

	void prepare(wxString _query) {
		prepare(_query.c_str());
	}

	bool dsPostgreSQLQuery::isNull(const wxString &_fieldValue) {
		if(PQgetisnull(dsResult, rowsCount - 1, PQfnumber(dsResult, futf(_fieldValue))))
			return true;
		else
			return false;	
	}

#endif

bool dsPostgreSQLQuery::exec(bool storeResult) {
	return query((char*)sQuery.c_str(), storeResult);
}

std::string dsPostgreSQLQuery::field(int _fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, _fieldValue))
		return _N("");
	else
		return PQgetvalue(dsResult, rowsCount - 1, _fieldValue);
}

std::string dsPostgreSQLQuery::column(int _columnValue) {
	return PQfname(dsResult, _columnValue);
}

std::string dsPostgreSQLQuery::field(const char *_fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, PQfnumber(dsResult, _fieldValue)))
		return _N("");
	else
		return PQgetvalue(dsResult, rowsCount - 1, PQfnumber(dsResult, _fieldValue));
		
}
#else

bool dsPostgreSQLQuery::query(char *query, bool storeResult) {
	rowsCount = 0;
	if((dsResult = PQexec(dps->dsConnection, query))) {
		printf("1\n");
		if(!dsResult) {
			printf("2\n");
			isQuery = false;
			return false;
		} else {
			printf("3\n");
			int tmp = PQresultStatus(dsResult);
			printf("%s\n", PQresultErrorMessage(dsResult));
			if(tmp == PGRES_TUPLES_OK || tmp == PGRES_COMMAND_OK) {
			printf("4\n");
				if(!storeResult)
					PQclear(dsResult);
				isQuery = true;
				return true;
			} else {
				printf("5\n");
				isQuery = false;
				return false;
			}
		}
	} else {
		printf("5\n");
		isQuery = false;
		return false;
	}
}


bool dsPostgreSQLQuery::query(const wxString &_query, bool storeResult, wxString *statusMessage, wxString *errorMessage) {
	rowsCount = 0;
	if(dps->isConnect()) {
		dsResult = PQexec(dps->dsConnection, futf(_query));
		if(!dsResult) {
			isQuery = false;
			return false;
		} else {
			int tmp = PQresultStatus(dsResult);
			if(tmp == PGRES_TUPLES_OK || tmp == PGRES_COMMAND_OK) {
				if(!storeResult) {
					PQclear(dsResult);
				}
				isQuery = true;
				return true;
			} else {
				#ifndef __WXMSW__
					if(errorMessage == NULL) {
						dsPostgreSQLInfo info(_query);
					}
				#endif
				if(errorMessage != NULL) {
					*errorMessage = getError();
				}
				if(statusMessage != NULL) {
					*statusMessage = getStatus();
				}
				isQuery = false;
				return false;
			}
		}
	} else {
		isQuery = false;
		return false;
	}
}

wxString dsPostgreSQLQuery::escape(wxString str) {
	// Ich hoffe, dass das reicht ...
	str.Replace(_N("\\"), _N("\\\\"));
	str.Replace(_N("'"), _N("\\'"));
	return str;
}

void dsPostgreSQLQuery::bindValue(const wxString &_key, wxString _value, bool addCommas, bool escapeString) {
	if(escapeString)
		_value = escape(_value);

	if(addCommas) _value = _N("'") + _value + _N("'");
	sQuery.Replace(_key, _value);
}

wxString dsPostgreSQLQuery::escapeBin(char *buffer, size_t size) {
	size_t newSize;
	unsigned char *binData = PQescapeByteaConn(dps->dsConnection, (unsigned char *) buffer, size, &newSize);
	return wxString((const char *) binData, wxConvUTF8, newSize);
}

char *dsPostgreSQLQuery::escapeBinChar(char *buffer, size_t size, size_t &newSize) {
	return (char *) PQescapeByteaConn(dps->dsConnection, (unsigned char *) buffer, size, &newSize);
}

/*wxString dsPostgreSQLQuery::escapeBin(char buffer [], size_t size) {
	size_t newSize;
	unsigned char *binData = PQescapeBytea((unsigned char *) buffer, size, &newSize);
	return wxString((const char *) binData, wxConvUTF8, newSize);
}*/

unsigned char *dsPostgreSQLQuery::field(const wxString &fieldValue, size_t &size) {
	char *result = PQgetvalue(dsResult, rowsCount - 1, PQfnumber(dsResult, futf(fieldValue)));
	return PQunescapeBytea((unsigned char *) result, &size);
}

void dsPostgreSQLQuery::bindValueNull(const wxString &key, const wxString &value, bool addCommas, bool escapeString) {
	if(value.IsEmpty())
		bindValue(key, _N("NULL"), false, false);
	else
		bindValue(key, value, addCommas, escapeString);
}

void dsPostgreSQLQuery::bindValueFloat(const wxString &key, DSCurrency value) {
	wxString val(wxString::Format(_N("%.2f"), value.ToDouble()));
	val.Replace(_N(","), _N("."));
	bindValue(key, val, false, false);
}

void dsPostgreSQLQuery::bindValueFloat(const wxString &key, wxString value) {
	value.Replace(_N(","), _N("."));
	if(value.Length() == 0) value = _N("0.00");
	bindValue(key, value, false, false);
}

void dsPostgreSQLQuery::bindValueInt(const wxString &key, int value) {
	bindValue(key, wxString::Format(_N("%i"), value), false, false);
}

void dsPostgreSQLQuery::bindValueBool(const wxString &key, bool value) {
	wxString newValue;
	if(value) newValue = _N("TRUE");
	else newValue = _N("FALSE");
	bindValue(key, newValue, false, false);
}

bool dsPostgreSQLQuery::exec(bool storeResult) {
	return query(sQuery, storeResult);
}

wxString dsPostgreSQLQuery::column(int _columnValue) {
	return wxString(PQfname(dsResult, _columnValue), wxConvUTF8);
}

dsPostgreSQLConvert dsPostgreSQLQuery::field(int _fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, _fieldValue))
		return dsPostgreSQLConvert(_N(""));
	else
		return dsPostgreSQLConvert(wxString(PQgetvalue(dsResult, rowsCount - 1, _fieldValue), wxConvUTF8));
}

dsPostgreSQLConvert dsPostgreSQLQuery::field(const wxString &_fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, PQfnumber(dsResult, futf(_fieldValue))))
		return dsPostgreSQLConvert(_N(""));
	else
		return dsPostgreSQLConvert(wxString(PQgetvalue(dsResult, rowsCount - 1, PQfnumber(dsResult, futf(_fieldValue))), wxConvUTF8));
		
}
#endif

bool dsPostgreSQLQuery::nextRecord() {
	if(isQuery) {
		if(rowsCount < PQntuples(dsResult)) {
			rowsCount++;
			return true;
		} else {
			return false;
		}
	} else return false;
}

bool dsPostgreSQLQuery::isNull(int _fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, _fieldValue))
		return true;
	else
		return false;
}

bool dsPostgreSQLQuery::isNull(const wxString &_fieldValue) {
	if(PQgetisnull(dsResult, rowsCount - 1, PQfnumber(dsResult, futf(_fieldValue))))
		return true;
	else
		return false;	
}

#ifdef wxUSE_UNICODE
	wxArrayString dsPostgreSQLConvert::split(const wxString &zeichen, const wxString &string) {
		wxArrayString rueckgabe;
		wxString temp, letter;
		int count = 0;	

		for(unsigned int i = 0; i < string.Length(); i++) {
			letter = string.Mid(i, zeichen.Length());
			if(letter == zeichen) {
				if(!temp.IsEmpty() || i == string.Length() - 1) {
					rueckgabe.Add(temp);
					if(i == string.Length() - 1) {
						rueckgabe.Add(wxEmptyString);
					}
				}
				temp = wxEmptyString;
				count++;
			} else {
				temp += letter;
				if(i == string.Length() - 1) {
					rueckgabe.Add(temp);
					if(rueckgabe.GetCount() < 2)
						rueckgabe.Add(wxEmptyString);
				}
				count = 0;
			}
			if(count == 2) {
				count--;
				rueckgabe.Add(wxEmptyString);
			}
		}
		return rueckgabe;
	}


	wxString dsPostgreSQLConvert::betragVervollstaendigen(const wxString &temp) {
		if(temp.IsEmpty()) {
			return _N("0,00");
		}
		
		int pos = temp.Find(_N(","));
		if(pos == wxNOT_FOUND) {
			return temp + _N(",00");
		} else {
			wxArrayString as(split(_N(","), temp));
			if(as.GetCount() > 1) {
				if(as[1].IsEmpty()) {
					return temp + _N("00");
				} else {
					if(as[1].Length() < 2) {
						return temp + _N("0");
					} else {
						return temp;
					}
				}
			}
		}
		return _N("0,00");
	}

	dsPostgreSQLConvert::dsPostgreSQLConvert(wxString _s) {
		s = _s;
	}
	
	bool dsPostgreSQLConvert::asBool() {
		return (s == _N("t"));
	}
	
	long dsPostgreSQLConvert::asInteger() {
		long result;
		s.ToLong(&result);
		return result;
	}
	
	wxString dsPostgreSQLConvert::asString() {
		return s;
	}
	
	wxString dsPostgreSQLConvert::asFloatString() {
		s.Replace(_N("."), _N(","));
		return betragVervollstaendigen(s);
	}

	DSCurrency dsPostgreSQLConvert::asFloat() {
		double temp;
		wxString temp2(s);
		temp2.Replace(_N("."), _N(","));

		if(temp2.ToDouble(&temp))
			return DSCurrency((double) temp);
		return DSCurrency();
	}

	DSCurrency dsPostgreSQLConvert::ToDouble() {
		return asFloat();
	}
#endif


// Ziemlich dreckig, ich habe aber keine Ahnung,
// wie man und und oder Verknuepfungen bei defines bastelt
// Windowsversion
#ifdef USE_WXWIDGETS
#ifndef wxUSE_UNICODE
	wxArrayString dsPostgreSQLConvert::split(const wxString &zeichen, const wxString &string) {
		wxArrayString rueckgabe;
		wxString temp, letter;
		int count = 0;	

		for(unsigned int i = 0; i < string.Length(); i++) {
			letter = string.Mid(i, zeichen.Length());
			if(letter == zeichen) {
				if(!temp.IsEmpty() || i == string.Length() - 1) {
					rueckgabe.Add(temp);
					if(i == string.Length() - 1) {
						rueckgabe.Add(wxEmptyString);
					}
				}
				temp = wxEmptyString;
				count++;
			} else {
				temp += letter;
				if(i == string.Length() - 1) {
					rueckgabe.Add(temp);
					if(rueckgabe.GetCount() < 2)
						rueckgabe.Add(wxEmptyString);
				}
				count = 0;
			}
			if(count == 2) {
				count--;
				rueckgabe.Add(wxEmptyString);
			}
		}
		return rueckgabe;
	}


	wxString dsPostgreSQLConvert::betragVervollstaendigen(const wxString &temp) {
		if(temp.IsEmpty()) {
			return _N("0,00");
		}
		
		int pos = temp.Find(_N(","));
		if(pos == wxNOT_FOUND) {
			return temp + _N(",00");
		} else {
			wxArrayString as(split(_N(","), temp));
			if(as.GetCount() > 1) {
				if(as[1].IsEmpty()) {
					return temp + _N("00");
				} else {
					if(as[1].Length() < 2) {
						return temp + _N("0");
					} else {
						return temp;
					}
				}
			}
		}
		return _N("0,00");
	}

	dsPostgreSQLConvert::dsPostgreSQLConvert(wxString _s) {
		s = _s;
	}
	
	bool dsPostgreSQLConvert::asBool() {
		return (s == _N("t"));
	}
	
	long dsPostgreSQLConvert::asInteger() {
		long result;
		s.ToLong(&result);
		return result;
	}
	
	wxString dsPostgreSQLConvert::asString() {
		return s;
	}
	
	wxString dsPostgreSQLConvert::asFloatString() {
		s.Replace(_N("."), _N(","));
		return betragVervollstaendigen(s);
	}
	
	DSCurrency dsPostgreSQLConvert::asFloat() {
		double temp;
		wxString temp2(s);
		tNemp2.Replace(_N("."), _N(","));

		if(temp2.ToDouble(&temp))
			return DSCurrency((double) temp);
		return DSCurrency();
	}

	DSCurrency dsPostgreSQLConvert::ToDouble() {
		return asFloat();
	}

#endif
#endif
