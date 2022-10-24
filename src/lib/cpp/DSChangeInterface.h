#include "DSSetup.h"
#ifdef DS_WITH_GUI

#ifndef DS_CHANGEINTERFACE_H_
#define DS_CHANGEINTERFACE_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_CHANGEINTERFACE_VERSION        _N("0.0.1")
#define DS_CHANGEINTERFACE_NAME           _N("DSChangeInterface")
#define DS_CHANGEINTERFACE_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSChangeInterface : public DSLib {

		public:
			DSChangeInterface(bool *changed = NULL);

			DSClassInfo GetClassInfo();

			void SetChange(bool *changed);
			bool *GetChange() const;
			bool SetChanged(const bool changed);

		protected:
			bool *changed;

	};

}

#endif /* DS_CHANGEINTERFACE_H_ */

#endif /* DS_WITH_GUI */
