#include "DSPayPalPaymentInfos.h"
#include "DSCasts.h"

DynSoft::DSPayPalPaymentInfos::DSPayPalPaymentInfos() : DSType() {
	SetSuccessPageRedirectRequested(false);
	SetShippingOptionIsDefault(false);
	SetInsuranceOptionSelected(false);
}

DynSoft::DSPayPalPaymentInfos::DSPayPalPaymentInfos(
	const bool successPageRedirectRequested,
	const bool shippingOptionIsDefault,
	const bool insuranceOptionSelected
) {
	SetSuccessPageRedirectRequested(successPageRedirectRequested);
	SetShippingOptionIsDefault(shippingOptionIsDefault);
	SetInsuranceOptionSelected(insuranceOptionSelected);
}

DynSoft::DSPayPalPaymentInfos::~DSPayPalPaymentInfos() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalPaymentInfos::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_PAYMENT_INFOS_NAME,
        DS_PAYPAL_PAYMENT_INFOS_VERSION,
        DS_PAYPAL_PAYMENT_INFOS_AUTHOR
    );
}

void DynSoft::DSPayPalPaymentInfos::SetSuccessPageRedirectRequested(const bool successPageRedirectRequested) {
	this->successPageRedirectRequested = successPageRedirectRequested;
}

bool DynSoft::DSPayPalPaymentInfos::GetSuccessPageRedirectRequested() const {
	return successPageRedirectRequested;
}

void DynSoft::DSPayPalPaymentInfos::SetShippingOptionIsDefault(const bool shippingOptionIsDefault) {
	this->shippingOptionIsDefault = shippingOptionIsDefault;
}

bool DynSoft::DSPayPalPaymentInfos::GetShippingOptionIsDefault() const {
	return shippingOptionIsDefault;
}

void DynSoft::DSPayPalPaymentInfos::SetInsuranceOptionSelected(const bool insuranceOptionSelected) {
	this->insuranceOptionSelected = insuranceOptionSelected;
}

bool DynSoft::DSPayPalPaymentInfos::GetInsuranceOptionSelected() const {
	return insuranceOptionSelected;
}

DynSoft::DSPayPalPaymentInfo *DynSoft::DSPayPalPaymentInfos::AddPaymentInfo(
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
	DSPayPalPaymentInfo *paymentInfo = new DSPayPalPaymentInfo(
		ack,
		errorCode,
		protectionEligibilityType,
		protectionEligibility,
		transactionType,
		transactionId,
		secureMerchantAccountId,
		paymentStatus,
		paymentType,
		reasonCode,
		pendingReason,
		orderTime,
		currencyCode,
		amt,
		taxAmt,
		feeAmt
	);
	paymentInfos.Add(paymentInfo);
	return paymentInfo;
}

void DynSoft::DSPayPalPaymentInfos::AddPaymentInfo(DynSoft::DSPayPalPaymentInfo *paymentInfo) {
	paymentInfos.Add(paymentInfo);
}

unsigned int DynSoft::DSPayPalPaymentInfos::GetPaymentInfoCount() const {
	return paymentInfos.GetCount();
}

DynSoft::DSPayPalPaymentInfo *DynSoft::DSPayPalPaymentInfos::GetPaymentInfo(const unsigned int number) {
	return paymentInfos.Get(number);
}

bool DynSoft::DSPayPalPaymentInfos::HasPaymentInfos() const {
	return GetPaymentInfoCount() > 0;
}

void DynSoft::DSPayPalPaymentInfos::CleanPaymentInfos() {
	paymentInfos.Clear(true);
}

unsigned int DynSoft::DSPayPalPaymentInfos::ParsePaymentInfoHashMap(DSStringHashMap &paymentInfoHashMap) {
	SetSuccessPageRedirectRequested(DSCasts::ToBool(paymentInfoHashMap[_N("SUCCESSPAGEREDIRECTREQUESTED")]));
	SetShippingOptionIsDefault(DSCasts::ToBool(paymentInfoHashMap[_N("SHIPPINGOPTIONISDEFAULT")]));
	SetInsuranceOptionSelected(DSCasts::ToBool(paymentInfoHashMap[_N("INSURANCEOPTIONSELECTED")]));

	unsigned int result = 0;
	wxString prefix;

	for(bool found = true; found; result++) {
		prefix = _N("PAYMENTINFO_") + DynSoft::DSCasts::ToString(result) + _N("_");
		if(!paymentInfoHashMap[prefix + _N("ACK")].IsEmpty()) {
			AddPaymentInfo(
				paymentInfoHashMap[prefix + _N("ACK")] == _N("Success"),
				DSCasts::ToInt(paymentInfoHashMap[prefix + _N("ERRORCODE")]),
				paymentInfoHashMap[prefix + _N("PROTECTIONELIGIBILITYTYPE")],
				paymentInfoHashMap[prefix + _N("PROTECTIONELIGIBILITY")],
				paymentInfoHashMap[prefix + _N("TRANSACTIONTYPE")],
				paymentInfoHashMap[prefix + _N("TRANSACTIONID")],
				paymentInfoHashMap[prefix + _N("SECUREMERCHANTACCOUNTID")],
				paymentInfoHashMap[prefix + _N("PAYMENTSTATUS")],
				paymentInfoHashMap[prefix + _N("PAYMENTTYPE")],
				paymentInfoHashMap[prefix + _N("REASONCODE")],
				paymentInfoHashMap[prefix + _N("PENDINGREASON")],
				paymentInfoHashMap[prefix + _N("ORDERTIME")],
				paymentInfoHashMap[prefix + _N("CURRENCYCODE")],
				DSCurrency(paymentInfoHashMap[prefix + _N("AMT")]),
				DSCurrency(paymentInfoHashMap[prefix + _N("TAXAMT")]),
				DSCurrency(paymentInfoHashMap[prefix + _N("FEEAMT")])
			);
		} else {
			found = false;
		}
	}

	return result;
}

wxString DynSoft::DSPayPalPaymentInfos::ToString() {
	wxString result;

	result += _N("Success page redirect requested: ") + DynSoft::DSCasts::ToString(GetSuccessPageRedirectRequested()) + _N("\n");
	result += _N("     Shipping option is default: ") + DynSoft::DSCasts::ToString(GetShippingOptionIsDefault()) + _N("\n");
	result += _N("     Insureance option selected: ") + DynSoft::DSCasts::ToString(GetInsuranceOptionSelected()) + _N("\n");

	const unsigned int count = GetPaymentInfoCount();
	for(unsigned int i = 0; i < count; i++) {
		result += GetPaymentInfo(i)->ToString();
		if(i + 1 < count)
			result += _N("\n");
	}

	return result;
}
