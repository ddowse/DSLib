#include "DSPayPalPostgreSQLPersist.h"
#include "DSPostgreSQLQuery.h"

DynSoft::DSPayPalPostgreSQLPersist::DSPayPalPostgreSQLPersist(
	DSPostgreSQLDatabase *db
) : DSPayPalPersist(
) {
	SetDatabase(db);
}

DynSoft::DSPayPalPostgreSQLPersist::~DSPayPalPostgreSQLPersist() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalPostgreSQLPersist::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_POSTGRESQL_PERSIST_NAME,
        DS_PAYPAL_POSTGRESQL_PERSIST_VERSION,
        DS_PAYPAL_POSTGRESQL_PERSIST_AUTHOR
    );
}

void DynSoft::DSPayPalPostgreSQLPersist::SetDatabase(DynSoft::DSPostgreSQLDatabase *db) {
	this->db = db;
}

DynSoft::DSPostgreSQLDatabase *DynSoft::DSPayPalPostgreSQLPersist::GetDatabase() const {
	return db;
}

bool DynSoft::DSPayPalPostgreSQLPersist::Persist(
	DynSoft::DSPayPalToken &token,
	DynSoft::DSPayPalCarts &carts,
	const wxString &transactionId
) {
	bool run = true;
	DSPostgreSQLQuery query(GetDatabase());

	query.Begin();

	query.Prepare(_N(
		"INSERT INTO paypal_carts ("
		"	\"token\", "
		"	\"payerId\", "
		"	\"transactionId\""
		") VALUES ("
		"	:token:, "
		"	:payerId:, "
		"	:transactionId:"
		")"
	));
	query.Bind(_N("token"), token.GetToken());
	query.Bind(_N("payerId"), token.GetPayerId());
	query.Bind(_N("transactionId"), transactionId);

	if(query.Exec(false)) {
		unsigned int id               = 0;
		unsigned int cartItemCount    = 0;
		DSPayPalCartItem *cartItem    = NULL;
		DSPayPalCart *cart            = NULL;		
		const unsigned int cartsCount = carts.GetCartCount();
		for(unsigned int i = 0; i < cartsCount && run; i++) {
			cart = carts.GetCart(i);
			if(cart) {
				query.Prepare(_N(
					"INSERT INTO paypal_cart ("
					"	\"token\", "
					"	\"shippingPrice\", "
					"	\"currencyCode\", "
					"	\"sellerPayPalAccountId\", "
					"	\"paymentRequestId\""
					") VALUES ("
					"	:token:, "
					"	:shippingPrice:, "
					"	:currencyCode:, "
					"	:sellerPayPalAccountId:, "
					"	:paymentRequestId:"
					")"
				));
				query.Bind(_N("token"), token.GetToken());
				query.Bind(_N("shippingPrice"), cart->GetShippingPrice());
				query.Bind(_N("currencyCode"), cart->GetCurrencyCode());
				query.Bind(_N("sellerPayPalAccountId"), cart->GetSellerPayPalAccountId());
				query.Bind(_N("paymentRequestId"), cart->GetPaymentRequestId());

				if(query.Exec(false)) {
					query.Query(_N("SELECT CURRVAL('paypal_cart_id_seq') AS id"));
					if(query.NextRecord()) {
						id  = query.GetField(_N("id")).ToUnsignedInt();
						run = id > 0;
					}
					query.FreeResult();

					if(run) {
						cartItemCount = cart->GetCartItemCount();
						for(unsigned int j = 0; j < cartItemCount && run; j++) {
							cartItem = cart->GetCartItem(j);
							if(cartItem) {
								query.Prepare(_N(
									"INSERT INTO paypal_cart_item ("
									"	\"cart\", "
									"	\"name\", "
									"	\"description\", "
									"	\"price\""
									") VALUES ("
									"	:cart:, "
									"	:name:, "
									"	:description:, "
									"	:price:"
									")"
								));
								query.Bind(_N("cart"), id);
								query.Bind(_N("name"), cartItem->GetName());
								query.Bind(_N("description"), cartItem->GetDescription());
								query.Bind(_N("price"), cartItem->GetPrice());

								if(!query.Exec(false))
									run = false;
							}
						}
					}
				}
			}
		}
	} else {
		run = false;
	}

	if(!run || !query.Commit()) {
		query.Rollback();
		return false;
	}

	return true;
}

bool DynSoft::DSPayPalPostgreSQLPersist::Restore(
	DynSoft::DSPayPalToken &token,
	DynSoft::DSPayPalCarts &carts,
	wxString *transactionId
) {
	bool ok = false;

	DSPostgreSQLQuery query(GetDatabase());
	query.Prepare(_N("SELECT * FROM paypal_carts WHERE token = :token:"));
	query.Bind(_N("token"), token.GetToken());
	query.Exec();
	if(query.NextRecord()) {
		token.SetToken(query.GetField(_N("token")).ToString());
		token.SetPayerId(query.GetField(_N("payerId")).ToString());

		if(transactionId)
			*transactionId = query.GetField(_N("transactionId")).ToString();

		ok = true;
	}
	query.FreeResult();

	if(ok) {
		DSPostgreSQLQuery query2(GetDatabase());
		DSPayPalCart *cart = NULL;
		query.Prepare(_N("SELECT * FROM paypal_cart WHERE token = :token:"));
		query.Bind(_N("token"), token.GetToken());
		query.Exec();
		while(query.NextRecord()) {
			cart = new DSPayPalCart(
				query.GetField(_N("shippingPrice")).ToCurrency(),
				query.GetField(_N("currencyCode")).ToString(),
				query.GetField(_N("sellerPayPalAccountId")).ToString(),
				query.GetField(_N("paymentRequestId")).ToString()
			);

			query2.Prepare(_N("SELECT * FROM paypal_cart_item WHERE cart = :cart:"));
			query2.Bind(_N("cart"), query.GetField(_N("id")).ToUnsignedInt());
			query2.Exec();
			while(query2.NextRecord()) {
				cart->AddCartItem(
					query2.GetField(_N("name")).ToString(),
					query2.GetField(_N("description")).ToString(),
					query2.GetField(_N("price")).ToCurrency()
				);
			}
			query2.FreeResult();

			carts.AddCart(cart);
		}
		query.FreeResult();
	}

	return ok;
}

bool DynSoft::DSPayPalPostgreSQLPersist::Remove(
	DynSoft::DSPayPalToken &token
) {
	DSPostgreSQLQuery query(GetDatabase());
	query.Prepare(_N("DELETE FROM paypal_carts WHERE token = :token:"));
	query.Bind(_N("token"), token.GetToken());
	return query.Exec(false);
}
