#ifndef DS_PAYPAL_PAYMENT_INFO_H_
#define DS_PAYPAL_PAYMENT_INFO_H_

#define DS_PAYPAL_PAYMENT_INFO_VERSION _N("0.0.1")
#define DS_PAYPAL_PAYMENT_INFO_NAME    _N("DSPayPalPaymentInfo")
#define DS_PAYPAL_PAYMENT_INFO_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSCurrency.h"

namespace DynSoft {

	class DSPayPalPaymentInfo : public DSType {

		public:
			DSPayPalPaymentInfo();
			DSPayPalPaymentInfo(
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
			~DSPayPalPaymentInfo();

			DSClassInfo GetClassInfo();

			void SetAck(const bool ack);
			bool GetAck() const;

			void SetErrorCode(const int errorCode);
			int GetErrorCode() const;

			void SetProtectionEligibility(const wxString &protectionEligibility);
			wxString GetProtectionEligibility() const;

			void SetProtectionEligibilityType(const wxString &protectionEligibilityType);
			wxString GetProtectionEligibilityType() const;

			void SetTransactionType(const wxString &transactionType);
			wxString GetTransactionType() const;

			void SetTransactionId(const wxString &transactionId);
			wxString GetTransactionId() const;

			void SetSecureMerchantAccountId(const wxString &secureMerchantAccountId);
			wxString GetSecureMerchantAccountId() const;

			void SetPaymentStatus(const wxString &paymentStatus);
			wxString GetPaymentStatus() const;

			void SetPaymentType(const wxString &paymentType);
			wxString GetPaymentType() const;

			void SetReasonCode(const wxString &reasonCode);
			wxString GetReasonCode() const;

			void SetPendingReason(const wxString &pendingReason);
			wxString GetPendingReason() const;

			void SetOrderTime(const wxString &orderTime);
			wxString GetOrderTime() const;

			void SetCurrencyCode(const wxString &currencyCode);
			wxString GetCurrencyCode() const;

			void SetAmt(const DSCurrency amt);
			DSCurrency GetAmt() const;

			void SetTaxAmt(const DSCurrency taxAmt);
			DSCurrency GetTaxAmt() const;

			void SetFeeAmt(const DSCurrency feeAmt);
			DSCurrency GetFeeAmt() const;

			wxString ToString();

		protected:
			bool ack;
			int errorCode;
			wxString protectionEligibilityType;
			wxString protectionEligibility;
			wxString transactionType;
			wxString transactionId;
			wxString secureMerchantAccountId;
			wxString paymentStatus;
			wxString paymentType;
			wxString reasonCode;
			wxString pendingReason;
			wxString orderTime;
			wxString currencyCode;
			DSCurrency amt;
			DSCurrency taxAmt;
			DSCurrency feeAmt;

	};

}

#endif /* DS_PAYPAL_PAYMENT_INFO_H_ */
