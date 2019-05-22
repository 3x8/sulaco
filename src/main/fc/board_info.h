#pragma once

void initBoardInformation(void);

char *getBoardName(void);
char *getManufacturerId(void);
bool boardInformationIsSet(void);

bool setBoardName(char *newBoardName);
bool setManufacturerId(char *newManufacturerId);
bool persistBoardInformation(void);

uint8_t * getSignature(void);
bool signatureIsSet(void);

bool setSignature(uint8_t *newSignature);
bool persistSignature(void);
