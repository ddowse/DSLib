#ifndef DS_ERROR_TYPE_H_
#define DS_ERROR_TYPE_H_

#include <wx/wx.h>
#include "DSContainerType.h"
#include "DSClassInfo.h"
#include "DSDateTime.h"

#define DS_ERROR_TYPE_NAME		_N("DSErrorType")
#define DS_ERROR_TYPE_VERSION	_N("1.0.1")
#define DS_ERROR_TYPE_AUTHOR	_N("Thorsten Geppert (thorsten@dynsoft.com)")

namespace DynSoft {

	class DSErrorType : public DSContainerType {

		public:
			DSErrorType();
			DSErrorType(
				const int number,
				const wxString &module,
				const wxString &description,
				const wxString &message,
				const DSDateTime &date
			);

			DSClassInfo GetClassInfo();

			void SetNumber(const int number);
			int GetNumber() const;

			void SetModule(const wxString &module);
			wxString GetModule() const;

			void SetDescription(const wxString &description);
			wxString GetDescription() const;

			void SetMessage(const wxString &message);
			wxString GetMessage() const;

			void SetDate(const DSDateTime &date);
			DSDateTime GetDate() const;

		protected:
			int number;
			wxString module;
			wxString description;
			wxString message;
			DSDateTime date;

	};

}

#endif /* DS_ERROR_TYPE_H_ */
