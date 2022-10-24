#include "DSPayPalPaymentInfo.h"
#include "DSCasts.h"

DynSoft::DSPayPalPaymentInfo::DSPayPalPaymentInfo() : DSType() {
	SetAck(false);
	SetErrorCode(0);
}

DynSoft::DSPayPalPaymentInfo::DSPayPalPaymentInfo(
	const bool ack,
	const int errorCode,
	const wxString &protectionEligibilityType,
	const wxString &protectionEligibility,
	const wxString &transactionType,
	const wxString &transactionId,
	const wxString &secureMerchantAccountId,
	const wxString &paymentStatus,
	const wxString &paymentType,
	const wxString &reasonCode,
	const wxString &pendingReason,
	const wxString &orderTime,
	const wxString &currencyCode,
	const DSCurrency amt,
	const DSCurrency taxAmt,
	const DSCurrency feeAmt
) {
	SetAck(ack);
	SetErrorCode(errorCode);
	SetProtectionEligibility(protectionEligibility);
	SetProtectionEligibilityType(protectionEligibilityType);
	SetTransactionType(transactionType);
	SetTransactionId(transactionId);
	SetSecureMerchantAccountId(secureMerchantAccountId);
	SetPaymentStatus(paymentStatus);
	SetPaymentType(paymentType);
	SetReasonCode(reasonCode);
	SetPendingReason(pendingReason);
	SetOrderTime(orderTime);
	SetCurrencyCode(currencyCode);
	SetAmt(amt);
	SetTaxAmt(taxAmt);
	SetFeeAmt(feeAmt);
}

DynSoft::DSPayPalPaymentInfo::~DSPayPalPaymentInfo() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalPaymentInfo::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_PAYMENT_INFO_NAME,
        DS_PAYPAL_PAYMENT_INFO_VERSION,
        DS_PAYPAL_PAYMENT_INFO_AUTHOR
    );
}

void DynSoft::DSPayPalPaymentInfo::SetAck(const bool ack) {
	this->ack = ack;
}

bool DynSoft::DSPayPalPaymentInfo::GetAck() const {
	return ack;
}

void DynSoft::DSPayPalPaymentInfo::SetErrorCode(const int errorCode) {
	this->errorCode = errorCode;
}

int DynSoft::DSPayPalPaymentInfo::GetErrorCode() const {
	return errorCode;
}

void DynSoft::DSPayPalPaymentInfo::SetProtectionEligibility(const wxString &protectionEligibility) {
	this->protectionEligibility = protectionEligibility;
}

wxString DynSoft::DSPayPalPaymentInfo::GetProtectionEligibility() const {
	return protectionEligibility;
}

void DynSoft::DSPayPalPaymentInfo::SetProtectionEligibilityType(const wxString &protectionEligibilityType) {
	this->protectionEligibilityType = protectionEligibilityType;
}

wxString DynSoft::DSPayPalPaymentInfo::GetProtectionEligibilityType() const {
	return protectionEligibilityType;
}

void DynSoft::DSPayPalPaymentInfo::SetTransactionType(const wxString &transactionType) {
	this->transactionType = transactionType;
}

wxString DynSoft::DSPayPalPaymentInfo::GetTransactionType() const {
	return transactionType;
}

void DynSoft::DSPayPalPaymentInfo::SetTransactionId(const wxString &transactionId) {
	this->transactionId = transactionId;
}

wxString DynSoft::DSPayPalPaymentInfo::GetTransactionId() const {
	return transactionId;
}

void DynSoft::DSPayPalPaymentInfo::SetSecureMerchantAccountId(const wxString &secureMerchantAccountId) {
	this->secureMerchantAccountId = secureMerchantAccountId;
}

wxString DynSoft::DSPayPalPaymentInfo::GetSecureMerchantAccountId() const {
	return secureMerchantAccountId;
}

void DynSoft::DSPayPalPaymentInfo::SetPaymentStatus(const wxString &paymentStatus) {
	this->paymentStatus = paymentStatus;
}

wxString DynSoft::DSPayPalPaymentInfo::GetPaymentStatus() const {
	return paymentStatus;
}

void DynSoft::DSPayPalPaymentInfo::SetPaymentType(const wxString &paymentType) {
	this->paymentType = paymentType;
}

wxString DynSoft::DSPayPalPaymentInfo::GetPaymentType() const {
	return paymentType;
}

void DynSoft::DSPayPalPaymentInfo::SetReasonCode(const wxString &reasonCode) {
	this->reasonCode = reasonCode;
}

wxString DynSoft::DSPayPalPaymentInfo::GetReasonCode() const {
	return reasonCode;
}

void DynSoft::DSPayPalPaymentInfo::SetPendingReason(const wxString &pendingReason) {
	this->pendingReason = pendingReason;
}

wxString DynSoft::DSPayPalPaymentInfo::GetPendingReason() const {
	return pendingReason;
}

void DynSoft::DSPayPalPaymentInfo::SetOrderTime(const wxString &orderTime) {
	this->orderTime = orderTime;
}

wxString DynSoft::DSPayPalPaymentInfo::GetOrderTime() const {
	return orderTime;
}

void DynSoft::DSPayPalPaymentInfo::SetCurrencyCode(const wxString &currencyCode) {
	this->currencyCode = currencyCode;
}

wxString DynSoft::DSPayPalPaymentInfo::GetCurrencyCode() const {
	return currencyCode;
}

void DynSoft::DSPayPalPaymentInfo::SetAmt(const DynSoft::DSCurrency amt) {
	this->amt = amt;
}

DynSoft::DSCurrency DynSoft::DSPayPalPaymentInfo::GetAmt() const {
	return amt;
}

void DynSoft::DSPayPalPaymentInfo::SetTaxAmt(const DynSoft::DSCurrency taxAmt) {
	this->taxAmt = amt;
}

DynSoft::DSCurrency DynSoft::DSPayPalPaymentInfo::GetTaxAmt() const {
	return taxAmt;
}

void DynSoft::DSPayPalPaymentInfo::SetFeeAmt(const DynSoft::DSCurrency feeAmt) {
	this->feeAmt = feeAmt;
}

DynSoft::DSCurrency DynSoft::DSPayPalPaymentInfo::GetFeeAmt() const {
	return feeAmt;
}

wxString DynSoft::DSPayPalPaymentInfo::ToString() {
	wxString result;

	result += _N("                            Ack: ") + (GetAck() ? _N("Success") : _N("Failure")) + _N("\n");
	result += _N("                     Error code: ") + DynSoft::DSCasts::ToString(GetErrorCode()) + _N("\n");
	result += _N("    Protection eligibility type: ") + GetProtectionEligibilityType() + _N("\n");
	result += _N("         Protection eligibility: ") + GetProtectionEligibility() + _N("\n");
	result += _N("               Transaction type: ") + GetTransactionType() + _N("\n");
	result += _N("                 Transaction id: ") + GetTransactionId() + _N("\n");
	result += _N("     Secure merchant account id: ") + GetSecureMerchantAccountId() + _N("\n");
	result += _N("                 Payment status: ") + GetPaymentStatus() + _N("\n");
	result += _N("                   Payment type: ") + GetPaymentType() + _N("\n");
	result += _N("                    Reason code: ") + GetReasonCode() + _N("\n");
	result += _N("                 Pending reason: ") + GetPendingReason() + _N("\n");
	result += _N("                     Order time: ") + GetOrderTime() + _N("\n");
	result += _N("                  Currency code: ") + GetCurrencyCode() + _N("\n");
	result += _N("                            AMT: ") + GetAmt().ToString() + _N("\n");
	result += _N("                        Tax AMT: ") + GetTaxAmt().ToString() + _N("\n");
	result += _N("                        Fee AMT: ") + GetFeeAmt().ToString();

	return result;
}
