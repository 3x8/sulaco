#pragma once

#include "pg/pg.h"
#include "io/serial.h"
#include "telemetry/ibus_shared.h"

typedef enum {
  FRSKY_FORMAT_DMS = 0,
  FRSKY_FORMAT_NMEA
} frskyGpsCoordFormat_e;

typedef enum {
  FRSKY_UNIT_METRICS = 0,
  FRSKY_UNIT_IMPERIALS
} frskyUnit_e;

typedef struct telemetryConfig_s {
  int16_t gpsNoFixLatitude;
  int16_t gpsNoFixLongitude;
  uint8_t telemetry_inverted;
  uint8_t halfDuplex;
  frskyGpsCoordFormat_e frsky_coordinate_format;
  frskyUnit_e frsky_unit;
  uint8_t frsky_vfas_precision;
  uint8_t hottAlarmSoundInterval;
  uint8_t pidValuesAsTelemetry;
  uint8_t report_cell_voltage;
  uint8_t flysky_sensors[IBUS_SENSOR_COUNT];
  uint8_t smartport_use_extra_sensors;
} telemetryConfig_t;

PG_DECLARE(telemetryConfig_t, telemetryConfig);

extern serialPort_t *telemetrySharedPort;

void telemetryInit(void);
bool telemetryCheckRxPortShared(const serialPortConfig_t *portConfig);

void telemetryCheckState(void);
void telemetryProcess(uint32_t currentTime);

bool telemetryDetermineEnabledState(portSharing_e portSharing);
