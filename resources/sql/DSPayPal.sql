CREATE TABLE paypal_carts (
	"token" VARCHAR(255),
	"transactionId" VARCHAR(255),
	"payerId" VARCHAR(255),
	"created" TIMESTAMP DEFAULT NOW(),
	"changed" TIMESTAMP DEFAULT NOW(),
	PRIMARY KEY ("token")
);

CREATE TABLE paypal_cart (
	"id" SERIAL,
	"token" VARCHAR(255),
	"shippingPrice" FLOAT8,
	"currencyCode" CHAR(3),
	"sellerPayPalAccountId" VARCHAR(255),
	"paymentRequestId" VARCHAR(255),
	PRIMARY KEY ("id"),
	FOREIGN KEY ("token") REFERENCES paypal_carts ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE paypal_cart_item (
	"id" SERIAL,
	"cart" INTEGER,
	"name" VARCHAR(255),
	"description" TEXT,
	"price" FLOAT8,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("cart") REFERENCES paypal_cart ON UPDATE CASCADE ON DELETE CASCADE
);
