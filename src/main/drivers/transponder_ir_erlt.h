#pragma once

void transponderIrInitERLT(transponder_t *transponder);
void updateTransponderDMABufferERLT(transponder_t *transponder, const uint8_t* transponderData);
void addBitToBuffer(transponder_t *transponder, uint8_t cycles, uint8_t pulsewidth);
