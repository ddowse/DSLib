#ifndef _DSPOSTGRESQL_H_
#define _DSPOSTGRESQL_H_

#include "DSCurrency.h"
#include <libpq-fe.h>
#include <string>
#include "DSLib.h"
#include "DSPostgreSQLDatabase.h"
#include <wx/wx.h>

#ifndef wxUSE_UNICODE
	#define wxUSE_UNICODE
#endif

#ifdef wxUSE_UNICODE
	#define futf(value) ( (const char *) (value).mb_str(wxConvUTF8) )
	#define tutf(value) ( wxString((value).c_str(), wxConvUTF8) )
#else
	#define futf(value) (value).c_str()
	#define tutf(value) (value).c_str()
#endif

using namespace DynSoft;

class dsPostgreSQLInfo {

	public:
		dsPostgreSQLInfo(const wxString &query) {
			DSLib::Print(query);
		}

};

class dsPostgreSQL {
	
	public:
		dsPostgreSQL();
		~dsPostgreSQL();
		DSPostgreSQLDatabase *GetNewDbObject();
		/*
		void setHostname(const char* = "localhost");
		void setDatabase(const char* = "test");
		void setUsername(const char* = "root");
		void setPassword(const char* = "");
		void setPort(const char* = "5432");
		void setFlags(const char* = NULL);
		void setTty(const char* = NULL);
		*/
		void setHostname(const wxString & = _N("localhost"));
		void setDatabase(const wxString & = _N("test"));
		void setUsername(const wxString & = _N("root"));
		void setPassword(const wxString & = wxEmptyString);
		void setPort(const wxString & = _N("5432"));

		wxString getHostname() const;
		wxString getDatabase() const;
		wxString getUsername() const;
		wxString getPassword() const;
		wxString getPort() const;
		char *getTty() const;
		char *getFlags() const;

		void setFlags(char * = NULL);
		void setTty(char * = NULL);
		bool connect();
		void disconnect();
		bool isConnect();

		PGconn *dsConnection;
		
	private:
		bool isSetHostname;
		bool isSetDatabase;
		bool isSetUsername;
		bool isSetPassword;
		bool isSetPort;
		bool isSetFlags;
		bool isSetTty;
		bool isConnected;

		wxString hostname;
		wxString database;
		wxString username;
		wxString password;
		wxString port;
		char *flags;
		char *tty;

		DSPostgreSQLDatabase *newDbObject;

};

#ifdef wxUSE_UNICODE
	class dsPostgreSQLConvert {
		
		public:
			dsPostgreSQLConvert(wxString);
			wxArrayString split(const wxString &, const wxString &);
			wxString betragVervollstaendigen(const wxString &);

			long asInteger();
			wxString asString();
			bool asBool();
			wxString asFloatString();
			DSCurrency asFloat();
			DSCurrency ToDouble();
			
		private:
			wxString s;
		
	};
#endif

class dsPostgreSQLQuery {
	public:
		dsPostgreSQLQuery(dsPostgreSQL *);
		bool exec(bool = true);
		void freeResult();
#ifndef wxUSE_UNICODE
		bool query(char *, bool = true);
		void bindValue(std::string, std::string, bool = true, bool = true);
		void bindValueNull(std::string, std::string, bool = true, bool = true);
		void bindValueInt(std::string, int);
		void bindValueBool(std::string, bool);
		void bindValueFloat(std::string, float);
		void bindValueFloat(std::string, std::string);
		std::string field(const char *);
		std::string field(int);
		std::string column(int);
		std::string getQuery() { return sQuery; }
		void prepare(std::string _query) { sQuery = _query; }
		std::string getError() { return PQresultErrorMessage(dsResult); }
		std::string getStatus() { return PQresStatus(PQresultStatus(dsResult)); }
		bool isNull(const char *);
#ifdef USE_WXWIDGETS
		bool query(const wxString &, bool = true, wxString * = NULL, wxString * = NULL);
		dsPostgreSQLConvert field(const wxString);
		dsPostgreSQLConvert field(int);
		wxString column(int);
		void bindValue(const wxString &, const wxString &, bool = true, bool = true);
		void bindValueNull(const wxString &, const wxString &, bool = true, bool = true);
		void bindValueInt(const wxString &, int);
		void bindValueBool(const wxString &, bool);
		void bindValueFloat(const wxString &, DSCurrency);
		void bindValueFloat(const wxString &, wxString);
		void prepare(wxString _query) { sQuery = _query; }
		wxString getError() { return PQresultErrorMessage(dsResult); }
		wxString getStatus() { return PQresStatus(PQresultStatus(dsResult)); }
		bool isNull(const wxString &);
#endif
#else
		bool query(char *, bool = false);
		static wxString escape(wxString str);
		bool query(const wxString &, bool = true, wxString * = NULL, wxString * = NULL);
		void bindValueNull(const wxString &, const wxString &, bool = true, bool = true);
		void bindValue(const wxString &, wxString, bool = true, bool = true);
		void bindValueInt(const wxString &, int);
		void bindValueBool(const wxString &, bool);
		void bindValueFloat(const wxString &, DSCurrency);
		void bindValueFloat(const wxString &, wxString);
		wxString escapeBin(char *, size_t);
		char *escapeBinChar(char *, size_t, size_t &);
		unsigned char *field(const wxString &, size_t &);
		dsPostgreSQLConvert field(int);
		dsPostgreSQLConvert field(const wxString &);
		wxString column(int);
		wxString getQuery() { return sQuery; }
		void prepare(wxString _query) { sQuery = _query; }
		wxString getError() { return wxString(PQresultErrorMessage(dsResult), wxConvUTF8); }
		wxString getStatus() { return wxString(PQresStatus(PQresultStatus(dsResult)), wxConvUTF8); }
		bool isNull(const wxString &);
#endif
		bool nextRecord();

		bool isNull(int);
		unsigned int numRows();
		unsigned int numFields();
		
		bool begin();
		bool commit();
		bool rollback();
		
	private:
	
#ifndef wxUSE_UNICODE
		std::string sQuery;
#else
		wxString sQuery;
#endif
		PGresult *dsResult;

		dsPostgreSQL *dps;

		bool isQuery;

		int rowsCount;

};


#endif //_DSPOSTGRESQL_H_

