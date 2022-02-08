#include "DSPayPalResponse.h"
#include "DSCasts.h"

DynSoft::DSPayPalResponse::DSPayPalResponse() : DSType(
) {
}

DynSoft::DSPayPalResponse::DSPayPalResponse(
	const bool ack,
	const wxString &version,
	const wxString &timeStamp,
	const wxString &build,
	const wxString &contentType,
	const unsigned long contentLength,
	const wxString correlationId,
	const wxString &connection,
	const wxString &server,
	const wxString &cookie
) {
	Set(
		ack,
		version,
		timeStamp,
		build,
		contentType,
		contentLength,
		correlationId,
		connection,
		server,
		cookie
	);
}

DynSoft::DSPayPalResponse::~DSPayPalResponse() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalResponse::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_RESPONSE_NAME,
        DS_PAYPAL_RESPONSE_VERSION,
        DS_PAYPAL_RESPONSE_AUTHOR
    );
}

void DynSoft::DSPayPalResponse::Set(
	const bool ack,
	const wxString &version,
	const wxString &timeStamp,
	const wxString &build,
	const wxString &contentType,
	const unsigned long contentLength,
	const wxString correlationId,
	const wxString &connection,
	const wxString &server,
	const wxString &cookie
) {
	SetAck(ack);
	SetVersion(version);
	SetRealTimeStamp(timeStamp);
	SetBuild(build);
	SetContentType(contentType);
	SetContentLength(contentLength);
	SetCorrelationId(correlationId);
	SetConnection(connection);
	SetServer(server);
	SetCookie(cookie);
}

void DynSoft::DSPayPalResponse::SetBuild(const wxString &build) {
	this->build = build;
}

wxString DynSoft::DSPayPalResponse::GetBuild() const {
	return build;
}

void DynSoft::DSPayPalResponse::SetContentType(const wxString &contentType) {
	this->contentType = contentType;
}

wxString DynSoft::DSPayPalResponse::GetContentType() const {
	return contentType;
}

void DynSoft::DSPayPalResponse::SetVersion(const wxString &version) {
	this->version = version;
}

wxString DynSoft::DSPayPalResponse::GetVersion() const {
	return version;
}

void DynSoft::DSPayPalResponse::SetRealTimeStamp(const wxString &timeStamp) {
	this->timeStamp = timeStamp;
}

wxString DynSoft::DSPayPalResponse::GetRealTimeStamp() const {
	return timeStamp;
}

DynSoft::DSDateTime DynSoft::DSPayPalResponse::GetTimeStamp() const {
	return DSDateTime(); // TODO
}

void DynSoft::DSPayPalResponse::SetCorrelationId(const wxString &correlationId) {
	this->correlationId = correlationId;
}

wxString DynSoft::DSPayPalResponse::GetCorrelationId() const {
	return correlationId;
}

void DynSoft::DSPayPalResponse::SetContentLength(const unsigned int contentLength) {
	this->contentLength = contentLength;
}

unsigned int DynSoft::DSPayPalResponse::GetContentLength() const {
	return contentLength;
}

void DynSoft::DSPayPalResponse::SetConnection(const wxString &connection) {
	this->connection = connection;
}

wxString DynSoft::DSPayPalResponse::GetConnection() const {
	return connection;
}

void DynSoft::DSPayPalResponse::SetServer(const wxString &server) {
	this->server = server;
}

wxString DynSoft::DSPayPalResponse::GetServer() const {
	return server;
}

void DynSoft::DSPayPalResponse::SetAck(const bool ack) {
	this->ack = ack;
}

bool DynSoft::DSPayPalResponse::GetAck() const {
	return ack;
}

void DynSoft::DSPayPalResponse::SetCookie(const wxString &cookie) {
	this->cookie = cookie;
}

wxString DynSoft::DSPayPalResponse::GetCookie() const {
	return cookie;
}

DynSoft::DSPayPalErrors *DynSoft::DSPayPalResponse::GetErrors() {
	return &errors;
}

bool DynSoft::DSPayPalResponse::HasErrors() const {
	return errors.HasErrors();
}

DynSoft::DSPayPalPaymentInfos *DynSoft::DSPayPalResponse::GetPaymentInfos() {
	return &paymentInfos;
}

bool DynSoft::DSPayPalResponse::HasPaymentInfos() const {
	return paymentInfos.HasPaymentInfos();
}

void DynSoft::DSPayPalResponse::ParseResponseHashMap(DSStringHashMap &responseHashMap) {
	Set(
		responseHashMap[_N("ACK")] == _N("Success"),
		responseHashMap[_N("VERSION")],
		responseHashMap[_N("TIMESTAMP")],
		responseHashMap[_N("BUILD")],
		responseHashMap[_N("Content-Type")],
		DynSoft::DSCasts::ToUnsignedInt(responseHashMap[_N("Content-Length")]),
		responseHashMap[_N("CORRELATIONID")],
		responseHashMap[_N("Connection")],
		responseHashMap[_N("Server")],
		responseHashMap[_N("Set-Cookie")]
	);

	GetErrors()->ParseErrorHashMap(responseHashMap);
	GetPaymentInfos()->ParsePaymentInfoHashMap(responseHashMap);
}

wxString DynSoft::DSPayPalResponse::ToString() {
	wxString result;

	result += _N("                            ACK: ") + (GetAck() ? _N("Success") : _N("Failure")) + _N("\n");
	result += _N("                        VERSION: ") + GetVersion() + _N("\n");
	result += _N("                      TIMESTAMP: ") + GetRealTimeStamp() + _N("\n");
	result += _N("                          BUILD: ") + GetBuild() + _N("\n");
	result += _N("                   Content-Type: ") + GetContentType() + _N("\n");
	result += _N("                 Content-Length: ") + (DynSoft::DSCasts::ToString(GetContentLength())) + _N("\n");
	result += _N("                  CORRELATIONID: ") + GetCorrelationId() + _N("\n");
	result += _N("                     Connection: ") + GetConnection() + _N("\n");
	result += _N("                         Server: ") + GetServer() + _N("\n");
	result += _N("                     Set-Cookie: ") + GetCookie() + _N("\n");

	result += _N("                         Errors: ") + DynSoft::DSCasts::ToString(GetErrors()->GetErrorCount()) + _N("\n");
	if(HasErrors())
		result += GetErrors()->ToString() + _N("\n");

	result += _N("   SUCCESSPAGEREDIRECTREQUESTED: ") + DynSoft::DSCasts::ToString(GetPaymentInfos()->GetSuccessPageRedirectRequested()) + _N("\n");
	result += _N("        SHIPPINGOPTIONISDEFAULT: ") + DynSoft::DSCasts::ToString(GetPaymentInfos()->GetShippingOptionIsDefault()) + _N("\n");
	result += _N("        INSURANCEOPTIONSELECTED: ") + DynSoft::DSCasts::ToString(GetPaymentInfos()->GetInsuranceOptionSelected()) + _N("\n");
	result += _N("                   PaymentInfos: ") + DynSoft::DSCasts::ToString(GetPaymentInfos()->GetPaymentInfoCount());
	if(HasPaymentInfos())
		result += _N("\n") + GetPaymentInfos()->ToString();

	return result;
}
