#include "DSData.h"

DynSoft::DSData::DSData(DynSoft::DSQuery *query, const bool cleanUp) : DSLib() {
	this->query   = query;
	this->cleanUp = cleanUp;
	this->running = false;
}

DynSoft::DSData::~DSData() {
	if(GetCleanUp())
		delete query;
}

DynSoft::DSClassInfo DynSoft::DSData::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DATA_NAME,
		DS_DATA_VERSION,
		DS_DATA_AUTHOR
	);
}

void DynSoft::DSData::SetCleanUp(const bool cleanUp) {
	this->cleanUp = cleanUp;
}

bool DynSoft::DSData::GetCleanUp() const {
	return cleanUp;
}

bool DynSoft::DSData::GetRunning() const {
	return running;
}

void DynSoft::DSData::SetQuery(DynSoft::DSQuery *query, bool deleteOld) {
	if(deleteOld)
		delete this->query;
	this->query = query;
}

DynSoft::DSQuery *DynSoft::DSData::GetQuery() const {
	return query;
}


void DynSoft::DSData::Reset() {
	if(GetRunning())
		if(query != NULL)
			query->FreeResult();
	running = false;
}

bool DynSoft::DSData::Run() {
	if(query != NULL) {
		if(GetRunning()) {
			if(query->NextRecord()) {
				return true;
			} else {
				Reset();
			}
		}
	}
	return false;
}

unsigned int DynSoft::DSData::GetCount() {
	if(query != NULL && GetRunning())
		return query->GetRowCount();
	else
		return (unsigned int) 0;
}

bool DynSoft::DSData::Create(const wxString &parsedQuery) {
	running = query->Query(parsedQuery);
	return running;
}

