#include "DkSys.h"
#include "DkGpio.h"
#include "DkRcc.h"

#define STACK_ADDRESS	((0x20000000 + 0x00005000) - 1)

void ResetHandler();

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

void ResetHandler()
{
	RCC_ENA_APB2_CTRL_CLK(ENABLE, RCC_APB2_CTRL_IOPC);
	GPIO_SET_MODE_OUTPUT(GPIO_PORT_C, GPIO_PIN_13, GPIO_CNF_OUT_GEN_PUSH_PULL, GPIO_MOD_OUT_2MHZ);
	GPIO_WRITE(GPIO_PORT_C, GPIO_PIN_13, 1);

	while (1)
	{
		GPIO_WRITE(GPIO_PORT_C, GPIO_PIN_13, 0);
		Spin(480000);
		GPIO_WRITE(GPIO_PORT_C, GPIO_PIN_13, 1);
		Spin(480000);
	}
}
