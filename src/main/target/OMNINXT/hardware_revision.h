#pragma once

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);
ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);
