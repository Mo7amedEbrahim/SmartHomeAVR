#include "../../LIB/STD_TYPES.h"
#include "eeprom.h"
#include "../I2C/I2C_INTERFACE.h"


//2c02

void EEpromInit(void)
{
	I2C_SetMaster();
}



void EEpromWriteByte(u16 address, u8 data)
{
	I2C_Start();
	I2C_SendSlaveAddressWithWriteReq( 0b01010000 /*| ((address & 0x0700)>>8) */);
	I2C_WriteByte((u8)address);
	I2C_WriteByte(data);
	I2C_Stop();
    return;
}



u8 EEpromReadByte(u16 address)
{
	u8 data;
	I2C_Start();
	I2C_SendSlaveAddressWithWriteReq( 0b01010000 /*| ((address & 0x07)>>8) */);
	I2C_WriteByte((u8)address);
	I2C_RepeatedStart();
	I2C_SendSlaveAddressWithReadReq( 0b01010000 /*| ((address & 0x07)>>8)*/ );
	data = I2C_ReadByte();
	I2C_Stop();
    return data;
}
