#ifndef DK_USART_H
#define DK_USART_H

#include "DkSys.h"

#define USART1_BASE				0x40013800
#define USART2_BASE				0x40004400
#define USART3_BASE				0x40004800
#define USART4_BASE				0x40004C00
#define USART5_BASE				0x40005000

#define USART1					USART1_BASE
#define USART2					USART2_BASE
#define USART3					USART3_BASE
#define USART4					USART4_BASE
#define USART5					USART5_BASE

#define USART_SR_OFFSET			0x00
#define USART_DR_OFFSET			0x04
#define USART_BRR_OFFSET		0x08
#define USART_CR1_OFFSET		0x0C
#define USART_CR2_OFFSET		0x10
#define USART_CR3_OFFSET		0x14
#define USART_GTPR_OFFSET		0x18

#define USART_MMAP(UsartNo, RegOffset)	IO_MMAP((UsartNo + RegOffset))

#define USART_IS_TX_EMPTY(UsartNo)		(USART_MMAP(UsartNo, USART_SR_OFFSET) & BIT_HEX_7)

#define USART_IS_TX_CMPLT(UsartNo)		(USART_MMAP(UsartNo, USART_SR_OFFSET) & BIT_HEX_6)
#define USART_CLR_TX_CMPLT(UsartNo)		USART_MMAP(UsartNo, USART_SR_OFFSET) &= ~BIT_HEX_6

#define USART_IS_RX_READY(UsartNo)		(USART_MMAP(UsartNo, USART_SR_OFFSET) & BIT_HEX_5)
#define USART_CLR_RX_READY(UsartNo)		USART_MMAP(UsartNo, USART_SR_OFFSET) &= ~BIT_HEX_5

#define USART_READ(UsartNo)				(USART_MMAP(UsartNo, USART_DR_OFFSET))

#define USART_WRITE(UsartNo, Val)		USART_MMAP(UsartNo, USART_DR_OFFSET) = Val

#define USART_SET_BAUD_FRACT(UsartNo, DivMantisa, DivFraction)			\
	USART_MMAP(UsartNo, USART_BRR_OFFSET) = ((DivMantisa & 0xFFF) << 4) | (DivFraction & 0xF)

#define USART_ENABLE(UsartNo, Ena)		ENABLE_BIT((UsartNo + USART_CR1_OFFSET), BIT_NO_13, Ena)

#define USART_DATA_LEN_8_DATABITS		0x0
#define USART_DATA_LEN_9_DATABITS		0x1

#define USART_SET_DATA_LEN(DatLen)		ENABLE_BIT((UsartNo + USART_CR1_OFFSET), BIT_NO_12, DatLen)

#define USART_ENA_TX(UsartNo, Ena)		ENABLE_BIT((UsartNo + USART_CR1_OFFSET), BIT_NO_3, Ena)

#define USART_ENA_RX(UsartNo, Ena)		ENABLE_BIT((UsartNo + USART_CR1_OFFSET), BIT_NO_2, Ena)

#define USART_STOP_BIT_1			0x0
#define USART_STOP_BIT_0_DOT_5		0x1
#define USART_STOP_BIT_2			0x2
#define USART_STOP_BIT_1_DOT_5		0x3

#define USART_SET_STOP_BIT(UsartNo, StopBit)		SET_BITS((UsartNo + USART_CR2_OFFSET), BIT_NO_12, BIT_MASK_2_BITS, StopBit)

#endif   // End of DK_USART_H
