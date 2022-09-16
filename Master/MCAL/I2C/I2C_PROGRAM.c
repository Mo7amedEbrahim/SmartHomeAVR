/*
 * I2C_PROGRAM.c
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedhamdy8
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "I2C_CONFIG.h"
#include "I2C_PRIVATE.h"
#include "I2C_INTERFACE.h"

#ifndef I2C_PROGRAM_C_
#define I2C_PROGRAM_C_

void I2C_SetMaster(void)
{
	TWBR = 0x07;
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0));
	TWCR = (1<<TWEN);
	return;
}

void I2C_SetSlave(void)
{
	TWAR = (1<<1);
	TWCR = (1<<TWEN);
	return;
}

void I2C_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != START_ACK);
	return;
}

void I2C_RepeatedStart(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != REP_START_ACK);
	return;
}

void I2C_SendSlaveAddressWithWriteReq(u8 Saddress)
{
	TWDR = (Saddress<<1);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK);
	return;
}

void I2C_SendSlaveAddressWithReadReq(u8 Saddress)
{
	TWDR = (Saddress<<1);
	TWDR |= (1<<0);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK);
}

void I2C_WriteByte(u8 byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != WR_BYTE_ACK);
	return;
}

u8 I2C_ReadByte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != RD_BYTE_ACK);
	return TWDR;
}

void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	return;
}

void I2C_CheckSlaveAddressReceivedWithWriteReq(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != SLAVE_ADD_RCVD_WR_REQ);
	return;
}

void I2C_CheckSlaveAddressReceivedWithReadReq(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != SLAVE_ADD_RCVD_RD_REQ);
	return;
}

u8 I2C_SlaveReadByte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != SLAVE_DATA_RECEIVED);
	return TWDR;
}

#endif /* I2C_PROGRAM_C_ */
