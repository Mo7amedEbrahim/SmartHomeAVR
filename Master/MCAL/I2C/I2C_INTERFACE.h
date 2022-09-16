/*
 * I2C_INTERFACE.h
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedhamdy8
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

void I2C_SetMaster(void);
void I2C_SetSlave(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_SendSlaveAddressWithWriteReq(u8 Saddress);
void I2C_SendSlaveAddressWithReadReq(u8 Saddress);
void I2C_WriteByte(u8 byte);
u8 I2C_ReadByte(void);
void I2C_Stop(void);
void I2C_CheckSlaveAddressReceivedWithWriteReq(void);
void I2C_CheckSlaveAddressReceivedWithReadReq(void);
u8 I2C_SlaveReadByte(void);

#endif /* I2C_INTERFACE_H_ */
