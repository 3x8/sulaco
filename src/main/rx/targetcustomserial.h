#pragma once

// Function to be implemented on a per-target basis under src/main/target/<TARGET>/serialrx.c
bool targetCustomSerialRxInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig);
