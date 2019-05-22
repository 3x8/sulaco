#include "version.h"

const char * const targetName = __TARGET__;
const char * const shortGitRevision = __REVISION__;
const char * const buildDate = __DATE__;
const char * const buildTime = __TIME__;

#ifdef STM32F1
#warning STM32F1 based targets are unsupported
#endif
