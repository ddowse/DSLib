#include "DSQuery.h"

DynSoft::DSQuery::DSQuery(DynSoft::DSDatabase *db) : DSQueryParser() {
	this->db = db;
	storeResult = false;
	running = false;
}

DynSoft::DSQuery::~DSQuery() {
}

DynSoft::DSClassInfo DynSoft::DSQuery::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_QUERY_NAME,
		DS_QUERY_VERSION,
		DS_QUERY_AUTHOR
	);
}

bool DynSoft::DSQuery::Query(
	const wxString &query,
	const bool storeResult
) {
	this->query = query;
	return Exec(storeResult);
}

bool DynSoft::DSQuery::QueryByResource(
	const wxString &resource,
	const bool storeResult
) {
	return Query(GetResourceByName(resource), storeResult);
}

bool DynSoft::DSQuery::IsRunning() const {
	return running;
}

bool DynSoft::DSQuery::ExistsColumn(const wxString &column) {
	const unsigned int count = GetColumnCount();
	for(unsigned int i = 0; i < count; i++) {
		if(GetColumn(i).ToString() == column)
			return true;
	}

	return false;
}


DynSoft::DSDatabase *DynSoft::DSQuery::GetDb() const {
	return db;
}

DynSoft::DSDateTime DynSoft::DSQuery::GetDate(const wxString &date) {
	if(date.Length() < 10)
		return DSDateTime();

	int pos = date.First(_N("-"));

	DynSoft::DSDateTime result;
	result.SetYear(DynSoft::DSCasts::ToInt(date.Mid(0, pos)));
	result.SetDay(DynSoft::DSCasts::ToUnsignedShort(date.Mid(pos + 4, 2)));
	result.SetMonth(DSDateTime::GetRealMonth(DynSoft::DSCasts::ToInt(date.Mid(pos + 1, 2))));

	return result;
}

DynSoft::DSDateTime DynSoft::DSQuery::GetTime(const wxString &time) {
	int pos = time.First(_N(" ")) + 1;

	DynSoft::DSDateTime result;

	result.SetHour(DynSoft::DSCasts::ToUnsignedShort(time.Mid(pos, 2)));
	result.SetMinute(DynSoft::DSCasts::ToUnsignedShort(time.Mid(pos + 3, 2)));
	result.SetSecond(DynSoft::DSCasts::ToUnsignedShort(time.Mid(pos + 6, 2)));

	return result;
}

DynSoft::DSDateTime DynSoft::DSQuery::GetDateTime(const wxString &dateTime) {
	DynSoft::DSDateTime date = GetDate(dateTime);
	DynSoft::DSDateTime time = GetTime(dateTime);

	date.SetHour(time.GetHour());
	date.SetMinute(time.GetMinute());
	date.SetSecond(time.GetSecond());

	return date;
}
