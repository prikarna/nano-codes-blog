#include "UsbSkel.h"

#ifdef _CHIP_NUC1XX

PUSB_SETUP	gpStp = (PUSB_SETUP) (USB_SRAM);

#elif defined _CHIP_STM32F10XXXXX

USB_SETUP_16	gStp;
PUSB_SETUP_16	gpStp = &gStp;
uint8_ptr_t		gpEp1Buf = 0;

#else
# error No chipset defined!!!
#endif

#ifdef _CHIP_NUC1XX

void On_FloatDetInt()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);

	if (USB_FLOAT_DETECT()) {
		DBG_PRINTF("%s(): Attached\r\n", __FUNCTION__);
		USB_SET_ATTRS(USB_ATTR_CTRL_ENABLE, SET);
	} else {
		DBG_PRINTF("%s(): Detached\r\n", __FUNCTION__);
		USB_SET_ATTRS(USB_ATTR_CTRL_ENABLE, CLEAR);
	}

	USB_CLR_INTRS(USB_INTR_STATUS_FLDET);
}

void On_BusInt()
{
	uint8_t	uBusStat = USB_BUS_GET_STATUS();

	//DBG_PRINTF("%s()\r\n", __FUNCTION__);

	switch (uBusStat)
	{
	case USB_BUS_STATUS_TIMEOUT:
		DBG_PRINTF("%s(): Time out\r\n", __FUNCTION__);
		break;

	case USB_BUS_STATUS_RESUME:
		DBG_PRINTF("%s(): Resume\r\n", __FUNCTION__);
		USB_SET_ATTRS(USB_ATTR_REMOTE_WAKE_UP, CLEAR);
		USB_SET_ATTRS(USB_ATTR_PHY_ENABLE, SET);
		break;

	case USB_BUS_STATUS_SUSPEND:
		DBG_PRINTF("%s(): Suspend\r\n", __FUNCTION__);
		USB_SET_ATTRS(USB_ATTR_PHY_ENABLE, CLEAR);
		USB_SET_ATTRS(USB_ATTR_REMOTE_WAKE_UP, SET);
		break;

	case USB_BUS_STATUS_RESET:
		DBG_PRINTF("%s(): Reset\r\n", __FUNCTION__);
		On_BusReset();
		break;

	default:
		DBG_PRINTF("%s(): Unknown bus status = 0x%b\r\n", __FUNCTION__, uBusStat);
		DBG_BREAK();
		break;
	}

	USB_CLR_INTRS(USB_INTR_STATUS_BUS);
}

#elif defined _CHIP_STM32F10XXXXX

void On_CorrectTransInt()
{
	uint8_t			uIsStpReq = USB_EP_IS_SETUP(USB_EP_REG_0);
	PUSB_SETUP_16	pStp;
	uint8_t			uEp;

	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	
	if (uIsStpReq) {
		pStp = (PUSB_SETUP_16) USB_EP_GET_RX_BUF_ADDR(USB_EP_REG_0, 0);
		MemCopy((uint8_ptr_t) gpStp, (uint8_ptr_t) pStp, sizeof(USB_SETUP_16));
		On_StpInt();
	} else {
		uEp = USB_GET_TRANSACT_EP_ID();
		switch (uEp)
		{
		case USB_EP_REG_0:
			On_EpReg0Int();
			break;

		case USB_EP_REG_1:
			On_EpReg1Int();
			break;
		
		case USB_EP_REG_2:
			On_EpReg2Int();
			break;

		case USB_EP_REG_3:
			On_EpReg3Int();
			break;

		default:
			DBG_PRINTF("%s(): Unhandled endpoint register %d event\r\n", __FUNCTION__, uEp);
			DBG_BREAK();
			break;
		}
	}

}

void On_PackMemOvrUndRunInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_ErrorInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_StartOfFrameInt()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	USB_CLR_START_OF_FRAME_INT();
}

void On_ExpectStartOfFrameInt()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	USB_CLR_EXPECT_START_OF_FRAME_INT();
}

void On_SuspendInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	USB_SET_FORCE_SUSPEND(SET);
	USB_CLR_SUSPEND_INT();
}

#else
# error No chipset defined!!!
#endif

void On_BusReset()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);

#ifdef _CHIP_NUC1XX

	USB_SET_ATTRS(USB_ATTR_REMOTE_WAKE_UP, CLEAR);
	USB_SET_ATTRS(USB_ATTR_PHY_ENABLE, SET);

	USB_SET_FUNC_ADDR(0);

	USB_EP_SET(USB_EP_REG0, SET, CLEAR, USB_EP_STATE_IN, 0, 0);
	USB_EP_SET_BUFF_SEG(USB_EP_REG0, EP0_BUF_SEG);

	USB_EP_SET(USB_EP_REG1, SET, CLEAR, USB_EP_STATE_OUT, 0, 0);
	USB_EP_SET_BUFF_SEG(USB_EP_REG1, EP1_BUF_SEG);

	USB_EP_SET(USB_EP_REG2, CLEAR, CLEAR, USB_EP_STATE_IN, 0, 1);
	USB_EP_SET_BUFF_SEG(USB_EP_REG2, EP2_BUF_SEG);

#elif defined _CHIP_STM32F10XXXXX

	USB_SET_BTBL_ADDR(0);
	USB_SET_DEV_ADDR(0);
	USB_ENABLE(ENABLE);

	USB_EP_SET_RX_BUF_ADDR(USB_EP_REG_0, 0, EP0_RX_BUF_SEG);
	USB_EP_SET_RX_BUF_LEN(0, USB_EP_REG_0, 1, 1);

	USB_EP_SET_TX_BUF_ADDR(USB_EP_REG_0, 0, EP0_TX_BUF_SEG);
	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, EP_MAX_LEN);

	USB_EP_SET_TX_BUF_ADDR(USB_EP_REG_1, 0, EP1_TX_BUF_SEG);
	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_1, 0, EP_MAX_LEN);

	USB_EP_SET(USB_EP_REG_0, USB_EP_TYPE_CONTROL, USB_EP_KIND_NONE, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_INIT);

	USB_EP_SET(USB_EP_REG_1, USB_EP_TYPE_INTERRUPT, USB_EP_KIND_NONE, 1);
	USB_EP_CTL_EX(USB_EP_REG_1, 1, USB_EP_CTL_EX_INT_TRANS_TX_INIT);

	USB_CLR_RESET_INT();

#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX
}

void On_WakeUpInt()
{

	DBG_PRINTF("%s()\r\n", __FUNCTION__);

#ifdef _CHIP_NUC1XX

	USB_CLR_INTRS(USB_INTR_STATUS_WAKEUP);

#elif defined _CHIP_STM32F10XXXXX
	
	USB_SET_FORCE_SUSPEND(CLEAR);
	USB_CLR_WAKE_UP_INT();

#else
# error No chipset defined!!!
#endif
}

void On_StpInt()
{
	uint8_t		uReq = (uint8_t) ((gpStp->bmRequestType >> 5) & 0x3);

	//DBG_PRINTF("%s(): uReq = 0x%b, bmRequestType = 0x%b\r\n", __FUNCTION__, uReq, gpStp->bmRequestType);

	switch (uReq)
	{
	case REQTYPE_STANDARD:
		On_Stp_StdReq();
		break;

	case REQTYPE_CLASS:
		On_Stp_ClsReq();
		break;

	case REQTYPE_VENDOR:
		On_Stp_VendReq();
		break;

	case REQTYPE_RESERVED:
		On_Stp_RsvdReq();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (0x%b)\r\n", __FUNCTION__, uReq);
		DBG_BREAK();
		break;
	}

#ifdef _CHIP_NUC1XX
	USB_CLR_INTRS((USB_INTR_STATUS_SETUP | USB_INTR_STATUS_USB));
#elif defined _CHIP_STM32F10XXXXX
	// Do nothing
#else
# error No chipset defined!!!
#endif
}

void On_EpReg0Int()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	
	uint8_t	uReq = (uint8_t) ((gpStp->bmRequestType >> 5) & 0x3);

	switch (uReq)
	{
	case REQTYPE_STANDARD:
		On_EpReg0_StdReq();
		break;

	case REQTYPE_CLASS:
		On_EpReg0_ClsReq();
		break;

	case REQTYPE_VENDOR:
		On_EpReg0_VendReq();
		break;

	case REQTYPE_RESERVED:
		On_EpReg0_RsvdReq();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (0x%b)\r\n", __FUNCTION__, uReq);
		DBG_BREAK();
		break;
	}

#ifdef _CHIP_NUC1XX
	USB_CLR_INTRS(USB_INTR_STATUS_EPEVT0);
#elif defined _CHIP_STM32F10XXXXX
	// No nothing
#else
# error No chipset defined!!!
#endif
}

void On_EpReg1Int()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);

#ifdef _CHIP_NUC1XX

	uint8_t	uReq = (uint8_t) ((gpStp->bmRequestType >> 5) & 0x3);

	//DBG_PRINTF("%s()\r\n", __FUNCTION__);

	switch (uReq)
	{
	case REQTYPE_STANDARD:
		On_EpReg1_StdReq();
		break;

	case REQTYPE_CLASS:
		On_EpReg1_ClsReq();
		break;

	case REQTYPE_VENDOR:
		On_EpReg1_VendReq();
		break;

	case REQTYPE_RESERVED:
		On_EpReg1_RsvdReq();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (0x%b)\r\n", __FUNCTION__, uReq);
		DBG_BREAK();
		break;
	}

	USB_CLR_INTRS(USB_INTR_STATUS_EPEVT1);

#elif defined _CHIP_STM32F10XXXXX

	static uint8_t	u = 0;
	uint32_t		uDiv, uMod;

	//DBG_PRINTF("%s(): Dir=%d, Ep1=0x%X\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_1)));
	//DBG_BREAK();
	
	u++;
	uDiv = u / 60;
	uMod = u - (uDiv * 60);
	if (uMod == 0) {
		//DBG_PRINTF("%s(): (+) Dir=%d, Ep1=0x%h\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_1)));
		DBG_PRINTF("%s(): Counter = %d\r\n", __FUNCTION__, u);
		gpEp1Buf = (uint8_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_1, 0);
		*((uint8_ptr_t) gpEp1Buf) = u;

		USB_EP_SET_TX_BUF_LEN(USB_EP_REG_1, 0, 0x40);
	} else {
		//DBG_PRINTF("%s(): (-) Dir=%d, Ep1=0x%h\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_1)));
		USB_EP_SET_TX_BUF_LEN(USB_EP_REG_1, 0, 0);
	}

	USB_EP_CTL_EX(USB_EP_REG_1, 1, USB_EP_CTL_EX_INT_TRANS_IN);

#else
# error No chipset defind!!!
#endif
}

extern void On_EpReg2();

void On_EpReg2Int()
{
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	On_EpReg2();
#elif defined _CHIP_STM32F10XXXXX
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}

void On_EpReg3Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg4Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg5Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}
