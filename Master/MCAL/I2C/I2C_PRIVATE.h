/*
 * I2C_PRIVATE.h
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedhamdy8
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define 	TWCR			*((volatile u8*)0x56)
#define 	TWINT			7
#define 	TWEA			6
#define 	TWSTA			5
#define 	TWSTO			4
#define 	TWWC			3
#define 	TWEN			2
#define 	TWIE			0

#define 	TWDR			*((volatile u8*)0x23)
#define 	TWBR			*((volatile u8*)0x20)

#define 	TWAR			*((volatile u8*)0x22)
#define 	TWA6			7
#define 	TWA5			6
#define 	TWA4			5
#define 	TWA3			4
#define 	TWA2			3
#define 	TWA1			2
#define 	TWA0			1
#define 	TWGCE			0

#define 	TWSR			*((volatile u8*)0x21)
#define 	TWS7			7
#define 	TWS6			6
#define 	TWS5			5
#define 	TWS4			4
#define 	TWS3			3
#define 	TWPS1			1
#define 	TWPS0			0

#define START_ACK					0x08
#define	REP_START_ACK				0x10
#define	SLAVE_ADD_AND_WR_ACK		0x18
#define	SLAVE_ADD_AND_RD_ACK		0x40
#define	WR_BYTE_ACK					0x28
#define	RD_BYTE_ACK					0x58
#define	SLAVE_ADD_RCVD_WR_REQ		0x60
#define	SLAVE_ADD_RCVD_RD_REQ		0xA8
#define	SLAVE_DATA_RECEIVED			0x80
#define Slave_BYTR_TRANSMITTED		0xC0

#endif /* I2C_PRIVATE_H_ */
