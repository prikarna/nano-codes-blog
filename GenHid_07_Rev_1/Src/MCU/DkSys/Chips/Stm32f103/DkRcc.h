#ifndef DK_RCC_H
#define DK_RCC_H

#include "DkSys.h"

#define RCC_HSI_CLK					8000000UL
#define RCC_HSE_CLK					8000000UL

#define RCC_BASE					0x40021000

#define RCC_CR_OFFSET				0x00
#define RCC_CFGR_OFFSET				0x04
#define RCC_CIR_OFFSET				0x08
#define RCC_APB2RSTR_OFFSET			0x0C
#define RCC_APB1RSTR_OFFSET			0x10
#define RCC_AHBENR_OFFSET			0x14
#define RCC_APB2ENR_OFFSET			0x18
#define RCC_APB1ENR_OFFSET			0x1C
#define RCC_BDCR_OFFSET				0x20
#define RCC_CSR_OFFSET				0x24

#define RCC_REG_ADDR(RegOffset)		(RCC_BASE + RegOffset)
#define RCC_MMAP(RegOffset)			IO_MMAP((RCC_BASE + RegOffset))

#define RCC_ENA_HSI(Ena)			ENABLE_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_0, Ena)

#define RCC_IS_HSI_READY()			GET_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), 1)

#define RCC_SET_HSI_TRIMM(TrimVal)	SET_BITS(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_3, BIT_MASK_5_BITS, TrimVal)

#define RCC_GET_HSI_TRIM()			GET_BITS(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_3, BIT_MASK_5_BITS)

#define RCC_GET_HSI_CALIB()			GET_BITS(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_8, BIT_MASK_8_BITS)

#define RCC_ENA_HSE(Ena)			ENABLE_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_16, Ena)

#define RCC_IS_HSE_READY()			GET_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_17)

#define RCC_ENA_HSE_BYPASS(Ena)		ENABLE_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_18, Ena)

#define RCC_ENA_CLK_SEC_SYS(Ena)	ENABLE_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_19, Ena)

#define RCC_ENA_PLL(Ena)			ENABLE_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_24, Ena)

#define RCC_IS_PLL_READY()			GET_BIT(RCC_REG_ADDR(RCC_CR_OFFSET), BIT_NO_25)

#define RCC_APB_PRESCALE_HCLK_DIV_BY_1		0x0		// 0xx: HCLK not divided
#define RCC_APB_PRESCALE_HCLK_DIV_BY_2		0x4		// 100: HCLK divided by 2
#define RCC_APB_PRESCALE_HCLK_DIV_BY_4		0x5		// 101: HCLK divided by 4
#define RCC_APB_PRESCALE_HCLK_DIV_BY_8		0x6		// 110: HCLK divided by 8
#define RCC_APB_PRESCALE_HCLK_DIV_BY_16		0x7		// 111: HCLK divided by 16

#define RCC_GET_APB1_PRESCALE()					GET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_8, BIT_MASK_3_BITS)

#define RCC_SET_APB1_PRESCALE(RccApbPresc)		SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_8, BIT_MASK_3_BITS, RccApbPresc)

#define RCC_GET_APB2_PRESCALE()					GET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_11, BIT_MASK_3_BITS)

#define RCC_SET_APB2_PRESCALE(RccApbPresc)		SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_11, BIT_MASK_3_BITS, RccApbPresc)

#define RCC_MCO_NO_CLOCK			0x0
#define RCC_MCO_SYSCLK				0x4
#define RCC_MCO_HSI					0x5
#define RCC_MCO_HSE					0x6
#define RCC_MCO_PLL_DIV_2			0x7

#define RCC_SET_MCO_CLK(McoClk)				SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_24, BIT_MASK_3_BITS, McoClk)

#define RCC_USB_PRESCALE_DIV_1_5			0x0
#define RCC_USB_PRESCALE_DIV_1				0x1

#define RCC_SET_USB_PRESC(UsbPrescale)		ENABLE_BIT(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_22, UsbPrescale)

#define RCC_PLL_MUL_BY_2			0x0
#define RCC_PLL_MUL_BY_3			0x1
#define RCC_PLL_MUL_BY_4			0x2
#define RCC_PLL_MUL_BY_5			0x3
#define RCC_PLL_MUL_BY_6			0x4
#define RCC_PLL_MUL_BY_7			0x5
#define RCC_PLL_MUL_BY_8			0x6
#define RCC_PLL_MUL_BY_9			0x7
#define RCC_PLL_MUL_BY_10			0x8
#define RCC_PLL_MUL_BY_11			0x9
#define RCC_PLL_MUL_BY_12			0xA
#define RCC_PLL_MUL_BY_13			0xB
#define RCC_PLL_MUL_BY_14			0xC
#define RCC_PLL_MUL_BY_15			0xD
//#define RCC_PLL_MUL_BY_16			0xE
#define RCC_PLL_MUL_BY_16			0xF

#define RCC_SET_PLL_MUL(MulBy)		SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_18, BIT_MASK_4_BITS, MulBy)

#define RCC_GET_PLL_MUL()			GET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_18, BIT_MASK_4_BITS)

#define RCC_SET_PLLXTPRE(Set)		ENABLE_BIT(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_17, Set)

#define RCC_PLL_SRC_HSI_DIV_2		0x0
#define RCC_PLL_SRC_PREDIV1			0x1
#define RCC_PLL_SRC_HSE				RCC_PLL_SRC_PREDIV1

#define RCC_SET_PLL_SRC(PllSrc)		ENABLE_BIT(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_16, PllSrc)

#define RCC_GET_PLL_SRC()			GET_BIT(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_16)

#define RCC_ADC_PRESCALE_PCLK2_DIV_2		0x0
#define RCC_ADC_PRESCALE_PCLK2_DIV_4		0x1
#define RCC_ADC_PRESCALE_PCLK2_DIV_6		0x2
#define RCC_ADC_PRESCALE_PCLK2_DIV_8		0x3

#define RCC_SET_ADC_PRESCALE(AdcPrescale)	SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_14, BIT_MASK_2_BITS, AdcPrescale)

#define RCC_AHB_PRESCALE_SYSCLK				0x0		//	0xxx: SYSCLK not divided
#define RCC_AHB_PRESCALE_SYSCLK_DIV_2		0x8		//	1000: SYSCLK divided by 2
#define RCC_AHB_PRESCALE_SYSCLK_DIV_4		0x9		//	1001: SYSCLK divided by 4
#define RCC_AHB_PRESCALE_SYSCLK_DIV_8		0xA		//	1010: SYSCLK divided by 8
#define RCC_AHB_PRESCALE_SYSCLK_DIV_16		0xB		//	1011: SYSCLK divided by 16
#define RCC_AHB_PRESCALE_SYSCLK_DIV_64		0xC		//	1100: SYSCLK divided by 64
#define RCC_AHB_PRESCALE_SYSCLK_DIV_128		0xD		//	1101: SYSCLK divided by 128
#define RCC_AHB_PRESCALE_SYSCLK_DIV_256		0xE		//	1110: SYSCLK divided by 256
#define RCC_AHB_PRESCALE_SYSCLK_DIV_512		0xF		//	1111: SYSCLK divided by 512

#define RCC_SET_AHB_PRESCALE(AhbPrescale)	SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_4, BIT_MASK_4_BITS, AhbPrescale)

#define RCC_GET_AHB_PRESCALE()				GET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_4, BIT_MASK_4_BITS)

#define RCC_SYSCLK_SRC_HSI					0x0		//	00: HSI oscillator used as system clock
#define RCC_SYSCLK_SRC_HSE					0x1		//	01: HSE oscillator used as system clock
#define RCC_SYSCLK_SRC_PLL					0x2		//	10: PLL used as system clock

#define	RCC_GET_SYSCLK_SRC()				GET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_2, BIT_MASK_2_BITS)

#define RCC_SYSCLK_HSI						0x0		//	00: HSI selected as system clock
#define RCC_SYSCLK_HSE						0x1		//	01: HSE selected as system clock
#define RCC_SYSCLK_PLL						0x2		//	10: PLL selected as system clock

#define RCC_SWITCH_SYSCLK(SysClk)			SET_BITS(RCC_REG_ADDR(RCC_CFGR_OFFSET), BIT_NO_0, BIT_MASK_2_BITS, SysClk)

#define RCC_APB2_CTRL_TIM11			BIT_HEX_21
#define RCC_APB2_CTRL_TIM10			BIT_HEX_20
#define RCC_APB2_CTRL_TIM9			BIT_HEX_19
#define RCC_APB2_CTRL_ADC3			BIT_HEX_15
#define RCC_APB2_CTRL_USART1		BIT_HEX_14
#define RCC_APB2_CTRL_TIM8			BIT_HEX_13
#define RCC_APB2_CTRL_API1			BIT_HEX_12
#define RCC_APB2_CTRL_TIM1			BIT_HEX_11
#define RCC_APB2_CTRL_ADC2			BIT_HEX_10
#define RCC_APB2_CTRL_ADC1			BIT_HEX_9
#define RCC_APB2_CTRL_IOPG			BIT_HEX_8
#define RCC_APB2_CTRL_IOPF			BIT_HEX_7
#define RCC_APB2_CTRL_IOPE			BIT_HEX_6
#define RCC_APB2_CTRL_IOPD			BIT_HEX_5
#define RCC_APB2_CTRL_IOPC			BIT_HEX_4
#define RCC_APB2_CTRL_IOPB			BIT_HEX_3
#define RCC_APB2_CTRL_IOPA			BIT_HEX_2
#define RCC_APB2_CTRL_AFIO			BIT_HEX_0

#define RCC_RESET_APB2_CTRL(Apb2Ctrl)		RCC_MMAP(RCC_APB2RSTR_OFFSET) |= Apb2Ctrl

#define RCC_APB1_CTRL_DAC			BIT_HEX_29
#define RCC_APB1_CTRL_PWR			BIT_HEX_28
#define RCC_APB1_CTRL_BKP			BIT_HEX_27
#define RCC_APB1_CTRL_CAN			BIT_HEX_25
#define RCC_APB1_CTRL_USB			BIT_HEX_23
#define RCC_APB1_CTRL_I2C2			BIT_HEX_22
#define RCC_APB1_CTRL_I2C1			BIT_HEX_21
#define RCC_APB1_CTRL_UART5			BIT_HEX_20
#define RCC_APB1_CTRL_UART4			BIT_HEX_19
#define RCC_APB1_CTRL_USART3		BIT_HEX_18
#define RCC_APB1_CTRL_USART2		BIT_HEX_17
#define RCC_APB1_CTRL_SPI3			BIT_HEX_15
#define RCC_APB1_CTRL_SPI2			BIT_HEX_14
#define RCC_APB1_CTRL_WWDG			BIT_HEX_11
#define RCC_APB1_CTRL_TIM14			BIT_HEX_8
#define RCC_APB1_CTRL_TIM13			BIT_HEX_7
#define RCC_APB1_CTRL_TIM12			BIT_HEX_6
#define RCC_APB1_CTRL_TIM7			BIT_HEX_5
#define RCC_APB1_CTRL_TIM6			BIT_HEX_4
#define RCC_APB1_CTRL_TIM5			BIT_HEX_3
#define RCC_APB1_CTRL_TIM4			BIT_HEX_2
#define RCC_APB1_CTRL_TIM3			BIT_HEX_1
#define RCC_APB1_CTRL_TIM2			BIT_HEX_0

#define RCC_RESET_APB1_CTRL(Apb1Ctrl)		RCC_MMAP(RCC_APB1RSTR_OFFSET) |= Apb1Ctrl

#define RCC_AHB_CTRL_SDIOEN				BIT_HEX_10
#define RCC_AHB_CTRL_FSMCEN				BIT_HEX_8
#define RCC_AHB_CTRL_CRCEN				BIT_HEX_6
#define RCC_AHB_CTRL_FLITFEN			BIT_HEX_4
#define RCC_AHB_CTRL_SRAMEN				BIT_HEX_2
#define RCC_AHB_CTRL_DMA2EN				BIT_HEX_1
#define RCC_AHB_CTRL_DMA1EN				BIT_HEX_0

#define RCC_ENA_AHB_CTRL_CLK(Ena, AhbCtrl)				\
	(Ena) ? (RCC_MMAP(RCC_AHBENR_OFFSET) |= AhbCtrl) : (RCC_MMAP(RCC_AHBENR_OFFSET) &= ~(AhbCtrl))

#define RCC_ENA_APB2_CTRL_CLK(Ena, Apb2Ctrl)			\
	(Ena) ? (RCC_MMAP(RCC_APB2ENR_OFFSET) |= Apb2Ctrl) : (RCC_MMAP(RCC_APB2ENR_OFFSET) &= ~(Apb2Ctrl))

#define RCC_ENA_APB1_CTRL_CLK(Ena, Apb1Ctrl)			\
	(Ena) ? (RCC_MMAP(RCC_APB1ENR_OFFSET) |= Apb1Ctrl) : (RCC_MMAP(RCC_APB1ENR_OFFSET) &= ~(Apb1Ctrl))

#define RCC_RESET_BACK_DOM()								\
	{														\
		SET_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_16);	\
		asm("nop\n\tnop\n\tnop");							\
	}

#define RCC_CLR_RST_BACK_DOM()								\
	{														\
		CLR_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_16);	\
		asm("nop\n\tnop\n\tnop");							\
	}

#define RCC_ENA_RTC_CTRL(Ena)										\
	{																\
		ENABLE_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_15, Ena);	\
		asm("nop\n\tnop\n\tnop");									\
	}

#define RCC_RTC_CLK_SRC_NONE			0x0
#define RCC_RTC_CLK_SRC_LSE				0x1
#define RCC_RTC_CLK_SRC_LSI				0x2
#define RCC_RTC_CLK_SRC_LSE_DIV_128		0x3

#define RCC_SET_RTC_CLK_SRC(RtcClkSrc)													\
	SET_BITS(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_8, BIT_MASK_2_BITS, RtcClkSrc);		\
	asm("nop\n\tnop\n\tnop")

#define RCC_ENA_LSE_BYPASS(Ena)											\
	ENABLE_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_2, Ena);			\
	asm("nop\n\tnop\n\tnop")

#define RCC_IS_LSE_READY()				GET_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_1)

#define RCC_ENA_LSE(Ena)												\
	ENABLE_BIT(RCC_REG_ADDR(RCC_BDCR_OFFSET), BIT_NO_0, Ena);			\
	asm("nop\n\tnop\n\tnop")

#define RCC_GET_LOW_PWR_RST_FLAG()										\
	{																	\
	uint32_t res = (RCC_MMAP(RCC_CSR_OFFSET) & BIT_HEX_31) ? 1 : 0;		\
	asm("nop\n\tnop\n\tnop");											\
	return res;															\
	}

#define RCC_GET_WND_WATCHDOG_FLAG()										\
	{																	\
	uint32_t res = (RCC_MMAP(RCC_CSR_OFFSET) & BIT_HEX_30) ? 1 : 0;		\
	asm("nop\n\tnop\n\tnop");											\
	return res;															\
	}

#define RCC_GET_INDP_WATCHDOG_FLAG()									\
	{																	\
	uint32_t res = (RCC_MMAP(RCC_CSR_OFFSET) & BIT_HEX_29) ? 1 : 0;		\
	asm("nop\n\tnop\n\tnop");											\
	return res;															\
	}

#define RCC_GET_SOFT_RST_FLAG()											\
	{																	\
	uint32_t res = (RCC_MMAP(RCC_CSR_OFFSET) & BIT_HEX_28) ? 1 : 0;		\
	asm("nop\n\tnop\n\tnop");											\
	return res;															\
	}

#define RCC_GET_POR_RST_FLAG()											\
	{																	\
	uint32_t res = (RCC_MMAP(RCC_CSR_OFFSET) & BIT_HEX_27) ? 1 : 0;		\
	asm("nop\n\tnop\n\tnop");											\
	return res;															\
	}

#define RCC_REMOVE_RESET_FLAG()											\
	SET_BIT(RCC_REG_ADDR(RCC_CSR_OFFSET), BIT_NO_24);					\
	asm("nop\n\tnop\n\tnop")

#define RCC_ENA_LSI(Ena)												\
	ENABLE_BIT(RCC_REG_ADDR(RCC_CSR_OFFSET), BIT_NO_0, Ena);			\
	asm("nop\n\tnop\n\tnop")

#endif   // End of DK_RCC_H
