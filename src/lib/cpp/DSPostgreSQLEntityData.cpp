#include "DSPostgreSQLEntityData.h"
#include "DSPostgreSQLQuery.h"

DynSoft::DSPostgreSQLEntityData::DSPostgreSQLEntityData(
	DSPostgreSQLDatabase *db,
	const wxString &table,
	const wxString &primaryKey,
	const wxString &orderByField,
	const unsigned int order
) : DSEntityData(
	new DSPostgreSQLQuery(db),
	table,
	primaryKey,
	orderByField,
	order,
	true
) {
	ndb = db;
}

DynSoft::DSClassInfo DynSoft::DSPostgreSQLEntityData::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_POSTGRESQL_ENTITY_DATA_NAME,
		DS_POSTGRESQL_ENTITY_DATA_VERSION,
		DS_POSTGRESQL_ENTITY_DATA_AUTHOR
	);
}

void DynSoft::DSPostgreSQLEntityData::Get(DSPostgreSQLDatabaseEntity *entity) {
	Get(entity, _N("\""), _("\""));
}

void DynSoft::DSPostgreSQLEntityData::Get() {
	DSQueryParser parser;
	if(orderByField.IsEmpty()) {
		parser.Prepare(_N("SELECT * FROM \":table:\""));
	} else {
		parser.Prepare(_N("SELECT * FROM \":table:\" ORDER BY \":orderByField:\" :order:"));
		parser.Bind(_N("orderByField"), orderByField, false);
		parser.Bind(_N("order"), order, false);
	}
	parser.Bind(_N("table"), table, false);
	Create(parser.GetParsedQuery());
}

void DynSoft::DSPostgreSQLEntityData::Get(const unsigned int primaryKey) {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT * FROM \":table:\" WHERE \":primaryKey:\" = :value:"));
	parser.Bind(_N("table"), table, false);
	parser.Bind(_N("primaryKey"), this->primaryKey, false);
	parser.Bind(_N("value"), primaryKey);
	Create(parser.GetParsedQuery());
}

void DynSoft::DSPostgreSQLEntityData::Get(const wxString &primaryKey, const bool delimiters) {
	DSQueryParser parser;
	parser.Prepare(_N("SELECT * FROM \":table:\" WHERE \":primaryKey:\" = :value:"));
	parser.Bind(_N("table"), table, false);
	parser.Bind(_N("primaryKey"), this->primaryKey, false);
	parser.Bind(_N("value"), primaryKey, delimiters);
	Create(parser.GetParsedQuery());
}

void DynSoft::DSPostgreSQLEntityData::Get(const wxString &field, const wxString &value, const bool delimiters) {
	DSQueryParser parser;
	if(orderByField.IsEmpty()) {
		parser.Prepare(_N("SELECT * FROM \":table:\" WHERE \":field:\" = :value:"));
	} else {
		parser.Prepare(_N("SELECT * FROM \":table:\" WHERE \":field:\" = :value: ORDER BY \":orderByField:\" :order:"));
		parser.Bind(_N("orderByField"), orderByField, false);
		parser.Bind(_N("order"), order, false);
	}
	parser.Bind(_N("table"), table, false);
	parser.Bind(_N("field"), field, false);
	parser.Bind(_N("value"), value, delimiters);
	Create(parser.GetParsedQuery());
}

bool DynSoft::DSPostgreSQLEntityData::Exists(
	const wxString &field,
	const wxString &value,
	const wxString &oldValue,
	const bool separators,
	const bool escape
) {
	wxString queryString;
	queryString.Append(_N("SELECT COUNT(*) AS counter FROM \":table:\" WHERE \":field:\" = :value:"));
	if(!oldValue.IsEmpty())
		queryString.Append(_N(" AND \":field:\" != :oldValue:"));

	query->Prepare(queryString);
	query->Bind(_N("table"), table, false);
	query->Bind(_N("field"), field, false);
	query->Bind(_N("value"), value, separators, escape);
	if(!oldValue.IsEmpty()) {
		query->Bind(_N("field"), field, false);
		query->Bind(_N("oldValue"), oldValue, separators, escape);
	}
	query->Exec();
	query->NextRecord();
	const bool exists = query->GetField(_N("counter")).ToUnsignedInt() > 0;
	query->FreeResult();
	return exists;
}
