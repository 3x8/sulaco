#pragma once

#define FLASHFS_WRITE_BUFFER_SIZE 128
#define FLASHFS_WRITE_BUFFER_USABLE (FLASHFS_WRITE_BUFFER_SIZE - 1)

// Automatically trigger a flush when this much data is in the buffer
#define FLASHFS_WRITE_BUFFER_AUTO_FLUSH_LEN 64

void flashfsEraseCompletely(void);
void flashfsEraseRange(uint32_t start, uint32_t end);

uint32_t flashfsGetSize(void);
uint32_t flashfsGetOffset(void);
uint32_t flashfsGetWriteBufferFreeSpace(void);
uint32_t flashfsGetWriteBufferSize(void);
int flashfsIdentifyStartOfFreeSpace(void);
struct flashGeometry_s;
const struct flashGeometry_s* flashfsGetGeometry(void);

void flashfsSeekAbs(uint32_t offset);
void flashfsSeekRel(int32_t offset);

void flashfsWriteByte(uint8_t byte);
void flashfsWrite(const uint8_t *data, unsigned int len, bool sync);

int flashfsReadAbs(uint32_t offset, uint8_t *data, unsigned int len);

bool flashfsFlushAsync(void);
void flashfsFlushSync(void);

void flashfsClose(void);
void flashfsInit(void);
bool flashfsIsSupported(void);

bool flashfsIsReady(void);
bool flashfsIsEOF(void);
