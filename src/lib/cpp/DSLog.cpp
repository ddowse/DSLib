#include "DSLog.h"
#include "DSQueryParser.h"

DynSoft::DSLog::DSLog(
	DSQuery *query,
	const bool cleanUp,
	const wxString &table
) : DSData(
	query,
	cleanUp
) {
	SetTable(table);
	initialized = false;
}

DynSoft::DSClassInfo DynSoft::DSLog::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_LOG_NAME,
		DS_LOG_VERSION,
		DS_LOG_NAME
	);
}

bool DynSoft::DSLog::GetInitialized() const {
	return initialized;
}

bool DynSoft::DSLog::Initialize() {
	DSLogType log(
		DS_LOG_INITIALIZE_NUMBER,
		DS_LOG_INITIALIZE_MODULE,
		DS_LOG_INITIALIZE_USERNAME,
		DS_LOG_INITIALIZE_DESCRIPTION,
		DS_LOG_INITIALIZE_MESSAGE,
		DS_LOG_INITIALIZE_DATE
	);

	initialized = Add(log, true);
	return initialized;
}

bool DynSoft::DSLog::Add(const DSLogType &log, const bool withoutInitialization) {
	if(!withoutInitialization)
		if(!GetInitialized())
			return false;

	query->Prepare(_N(
		"INSERT INTO log ("
		"	stamp, "
		"	username, "
		"	number, "
		"	module, "
		"	description, "
		"	message"
		") VALUES ("
		"	:stamp:, "
		"	:username:, "
		"	:number:, "
		"	:module:, "
		"	:description:, "
		"	:message:"
		")"
	));

	query->Bind(_N("table"), GetTable(), false);
	query->Bind(_N("stamp"), log.GetDate().ToDatabaseDateTime());
	query->Bind(_N("username"), log.GetUsername());
	query->Bind(_N("number"), log.GetNumber());
	query->Bind(_N("module"), log.GetModule());
	query->Bind(_N("description"), log.GetDescription());
	query->Bind(_N("message"), log.GetMessage());

	return query->Exec(false);
}

void DynSoft::DSLog::SetTable(const wxString &table) {
	this->table = table;
}

wxString DynSoft::DSLog::GetTable() const {
	return table;
}

bool DynSoft::DSLog::GetAll() {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT * FROM :table: ORDER BY stamp DESC"));
	parser.Bind(_N("table"), GetTable(), false);
	return Create(parser.GetParsedQuery());
}

bool DynSoft::DSLog::GetLimited(const unsigned int limit) {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT * FROM :table: ORDER BY stamp DESC LIMIT :limit:"));
	parser.Bind(_N("table"), GetTable(), false);
	parser.Bind(_N("limit"), limit);
	return Create(parser.GetParsedQuery());
}

bool DynSoft::DSLog::GetUsers() {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT DISTINCT username FROM :table: ORDER BY username"));
	parser.Bind(_N("table"), GetTable(), false);
	return Create(parser.GetParsedQuery());
}

bool DynSoft::DSLog::GetModules() {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT DISTINCT module FROM :table: ORDER BY module"));
	parser.Bind(_N("table"), GetTable(), false);
	return Create(parser.GetParsedQuery());
}

bool DynSoft::DSLog::Search(
	wxString from,
	wxString to,
	const wxString &username,
	const int number,
	const wxString &module,
	const wxString &description,
	const wxString &message,
	const unsigned int limit
) {
	wxString q;
	
	// Stamp
	if(!from.IsEmpty() && !to.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("stamp BETWEEN :from: AND :to:"));
	} else if(!from.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("stamp LIKE ':from:%'"));
	} else if(!to.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("stamp LIKE ':to:%'"));
	}
	
	// Username
	if(!username.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("username ILIKE ':username:'"));
	}
	
	// Number
	if(number >= 0) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("number = :number:"));
	}

	if(!module.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("module ILIKE ':module:'"));
	}

	if(!description.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("description ILIKE ':description:'"));
	}

	if(!message.IsEmpty()) {
		if(q.IsEmpty()) q.Append(_N(" WHERE "));
		else            q.Append(_N(" AND "));
		q.Append(_N("message ILIKE ':message:'"));
	}

	q.Prepend(_N("SELECT * FROM :table:"));
	q.Append(_N(" ORDER BY stamp DESC "));

	if(limit > 0)
		q.Append(_N("LIMIT :limit:"));

	DSQueryParser parser;
	parser.Prepare(q);

	from.Append(_N(" 00:00:00"));
	to.Append(_N(" 23:59:59"));

	parser.Bind(_N("table"), GetTable(), false);
	parser.Bind(_N("from"), from);
	parser.Bind(_N("to"), to);
	parser.Bind(_N("username"), username, false);
	parser.Bind(_N("number"), number);
	parser.Bind(_N("module"), module, false);
	parser.Bind(_N("description"), description, false);
	parser.Bind(_N("message"), message, false);
	parser.Bind(_N("limit"), limit);
	return Create(parser.GetParsedQuery());
}

void DynSoft::DSLog::Get(DSLogType *log) {
	log->SetDate(DSQuery::GetDateTime(query->GetField(_N("stamp")).ToString()));
	log->SetUsername(query->GetField(_N("username")).ToString());
	log->SetNumber(query->GetField(_N("number")).ToInt());
	log->SetModule(query->GetField(_N("module")).ToString());
	log->SetDescription(query->GetField(_N("description")).ToString());
	log->SetMessage(query->GetField(_N("message")).ToString());
}

wxString DynSoft::DSLog::GetUsername() {
	return query->GetField(_N("username")).ToString();
}

wxString DynSoft::DSLog::GetModule() {
	return query->GetField(_N("module")).ToString();
}
