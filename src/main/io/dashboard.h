#pragma once

#include "common/time.h"
#include "pg/pg.h"
#include "drivers/bus_i2c.h"

#define ENABLE_DEBUG_DASHBOARD_PAGE

#if !defined(DASHBOARD_I2C_INSTANCE)
#if defined(I2C_DEVICE)
#define DASHBOARD_I2C_INSTANCE I2C_DEVICE
#else
#define DASHBOARD_I2C_INSTANCE I2C_NONE
#endif
#endif

#define DASHBOARD_I2C_ADDRESS   0x3C     // OLED at address 0x3C in 7bit

typedef enum {
    PAGE_WELCOME,
    PAGE_ARMED,
    PAGE_BATTERY,
    PAGE_SENSORS,
    PAGE_RX,
    PAGE_PROFILE,
    PAGE_RPROF,
#ifndef SKIP_TASK_STATISTICS
    PAGE_TASKS,
#endif
#ifdef USE_GPS
    PAGE_GPS,
#endif
#ifdef ENABLE_DEBUG_DASHBOARD_PAGE
    PAGE_DEBUG,
#endif

    PAGE_COUNT
} pageId_e;

void dashboardInit(void);
void dashboardUpdate(timeUs_t currentTimeUs);

void dashboardShowFixedPage(pageId_e pageId);

void dashboardEnablePageCycling(void);
void dashboardDisablePageCycling(void);
void dashboardResetPageCycling(void);
void dashboardSetNextPageChangeAt(timeUs_t futureMicros);
