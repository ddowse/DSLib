#include "DSPayPalRequest.h"
#include "DSCgi.h"
#include "DSCasts.h"
#include "DSSSLSocket.h"
#include <wx/uri.h>
#include "DSPayPalResponse.h"

DynSoft::DSPayPalRequest::DSPayPalRequest() : DSLib(
) {
}

DynSoft::DSPayPalRequest::~DSPayPalRequest() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalRequest::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_REQUEST_NAME,
        DS_PAYPAL_REQUEST_VERSION,
        DS_PAYPAL_REQUEST_AUTHOR
    );
}

DynSoft::DSPayPalResponse *DynSoft::DSPayPalRequest::Request(
	DSPayPalConnectionType &connection,
	DSPayPalMethod &method,
	DSPayPalToken &token,
	DSPayPalCarts &carts
) {
	if(!method.IsOk())
		return NULL;

	wxString cartsString;
	wxString tokenString;
	switch(method.GetMethod()) {
		case DSPayPalMethod::SETEXPRESSCHECKOUT:
			cartsString = carts.ToSetExpressCheckout();
			break;
		case DSPayPalMethod::DOEXPRESSCHECKOUTPAYMENT:
			cartsString = carts.ToDoExpressCheckoutPayment();
			tokenString = _N("&") + token.ToUrlString();
			break;
	}

	const wxString request(
		connection.ToCallableString() + _N("&") +
		method.ToUrlString() + _N("&") +
		cartsString +
		tokenString
	);

	DSStringHashMap tmp = Request(connection, request);
	DSPayPalResponse *response = new DSPayPalResponse;
	response->ParseResponseHashMap(tmp);

	if(method.GetMethod() == DSPayPalMethod::SETEXPRESSCHECKOUT)
		token.ParseTokenHashMap(tmp);

	return response;
}

DSStringHashMap DynSoft::DSPayPalRequest::Request(
	DSPayPalConnectionType &connection,
	const wxString &request
) {
	DSStringHashMap headers;

	DSSSLSocket client;
	client.SetAddress(connection.GetHostname(), connection.GetPort());
	client.SetTimeout(connection.GetTimeout());

	if(client.Connect()) {
		const wxString realRequest(
			_N("GET ") + request + _N(" HTTP/1.1\r\n") +
			_N("Host: ") + connection.GetHostname() + _N("\r\n\r\n")
		);

		client.Send(realRequest);

		char buffer [BUFFER_SIZE];
		size_t buffer_counter    = 0;
		const size_t buffer_size = sizeof(buffer);
		const size_t char_size   = sizeof(char);
		char *content            = NULL;
		size_t content_size      = 0;
		char c                   = 0;
		size_t newlines          = 0;
		bool run                 = true;

		while(run) {
			if(buffer_counter == buffer_size || newlines == 4) {
				content               = (char *) realloc(content, (buffer_size * char_size) + (content_size * char_size) + char_size);
				content[content_size] = '\0';
				strncat(content, buffer, buffer_counter);
				content_size          = strlen(content);
				buffer_counter        = 0;

				if(newlines == 4)
					break;
			}

			run = client.Receive(&c, 1) > 0;
			buffer[buffer_counter++] = c;
			
			switch(c) {
				case '\r':
				case '\n':
					newlines++;
					break;
				default:
					newlines = 0;
					break;
			}
		}

		wxString header(DSCasts::ToString(content));
		free(content);

		header.Replace(_N("\r\n"), _N("\n"));
		header.Replace(_N("\r"),   _N("\n"));

		wxArrayString fields;
		wxArrayString lines(DSLib::Split(header, '\n'));
		unsigned int count = lines.GetCount();
		for(unsigned int i = 0; i < count; i++) {
			fields = DSLib::Split(lines[i], ':');
			if(fields.GetCount() == 2)
				headers[fields[0]] = fields[1].Trim(false).Trim();
		}


		content_size = DSCasts::ToUnsignedInt(headers[_N("Content-Length")]);
		content      = (char *) calloc(content_size + 1, char_size);

		client.Receive(content, content_size);
		client.Disconnect();

		lines = DSLib::Split(DSCasts::ToString(content), '&');
		free(content);

		count = lines.GetCount();
		for(unsigned int i = 0; i < count; i++) {
			fields = DSLib::Split(lines[i], '=');
			if(fields.GetCount() == 2)
				headers[fields[0]] = DSCgi::Hex2Ascii(fields[1]);
		}
	}

	return headers;
}
