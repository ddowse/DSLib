#ifndef DS_PAYPAL_POSTGRESQL_PERSIST_H_
#define DS_PAYPAL_POSTGRESQL_PERSIST_H_

#define DS_PAYPAL_POSTGRESQL_PERSIST_VERSION _N("0.0.1")
#define DS_PAYPAL_POSTGRESQL_PERSIST_NAME    _N("DSPayPalPostgreSQLPersist")
#define DS_PAYPAL_POSTGRESQL_PERSIST_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

#include "DSPostgreSQLDatabase.h"
#include "DSPayPalPersist.h"
#include "DSPayPalToken.h"
#include "DSPayPalCarts.h"

namespace DynSoft {

	class DSPayPalPostgreSQLPersist : public DSPayPalPersist {

		public:
			DSPayPalPostgreSQLPersist(DSPostgreSQLDatabase *db);
			~DSPayPalPostgreSQLPersist();

			DSClassInfo GetClassInfo();

			void SetDatabase(DSPostgreSQLDatabase *db);
			DSPostgreSQLDatabase *GetDatabase() const;

			virtual bool Persist(DSPayPalToken &token, DSPayPalCarts &carts, const wxString &transactionId);
			virtual bool Restore(DSPayPalToken &token, DSPayPalCarts &carts, wxString *transactionId);
			virtual bool Remove(DSPayPalToken &token);

		protected:
			DSPostgreSQLDatabase *db;

	};

}

#endif /* DS_PAYPAL_POSTGRESQL_PERSIST_H_ */
