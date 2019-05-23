#pragma once

extern uint8_t cliMode;
extern int cliSmartMode;

struct clivalue_s;
void *cliGetValuePointer(const struct clivalue_s *value);
const void *cliGetDefaultPointer(const struct clivalue_s *value);

struct serialConfig_s;
void cliInit(const struct serialConfig_s *serialConfig);
void cliProcess(void);
struct serialPort_s;
void cliEnter(struct serialPort_s *serialPort);
