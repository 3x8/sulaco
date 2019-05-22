#pragma once

// Called to flush the buffer.
typedef void (*bufWrite_t)(void *arg, void *data, int count);

typedef struct bufWriter_s {
    bufWrite_t writer;
    void *arg;
    uint8_t capacity;
    uint8_t at;
    uint8_t data[];
} bufWriter_t;

// Initialise a block of memory as a buffered writer.
//
// b should be sizeof(bufWriter_t) + the number of bytes to buffer.
// total_size should be the total size of b.
//
bufWriter_t *bufWriterInit(uint8_t *b, int total_size, bufWrite_t writer, void *p);
void bufWriterAppend(bufWriter_t *b, uint8_t ch);
void bufWriterFlush(bufWriter_t *b);
