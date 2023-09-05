/*
 * TWI_private.h
 *
 * Created: 7/1/2023 1:47:27 PM
 *  Author: Ahmed
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_
/* TWDR: Two-wire Serial Interface Data Register */
#define TWI_u8_TWDR_REG				*((volatile u8*)0x23)
/* TWAR: TWA6 TWA5 TWA4 TWA3 TWA2 TWA1 TWA0 TWGCE */
#define TWI_u8_TWAR_REG				*((volatile u8*)0x22)
/* TWSR: TWS7 TWS6 TWS5 TWS4 TWS3 _ TWS1 TWS0 */
#define TWI_u8_TWSR_REG				*((volatile u8*)0x21)
/* TWDR: Two-wire Serial Interface Bit Rate Register */
#define TWI_u8_TWBR_REG				*((volatile u8*)0x20)

#define TWI_u8_TWCR_REG				*((volatile u8*)0x56)

#endif /* TWI_PRIVATE_H_ */