#include "GamePad.h"

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
	uint8_ptr_t		pStp;
	uint8_t			uEp;

	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	
	if (uIsStpReq) {
		pStp = (uint8_ptr_t) USB_EP_GET_RX_BUF_ADDR(USB_EP_REG_0, 0);
		MemCopy((uint8_ptr_t) gpStp, pStp, sizeof(USB_SETUP_16));
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
	DBG_PRINTF("%s(): Dir=0x%b, EP=0x%b\r\n", __FUNCTION__,USB_GET_TRANSACT_DIR(), USB_GET_TRANSACT_EP_ID());
	DBG_BREAK();
	USB_CLR_ERR_INT();
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
	//DBG_PRINTF("%s()\r\n", __FUNCTION__);

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
	uint16_t		uReq = ((((uint16_t) gpStp->bmRequestType) << 8) | gpStp->bRequest);
	uint8_t			uDescType;

	switch (uReq)
	{
	case USB_STD_GET_DESCRIPTOR:
	case USB_STD_GET_DESCRIPTOR_INTERFACE:
		uDescType = (uint8_t) ((gpStp->wValue >> 8) & 0xFF);
		switch (uDescType)
		{
		case DESCTYPE_DEVICE:
			On_Stp_Std_GetDesc_Dev();
			break;

		case DESCTYPE_CONFIGURATION:
			On_Stp_Std_GetDesc_Config();
			break;

		case DESCTYPE_DEVICE_QUALIFIER:
			DefaultHandler_Stall();
			break;

		case DESCTYPE_STRING:
			On_Stp_Std_GetDesc_String();
			break;

		case DESCTYPE_HID_REPORT:
			On_Stp_Std_GetDesc_Hid_Report();
			break;

		default:
			DBG_PRINTF("%s(): Unknown USB descriptor type (bmRequestType=0x%b, bRequest=0x%b)\r\n", gpStp->bmRequestType, gpStp->bRequest);
			DBG_BREAK();
			DefaultHandler_Stall();
			break;
		}
		break;

	case USB_STD_SET_ADDRESS:
		On_Stp_Std_SetAddr();
		break;

	case USB_STD_SET_CONFIGURATION:
		On_Stp_Std_SetConfig();
		break;

	case USB_STD_SET_DESCRIPTOR:
	case USB_HID_GET_IDLE:
	case USB_HID_GET_PROTOCOL:
	case USB_HID_GET_REPORT:
	case USB_HID_SET_PROTOCOL:
	case USB_HID_SET_REPORT:
		DefaultHandler_Stall();
		break;

	case USB_HID_SET_IDLE:
		On_Stp_Cls_Hid_SetIdle();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (bmRequestType=0x%b, bRequest=0x%b)\r\n", __FUNCTION__, gpStp->bmRequestType, gpStp->bRequest);
		DBG_BREAK();
		DefaultHandler_Stall();
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
	uint16_t		uReq = ((((uint16_t) gpStp->bmRequestType) << 8) | gpStp->bRequest);
	uint8_t			uDescType;

	switch (uReq)
	{
	case USB_STD_GET_DESCRIPTOR:
	case USB_STD_GET_DESCRIPTOR_INTERFACE:
		uDescType = (uint8_t) ((gpStp->wValue >> 8) & 0xFF);
		switch (uDescType)
		{
		case DESCTYPE_DEVICE:
			On_EpReg0_Std_GetDesc_Dev();
			break;

		case DESCTYPE_CONFIGURATION:
			On_EpReg0_Std_GetDesc_Config();
			break;

		case DESCTYPE_DEVICE_QUALIFIER:
			DefaultHandler_Stall();
			break;

		case DESCTYPE_STRING:
			On_EpReg0_Std_GetDesc_String();
			break;

		case DESCTYPE_HID_REPORT:
			On_EpReg0_Std_GetDesc_Hid_Report();
			break;

		default:
			DBG_PRINTF("%s(): Unknown USB descriptor type (bmRequestType=0x%b, bRequest=0x%b)\r\n", gpStp->bmRequestType, gpStp->bRequest);
			DBG_BREAK();
			DefaultHandler_Stall();
			break;
		}
		break;

	case USB_STD_SET_ADDRESS:
		On_EpReg0_Std_SetAddr();
		break;

	case USB_STD_SET_CONFIGURATION:
		On_EpReg0_Std_SetConfig();
		break;

	case USB_STD_SET_DESCRIPTOR:
	case USB_HID_GET_IDLE:
	case USB_HID_GET_PROTOCOL:
	case USB_HID_GET_REPORT:
		DefaultHandler_Stall();
		break;

	case USB_HID_SET_IDLE:
		On_EpReg0_Cls_Hid_SetIdle();
		break;

	case USB_HID_SET_PROTOCOL:
	case USB_HID_SET_REPORT:
		DefaultHandler_Stall();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (bmRequestType=0x%b, bRequest=0x%b)\r\n", __FUNCTION__, gpStp->bmRequestType, gpStp->bRequest);
		DBG_BREAK();
		DefaultHandler_Stall();
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

	uint16_t		uReq = ((((uint16_t) gpStp->bmRequestType) << 8) | gpStp->bRequest);

	switch (uReq)
	{
	case USB_STD_GET_DESCRIPTOR:
	case USB_STD_GET_DESCRIPTOR_INTERFACE:
	case USB_STD_SET_ADDRESS:
	case USB_STD_SET_CONFIGURATION:
	case USB_STD_SET_DESCRIPTOR:
	case USB_HID_GET_IDLE:
	case USB_HID_GET_PROTOCOL:
	case USB_HID_GET_REPORT:
	case USB_HID_SET_IDLE:
	case USB_HID_SET_PROTOCOL:
	case USB_HID_SET_REPORT:
		On_EpReg1_Default();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB setup request type (bmRequestType=0x%b, bRequest=0x%b)\r\n", __FUNCTION__, gpStp->bmRequestType, gpStp->bRequest);
		DBG_BREAK();
		DefaultHandler_Stall();
		break;
	}

	USB_CLR_INTRS(USB_INTR_STATUS_EPEVT1);

#elif defined _CHIP_STM32F10XXXXX

	uint8_t		u;

	//DBG_PRINTF("%s(): Dir=%d, Ep1=0x%X\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_1)));
	//DBG_BREAK();
	
	u = (uint8_t) GPIO_READ4(GPIO_PORT_B, GPIO_PIN_6);
	GPIO_WRITE4(GPIO_PORT_B, GPIO_PIN_12, u);
	u = ~(0xF0 | u);
	gpEp1Buf = (uint8_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_1, 0);
	*((uint32_ptr_t) gpEp1Buf) = u;

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_1, 0, 1);
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
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}
