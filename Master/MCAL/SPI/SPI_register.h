/*************************************************************************************/
/**********************    Author: Islam Ahmed  *************************************/
/**********************    Layer:  MCAL         **************************************/
/**********************    SWC:    SPI           ***********************************/
/**********************   Version: 1.00        *************************************/
/***********************************************************************************/
#ifndef SPI_REGISTER_H_  
#define SPI_REGISTER_H_

#define SPDR  			*((volatile u8*)0x2F)       //spi data register

#define SPSR  			*((volatile u8*)0x2E)       //spi status register
#define SPSR_SPIF       7                          //spi interrupt flag
#define SPSR_SPI2X      0                          //prescaller bit 2

#define SPCR  			*((volatile u8*)0x2D)
#define SPCR_SPE        6                           //spi enable
#define SPCR_MSTR       4                          //master bit
#define SPCR_SPR1       1                          //prescaller bit 1
#define SPCR_SPR0       0                         //prescaller bit 0
 


#endif
