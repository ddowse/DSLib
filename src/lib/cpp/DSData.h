#ifndef DS_DATA_H_
#define DS_DATA_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSQuery.h"

#define DS_DATA_NAME		_N("DSData")
#define DS_DATA_VERSION		_N("0.8.0")
#define DS_DATA_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSData : public DSLib {
	
		public:
			DSData(DSQuery *query, const bool cleanUp = true);
			virtual ~DSData();

			DSClassInfo GetClassInfo();

			void SetCleanUp(const bool cleanUp);
			bool GetCleanUp() const;
			bool GetRunning() const;

			void SetQuery(DSQuery *query, const bool deleteOld = true);
			DSQuery *GetQuery() const;

			void Reset();
			bool Run();
			unsigned int GetCount();
			bool Create(const wxString &parsedQuery);

		protected:
			DSQuery *query;
			bool cleanUp;
			bool running;
	
	};

}

#endif /* DS_DATA_H_ */
