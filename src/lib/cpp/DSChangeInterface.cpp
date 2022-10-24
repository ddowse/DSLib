#include "DSSetup.h"
#ifdef DS_WITH_GUI

#include "DSChangeInterface.h"

DynSoft::DSChangeInterface::DSChangeInterface(bool *changed) : DynSoft::DSLib() {
	this->changed = changed;
	SetChange(changed);
}

DynSoft::DSClassInfo DynSoft::DSChangeInterface::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_CHANGEINTERFACE_NAME,
		DS_CHANGEINTERFACE_VERSION,
		DS_CHANGEINTERFACE_AUTHOR
	);
}

void DynSoft::DSChangeInterface::SetChange(bool *changed) {
	this->changed = changed;
}

bool *DynSoft::DSChangeInterface::GetChange() const {
	return changed;
}

bool DynSoft::DSChangeInterface::SetChanged(const bool changed) {
	const bool ok = this->changed != NULL;
	if(ok)
		*this->changed = changed;
	return ok;
}

#endif
