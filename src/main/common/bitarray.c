#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "bitarray.h"

#define BITARRAY_BIT_OP(array, bit, op) ((array)[(bit) / (sizeof((array)[0]) * 8)] op (1 << ((bit) % (sizeof((array)[0]) * 8))))

bool bitArrayGet(const void *array, unsigned bit)
{
    return BITARRAY_BIT_OP((uint32_t*)array, bit, &);
}

void bitArraySet(void *array, unsigned bit)
{
    BITARRAY_BIT_OP((uint32_t*)array, bit, |=);
}

void bitArrayClr(void *array, unsigned bit)
{
    BITARRAY_BIT_OP((uint32_t*)array, bit, &=~);
}

void bitArrayXor(void *dest, size_t size, void *op1, void *op2)
{
    for (size_t i = 0; i < size; i++) {
        ((uint8_t*)dest)[i] = ((uint8_t*)op1)[i] ^ ((uint8_t*)op2)[i];
    }
}

void bitArrayCopy(void *array, unsigned from, unsigned to)
{
    if (bitArrayGet(array, from)) {
        bitArraySet(array, to);
    } else {
        bitArrayClr(array, to);
    }
}
