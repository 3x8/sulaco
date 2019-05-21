#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "config/feature.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"


static uint32_t activeFeaturesLatch = 0;

PG_REGISTER_WITH_RESET_TEMPLATE(featureConfig_t, featureConfig, PG_FEATURE_CONFIG, 0);

PG_RESET_TEMPLATE(featureConfig_t, featureConfig,
    .enabledFeatures = DEFAULT_FEATURES | DEFAULT_RX_FEATURE | FEATURE_DYNAMIC_FILTER | FEATURE_ANTI_GRAVITY,
);

void intFeatureSet(uint32_t mask, uint32_t *features)
{
    *features |= mask;
}

void intFeatureClear(uint32_t mask, uint32_t *features)
{
    *features &= ~(mask);
}

void intFeatureClearAll(uint32_t *features)
{
    *features = 0;
}

void latchActiveFeatures(void)
{
    activeFeaturesLatch = featureConfig()->enabledFeatures;
}

bool featureConfigured(uint32_t mask)
{
    return featureConfig()->enabledFeatures & mask;
}

bool feature(uint32_t mask)
{
    return activeFeaturesLatch & mask;
}

void featureSet(uint32_t mask)
{
    intFeatureSet(mask, &featureConfigMutable()->enabledFeatures);
}

void featureClear(uint32_t mask)
{
    intFeatureClear(mask, &featureConfigMutable()->enabledFeatures);
}

void featureClearAll(void)
{
    intFeatureClearAll(&featureConfigMutable()->enabledFeatures);
}

uint32_t featureMask(void)
{
    return featureConfig()->enabledFeatures;
}
