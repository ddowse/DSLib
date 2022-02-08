#ifndef DS_TEST_H_
#define DS_TEST_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSType.h"
#include "DSClassInfo.h"
#include "DSDateTime.h"
#include "DSTemplateContainer.h"

#define DS_TEST_VERSION			_N("0.0.3")
#define DS_TEST_NAME			_N("DSTest")
#define DS_TEST_AUTHOR			_N("Thorsten Geppert (thorsten@ext2fs.de")

#define DS_TESTENTITY_VERSION	_N("0.0.2")
#define DS_TESTENTITY_NAME		_N("DSTestEntity")
#define DS_TESTENTITY_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de")

namespace DynSoft {

	class DSTest : public DSType {

		public:
			class DSTestEntity : public DSType {
			
				public:
					DSTestEntity();
					DSTestEntity(
						const bool success,
						const wxString &description,
						const wxString &successMessage,
						const wxString &errorMessage,
						const DSDateTime &timeStamp
					);

					DSClassInfo GetClassInfo();

					void SetSuccess(const bool success);
					bool GetSuccess() const;

					void SetDescription(const wxString &description);
					wxString GetDescription() const;

					void SetSuccessMessage(const wxString &successMessage);
					wxString GetSuccessMessage() const;

					void SetErrorMessage(const wxString &errorMessage);
					wxString GetErrorMessage() const;

					void SetTimeStamp(const DSDateTime &timeStamp);
					DSDateTime GetTimeStamp() const;

				protected:
					bool success;
					wxString description;
					wxString successMessage;
					wxString errorMessage;
					DSDateTime timeStamp;
			
			};

			DSTest(const wxString &module);
			~DSTest();

			DSClassInfo GetClassInfo();

			void __Assert(
				const bool success,
				const wxString &description,
				const wxString &errorMessage = _N("Not Ok"),
				const wxString &successMessage = _N("Ok")
			);

			virtual void __Test() = 0;

			DSTemplateContainer<DSTestEntity *> *__GetEntities();
			wxString __GetModule() const;

		protected:
			wxString module;
			DSTemplateContainer<DSTestEntity *> entities;
	
	};

}

#endif /* DS_TEST_H_ */
