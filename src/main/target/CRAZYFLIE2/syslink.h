#pragma once

/*
 * This file contains definitions for the syslink protocol, a UART-based
 * protocol for communication between the NRF51 MCU and the STM32 MCU on
 * the Crazyflie flight controller board.
 *
 * For more details, see https://wiki.bitcraze.io/doc:crazyflie:syslink:index
 */

#define SYSLINK_MTU 32

#define SYSLINK_START_BYTE1 0xBC
#define SYSLINK_START_BYTE2 0xCF

#define SYSLINK_RADIO_GROUP         0x00
#define SYSLINK_RADIO_RAW           0x00
#define SYSLINK_RADIO_CHANNEL       0x01
#define SYSLINK_RADIO_DATARATE      0x02
#define SYSLINK_RADIO_CONTWAVE      0x03
#define SYSLINK_RADIO_RSSI          0x04
#define SYSLINK_RADIO_ADDRESS       0x05
#define SYSLINK_RADIO_RAW_BROADCAST 0x06

#define SYSLINK_PM_GROUP              0x10
#define SYSLINK_PM_SOURCE             0x10
#define SYSLINK_PM_ONOFF_SWITCHOFF    0x11
#define SYSLINK_PM_BATTERY_VOLTAGE    0x12
#define SYSLINK_PM_BATTERY_STATE      0x13
#define SYSLINK_PM_BATTERY_AUTOUPDATE 0x14

#define SYSLINK_OW_GROUP    0x20
#define SYSLINK_OW_SCAN     0x20
#define SYSLINK_OW_GETINFO  0x21
#define SYSLINK_OW_READ     0x22
#define SYSLINK_OW_WRITE    0x23

typedef struct syslinkPacket_s
{
  uint8_t type;
  uint8_t length;
  char data[SYSLINK_MTU];
} __attribute__((packed)) syslinkPacket_t;

// State machine states for receiving syslink packets
typedef enum
{
  waitForFirstStart,
  waitForSecondStart,
  waitForType,
  waitForLength,
  waitForData,
  waitForChksum1,
  waitForChksum2
} syslinkRxState_e;
