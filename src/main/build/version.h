#pragma once

#include "common/utils.h"

#define FC_FIRMWARE_NAME            "ButterFlight"
#define FC_VERSION_MAJOR            4  // increment when a major release is made (big new feature, etc)
#define FC_VERSION_MINOR            0  // increment when a minor release is made (small new feature, change etc)
#define FC_VERSION_PATCH_LEVEL      1  // increment when a bug is fixed


#define FC_VERSION_STRING STR(FC_VERSION_MAJOR) "." STR(FC_VERSION_MINOR) "." STR(FC_VERSION_PATCH_LEVEL)

extern const char* const targetName;

#define GIT_SHORT_REVISION_LENGTH   7 // lower case hexadecimal digits.
extern const char* const shortGitRevision;

#define BUILD_DATE_LENGTH 11
extern const char* const buildDate;  // "MMM DD YYYY" MMM = Jan/Feb/...

#define BUILD_TIME_LENGTH 8
extern const char* const buildTime;  // "HH:MM:SS"

#define MSP_API_VERSION_STRING STR(API_VERSION_MAJOR) "." STR(API_VERSION_MINOR)
