#ifndef DS_QUERY_H_
#define DS_QUERY_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSDatabase.h"
#include "DSClassInfo.h"
#include "DSQueryParser.h"
#include "DSCasts.h"
#include "DSDateTime.h"

#define DS_QUERY_VERSION		_N("0.4.5")
#define DS_QUERY_NAME			_N("DSQuery")
#define DS_QUERY_AUTHOR			_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSQuery : public DSQueryParser {

		public:
			DSQuery(DSDatabase *db);
			virtual ~DSQuery();

			DSClassInfo GetClassInfo();

			virtual bool Exec(const bool storeResult = true)                                      = 0;
			virtual DSCasts GetField(const wxString &field, const bool caseSensitive = true)      = 0;
			virtual DSCasts GetField(const int column)                                            = 0;
			virtual DSCasts GetColumn(const int column)                                           = 0;
			virtual bool IsNull(const wxString &field)                                            = 0;
			virtual bool IsNull(const int column)                                                 = 0;
			virtual unsigned int GetRowCount() const                                              = 0;
			virtual unsigned int GetColumnCount() const                                           = 0;
			virtual bool Begin()                                                                  = 0;
			virtual bool Commit()                                                                 = 0;
			virtual bool Rollback()                                                               = 0;
			virtual bool NextRecord()                                                             = 0;
			virtual void FreeResult()                                                             = 0;

			static DSDateTime GetDate(const wxString &date);
			static DSDateTime GetTime(const wxString &time);
			static DSDateTime GetDateTime(const wxString &dateTime);

			virtual bool Query(
				const wxString &query,
				const bool storeResult = true
			);

			virtual bool QueryByResource(
				const wxString &resource,
				const bool storeResult = true
			);

			DSDatabase *GetDb() const;

			bool IsRunning() const;
			bool ExistsColumn(const wxString &column);
		
		protected:
			WX_DECLARE_STRING_HASH_MAP(wxString, KeyValues);

			DSDatabase *db;
			bool running;

	};

}

#endif /* DS_QUERY_H_ */
