#ifndef DS_ERROR_H_
#define DS_ERROR_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSContainer.h"
#include "DSErrorType.h"

#define DS_ERROR_VERSION	_N("0.8.1")
#define DS_ERROR_NAME		_N("DSError")
#define DS_ERROR_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	// FIXME Create class DSTemplateContainer
	// and use it
	class DSError : public DSContainer {
	
		public:
			DSError();

			DSClassInfo GetClassInfo();

			void AddError(DSErrorType *message);
			DSErrorType *GetError(unsigned int index);
			DSErrorType *GetLast();

	};

}

#endif /* DS_ERROR_H_ */
