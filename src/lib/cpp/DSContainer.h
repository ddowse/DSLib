#ifndef DS_CONTAINER_H_
#define DS_CONTAINER_H_

#include <wx/wx.h>
#include <vector>
#include "DSContainerType.h"
#include "DSClassInfo.h"

#define DS_CONTAINER_VERSION	_N("0.3.4")
#define DS_CONTAINER_NAME		_N("DSContainer")
#define DS_CONTAINER_AUTHOR		_N("Thorsten Geppert (thorsten@dynsoft.com")

namespace DynSoft {

	class DSContainer : public DSLib, private std::vector<DSContainerType *> {
	
		public:
			DSContainer(const bool cleanUp = false);
			virtual ~DSContainer();

			unsigned int CleanUp();

			DSClassInfo GetClassInfo();

			void SetCleanUp(const bool cleanUp);
			bool GetCleanUp() const;
			unsigned int GetCount() const;

			DSContainerType *Add(DSContainerType *entry, const bool check = false);
			DSContainerType *Get(unsigned int index);
			DSContainerType *Get(const wxString &compare);
			DSContainerType *Remove(unsigned int index);
			bool Remove(const wxString &compare);
			bool Remove(const DSContainerType *entry);

		protected:
			bool cleanUp;
	
	};

}

#endif /* DS_CONTAINER_H_ */
