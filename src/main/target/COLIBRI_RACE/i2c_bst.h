#pragma once

void bstProcessInCommand(void);
void bstSlaveProcessInCommand(void);
void taskBstMasterProcess(timeUs_t currentTimeUs);

bool writeGpsPositionPrameToBST(void);
bool writeRollPitchYawToBST(void);
bool writeRCChannelToBST(void);
bool writeFCModeToBST(void);
