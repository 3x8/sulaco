#include "pg/pg_ids.h"
#include "pg/rcdevice.h"

PG_REGISTER_WITH_RESET_FN(rcdeviceConfig_t, rcdeviceConfig, PG_RCDEVICE_CONFIG, 0);

void pgResetFn_rcdeviceConfig(rcdeviceConfig_t *rcdeviceConfig)
{
    rcdeviceConfig->initDeviceAttempts = 6;
    rcdeviceConfig->initDeviceAttemptInterval = 1000;
}
