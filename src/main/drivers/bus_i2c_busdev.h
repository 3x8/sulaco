#pragma once

bool i2cBusWriteRegister(const busDevice_t *busdev, uint8_t reg, uint8_t data);
bool i2cBusReadRegisterBuffer(const busDevice_t *busdev, uint8_t reg, uint8_t *data, uint8_t length);
uint8_t i2cBusReadRegister(const busDevice_t *bus, uint8_t reg);
