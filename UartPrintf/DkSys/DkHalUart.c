#include "DkSys.h"
#include <stdarg.h>

#ifdef _CHIP_NUC1XX
# include "Chips\Nuc120\DkClockCtl.h"
# include "Chips\Nuc120\DkGpio.h"
# include "Chips\Nuc120\DkUart.h"
#elif defined _CHIP_STM32F10XXXXX
# include "Chips\Stm32f103\DkRcc.h"
# include "Chips\Stm32f103\DkGpio.h"
# include "Chips\Stm32f103\DkUsart.h"
#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX

#ifdef _CHIP_NUC1XX

# define UA_SEL_PORT	UART1
# define UA_BUF_SZ		UA_UART1_BUF_SIZE

#elif defined _CHIP_STM32F10XXXXX

# define UA_SEL_PORT	USART3

#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX

static char			sHexChars[] = { "0123456789ABCDEF" };

void UaInit()
{
#ifdef _CHIP_NUC1XX

	CLK_SET_UART_CTRL_SRC(CLK_UART_SRC_INTL_22_1184MHZ);
	CLK_ENA_CTRL_CLOCK(CLK_CTRL_UART1, ENABLE);
	
	UA_ENA_UART1();
	UA_SET_LINE_CTL(UA_SEL_PORT, UA_LNCTL_CHAR_LEN_8_BITS, UA_LNCTL_STOP_BIT_1, 0);
	UA_SET_BAUD_DEVIDER(UA_SEL_PORT, 1, 1, 0, 0x16);

#elif defined _CHIP_STM32F10XXXXX

	RCC_ENA_APB2_CTRL_CLK(ENABLE, RCC_APB2_CTRL_IOPB);
	
	RCC_ENA_APB1_CTRL_CLK(ENABLE, RCC_APB1_CTRL_USART3);
	GPIO_SET_MODE_OUTPUT(GPIO_PORT_B, GPIO_PIN_10, GPIO_CNF_OUT_ALT_PUSH_PULL, GPIO_MOD_OUT_2MHZ);

	USART_ENABLE(UA_SEL_PORT, ENABLE);
	USART_SET_BAUD_FRACT(UA_SEL_PORT, 1, 1);
	USART_ENA_TX(UA_SEL_PORT, ENABLE);

#else
# error No chipset defined!!!
#endif
}

void UaWriteChar(unsigned char c)
{
#ifdef _CHIP_NUC1XX
	UA_WRITE(UA_SEL_PORT, c);
	while (UA_IS_TX_BUF_EMPTY(UA_SEL_PORT) == 0);
#elif defined _CHIP_STM32F10XXXXX
	while (USART_IS_TX_EMPTY(UA_SEL_PORT) == 0);
	USART_WRITE(UA_SEL_PORT, c);
#else
# error No chipset defined!!!
#endif   // End of _CHIP_XXX
}

void UaWriteString(const char *szStr)
{
	char *			p	 = (char *) szStr;

#ifdef _CHIP_NUC1XX

	int				i;
	unsigned char	isRunOut = 0;

	if (!p) return;

	while (1) {
		for (i = 0; i < UA_BUF_SZ; i++) {
			if (*p != '\0') {
				UA_WRITE(UA_SEL_PORT, *p++);
			} else {
				isRunOut = 1;
				break;
			}
		}
		while (UA_IS_TX_BUF_EMPTY(UA_SEL_PORT) == 0);
		if (isRunOut) break;
	}

#elif defined _CHIP_STM32F10XXXXX
	while (*p != '\0') {
		while (USART_IS_TX_EMPTY(UA_SEL_PORT) == 0);
		USART_WRITE(UA_SEL_PORT, *p++);
	}
#else
# error No chipset defined!!!
#endif
}

void UaWriteNum(unsigned int uNum)
{
	//
	// Assume unsinged int of uNumb has 32 bits long
	//

	unsigned int	uDiv = 0, uMod = 0, uRes = 0;
	char			buf[128];
	char *			pc;

	if (uNum < 0) return;

	buf[0] = 0x00;
	pc = &buf[1];
	uRes = uNum;

	do {
		uDiv = uRes / 10;
		uMod = uRes - (uDiv * 10);
		*pc++ = sHexChars[uMod];
		uRes = uDiv;
	} while (uDiv >= 10);
	if (uDiv != 0)
		*pc = sHexChars[uDiv];
	else
		pc--;

	while (*pc != '\0') {
		UaWriteChar(*pc--);
	}
}

void UaWriteShort(unsigned int uShort)
{
	//
	// Assume unsigned short of uShort has 16 bits long = 4 nibbles
	//

	char		buf[4];
	char		*pc;
	int			i, ch;

	pc = &buf[0];
	for (i = 0; i < sizeof(buf); i++) {
		ch = uShort & 0xF;
		*pc++ = sHexChars[ch];
		uShort >>= 4;
	}

	pc--;

#ifdef _CHIP_NUC1XX
	for (i = 0; i < sizeof(buf); i++) {
		UA_WRITE(UA_SEL_PORT, *pc--);
	}
	while (UA_IS_TX_BUF_EMPTY(UA_SEL_PORT) == 0);

#elif defined _CHIP_STM32F10XXXXX
	for (i = 0; i < sizeof(buf); i++) {
		USART_WRITE(UA_SEL_PORT, *pc--);
	}
	while (USART_IS_TX_EMPTY(UA_SEL_PORT) == 0);
#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX
}

void UaWriteHex(unsigned int uHex)
{
	//
	// Assume unsigned int of uiHex has 32 bits long = 8 nibbles
	//

	char		buf[8];
	char		*pc;
	int			i, ch;

	pc = &buf[0];
	for (i = 0; i < sizeof(buf); i++) {
		ch = uHex & 0xF;
		*pc++ = sHexChars[ch];
		uHex >>= 4;
	}

	pc--;

#ifdef _CHIP_NUC1XX
	for (i = 0; i < sizeof(buf); i++) {
		UA_WRITE(UA_SEL_PORT, *pc--);
	}
	while (UA_IS_TX_BUF_EMPTY(UA_SEL_PORT) == 0);

#elif defined _CHIP_STM32F10XXXXX
	for (i = 0; i < sizeof(buf); i++) {
		USART_WRITE(UA_SEL_PORT, *pc--);
	}
	while (USART_IS_TX_EMPTY(UA_SEL_PORT) == 0);
#else
# error No chipset defined!!!
#endif   // End of _CHIP_XXX
}

void UaWriteByte(unsigned char uChar)
{
	uint8_t		uHigh = sHexChars[((uChar >> 4) & 0xF)];
	uint8_t		uLow = sHexChars[(uChar & 0xF)];

#ifdef _CHIP_NUC1XX
	UA_WRITE(UA_SEL_PORT, uHigh);
	UA_WRITE(UA_SEL_PORT, uLow);
	while (UA_IS_TX_BUF_EMPTY(UA_SEL_PORT) == 0);
#elif defined _CHIP_STM32F10XXXXX
	USART_WRITE(UA_SEL_PORT, uHigh);
	USART_WRITE(UA_SEL_PORT, uLow);
	while (USART_IS_TX_EMPTY(UA_SEL_PORT) == 0);
#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX
}

void UaPrintf(const char *szFmt, ...)
{
	char *			pc = (char *) szFmt;
	va_list			list;
	unsigned int	u;
	unsigned char	c;
	char *			s;

	va_start(list, szFmt);

	while (*pc != '\0')
	{
		c = *pc++;
		if (c != '%')
		{
			UaWriteChar(c);
		}
		else
		{
			switch ((int) *pc++)
			{
			case 'b':
			case 'B':
				c = (uint8_t) va_arg(list, uint32_t);
				UaWriteByte(c);
				break;

			case 'd':
			case 'D':
				u = va_arg(list, uint32_t);
				UaWriteNum(u);
				break;

			case 'c':
			case 'C':
				c = (uint8_t) va_arg(list, uint32_t);
				UaWriteChar(c);
				break;

			case 'h':
			case 'H':
				u = va_arg(list, uint32_t);
				UaWriteShort(u);
				break;

			case 'x':
			case 'X':
				u = (uint32_t) va_arg(list, uint32_t);
				UaWriteHex(u);
				break;

			case 's':
				s = va_arg(list, int8_ptr_t);
				UaWriteString((const char *) s);
				break;

			case '%':
				c = (uint8_t) va_arg(list, uint32_t);
				UaWriteChar('%');
				break;

			default:
				UaWriteString(" [Unknown format: ");
				UaWriteChar(c);
				UaWriteString("] ");
				break;
			}
		}
	}

	va_end(list);
}
