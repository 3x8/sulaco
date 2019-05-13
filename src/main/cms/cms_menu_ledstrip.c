#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "platform.h"

#ifdef USE_CMS

#include "build/version.h"

#include "cms/cms.h"
#include "cms/cms_types.h"
#include "cms/cms_menu_ledstrip.h"

#include "config/feature.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "fc/config.h"


#ifdef USE_LED_STRIP

static bool featureRead = false;
static uint8_t cmsx_FeatureLedstrip;

static long cmsx_Ledstrip_FeatureRead(void)
{
    if (!featureRead) {
        cmsx_FeatureLedstrip = feature(FEATURE_LED_STRIP) ? 1 : 0;
        featureRead = true;
    }

    return 0;
}

static long cmsx_Ledstrip_FeatureWriteback(const OSD_Entry *self)
{
    UNUSED(self);
    if (featureRead) {
        if (cmsx_FeatureLedstrip)
            featureSet(FEATURE_LED_STRIP);
        else
            featureClear(FEATURE_LED_STRIP);
    }

    return 0;
}

static OSD_Entry cmsx_menuLedstripEntries[] =
{
    { "-- LED STRIP --", OME_Label, NULL, NULL, 0 },
    { "ENABLED",         OME_Bool,  NULL, &cmsx_FeatureLedstrip, 0 },

    { "BACK", OME_Back, NULL, NULL, 0 },
    { NULL, OME_END, NULL, NULL, 0 }
};

CMS_Menu cmsx_menuLedstrip = {
#ifdef CMS_MENU_DEBUG
    .GUARD_text = "MENULED",
    .GUARD_type = OME_MENU,
#endif
    .onEnter = cmsx_Ledstrip_FeatureRead,
    .onExit = cmsx_Ledstrip_FeatureWriteback,
    .entries = cmsx_menuLedstripEntries
};
#endif // LED_STRIP
#endif // CMS
