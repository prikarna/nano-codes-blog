#ifndef DK_UART_H
#define DK_UART_H

#include "DkSys.h"
#include "DkSmc.h"

#define UART0_BA			0x40050000
#define UART1_BA			0x40150000
#define UART2_BA			0x40154000

#define UART0				UART0_BA
#define UART1				UART1_BA
#define UART2				UART2_BA

#define UA_CHANS			3
#define UA_MAX_CHAN			(UA_CHANS - 1)

#define UA_RBR				0x00
#define UA_THR				0x00
#define UA_IER				0x04
#define UA_FCR				0x08
#define UA_LCR				0x0C
#define UA_MCR				0x10
#define UA_MSR				0x14
#define UA_FSR				0x18
#define UA_ISR				0x1C
#define UA_TOR				0x20
#define UA_BAUD				0x24
#define UA_IRCR				0x28
#define UA_ALT_CSR			0x2C
#define UA_FUN_SEL			0x30

#define UA_UART0_BUF_SIZE	64

#define UA_ENA_UART0()											\
	IO_MMAP(GPB_MFP) = ((IO_MMAP(GPB_MFP)) & ~(0xF)) | (0xF);	\
	IO_MMAP(ALT_MFP) &= ~(BIT_HEX_11 | BIT_HEX_14)

#define UA_UART1_BUF_SIZE	16

#define UA_ENA_UART1()											\
	IO_MMAP(GPB_MFP) = ((IO_MMAP(GPB_MFP)) & ~(0xF0)) | (0xF0);	\
	IO_MMAP(ALT_MFP) &= ~(BIT_HEX_11)

#define UA_UART2_BUF_SIZE	16

#define UA_ENA_UART2()		SET_BITS(GPD_MFP, BIT_NO_14, BIT_MASK_2_BITS, 0x3)

#define UA_ADDR(UartNo, RegOffset)			(UartNo + RegOffset)

#define UA_READ(UartNo)				GET_BITS(UA_ADDR(UartNo, UA_RBR), BIT_NO_0, BIT_MASK_8_BITS)
#define UA_WRITE(UartNo, Val)		SET_BITS(UA_ADDR(UartNo, UA_THR), BIT_NO_0, BIT_MASK_8_BITS, Val)

#define UA_LNCTL_OPT_BREAK_CTL_BIT				BIT_HEX_6
#define UA_LNCTL_OPT_STICK_PARITY_ENABLE		BIT_HEX_5
#define UA_LNCTL_OPT_EVENT_PARITY_ENABLE		BIT_HEX_4
#define UA_LNCTL_OPT_PARITY_BIT_ENABLE			BIT_HEX_3

#define UA_LNCTL_STOP_BIT_1					0
#define UA_LNCTL_STOP_BIT_2					1

#define UA_LNCTL_CHAR_LEN_5_BITS			0
#define UA_LNCTL_CHAR_LEN_6_BITS			1
#define UA_LNCTL_CHAR_LEN_7_BITS			2
#define UA_LNCTL_CHAR_LEN_8_BITS			3

#define UA_SET_LINE_CTL(UartNo, CharLen, StopBit, Opts)				\
	IO_MMAP(UA_ADDR(UartNo, UA_LCR)) = ((CharLen & BIT_MASK_2_BITS) | ((StopBit & 0x1) << BIT_NO_2) | (Opts))

#define UA_IS_TX_BUF_EMPTY(UartNo)			GET_BIT(UA_ADDR(UartNo, UA_FSR), BIT_NO_22)
#define UA_IS_RX_BUF_EMPTY(UartNo)			GET_BIT(UA_ADDR(UartNo, UA_FSR), BIT_NO_14)

#define UA_SET_BAUD_DEVIDER(UartNo, EnaDivX, DivXOne, DivX, Baud)	\
	IO_MMAP(UA_ADDR(UartNo, UA_BAUD)) = ((EnaDivX & 0x1) << 29) | ((DivXOne & 0x1) << 28) | ((DivX & 0xF) << 24) | (Baud & 0xFFFF)

#endif   // End of DK_UART_H
