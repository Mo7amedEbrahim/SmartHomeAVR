

#ifndef EEPROM_H_
#define EEPROM_H_


void EEpromInit(void);
void EEpromWriteByte(u16 address, u8 data);
u8 EEpromReadByte(u16 address);
 
#endif








