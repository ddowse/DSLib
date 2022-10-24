#ifndef DS_SESSION_H_
#define DS_SESSION_H_

#include <wx/wx.h>
#include "DSData.h"
#include "DSClassInfo.h"
#include "DSQuery.h"

#define DS_SESSION_NAME			_N("DSSession")
#define DS_SESSION_VERSION		_N("1.0.4")
#define DS_SESSION_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSSession : public DSData {
	
		public:
			DSSession(
				DSQuery *query,
				const bool cleanUp = true,
				const wxString &tableName = _N("sessions")
			);

			DSClassInfo GetClassInfo();
			
			wxString CreateNewSession(const wxString &information = wxEmptyString);
			bool IsValid(
				const wxString &sessionId,
				const bool actualize = true
			);
			bool Exists(const wxString &sessionId);
			static wxString CreateNewSessionId();
			bool RemoveSession(const wxString &sessionId);
			wxString GetInformation(const wxString &sessionId);
			bool SetInformation(const wxString &sessionId, const wxString &information);
		
		private:
			bool DeleteOld();
			wxString tableName;
	
	};

}

#endif /* DS_SESSION_H_ */
