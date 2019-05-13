#pragma once

bool bitArrayGet(const void *array, unsigned bit);
void bitArraySet(void *array, unsigned bit);
void bitArrayClr(void *array, unsigned bit);
void bitArrayXor(void *dest, size_t size, void *op1, void *op2);
void bitArrayCopy(void *array, unsigned from, unsigned to);
