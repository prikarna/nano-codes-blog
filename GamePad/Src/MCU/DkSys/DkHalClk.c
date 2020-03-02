#include "DkSys.h"

#ifdef _CHIP_NUC1XX
# include "Chips\Nuc120\DkClockCtl.h"
# include "Chips\Nuc120\DkSmc.h"
#elif defined _CHIP_STM32F10XXXXX
# include "Chips\Stm32f103\DkGpio.h"
# include "Chips\Stm32f103\DkRcc.h"
# include "Chips\Stm32f103\DkFlash.h"
#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX

#ifdef _CHIP_STM32F10XXXXX

uint32_t	ClkGetPllMul()
{
	uint32_t	pllMul = 0, pllMulType = 0;

	pllMulType = RCC_GET_PLL_MUL();
	switch (pllMulType)
	{
	case RCC_PLL_MUL_BY_2:
		pllMul = 2;
		break;

	case RCC_PLL_MUL_BY_3:
		pllMul = 3;
		break;

	case RCC_PLL_MUL_BY_4:
		pllMul = 4;
		break;

	case RCC_PLL_MUL_BY_5:
		pllMul = 5;
		break;

	case RCC_PLL_MUL_BY_6:
		pllMul = 6;
		break;

	case RCC_PLL_MUL_BY_7:
		pllMul = 7;
		break;

	case RCC_PLL_MUL_BY_8:
		pllMul = 8;
		break;

	case RCC_PLL_MUL_BY_9:
		pllMul = 9;
		break;

	case RCC_PLL_MUL_BY_10:
		pllMul = 10;
		break;

	case RCC_PLL_MUL_BY_11:
		pllMul = 11;
		break;

	case RCC_PLL_MUL_BY_12:
		pllMul = 12;
		break;

	case RCC_PLL_MUL_BY_13:
		pllMul = 13;
		break;

	case RCC_PLL_MUL_BY_14:
		pllMul = 14;
		break;

	case RCC_PLL_MUL_BY_15:
		pllMul = 15;
		break;

	case 0xE:
	case RCC_PLL_MUL_BY_16:
		pllMul = 16;
		break;

	default:
		pllMul = 1;
		break;
	}

	return pllMul;
}

uint32_t	ClkGetAHBDivider()
{
	uint32_t	uAhbPreScale, uDiv;

	uAhbPreScale = RCC_GET_AHB_PRESCALE();

	switch (uAhbPreScale)
	{
	case RCC_AHB_PRESCALE_SYSCLK:
		uDiv = 1;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_2:
		uDiv = 2;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_4:
		uDiv = 4;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_8:
		uDiv = 8;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_16:
		uDiv = 16;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_64:
		uDiv = 64;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_128:
		uDiv = 128;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_256:
		uDiv = 256;
		break;

	case RCC_AHB_PRESCALE_SYSCLK_DIV_512:
		uDiv = 512;
		break;

	default:
		uDiv = 1;
		break;
	}

	return uDiv;
}

uint32_t	ClkGetAPB1Devider()
{
	uint32_t	uApbPreScale, uDiv;

	uApbPreScale = RCC_GET_APB1_PRESCALE();
	switch (uApbPreScale)
	{
	case RCC_APB_PRESCALE_HCLK_DIV_BY_1:
		uDiv = 1;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_2:
		uDiv = 2;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_4:
		uDiv = 4;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_8:
		uDiv = 8;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_16:
		uDiv = 16;
		break;

	default:
		uDiv = 1;
		break;
	}

	return uDiv;
}

uint32_t	ClkGetAPB2Divider()
{
	uint32_t	uApbPreScale, uDiv;

	uApbPreScale = RCC_GET_APB2_PRESCALE();
	switch (uApbPreScale)
	{
	case RCC_APB_PRESCALE_HCLK_DIV_BY_1:
		uDiv = 1;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_2:
		uDiv = 2;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_4:
		uDiv = 4;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_8:
		uDiv = 8;
		break;

	case RCC_APB_PRESCALE_HCLK_DIV_BY_16:
		uDiv = 16;
		break;

	default:
		uDiv = 1;
		break;
	}

	return uDiv;
}

#endif  // End of _CHIP_STM32F10XXXXX

uint32_t ClkSetSysClkToMaxSpeed()
{
	uint32_t	u = 0, uRes = 0;

#ifdef _CHIP_NUC1XX

	//
	// Disable write protection
	//
	SMC_DISABLE_WRITE_PROTECT();

	//
	// Enable external clock source
	//
	CLK_ENA_CLOCK_SOURCE(CLK_SOURCE_EXTL_12MHZ, ENABLE);
	while (CLK_IS_EXT_4TO24MHZ_STABLE() == 0);

	//
	// Enable and set PLL clock
	//
	CLK_PLL_SET_SOURCE(CLK_PLL_SRC_EXTERN_4TO24MHZ);
	CLK_PLL_ENA_PWR_DOWN(DISABLE);
	CLK_PLL_SET_DIVIDER(3, 1, 48);
	CLK_PLL_ENABLE(ENABLE);
	while (CLK_IS_PLL_STABLE() == 0);

	//
	// Disable write protect again and 
	// set system clock to PLL clock as clock source
	//
	SMC_DISABLE_WRITE_PROTECT();
	CLK_SET_HCLK_SOURCE(CLK_HCLK_SRC_PLL);

	//
	// Get status of system clock
	//
	for (u = 0; u < 8; u++) {
		uRes = CLK_GET_HCLK_SOURCE();
		if (uRes == CLK_HCLK_SRC_PLL) break;
	}

	//
	// Enable write protect
	//
	SMC_ENABLE_WRITE_PROTECT();

	//
	// Return 1 if succeeded otherwise return 0
	//
	return (uRes == CLK_HCLK_SRC_PLL) ? 1 : 0;

#elif defined _CHIP_STM32F10XXXXX

	//
	// Make flash latency longer
	//
	FLASH_ENA_PREF_BUF(ENABLE);
	FLASH_SET_LATENCY(FLASH_LATENCY_TWO_WAIT_STATE);

	//
	// Enable High Speed External clock
	//
	RCC_ENA_HSE_BYPASS(DISABLE);
	RCC_ENA_HSE(ENABLE);
	while (RCC_IS_HSE_READY() == 0);

	//
	// Enable PLL clock
	//
	RCC_SET_PLL_MUL(RCC_PLL_MUL_BY_9);
	RCC_SET_PLLXTPRE(CLEAR);
	RCC_SET_PLL_SRC(RCC_PLL_SRC_PREDIV1);
	RCC_ENA_PLL(ENABLE);
	while (RCC_IS_PLL_READY() == 0);

	//
	// Adjust peripheral which is connected to APB1
	//
	RCC_SET_APB1_PRESCALE(RCC_APB_PRESCALE_HCLK_DIV_BY_2);

	//
	// Switch system clock to PLL clock as source clock
	//
	RCC_SWITCH_SYSCLK(RCC_SYSCLK_PLL);

	//
	// Check clock switching process and return 0 if failed
	//
	for (u = 0; u < 16; u++) {
		uRes = RCC_GET_SYSCLK_SRC();
		if (uRes == RCC_SYSCLK_SRC_PLL) break;
	}

	//
	// Restore flash latency if we fail to change clock source
	//
	if (uRes != RCC_SYSCLK_SRC_PLL) {
		FLASH_SET_LATENCY(FLASH_LATENCY_ZERO_WAIT_STATE);	
		return 0;
	}

	return 1;
#else
# error No cipset defined!!!
#endif  // End of _CHIP_XXX
}

uint32_t ClkGetSysClk()
{
#ifdef _CHIP_NUC1XX

	uint32_t	uClkSrc = 0, uClkSrcTyp = 0;
	uint32_t	uPllClkSrc = 0, uPllClkSrcType = 0;
	uint32_t	uPllFbDiv, uPllInDiv, uPllOutDiv;

	uClkSrcTyp = CLK_GET_HCLK_SOURCE();

	switch (uClkSrcTyp)
	{
	case CLK_HCLK_SRC_EXTL_4TO24MHZ:
		uClkSrc = CLK_EXTERN_HIGH_SPEED;
		break;

	case CLK_HCLK_SRC_EXTL_32_768KHZ:
		uClkSrc = CLK_EXTERN_LOW_SPEED;
		break;

	case CLK_HCLK_SRC_PLL:
		uPllClkSrcType = CLK_PLL_GET_SOURCE();
		switch (uPllClkSrcType)
		{
		case CLK_PLL_SRC_EXTERN_12MHZ:
			uPllClkSrc = CLK_EXTERN_HIGH_SPEED;
			break;

		case CLK_PLL_SRC_INTERN_22_1184MHZ:
			uPllClkSrc = CLK_INTERN_HIGH_SPEED;
			break;

		default:
			uPllClkSrc = CLK_INTERN_HIGH_SPEED;
			break;
		}
		uPllFbDiv = CLK_PLL_GET_FB_DIV() + 2;
		uPllInDiv = CLK_PLL_GET_IN_DIV() + 2;
		uPllOutDiv = CLK_PLL_GET_OUT_DIV();
		if (uPllOutDiv == 0) {
			uPllOutDiv = 1;
		} else if (uPllOutDiv == 1) {
			uPllOutDiv = 2;
		} else if (uPllOutDiv == 2) {
			uPllOutDiv = 2;
		} else {
			uPllOutDiv = 4;
		}
		uClkSrc = (uPllClkSrc * uPllFbDiv) / (uPllInDiv * uPllOutDiv);
		break;

	case CLK_HCLK_SRC_INTL_10KHZ:
		uClkSrc = CLK_INTERN_LOW_SPEED;
		break;

	case CLK_HCLK_SRC_INTL_22_1184MHZ:
		uClkSrc = CLK_INTERN_HIGH_SPEED;
		break;

	default:
		uClkSrc = CLK_INTERN_HIGH_SPEED;
		break;
	}

	return uClkSrc;

#elif defined _CHIP_STM32F10XXXXX

	uint32_t	clkSrc = 0, clk = 0;
	uint32_t	ahbDiv = 0;
	uint32_t	pllSrc, pllMul;

	ahbDiv = ClkGetAHBDivider();

	clkSrc = RCC_GET_SYSCLK_SRC();

	switch (clkSrc)
	{
	case RCC_SYSCLK_SRC_HSI:
		clk = RCC_HSI_CLK / ahbDiv;
		break;

	case RCC_SYSCLK_SRC_HSE:
		clk = RCC_HSE_CLK / ahbDiv;
		break;

	case RCC_SYSCLK_SRC_PLL:
		pllSrc = RCC_GET_PLL_SRC();
		pllMul = ClkGetPllMul();
		if (pllSrc == RCC_PLL_SRC_HSI_DIV_2) {
			clk = ((RCC_HSI_CLK / 2) * pllMul) / ahbDiv;
		} else {
			clk = (RCC_HSE_CLK * pllMul) / ahbDiv;
		}
		break;

	default:
		clk = RCC_HSI_CLK;
		break;
	}

	return clk;

#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX
}
