#include "DkSys.h"

#ifdef _CHIP_NUC1XX
# define STACK_ADDRESS	((0x20000000 + 0x00000200) - 1)
#elif defined _CHIP_STM32F10XXXXX
# define STACK_ADDRESS	((0x20000000 + 0x00005000) - 1)
#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX

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

extern void UaInit();
extern void UaPrintf(const char * szFmt, ...);

void ResetHandler()
{
	uint32_t	uCnt = 0;

	UaInit();
	
	UaPrintf("Hallo world!!!\r\n");
	UaPrintf("Test number first=%d, second=%d and third=%d, this function name is %s\r\n", 1, 2, 3, __FUNCTION__);

	while (1)
	{
		UaPrintf("Counter: %d\r", uCnt++);
		Spin(1680000);
	}
}