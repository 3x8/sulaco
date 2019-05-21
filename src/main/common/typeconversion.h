#pragma once

#define FTOA_BUFFER_LENGTH 11

void uli2a(unsigned long int num, unsigned int base, int uc, char *bf);
void li2a(long num, char *bf);
void ui2a(unsigned int num, unsigned int base, int uc, char *bf);
void i2a(int num, char *bf);
char a2i(char ch, const char **src, int base, int *nump);
char *ftoa(float x, char *floatString);
float fastA2F(const char *p);

#ifndef HAVE_ITOA_FUNCTION
char *itoa(int i, char *a, int r);
#endif
