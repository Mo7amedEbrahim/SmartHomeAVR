/*************************************************************************************/
/**********************    Author: Islam Ahmed  *************************************/
/**********************    Layer:  MCAL         **************************************/
/**********************    SWC:    SPI           ***********************************/
/**********************   Version: 1.00        *************************************/
/***********************************************************************************/
#ifndef SPI_INTERFACE_H_  
#define SPI_INTERFACE_H_

void SPI_voidInitMaster(void);


void SPI_voidInitSlave(void);


u8  SPI_u8Transceive(u8 Copy_u8Data);




#endif