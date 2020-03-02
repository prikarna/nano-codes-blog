#include "UsbSkel.h"

#ifdef _CHIP_NUC1XX
uint8_ptr_t	gpEp2Buf = (uint8_ptr_t) (USB_SRAM + EP2_BUF_SEG);
#elif defined _CHIP_STM32F10XXXXX
// No statement yet
#else
# error No chipset defined!!!
#endif

void On_EpReg2()
{
#ifdef _CHIP_NUC1XX
	static uint8_t	u = 0;
	uint32_t			uDiv, uMod;

	//DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	u++;
	uDiv = u / 60;
	uMod = u - (uDiv * 60);
	if (uMod == 0) {
		*((uint8_ptr_t) gpEp2Buf) = u;
		USB_EP_SET_MAX_PAYLOAD(USB_EP_REG2, 1);
		DBG_PRINTF("%s(): Count = %d\r\n", __FUNCTION__, u);
	}

	USB_CLR_INTRS(USB_INTR_STATUS_EPEVT2);

#elif defined _CHIP_STM32F10XXXXX
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}