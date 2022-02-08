#include "DSPayPalTextLog.h"
#include "DSFile.h"
#include "DSDateTime.h"

DynSoft::DSPayPalTextLog::DSPayPalTextLog(const wxString &filename) : DynSoft::DSPayPalLog(
) {
	SetFilename(filename);
}

DynSoft::DSPayPalTextLog::~DSPayPalTextLog() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalTextLog::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_TEXT_LOG_NAME,
        DS_PAYPAL_TEXT_LOG_VERSION,
        DS_PAYPAL_TEXT_LOG_AUTHOR
    );
}

bool DynSoft::DSPayPalTextLog::Write(
	DSPayPalConnectionType *payPalConnectionType,
	DSPayPalMethod *payPalMethod,
	DSPayPalToken *payPalToken,
	DSPayPalCarts *payPalCarts,
	DSPayPalResponse *payPalResponse
) {
	DynSoft::DSFile file(GetFilename(), _N("a"));
	if(!file.IsOpened())
		return false;
	

	wxString log;
	log += _N("Begin: ") + GetDateTimeAsString() + _N("\n\n");

	if(payPalConnectionType) {
		log += _N("Token informations\n");
		log += _N("================================================================================\n");
		log += payPalToken->ToString();
		log += _N("\n\n");
	}

	if(payPalConnectionType) {
		log += _N("Connection informations\n");
		log += _N("================================================================================\n");
		log += payPalConnectionType->ToString();
		log += _N("\n\n");
	}

	if(payPalMethod) {
		log += _N("Method informations\n");
		log += _N("================================================================================\n");
		log += payPalMethod->ToString();
		log += _N("\n\n");
	}

	if(payPalCarts) {
		log += _N("Carts informations\n");
		log += _N("================================================================================\n");
		log += payPalCarts->ToString();
		log += _N("\n\n");
	}

	if(payPalResponse) {
		log += _N("Response informations\n");
		log += _N("================================================================================\n");
		log += payPalResponse->ToString();
		log += _N("\n\n");
	}

	log += _N("End: ") + GetDateTimeAsString();
	log += _N("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	if(!file.Write(log)) {
		file.Close();
		return false;
	}

	if(!file.Close())
		return false;

	return true;
}

void DynSoft::DSPayPalTextLog::SetFilename(const wxString &filename) {
	this->filename = filename;
}

wxString DynSoft::DSPayPalTextLog::GetFilename() const {
	return filename;
}

wxString DynSoft::DSPayPalTextLog::GetDateTimeAsString() const {
	DSDateTime dt;
	dt.SetWxDateTime(wxDateTime::Now());
	return dt.ToDatabaseDateTime();
}
