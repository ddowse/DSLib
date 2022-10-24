#ifndef DS_CONTAINER_TYPE_H_
#define DS_CONTAINER_TYPE_H_

#include <wx/wx.h>
#include "DSType.h"
#include "DSClassInfo.h"

#define DS_CONTAINER_TYPE_VERSION	_N("0.2.1")
#define DS_CONTAINER_TYPE_NAME		_N("DSContainerType")
#define DS_CONTAINER_TYPE_AUTHOR	_N("Thorsten Geppert (thorsten@dynsoft.com")

namespace DynSoft {

	class DSContainerType : public DSType {
	
		public:
			DSContainerType();
			DSContainerType(const wxString &comparison);

			DSClassInfo GetClassInfo();

			void SetComparison(const wxString &comparison);
			wxString GetComparision() const;

		protected:
			wxString comparison;
	
	};

}

#endif /* DS_CONTAINER_TYPE_H_ */
