#include "config_helper.h"

#ifdef USE_TARGET_CONFIG

void targetSerialPortFunctionConfig(targetSerialPortFunction_t *config, size_t count)
{
    for (size_t i = 0 ; i < count ; i++) {
        int index = findSerialPortIndexByIdentifier(config[i].identifier);
        if (index >= 0) {
            serialConfigMutable()->portConfigs[index].functionMask = config[i].function;
        }
    }
}
#endif
