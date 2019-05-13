#pragma once

struct rxConfig_s;
struct rxRuntimeConfig_s;
void rxMspInit(const struct rxConfig_s *rxConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void rxMspFrameReceive(uint16_t *frame, int channelCount);
