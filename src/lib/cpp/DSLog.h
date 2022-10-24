#ifndef DS_LOG_H_
#define DS_LOG_H_

#include <wx/wx.h>
#include "DSData.h"
#include "DSClassInfo.h"
#include "DSLogType.h"
#include "DSQuery.h"

#define DS_LOG_VERSION					_N("0.0.2")
#define DS_LOG_NAME						_N("DSLog")
#define DS_LOG_AUTHOR					_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_LOG_DEFAULT_TABLE			_N("log")
#define DS_LOG_INITIALIZE_NUMBER		0
#define DS_LOG_INITIALIZE_MODULE		DS_LOG_NAME
#define DS_LOG_INITIALIZE_USERNAME		_N("System")
#define DS_LOG_INITIALIZE_DESCRIPTION	_N("Log-Initialization")
#define DS_LOG_INITIALIZE_MESSAGE		_N("First entry to initialize log system")
#define DS_LOG_INITIALIZE_DATE			DSDateTime()


namespace DynSoft {

	class DSLog : public DSData {
	
		public:
			DSLog(
				DSQuery *query,
				const bool cleanUp = true,
				const wxString &table = DS_LOG_DEFAULT_TABLE
			);

			DSClassInfo GetClassInfo();

			bool Initialize();
			bool Add(const DSLogType &log, const bool withoutInitialization = false);
			void SetTable(const wxString &table);
			wxString GetTable() const;
			bool GetInitialized() const;

			bool GetAll();
			bool GetLimited(const unsigned int limit);
			bool GetUsers();
			bool GetModules();
			bool Search(
				wxString from               = wxEmptyString,
				wxString to                 = wxEmptyString,
				const wxString &username    = wxEmptyString,
				const int number            = -1,
				const wxString &module      = wxEmptyString,
				const wxString &description = wxEmptyString,
				const wxString &message     = wxEmptyString,
				const unsigned int limit    = 0
			);

			void Get(DSLogType *log);
			wxString GetUsername();
			wxString GetModule();

		protected:
			bool initialized;
			wxString table;
	
	};

}

#endif /* DS_LOG_H_ */
