/*
 * TWI_program.c
 *
 * Created: 7/1/2023 1:46:38 PM
 *  Author: Ahmed
 */ 
#include "../../lib/std_types.h"
#include "../../lib/bit_math.h"
#include "TWI_private.h"
#include "TWI_config.h"
#include "TWI_interface.h"



void TWI_voidMasterInit(void){
	
	/* Set Prescaler value */
	CLR_BIT(TWI_u8_TWSR_REG,1);
	CLR_BIT(TWI_u8_TWSR_REG,0);
	/* Set TWBR with the value => 200KHz */
	/* warning for 8MHz */
	/* Freq = (CPU_CLK) / (16+2*TWBR) */
	TWI_u8_TWBR_REG = 12;
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,6);
	/* Enable I2C */
	SET_BIT(TWI_u8_TWCR_REG,2);
}


TWI_ErrorState TWI_u8SlaveInit(u8 Copy_u8Address){
	TWI_ErrorState Local_u8ErrorState = TWI_OK;
	/* set slave address in TWAR */
	TWI_u8_TWAR_REG = Copy_u8Address << 1;
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,6);
	/* Enable I2C */
	SET_BIT(TWI_u8_TWCR_REG,2);
	return Local_u8ErrorState;
	/* NOK if out of range */
}


TWI_ErrorState TWI_u8SendStartCondition(void){
	TWI_ErrorState Local_u8ErrorState = TWI_OK;
	/* clear flag + start condition */
	SET_BIT(TWI_u8_TWCR_REG,7);
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* wait for the flag to be 1 */
	while(!READ_BIT(TWI_u8_TWCR_REG,7));
	/* check the status code */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x08){
		Local_u8ErrorState = TWI_SC_Error;
	}
	/* clear start condition bit */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	return Local_u8ErrorState;
}

TWI_ErrorState TWI_u8SendRestartCondition(void){
	/* clear flag + start condition */
	/* wait for the flag to be 1 */
	/* check the status code => reperted start condition */
	/* clear start condition bit */
	return TWI_SC_Error;
}

TWI_ErrorState TWI_u8SendStopCondition(void){
	/* clear flag + stop condition */
	return TWI_SC_Error;
}

TWI_ErrorState TWI_u8SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){
	/* write slave address + 0 in TWDR */
	/* clear flag */
	/* wait for the flag to be 1 */
	/* check the status code = SLA+W */
	return TWI_SC_Error;
}

TWI_ErrorState TWI_u8sendSlaveAddWithRead(u8 Copy_u8SlaveAddress){
	/* write slave address + 1 in TWDR */
	/* clear flag */
	/* wait for the flag to be 1 */
	/* check the status code = SLA+R */
	return TWI_SC_Error;
}


TWI_ErrorState TWI_u8SendDataByte(u8 Copy_u8DataByte){
	/* write date in TWDR */
	/* clear flag */
	/* wait for the flag to be 1 */
	/* check the status code = MASTERSendData */
	return TWI_SC_Error;
}


TWI_ErrorState TWI_u8ReadDataByte(u8 * Copy_pu8ReturnedDataByte){
	/* check pinter */
	/* clear flag */
	/* wait for the flag to be 1 */
	/* check the status code = MasterRecievedData  */
	/* Read Data in the pointer */
	return TWI_SC_Error;
}

