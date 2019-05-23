#pragma once

#ifdef USE_BRUSHED_ESC_AUTODETECT
typedef enum {
    MOTOR_UNKNOWN = 0,
    MOTOR_BRUSHED,
    MOTOR_BRUSHLESS
} HardwareMotorTypes_e;

extern uint8_t hardwareMotorType;

void detectBrushedESC(void);
#endif
