#include "GamePad.h"

#ifdef _CHIP_NUC1XX
uint8_ptr_t	gpEp2Buf = (uint8_ptr_t) (USB_SRAM + EP2_BUF_SEG);
#elif defined _CHIP_STM32F10XXXXX
// Define nothing
#else
# error No chipset defined!!!
#endif

void On_EpReg2()
{
#ifdef _CHIP_NUC1XX
	
	uint8_t		u = GPIO_GET_INTR_4(GPIO_PORT_A, GPIO_PIN_0);

	GPIO_WRITE_4(GPIO_PORT_A, GPIO_PIN_4, ~u);
	gpEp2Buf[0] = u;
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG2, 1);
	USB_CLR_INTRS(USB_INTR_STATUS_EPEVT2);

#elif defined _CHIP_STM32F10XXXXX
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}
