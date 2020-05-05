#pragma once

#include <stdint.h>

#define HUFFMAN_TABLE_SIZE 257 // 256 characters plus EOF
typedef struct huffmanTable_s {
  uint8_t     codeLen;
  uint16_t    code;
} huffmanTable_t;

typedef struct huffmanState_s {
  uint16_t    bytesWritten;
  uint8_t     *outByte;
  uint16_t    outBufLen;
  uint8_t     outBit;
} huffmanState_t;

extern const huffmanTable_t huffmanTable[HUFFMAN_TABLE_SIZE];

struct huffmanInfo_s {
  uint16_t uncompressedByteCount;
};

#define HUFFMAN_INFO_SIZE sizeof(struct huffmanInfo_s)

int huffmanEncodeBuf(uint8_t *outBuf, int outBufLen, const uint8_t *inBuf, int inLen, const huffmanTable_t *huffmanTable);
int huffmanEncodeBufStreaming(huffmanState_t *state, const uint8_t *inBuf, int inLen, const huffmanTable_t *huffmanTable);
