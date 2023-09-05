/*
 * TWI_interface.h
 *
 * Created: 7/1/2023 1:47:08 PM
 *  Author: Ahmed
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum{
	TWI_OK = 1,
	TWI_SC_Error,
	TWI_RSC_Error		
} TWI_ErrorState;

void TWI_voidMasterInit(void);

TWI_ErrorState TWI_u8SlaveInit(u8 Copy_u8Address);

TWI_ErrorState TWI_u8SendStartCondition(void);

TWI_ErrorState TWI_u8SendRestartCondition(void);

TWI_ErrorState TWI_u8SendStopCondition(void);

TWI_ErrorState TWI_u8SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrorState TWI_u8sendSlaveAddWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrorState TWI_u8SendDataByte(u8 Copy_u8DataByte);

TWI_ErrorState TWI_u8ReadDataByte(u8 * Copy_pu8ReturnedDataByte);

#endif /* TWI_INTERFACE_H_ */