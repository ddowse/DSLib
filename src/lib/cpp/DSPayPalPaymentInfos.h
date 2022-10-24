#ifndef DS_PAYPAL_PAYMENT_INFOS_H_
#define DS_PAYPAL_PAYMENT_INFOS_H_

#define DS_PAYPAL_PAYMENT_INFOS_VERSION _N("0.0.1")
#define DS_PAYPAL_PAYMENT_INFOS_NAME    _N("DSPayPalPaymentInfos")
#define DS_PAYPAL_PAYMENT_INFOS_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSTemplateContainer.h"
#include "DSPayPalPaymentInfo.h"

namespace DynSoft {

	class DSPayPalPaymentInfos : public DSType {

		public:
			DSPayPalPaymentInfos();
			DSPayPalPaymentInfos(
				const bool successPageRedirectRequested,
				const bool shippingOptionIsDefault,
				const bool insuranceOptionSelected
			);
			~DSPayPalPaymentInfos();

			DSClassInfo GetClassInfo();

			void SetSuccessPageRedirectRequested(const bool successPageRedirectRequested);
			bool GetSuccessPageRedirectRequested() const;
			
			void SetShippingOptionIsDefault(const bool shippingOptionIsDefault);
			bool GetShippingOptionIsDefault() const;

			void SetInsuranceOptionSelected(const bool insuranceOptionSelected);
			bool GetInsuranceOptionSelected() const;

			DSPayPalPaymentInfo *AddPaymentInfo(
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
			);
			void AddPaymentInfo(DSPayPalPaymentInfo *paymentInfo);
			unsigned int GetPaymentInfoCount() const;
			DSPayPalPaymentInfo *GetPaymentInfo(const unsigned int number);
			bool HasPaymentInfos() const;
			void CleanPaymentInfos();

			unsigned int ParsePaymentInfoHashMap(DSStringHashMap &paymentInfoHashMap);

			wxString ToString();

		protected:
			bool successPageRedirectRequested;
			bool shippingOptionIsDefault;
			bool insuranceOptionSelected;

			DSTemplateContainer<DSPayPalPaymentInfo *> paymentInfos;

	};

}

#endif /* DS_PAYPAL_PAYMENT_INFOS_H_ */
