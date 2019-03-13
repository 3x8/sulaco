#pragma once

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#ifdef UNIT_TEST
// make these visible to unit test
#define STATIC_UNIT_TESTED
#define STATIC_INLINE_UNIT_TESTED
#define INLINE_UNIT_TESTED
#define UNIT_TESTED
#else
#define STATIC_UNIT_TESTED static
#define STATIC_INLINE_UNIT_TESTED static inline
#define INLINE_UNIT_TESTED inline
#define UNIT_TESTED
#endif

//#define SOFT_I2C // enable to test software i2c

#ifndef __CC_ARM
#define REQUIRE_CC_ARM_PRINTF_SUPPORT
#define REQUIRE_PRINTF_LONG_SUPPORT
#endif
