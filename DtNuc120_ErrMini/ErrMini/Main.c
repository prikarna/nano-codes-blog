#include "DkSys.h"
#include "DkGpio.h"

#define STACK_ADDRESS	((0x20000000 + 0x00000200) - 1)

void ResetHandler();

extern unsigned int GetAPSR();

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
	uint32_t u = GetAPSR();
	uint32_t i = 0;

	i = u / 13;

	GPIO_SET_MODE_4(GPIO_PORT_A, GPIO_PIN_4, GPIO_MODE_OUTPUT);

	while (1)
	{
		if (i <= 0)
			GPIO_WRITE_4(GPIO_PORT_A, GPIO_PIN_4, 0xA);
		else
			GPIO_WRITE_4(GPIO_PORT_A, GPIO_PIN_4, 0x0);
		
		Spin(560000);
		
		if (i <= 0)
			GPIO_WRITE_4(GPIO_PORT_A, GPIO_PIN_4, ~(0xA));
		else
			GPIO_WRITE_4(GPIO_PORT_A, GPIO_PIN_4, 0xF);

		Spin(560000);
	}
}
