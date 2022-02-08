#include "DSContainerType.h"

DynSoft::DSContainerType::DSContainerType() : DSType() {
}

DynSoft::DSContainerType::DSContainerType(const wxString &comparison) : DSType() {
	SetComparison(comparison);
}

DynSoft::DSClassInfo DynSoft::DSContainerType::GetClassInfo() {
	return DSClassInfo(
		DS_CONTAINER_TYPE_NAME,
		DS_CONTAINER_TYPE_VERSION,
		DS_CONTAINER_TYPE_AUTHOR
	);
}

void DynSoft::DSContainerType::SetComparison(const wxString &comparison) {
	this->comparison = comparison;
}

wxString DynSoft::DSContainerType::GetComparision() const {
	return comparison;
}

