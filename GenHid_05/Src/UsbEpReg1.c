#include "UsbSkel.h"

#ifdef _CHIP_NUC1XX

extern PUSB_SETUP		gpStp;

#elif defined _CHIP_STM32F10XXXXX

extern PUSB_SETUP_16	gpStp;

#else
# error No chipset defined!!!
#endif

void On_EpReg1_Std_GetStat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_ClrFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_SetFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_SetAddr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	
#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}

void On_EpReg1_Std_GetDesc_Dev()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);

#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	DBG_BREAK();
#else
# error No chipset defined!!!
#endif
}

void On_EpReg1_Std_GetDesc_Config()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_String()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_Intf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_EndPoint()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_DevQlfy()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_OthSpeedCfg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_IntfPwr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_Otg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_Debug()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc_IntfAssoc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetDesc()
{
	uint8_t uDescType = (uint8_t) ((gpStp->wValue >> 8) & 0xFF);

	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	switch (uDescType)
	{
	case DESCTYPE_DEVICE:
		On_EpReg1_Std_GetDesc_Dev();
		break;

	case DESCTYPE_CONFIGURATION:
		On_EpReg1_Std_GetDesc_Config();
		break;

	case DESCTYPE_STRING:
		On_EpReg1_Std_GetDesc_String();
		break;

	case DESCTYPE_INTERFACE:
		On_EpReg1_Std_GetDesc_Intf();
		break;

	case DESCTYPE_ENDPOINT:
		On_EpReg1_Std_GetDesc_EndPoint();
		break;

	case DESCTYPE_DEVICE_QUALIFIER:
		On_EpReg1_Std_GetDesc_DevQlfy();
		break;

	case DESCTYPE_OTHER_SPEED_CONFIGURATION:
		On_EpReg1_Std_GetDesc_OthSpeedCfg();
		break;

	case DESCTYPE_INTERFACE_POWER:
		On_EpReg1_Std_GetDesc_IntfPwr();
		break;

	case DESCTYPE_OTG:
		On_EpReg1_Std_GetDesc_Otg();
		break;

	case DESCTYPE_DEBUG:
		On_EpReg1_Std_GetDesc_Debug();
		break;

	case DESCTYPE_INTERFACE_ASSOCIATION:
		On_EpReg1_Std_GetDesc_IntfAssoc();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB descriptor type (0x%b)\r\n", __FUNCTION__, uDescType);
		DBG_BREAK();
		break;
	}
}

void On_EpReg1_Std_SetDesc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_GetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_SetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();
}

void On_EpReg1_Std_GetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_SetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_Std_SyncFrame()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_StdReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	switch (gpStp->bRequest)
	{
	case STDREQ_GET_STATUS:
		On_EpReg1_Std_GetStat();
		break;

	case STDREQ_CLEAR_FEATURE:
		On_EpReg1_Std_ClrFeat();
		break;

	case STDREQ_SET_FEATURE:
		On_EpReg1_Std_SetFeat();
		break;

	case STDREQ_SET_ADDRESS:
		On_EpReg1_Std_SetAddr();
		break;

	case STDREQ_GET_DESCRIPTOR:
		On_EpReg1_Std_GetDesc();
		break;

	case STDREQ_SET_DESCRIPTOR:
		On_EpReg1_Std_SetDesc();
		break;

	case STDREQ_GET_CONFIGURATION:
		On_EpReg1_Std_GetConfig();
		break;

	case STDREQ_SET_CONFIGURATION:
		On_EpReg1_Std_SetConfig();
		break;

	case STDREQ_GET_INTERFACE:
		On_EpReg1_Std_GetIntf();
		break;

	case STDREQ_SET_INTERFACE:
		On_EpReg1_Std_SetIntf();
		break;

	case STDREQ_SYNCH_FRAME:
		On_EpReg1_Std_SyncFrame();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB standard setup request type (0x%b)\r\n", __FUNCTION__, gpStp->bRequest);
		DBG_BREAK();
		break;
	}
}

void On_EpReg1_ClsReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_VendReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg1_RsvdReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}
