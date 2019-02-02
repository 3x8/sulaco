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

// Upper 4MB (32 blocks * 128KB/block) will be used for bad block replacement area.

// Blocks in this area are only written through bad block LUT,
// and factory written bad block marker in unused blocks are retained.

// When a replacement block is required,
// (1) "Read BB LUT" command is used to obtain the last block mapped,
// (2) blocks after the last block is scanned for a good block,
// (3) the first good block is used for replacement, and the BB LUT is updated.

// There are only 20 BB LUT entries, and there are 32 replacement blocks.
// There will be a least chance of running out of replacement blocks.
// If it ever run out, the device becomes unusable.


//
// Writes are done in three steps:
// (1) Load internal data buffer with data to write
//     - We use "Random Load Program Data", as "Load Program Data" resets unused data bytes in the buffer to 0xff.
//     - Each "Random Load Program Data" instruction must be accompanied by at least a single data.
//     - Each "Random Load Program Data" instruction terminates at the rising of CS.
// (2) Enable write
// (3) Issue "Execute Program"
//

/*
flashfs page program behavior
- Single program never crosses page boundary.
- Except for this characteristic, it program arbitral size.
- Write address is, naturally, not a page boundary.

To cope with this behavior.

pageProgramBegin:
If buffer is dirty and programLoadAddress != address, then the last page is a partial write;
issue PAGE_PROGRAM_EXECUTE to flash buffer contents, clear dirty and record the address as programLoadAddress and programStartAddress.
Else do nothing.

pageProgramContinue:
Mark buffer as dirty.
If programLoadAddress is on page boundary, then issue PROGRAM_LOAD_DATA, else issue RANDOM_PROGRAM_LOAD_DATA.
Update programLoadAddress.
Optionally observe the programLoadAddress, and if it's on page boundary, issue PAGE_PROGRAM_EXECUTE.

pageProgramFinish:
Observe programLoadAddress. If it's on page boundary, issue PAGE_PROGRAM_EXECUTE and clear dirty, else just return.
If pageProgramContinue observes the page boundary, then do nothing(?).
*/


/**
 * Write bytes to a flash page. Address must not cross a page boundary.
 *
 * Bits can only be set to zero, not from zero back to one again. In order to set bits to 1, use the erase command.
 *
 * Length must be smaller than the page size.
 *
 * This will wait for the flash to become ready before writing begins.
 *
 * Datasheet indicates typical programming time is 0.8ms for 256 bytes, 0.2ms for 64 bytes, 0.05ms for 16 bytes.
 * (Although the maximum possible write time is noted as 5ms).
 *
 * If you want to write multiple buffers (whose sum of sizes is still not more than the page size) then you can
 * break this operation up into one beginProgram call, one or more continueProgram calls, and one finishProgram call.
 */


 /**
  * Read `length` bytes into the provided `buffer` from the flash starting from the given `address` (which need not lie
  * on a page boundary).
  *
  * Waits up to W25N01G_TIMEOUT_PAGE_READ_MS milliseconds for the flash to become ready before reading.
  *
  * The number of bytes actually read is returned, which can be zero if an error or timeout occurred.
  */

 // Continuous read mode (BUF = 0):
 // (1) "Page Data Read" command is executed for the page pointed by address
 // (2) "Read Data" command is executed for bytes not requested and data are discarded
 // (3) "Read Data" command is executed and data are stored directly into caller's buffer
 //
 // Buffered read mode (BUF = 1), non-read ahead
 // (1) If currentBufferPage != requested page, then issue PAGE_DATA_READ on requested page.
 // (2) Compute transferLength as smaller of remaining length and requested length.
 // (3) Issue READ_DATA on column address.
 // (4) Return transferLength.
