#include "DSPayPalPersist.h"

DynSoft::DSPayPalPersist::DSPayPalPersist(
) : DSLib(
) {
}

DynSoft::DSPayPalPersist::~DSPayPalPersist() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalPersist::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_PERSIST_NAME,
        DS_PAYPAL_PERSIST_VERSION,
        DS_PAYPAL_PERSIST_AUTHOR
    );
}
