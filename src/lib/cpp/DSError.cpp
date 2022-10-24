#include "DSError.h"

DynSoft::DSError::DSError() : DSContainer(true) {
}

DynSoft::DSClassInfo DynSoft::DSError::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_ERROR_NAME,
		DS_ERROR_VERSION,
		DS_ERROR_AUTHOR
	);
}

void DynSoft::DSError::AddError(DSErrorType *message) {
	Add(message);
}

DynSoft::DSErrorType *DynSoft::DSError::GetError(unsigned int index) {
	return (DSErrorType *) Get(index);
}

DynSoft::DSErrorType *DynSoft::DSError::GetLast() {
	if(GetCount() > 0)
		return (DSErrorType *) Get(GetCount() - 1);
	return (DSErrorType *) NULL;
}


