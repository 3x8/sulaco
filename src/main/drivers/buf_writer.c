#include <stdint.h>

#include "buf_writer.h"

bufWriter_t *bufWriterInit(uint8_t *b, int total_size, bufWrite_t writer, void *arg)
{
    bufWriter_t *buf = (bufWriter_t *)b;
    buf->writer = writer;
    buf->arg = arg;
    buf->at = 0;
    buf->capacity = total_size - sizeof(*buf);

    return buf;
}

void bufWriterAppend(bufWriter_t *b, uint8_t ch)
{
    b->data[b->at++] = ch;
    if (b->at >= b->capacity) {
        bufWriterFlush(b);
    }
}

void bufWriterFlush(bufWriter_t *b)
{
    if (b->at != 0) {
        b->writer(b->arg, b->data, b->at);
        b->at = 0;
    }
}
