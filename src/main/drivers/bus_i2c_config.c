#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#if defined(USE_I2C) && !defined(SOFT_I2C)
  #include "build/build_config.h"
  #include "build/debug.h"
  #include "drivers/bus_i2c.h"
  #include "drivers/bus_i2c_impl.h"
  #include "drivers/io.h"
  #include "pg/bus_i2c.h"

  // Backward compatibility for overclocking and internal pullup.
  // These will eventually be configurable through PG-based configurator
  // (and/or probably through some cli extension).
  #ifndef I2C1_OVERCLOCK
    #define I2C1_OVERCLOCK false
  #endif
  #ifndef I2C2_OVERCLOCK
    #define I2C2_OVERCLOCK false
  #endif
  #ifndef I2C3_OVERCLOCK
    #define I2C3_OVERCLOCK false
  #endif
  #ifndef I2C4_OVERCLOCK
    #define I2C4_OVERCLOCK false
  #endif

  void i2cHardwareConfigure(const i2cConfig_t *i2cConfig) {
    for (int index = 0 ; index < I2CDEV_COUNT ; index++) {
      const i2cHardware_t *hardware = &i2cHardware[index];

      if (!hardware->reg) {
        continue;
      }
      I2CDevice device = hardware->device;
      i2cDevice_t *pDev = &i2cDevice[device];
      memset(pDev, 0, sizeof(*pDev));

      for (int pindex = 0 ; pindex < I2C_PIN_SEL_MAX ; pindex++) {
        if (i2cConfig[device].ioTagScl == hardware->sclPins[pindex].ioTag) {
          pDev->scl = IOGetByTag(i2cConfig[device].ioTagScl);
          #if defined(STM32F4)
            pDev->sclAF = hardware->sclPins[pindex].af;
          #endif
        }
        if (i2cConfig[device].ioTagSda == hardware->sdaPins[pindex].ioTag) {
          pDev->sda = IOGetByTag(i2cConfig[device].ioTagSda);
          #if defined(STM32F4)
            pDev->sdaAF = hardware->sdaPins[pindex].af;
          #endif
        }
      }

      if (pDev->scl && pDev->sda) {
        pDev->hardware = hardware;
        pDev->reg = hardware->reg;
        pDev->overClock = i2cConfig[device].overClock;
        pDev->pullUp = i2cConfig[device].pullUp;
      }
    }
  }

#endif //defined(USE_I2C) && !defined(USE_SOFT_I2C)
