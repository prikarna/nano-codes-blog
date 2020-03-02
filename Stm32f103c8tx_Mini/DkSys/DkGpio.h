#ifndef DK_GPIO_H
#define DK_GPIO_H

#include "DkSys.h"

#define GPIO_PORT_OFFSET		0x400

#define GPIO_PORT_A				0
#define GPIO_PORT_B				1
#define GPIO_PORT_C				2
#define GPIO_PORT_D				3
#define GPIO_PORT_E				4
#define GPIO_PORT_F				5
#define GPIO_PORT_G				6

#define GPIO_PORT_A_BASE				0x40010800

#define GPIO_CRL_OFFSET					0x00
#define GPIO_CRH_OFFSET					0x04
#define GPIO_IDR_OFFSET					0x08
#define GPIO_ODR_OFFSET					0x0C
#define GPIO_BSRR_OFFSET				0x10
#define GPIO_BRR_OFFSET					0x14
#define GPIO_LCKR_OFFSET				0x18

#define GPIO_PIN_0						0
#define GPIO_PIN_1						1
#define GPIO_PIN_2						2
#define GPIO_PIN_3						3
#define GPIO_PIN_4						4
#define GPIO_PIN_5						5
#define GPIO_PIN_6						6
#define GPIO_PIN_7						7
#define GPIO_PIN_8						8
#define GPIO_PIN_9						9
#define GPIO_PIN_10						10
#define GPIO_PIN_11						11
#define GPIO_PIN_12						12
#define GPIO_PIN_13						13
#define GPIO_PIN_14						14
#define GPIO_PIN_15						15
	
#define GPIO_ADDR(Port, RegOffset)		((GPIO_PORT_A_BASE + ((Port) * GPIO_PORT_OFFSET)) + (RegOffset))

#define GPIO_MMAP(Port, RegOffset)		IO_MMAP(GPIO_ADDR((Port), (RegOffset)))

#define GPIO_CNF_INP_ANALOG				0x00
#define GPIO_CNF_INP_FLOAT				0x04
#define GPIO_CNF_INP_PU_PD				0x08
#define GPIO_CNF_INP_RESVD				0x0C

#define GPIO_CNF_OUT_GEN_PUSH_PULL		0x00
#define GPIO_CNF_OUT_GEN_OPEN_DRAIN		0x04
#define GPIO_CNF_OUT_ALT_PUSH_PULL		0x08
#define GPIO_CNF_OUT_ALT_OPEN_DRAIN		0x0C

#define GPIO_MOD_INP					0x00
#define GPIO_MOD_OUT_10MHZ				0x01
#define GPIO_MOD_OUT_2MHZ				0x02
#define GPIO_MOD_OUT_50MHZ				0x03

#define GPIO_MODE_REG(Port, Pin)		(GPIO_ADDR(Port, GPIO_CRL_OFFSET) + ((Pin / 8) * 0x04))

#define GPIO_MODE_NTH_PIN(Pin)			((Pin * 4) - ((Pin / 8) * 32))

#define GPIO_SET_MODE_INPUT(Port, Pin, CnfInp)				\
	SET_BITS(GPIO_MODE_REG(Port, Pin), GPIO_MODE_NTH_PIN(Pin), BIT_MASK_4_BITS, (GPIO_MOD_INP | CnfInp))

#define GPIO_SET_MODE_OUTPUT(Port, Pin, CnfOut, ModeOut)					\
	SET_BITS(GPIO_MODE_REG(Port, Pin), GPIO_MODE_NTH_PIN(Pin), BIT_MASK_4_BITS, (CnfOut | ModeOut))

#define GPIO_READ(Port, Pin)				GET_BIT(GPIO_ADDR(Port, GPIO_IDR_OFFSET), Pin)
#define GPIO_READ4(Port, StartPin)			GET_BITS(GPIO_ADDR(Port, GPIO_IDR_OFFSET), StartPin, BIT_MASK_4_BITS)
#define GPIO_READ8(Port, StartPin)			GET_BITS(GPIO_ADDR(Port, GPIO_IDR_OFFSET), StartPin, BIT_MASK_8_BITS)

#define GPIO_WRITE(Port, Pin, Val)			(Val) ? (SET_BIT(GPIO_ADDR(Port, GPIO_ODR_OFFSET), Pin)) : (CLR_BIT(GPIO_ADDR(Port, GPIO_ODR_OFFSET), Pin))
#define GPIO_WRITE4(Port, StartPin, Val)	SET_BITS(GPIO_ADDR(Port, GPIO_ODR_OFFSET), StartPin, BIT_MASK_4_BITS, Val)
#define GPIO_WRITE8(Port, StartPin, Val)	SET_BITS(GPIO_ADDR(Port, GPIO_ODR_OFFSET), StartPin, BIT_MASK_8_BITS, Val)

#define GPIO_SET(Port, Pin)					SET_BIT(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), Pin)
#define GPIO_SET4(Port, StartPin)			SET_BITS(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), StartPin, BIT_MASK_4_BITS, 0xF)
#define GPIO_SET8(Port, StartPin)			SET_BITS(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), StartPin, BIT_MASK_8_BITS, 0xFF)

#define GPIO_RESET(Port, Pin)				SET_BIT(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), (Pin + 16))
#define GPIO_RESET4(Port, StartPin)			SET_BITS(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), (StartPin + 16), BIT_MASK_4_BITS, 0xF)
#define GPIO_RESET8(Port, StartPin)			SET_BITS(GPIO_ADDR(Port, GPIO_BSRR_OFFSET), (StartPin + 16), BIT_MASK_8_BITS, 0xFF)

#endif   // End of DK_GPIO_H
