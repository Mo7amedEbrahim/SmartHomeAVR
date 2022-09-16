/*************************************************************************************/
/**********************    Author: Islam Ahmed  *************************************/
/**********************    Layer:  MCAL         **************************************/
/**********************    SWC:    SPI           ***********************************/
/**********************   Version: 1.00        *************************************/
/***********************************************************************************/

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"SPI_interface.h"
#include"SPI_private.h"
#include"SPI_config.h"
#include"SPI_register.h"



void SPI_voidInitMaster(void)
{
	/*Master initialization*/
	SET_BIT(SPCR,SPCR_MSTR);

	/*clock prescasler :divided by 16*/
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI ENABLE*/
	SET_BIT(SPCR,SPCR_SPE);

}


void SPI_voidInitSlave(void)
{
	/*Slave initialization*/
	CLR_BIT(SPCR,SPCR_MSTR);

	/*SPI ENABLE*/
	SET_BIT(SPCR,SPCR_SPE);

}


u8  SPI_u8Transceive(u8 Copy_u8Data)
{
/*send the data*/
SPDR=Copy_u8Data;

/*wait (busy waiting) until transfer is completed*/
while(GET_BIT(SPSR,SPSR_SPIF)==0);

/*Get the data*/
return SPDR;


}
