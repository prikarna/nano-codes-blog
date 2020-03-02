#include "UsbSkel.h"

__attribute__ ((section(".eisr_vector")))
void (* const gHandlers[])(void) =
{
	(void *) (STACK_ADDRESS),
	ResetHandler
};

void Spin(uint32_t uTimes)
{
	while (uTimes-- > 0);
}

void InitUsbCtrl()
{
#ifdef _CHIP_NUC1XX

	CLK_ENA_CTRL_CLOCK(CLK_CTRL_USBD, ENABLE);
	USB_DRIVE_SE0(CLEAR);
	USB_ENA_INTRS(USB_INTR_INNACK, ENABLE);
	USB_SET_ATTRS((USB_ATTR_BYTE_MODE | USB_ATTR_PWR_DOWN | USB_ATTR_PULL_UP_USB_DP), SET);

#elif defined _CHIP_STM32F10XXXXX

# ifdef _DEBUG
	RCC_ENA_APB2_CTRL_CLK(ENABLE, RCC_APB2_CTRL_IOPA);
	GPIO_SET_MODE_OUTPUT(GPIO_PORT_A, GPIO_PIN_11, GPIO_CNF_OUT_GEN_PUSH_PULL, GPIO_MOD_OUT_50MHZ);
	GPIO_SET_MODE_OUTPUT(GPIO_PORT_A, GPIO_PIN_12, GPIO_CNF_OUT_GEN_PUSH_PULL, GPIO_MOD_OUT_50MHZ);
	GPIO_WRITE(GPIO_PORT_A, GPIO_PIN_11, 0);
	GPIO_WRITE(GPIO_PORT_A, GPIO_PIN_12, 0);
	DBG_PRINTF("%s(): Wait for host to remove previous USB device instance... ", __FUNCTION__);
	Spin(12000000);
	DBG_PRINTF("done.\r\n", 0);
	RCC_ENA_APB2_CTRL_CLK(DISABLE, RCC_APB2_CTRL_IOPA);
# endif

	RCC_SET_USB_PRESC(RCC_USB_PRESCALE_DIV_1_5);
	RCC_ENA_APB1_CTRL_CLK(ENABLE, RCC_APB1_CTRL_USB);

	USB_SET_CTL(CLEAR, USB_CTL_POWER_DOWN);
	Spin(12000);
	USB_SET_CTL(CLEAR, USB_CTL_FORCE_USB_RESET);

	USB_CLR_ALL_INTS();

#else
# error No chipset defined!!!
#endif   // End of _CHIP_XXX
}

void MainLoop()
{
	uint32_t	uInts = 0;

#ifdef _CHIP_NUC1XX

	while (1) {

		uInts = USB_INTR_GET_STATUS();

		if (uInts & USB_INTR_STATUS_FLDET)
		{
			On_FloatDetInt();
		}
		else if (uInts & USB_INTR_STATUS_BUS)
		{
			On_BusInt();
		}
		else if (uInts & USB_INTR_STATUS_WAKEUP)
		{
			On_WakeUpInt();
		}
		else if (uInts & USB_INTR_STATUS_USB)
		{
			if (uInts & USB_INTR_STATUS_SETUP)
			{
				On_StpInt();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT0)
			{
				On_EpReg0Int();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT1)
			{
				On_EpReg1Int();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT2)
			{
				On_EpReg2Int();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT3)
			{
				On_EpReg3Int();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT4)
			{
				On_EpReg4Int();
			}
			else if (uInts & USB_INTR_STATUS_EPEVT5)
			{
				On_EpReg5Int();
			}
			else
			{
				DBG_PRINTF("%s(); Unhandled USB interrupts: 0x%X\r\n", __FUNCTION__, uInts);
				DBG_BREAK();
			}
		}
		else
		{
			if (uInts > 0)
			{
				DBG_PRINTF("%s(); Unhandled USB controller interrupts: 0x%X\r\n", __FUNCTION__, uInts);
				DBG_BREAK();
			}
			else
			{
				// Do nothing
			}
		}
	}

#elif defined _CHIP_STM32F10XXXXX

	while (1)
	{
		uInts = USB_GET_ALL_INTS();

		if (uInts & USB_INT_EXPECT_START_OF_FRAME)
		{
			On_ExpectStartOfFrameInt();
		} 
		else if (uInts & USB_INT_START_OF_FRAME)
		{
			On_StartOfFrameInt();
		}
		else if (uInts & USB_INT_RESET)
		{
			On_BusReset();
		}
		else if (uInts & USB_INT_SUSPEND)
		{
			On_SuspendInt();
		}
		else if (uInts & USB_INT_WAKEUP)
		{
			On_WakeUpInt();
		}
		else if (uInts & USB_INT_ERROR)
		{
			On_ErrorInt();
		}
		else if (uInts & USB_INT_PACK_MEM_OVR_UND_RUN)
		{
			On_PackMemOvrUndRunInt();
		}
		else if (uInts & USB_INT_CORRECT_TRANS)
		{
			On_CorrectTransInt();
		}
		else
		{
			if (uInts != 0x0) {
				DBG_PRINTF("%s(): Unknown interrupt of 0x%X\r\n", __FUNCTION__, uInts);
				DBG_BREAK();
			}
		}
	}

#else
# error No chipset defined!!!
#endif   // End of _CHIP_XXX
}

void ResetHandler()
{
	uint32_t	uClk;

	ClkSetSysClkToMaxSpeed();

	DBG_INIT();
	uClk = ClkGetSysClk();

	DBG_PRINTF("Program %s, Ver. %s, chipset: %s\r\n", PROG_NAME_STR, PROG_VER_STR, TGT_CHIP_STR);
	DBG_PRINTF("Processor running at %d Hz (%d MHz)\r\n", uClk, (uClk / 1000000));

	InitUsbCtrl();

	MainLoop();
}
