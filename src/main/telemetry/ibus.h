#pragma once

void initIbusTelemetry(void);

void handleIbusTelemetry(void);
bool checkIbusTelemetryState(void);

void configureIbusTelemetryPort(void);
void freeIbusTelemetryPort(void);
