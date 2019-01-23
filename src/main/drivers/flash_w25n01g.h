/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

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
