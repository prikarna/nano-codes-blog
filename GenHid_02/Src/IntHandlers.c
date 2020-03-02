#include "UsbSkel.h"

#ifdef _CHIP_NUC1XX

PUSB_SETUP	gpStp = (PUSB_SETUP) (USB_SRAM);

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
		break;
	}

	USB_CLR_INTRS(USB_INTR_STATUS_BUS);
}

#elif defined _CHIP_STM32F10XXXXX

void On_CorrectTransInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
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
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	USB_CLR_START_OF_FRAME_INT();
}

void On_ExpectStartOfFrameInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
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

	USB_SET_ATTRS(USB_ATTR_PHY_ENABLE, SET);
	USB_SET_ATTRS(USB_ATTR_REMOTE_WAKE_UP, CLEAR);

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
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_INIT_STALL_CTRL_TRANS);

	USB_EP_SET(USB_EP_REG_1, USB_EP_TYPE_INTERRUPT, USB_EP_KIND_NONE, 1);
	USB_EP_CTL_EX(USB_EP_REG_1, 1, USB_EP_CTL_EX_INIT_VALID_TX_INT_TRANS);

	USB_CLR_RESET_INT();

#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX
}

void On_WakeUpInt()
{

	DBG_PRINTF("%s()\r\n", __FUNCTION__);

#ifdef _CHIP_NUC1XX

	DBG_BREAK();

#elif defined _CHIP_STM32F10XXXXX
	
	USB_SET_FORCE_SUSPEND(CLEAR);
	USB_CLR_WAKE_UP_INT();

#else
# error No chipset defined!!!
#endif
}

void On_StpInt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg2Int()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
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
