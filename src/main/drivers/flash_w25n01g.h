#pragma once

typedef struct bblut_s {
    uint16_t pba;
    uint16_t lba;
} bblut_t;

typedef struct eccerr_s {
    uint32_t block;
    uint32_t count;
} eccerr_t;

typedef struct w25nDevData_s {
    bblut_t  *bblut;
    int8_t   bblutEntries;
    int8_t   bblutCount;

    eccerr_t *eccError;
    int8_t   eccerrEntries;
    int8_t   eccerrCount;

    uint32_t nextSpareBlock;
} w25nDevData_t;

bool w25n01g_detect(flashDevice_t *fdevice, uint32_t chipID);
