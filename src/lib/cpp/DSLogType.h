#ifndef DS_LOG_TYPE_H_
#define DS_LOG_TYPE_H_

#include <wx/wx.h>
#include <wx/datetime.h>
#include "DSErrorType.h"
#include "DSClassInfo.h"

#define DS_LOG_TYPE_NAME		_N("DSLogType")
#define DS_LOG_TYPE_VERSION		_N("0.0.2")
#define DS_LOG_TYPE_AUTHOR		_N("Thorsten Geppert (thorsten@dynsoft.com)")

namespace DynSoft {

	class DSLogType : public DSErrorType {
	
		public:
			DSLogType();
			DSLogType(
				const int number,
				const wxString &module,
				const wxString &username,
				const wxString &description,
				const wxString &message,
				const DSDateTime &date
			);

			DSClassInfo GetClassInfo();

			void SetUsername(const wxString &username);
			wxString GetUsername() const;

		protected:
			wxString username;
	
	};

}

#endif /* DS_LOG_TYPE_H_ */
