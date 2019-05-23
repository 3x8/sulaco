typedef struct dashboardConfig_s {
    I2CDevice device;
    uint8_t   address;
} dashboardConfig_t;

PG_DECLARE(dashboardConfig_t, dashboardConfig);
