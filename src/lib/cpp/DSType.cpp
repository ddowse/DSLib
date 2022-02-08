#include "DSType.h"

DynSoft::DSType::DSType() : DSLib() {
}

DynSoft::DSClassInfo DynSoft::DSType::GetClassInfo() {
	return DSClassInfo(
		DS_TYPE_NAME,
		DS_TYPE_VERSION,
		DS_TYPE_AUTHOR
	);
}
