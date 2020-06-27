#pragma once

#define NOINLINE __attribute__((noinline))

#if !defined(UNIT_TEST) && !defined(SIMULATOR_BUILD) && !(USBD_DEBUG_LEVEL > 0)
  #pragma GCC poison sprintf snprintf
#endif

#if defined(STM32F745xx) || defined(STM32F746xx) || defined(STM32F722xx)
  #ifndef STM32F7
    #define STM32F7
  #endif

  #include "stm32f7xx.h"
  #include "stm32f7xx_hal.h"
  #include "system_stm32f7xx.h"

  #include "stm32f7xx_ll_spi.h"
  #include "stm32f7xx_ll_gpio.h"
  #include "stm32f7xx_ll_dma.h"
  #include "stm32f7xx_ll_rcc.h"
  #include "stm32f7xx_ll_bus.h"
  #include "stm32f7xx_ll_tim.h"
  #include "stm32f7xx_ll_system.h"
  #include "drivers/stm32f7xx_ll_ex.h"

  // Chip Unique ID on F7
  #if defined(STM32F722xx)
    #define U_ID_0 (*(uint32_t*)0x1ff07a10)
    #define U_ID_1 (*(uint32_t*)0x1ff07a14)
    #define U_ID_2 (*(uint32_t*)0x1ff07a18)
  #else
    #define U_ID_0 (*(uint32_t*)0x1ff0f420)
    #define U_ID_1 (*(uint32_t*)0x1ff0f424)
    #define U_ID_2 (*(uint32_t*)0x1ff0f428)
  #endif
#elif defined(STM32F40_41xxx) || defined (STM32F411xE) || defined (STM32F446xx)
  #ifndef STM32F4
    #define STM32F4
  #endif

  #include "stm32f4xx.h"

  // Chip Unique ID on F405
  #define U_ID_0 (*(uint32_t*)0x1fff7a10)
  #define U_ID_1 (*(uint32_t*)0x1fff7a14)
  #define U_ID_2 (*(uint32_t*)0x1fff7a18)
#elif defined(STM32F303xC)
  #ifndef STM32F3
    #define STM32F3
  #endif

  #include "stm32f30x_conf.h"
  #include "stm32f30x_rcc.h"
  #include "stm32f30x_gpio.h"
  #include "core_cm4.h"

  // Chip Unique ID on F303
  #define U_ID_0 (*(uint32_t*)0x1FFFF7AC)
  #define U_ID_1 (*(uint32_t*)0x1FFFF7B0)
  #define U_ID_2 (*(uint32_t*)0x1FFFF7B4)
#elif defined(STM32F10X)
  #ifndef STM32F1
    #define STM32F1
  #endif

  #include "stm32f10x_conf.h"
  #include "stm32f10x_gpio.h"
  #include "core_cm3.h"

  // Chip Unique ID on F103
  #define U_ID_0 (*(uint32_t*)0x1FFFF7E8)
  #define U_ID_1 (*(uint32_t*)0x1FFFF7EC)
  #define U_ID_2 (*(uint32_t*)0x1FFFF7F0)
#elif defined(SIMULATOR_BUILD)
  // Nop
#else // STM32F10X
  #error "Invalid chipset specified. Update platform.h"
#endif

#include "target/common_fc_pre.h"
#include "target.h"
#include "target/common_fc_post.h"
#include "target/common_defaults_post.h"
