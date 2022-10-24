#include "DSSession.h"
#include "DSCgi.h"
#include <stdlib.h>

#include "DSCasts.h"

#ifdef __WXMSW__
	long random() {
		return 0;
	}

	void srandom(unsigned int seed) {
	}
#endif

DynSoft::DSSession::DSSession(
	DSQuery *query,
	const bool cleanUp,
	const wxString &tableName
) : DSData(
	query,
	cleanUp
) {
	this->tableName = tableName;
}

DynSoft::DSClassInfo DynSoft::DSSession::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_SESSION_NAME,
		DS_SESSION_VERSION,
		DS_SESSION_AUTHOR
	);
}

wxString DynSoft::DSSession::CreateNewSession(const wxString &information) {
	wxString sessionId;

	do {
		sessionId = CreateNewSessionId();
	} while(Exists(sessionId));

	query->Prepare(_N(
		"INSERT INTO \":table:\" ("
		"	id, "
		"	ip, "
		"	useragent, "
		"	countdown, "
		"	information"
		") VALUES ("
		"	:id:, "
		"	:ip:, "
		"	:useragent:, "
		"	NOW(), "
		"	:information:"
		")"
	));
	query->Bind(_N("table"), tableName, false);
	query->Bind(_N("id"), sessionId);
	query->Bind(_N("ip"), DSCgi::GetVariable(_N("REMOTE_ADDR")));
	query->Bind(_N("useragent"), DSCgi::GetVariable(_N("HTTP_USER_AGENT")));
	if(!information.IsEmpty())
		query->Bind(_N("information"), information);
	else
		query->Bind(_N("information"), _N("NULL"), false);
	query->Exec(false);

	DeleteOld();

	return sessionId;
}

bool DynSoft::DSSession::Exists(const wxString &sessionId) {
	query->Prepare(_N("SELECT COUNT(*) AS counter FROM \":table:\" WHERE id = :id:"));
	query->Bind(_N("table"), tableName, false);
	query->Bind(_N("id"), sessionId);
	query->Exec();
	query->NextRecord();
	bool exists = query->GetField(_N("counter")).ToInt() > 0;
	query->FreeResult();
	return exists;
}

bool DynSoft::DSSession::IsValid(
	const wxString &sessionId,
	const bool actualize
) {
	query->Prepare(_N(
		"SELECT "
		"	COUNT(id) AS counter "
		"FROM "
		"	\":table:\" "
		"WHERE "
		"	id = :id: "
		"AND "
		"	EXTRACT('epoch' FROM countdown) + 21600 >= EXTRACT('epoch' FROM NOW()) "
		"AND "
		"	useragent = :useragent: "
		"AND "
		"	ip = :ip:"
	));
	query->Bind(_N("table"), tableName, false);
	query->Bind(_N("id"), sessionId);
	query->Bind(_N("ip"), DSCgi::GetVariable(_N("REMOTE_ADDR")));
	query->Bind(_N("useragent"), DSCgi::GetVariable(_N("HTTP_USER_AGENT")));
	query->Exec();
	query->NextRecord();
	bool active = query->GetField(_N("counter")).ToInt() > 0;
	query->FreeResult();

	if(actualize) {
		query->Prepare(_N("UPDATE sessions SET countdown = NOW() WHERE id = :id:"));
		query->Bind(_N("id"), sessionId);
		query->Exec(false);
	}

	DeleteOld();

	return active;
}

wxString DynSoft::DSSession::CreateNewSessionId() {
	char buffer [11];
	srandom(time(NULL));
	srandom(random());
	snprintf(buffer, 11, "%ld%ld", random(), random());
	return DSCasts::ToString(buffer);
}

bool DynSoft::DSSession::DeleteOld() {
	query->Prepare(_N(
		"DELETE FROM "
		"	\":table:\" "
		"WHERE "
		"	EXTRACT('epoch' FROM countdown) + 21600 < EXTRACT('epoch' FROM NOW())"
	));
	query->Bind(_N("table"), tableName, false);
	return query->Exec(false);
}

bool DynSoft::DSSession::RemoveSession(const wxString &sessionId) {
	query->Prepare(_N("DELETE FROM \":table:\" WHERE id = :id:"));
	query->Bind(_N("table"), tableName, false);
	query->Bind(_N("id"), sessionId);
	return query->Exec(false);
}

wxString DynSoft::DSSession::GetInformation(const wxString &sessionId) {
	wxString information;
	
	query->Prepare(_N("SELECT information FROM \":table:\" WHERE id = :id:"));
	query->Bind(_N("table"), tableName, false);
	query->Bind(_N("id"), sessionId);
	query->Exec();
	if(query->NextRecord())
		information = query->GetField(_N("information")).ToString();
	query->FreeResult();

	return information;
}

bool DynSoft::DSSession::SetInformation(
	const wxString &sessionId,
	const wxString &information
) {
	query->Prepare(_N("UPDATE \":table:\" SET information = :information: WHERE id = :id:"));
	query->Bind(_N("table"), tableName, false);
	if(!information.IsEmpty())
		query->Bind(_N("information"), information);
	else
		query->Bind(_N("information"), _N("NULL"), false);
	query->Bind(_N("id"), sessionId);
	return query->Exec(false);
}
