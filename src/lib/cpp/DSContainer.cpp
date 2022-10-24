#include "DSContainer.h"

DynSoft::DSContainer::DSContainer(const bool cleanUp) : DSLib(), std::vector<DSContainerType *>() {
	SetCleanUp(cleanUp);
}

DynSoft::DSContainer::~DSContainer() {
	if(GetCleanUp())
		CleanUp();
}

unsigned int DynSoft::DSContainer::CleanUp() {
	unsigned int i = 0;
	
	for(; i < GetCount(); i++)
		if(Get(i) != NULL)
			delete Get(i);
	this->clear();

	return i;
}

DynSoft::DSClassInfo DynSoft::DSContainer::GetClassInfo() {
	return DSClassInfo(
		DS_CONTAINER_NAME,
		DS_CONTAINER_VERSION,
		DS_CONTAINER_AUTHOR
	);
}

void DynSoft::DSContainer::SetCleanUp(const bool cleanUp) {
	this->cleanUp = cleanUp;
}

bool DynSoft::DSContainer::GetCleanUp() const {
	return cleanUp;
}

unsigned int DynSoft::DSContainer::GetCount() const {
	return this->size();
}

DynSoft::DSContainerType* DynSoft::DSContainer::Add(DSContainerType *entry, const bool check) {
	DSContainerType *tmp = NULL;
	if(check) {
		//tmp = entry;
		DSContainerType *tmp2 = NULL;
		for(unsigned int i = 0; i < GetCount(); i++) {
			tmp2 = Get(i);
			if(tmp2 != NULL) {
				if(tmp2->GetComparision() == entry->GetComparision()) {
					tmp = tmp2;
					break;
				}
			}
		}
	}

	if(tmp != entry)
		this->push_back(entry);
	
	return tmp;
}

DynSoft::DSContainerType *DynSoft::DSContainer::Get(unsigned int index) {
	if(index < GetCount())
		return (*this)[index];
	return (DSContainerType *) NULL;
}

DynSoft::DSContainerType *DynSoft::DSContainer::Get(const wxString &compare) {
	DSContainerType *type = NULL;
	const unsigned int count = GetCount();
	for(unsigned int i = 0; i < count; i++) {
		type = Get(i);
		if(type)
			if(type->GetComparision() == compare)
				return type;
	}

	return NULL;
}

DynSoft::DSContainerType *DynSoft::DSContainer::Remove(unsigned int index) {
	DSContainerType *entry = NULL;

	if(index < GetCount()) {
		entry = Get(index);
		this->erase(this->begin() + index);
	}
	
	return entry;
}

bool DynSoft::DSContainer::Remove(const DSContainerType *entry) {
	DSContainerType *tmp = NULL;

	for(unsigned int i = 0; i < GetCount(); i++) {
		tmp = Get(i);
		if(tmp != NULL && tmp == entry)
			return Remove(i) != NULL;
	}

	return false;
}

bool DynSoft::DSContainer::Remove(const wxString &compare) {
	return Remove(Get(compare));
}

