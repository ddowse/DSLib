#include "DSPayPalLog.h"

DynSoft::DSPayPalLog::DSPayPalLog() : DSLib(
) {
}

DynSoft::DSPayPalLog::~DSPayPalLog() {
}

DynSoft::DSClassInfo DynSoft::DSPayPalLog::GetClassInfo() {
    return DSClassInfo(
        DS_PAYPAL_LOG_NAME,
        DS_PAYPAL_LOG_VERSION,
        DS_PAYPAL_LOG_AUTHOR
    );
}
