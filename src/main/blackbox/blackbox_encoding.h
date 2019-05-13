#pragma once

int blackboxPrintf(const char *fmt, ...);
void blackboxPrintfHeaderLine(const char *name, const char *fmt, ...);

void blackboxWriteUnsignedVB(uint32_t value);
void blackboxWriteSignedVB(int32_t value);
void blackboxWriteSignedVBArray(int32_t *array, int count);
void blackboxWriteSigned16VBArray(int16_t *array, int count);
void blackboxWriteS16(int16_t value);
void blackboxWriteTag2_3S32(int32_t *values);
int blackboxWriteTag2_3SVariable(int32_t *values);
void blackboxWriteTag8_4S16(int32_t *values);
void blackboxWriteTag8_8SVB(int32_t *values, int valueCount);
void blackboxWriteU32(int32_t value);
void blackboxWriteFloat(float value);
