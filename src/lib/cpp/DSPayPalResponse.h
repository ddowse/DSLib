#ifndef DS_PAYPAL_RESPONSE_H_
#define DS_PAYPAL_RESPONSE_H_

#define DS_PAYPAL_RESPONSE_VERSION _N("0.0.1")
#define DS_PAYPAL_RESPONSE_NAME    _N("DSPayPalResponse")
#define DS_PAYPAL_RESPONSE_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSType.h"
#include "DSStringHashMap.h"
#include "DSDateTime.h"
#include "DSPayPalErrors.h"
#include "DSPayPalPaymentInfos.h"

namespace DynSoft {

	class DSPayPalResponse : public DSType {

		public:
			DSPayPalResponse();
			DSPayPalResponse(
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
			);
			~DSPayPalResponse();

			DSClassInfo GetClassInfo();

			void Set(
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
			);

			void SetBuild(const wxString &build);
			wxString GetBuild() const;

			void SetContentType(const wxString &contentType);
			wxString GetContentType() const;

			void SetVersion(const wxString &version);
			wxString GetVersion() const;

			void SetRealTimeStamp(const wxString &timeStamp);
			wxString GetRealTimeStamp() const;
			DSDateTime GetTimeStamp() const;

			void SetCorrelationId(const wxString &correlationId);
			wxString GetCorrelationId() const;

			void SetContentLength(const unsigned int contentLength);
			unsigned int GetContentLength() const;

			void SetConnection(const wxString &connection);
			wxString GetConnection() const;

			void SetServer(const wxString &server);
			wxString GetServer() const;

			void SetAck(const bool ack);
			bool GetAck() const;

			void SetCookie(const wxString &cookie);
			wxString GetCookie() const;

			DSPayPalErrors *GetErrors();
			bool HasErrors() const;
			DSPayPalPaymentInfos *GetPaymentInfos();
			bool HasPaymentInfos() const;

			void ParseResponseHashMap(DSStringHashMap &responseHashMap);

			wxString ToString();

		protected:
			wxString build;
			wxString contentType;
			wxString version;
			wxString timeStamp;
			wxString correlationId;
			unsigned long contentLength;
			wxString connection;
			wxString server;
			bool ack;
			wxString cookie;
			DSPayPalErrors errors;
			DSPayPalPaymentInfos paymentInfos;

	};

}

#endif /* DS_PAYPAL_RESPONSE_H_ */
