#include "DkHID.h"

CDkHID::CDkHID(void)
{
	_hHid		= INVALID_HANDLE_VALUE;
	_pPrepDat	= NULL;
}

CDkHID::~CDkHID(void)
{
}

bool CDkHID::Open()
{
	BOOL								fFound			= FALSE;
	BOOL								fRes			= FALSE;
	GUID								hidGuid;
	HDEVINFO							hDevInfo		= INVALID_HANDLE_VALUE;
	DWORD								dwIdx			= 0;
	SP_DEVICE_INTERFACE_DATA			sSpDevIntDat	= {0};
	PSP_DEVICE_INTERFACE_DETAIL_DATA	pIntDetDat		= NULL;
	SP_DEVINFO_DATA						sSpDevInfoDat	= {0};
	HGLOBAL								hGlob			= NULL;
	BOOLEAN								fAttr			= FALSE;
	HIDD_ATTRIBUTES						sHidAttr		= {0};
	
	HidD_GetHidGuid(&hidGuid);
	hDevInfo = ::SetupDiGetClassDevs(
									 &hidGuid, 
									 NULL, 
									 NULL, 
									 DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
									 );
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	hGlob = GlobalAlloc(GPTR, DK_HID_MAX_BUF);
	if (!hGlob) return false;

	pIntDetDat = (PSP_DEVICE_INTERFACE_DETAIL_DATA) GlobalLock(hGlob);

	while(TRUE)
	{
		RtlZeroMemory(&sSpDevIntDat, sizeof(SP_DEVICE_INTERFACE_DATA));
		sSpDevIntDat.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		fRes = ::SetupDiEnumDeviceInterfaces(
											 hDevInfo, 
											 NULL, 
											 &hidGuid, 
											 dwIdx, 
											 &sSpDevIntDat
											 );
		if (!fRes) break;

		RtlZeroMemory(pIntDetDat, DK_HID_MAX_BUF);
		pIntDetDat->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		RtlZeroMemory(&sSpDevInfoDat, sizeof(SP_DEVINFO_DATA));
		sSpDevInfoDat.cbSize = sizeof(SP_DEVINFO_DATA);

		fRes = ::SetupDiGetDeviceInterfaceDetail(
												 hDevInfo, 
												 &sSpDevIntDat, 
												 pIntDetDat, 
												 DK_HID_MAX_BUF, 
												 NULL, 
												 &sSpDevInfoDat
												 );
		if (fRes)
		{
			_hHid = CreateFile(
							   pIntDetDat->DevicePath,
							   GENERIC_READ | GENERIC_WRITE,
							   FILE_SHARE_READ,
							   NULL,
							   OPEN_EXISTING,
							   0,
							   NULL
							   );
			if (_hHid != INVALID_HANDLE_VALUE) 
			{
				RtlZeroMemory(&sHidAttr, sizeof(HIDD_ATTRIBUTES));
				sHidAttr.Size = sizeof(HIDD_ATTRIBUTES);
				fAttr = HidD_GetAttributes(_hHid, &sHidAttr);
				if (fAttr) 
				{
					if ((sHidAttr.ProductID == HID_TGT_PID) && 
						(sHidAttr.VendorID == HID_TGT_VID)) 
					{
						fFound = TRUE;
						break;
					}
				}
				if (!fFound) 
				{
					CloseHandle(_hHid);
					_hHid = INVALID_HANDLE_VALUE;
				}
			}
		}

		dwIdx++;
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	GlobalUnlock(hGlob);
	GlobalFree(hGlob);

	if (fFound)
	{
		if (!HidD_GetPreparsedData(_hHid, &_pPrepDat)) 
		{
			CloseHandle(_hHid);
			_hHid = INVALID_HANDLE_VALUE;
			return false;
		}
	}

	return (fFound) ? true : false;
}

void CDkHID::Close()
{
	if (_hHid != INVALID_HANDLE_VALUE) 
	{
		if (_pPrepDat) 
		{
			HidD_FreePreparsedData(_pPrepDat);
			_pPrepDat = NULL;
		}

		CloseHandle(_hHid);
		_hHid = INVALID_HANDLE_VALUE;
	}
}

bool CDkHID::GetAttributes(PHIDD_ATTRIBUTES pHidAttr)
{
	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pHidAttr == NULL))
	{
		return false;
	}

	RtlZeroMemory(pHidAttr, sizeof(HIDD_ATTRIBUTES));
	pHidAttr->Size = sizeof(HIDD_ATTRIBUTES);
	BOOLEAN	fRes = HidD_GetAttributes(_hHid, pHidAttr);

	return (fRes) ? true : false;
}

bool CDkHID::GetDevCaps(PHIDP_CAPS pHidCaps)
{
	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pHidCaps == NULL))
	{
		return false;
	}

	RtlZeroMemory(pHidCaps, sizeof(HIDP_CAPS));
	NTSTATUS ntStat = HidP_GetCaps(_pPrepDat, pHidCaps);

	return (ntStat != 0) ? true : false;
}

bool CDkHID::WriteReport(LPVOID pDat, ULONG uByteDatLen)
{
	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pDat == NULL) ||
		(uByteDatLen <= 0))
	{
		return false;
	}

	BOOLEAN	fRes = HidD_SetOutputReport(_hHid, pDat, uByteDatLen);

	return (fRes) ? true : false;
}

bool CDkHID::ReadReport(LPVOID pDat, ULONG uByteDatLen)
{
	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pDat == NULL) ||
		(uByteDatLen <= 0))
	{
		return false;
	}

	BOOLEAN	fRes = HidD_GetInputReport(_hHid, pDat, uByteDatLen);

	return (fRes) ? true : false;
}

bool CDkHID::Open(unsigned short uVendId, unsigned short uProdId)
{
	BOOL								fFound			= FALSE;
	BOOL								fRes			= FALSE;
	GUID								hidGuid;
	HDEVINFO							hDevInfo		= INVALID_HANDLE_VALUE;
	DWORD								dwIdx			= 0;
	SP_DEVICE_INTERFACE_DATA			sSpDevIntDat	= {0};
	PSP_DEVICE_INTERFACE_DETAIL_DATA	pIntDetDat		= NULL;
	SP_DEVINFO_DATA						sSpDevInfoDat	= {0};
	HGLOBAL								hGlob			= NULL;
	BOOLEAN								fAttr			= FALSE;
	HIDD_ATTRIBUTES						sHidAttr		= {0};
	
	HidD_GetHidGuid(&hidGuid);
	hDevInfo = ::SetupDiGetClassDevs(
									 &hidGuid, 
									 NULL, 
									 NULL, 
									 DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
									 );
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	hGlob = GlobalAlloc(GPTR, DK_HID_MAX_BUF);
	if (!hGlob) return false;

	pIntDetDat = (PSP_DEVICE_INTERFACE_DETAIL_DATA) GlobalLock(hGlob);

	while(TRUE)
	{
		RtlZeroMemory(&sSpDevIntDat, sizeof(SP_DEVICE_INTERFACE_DATA));
		sSpDevIntDat.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		fRes = ::SetupDiEnumDeviceInterfaces(
											 hDevInfo, 
											 NULL, 
											 &hidGuid, 
											 dwIdx, 
											 &sSpDevIntDat
											 );
		if (!fRes) break;

		RtlZeroMemory(pIntDetDat, DK_HID_MAX_BUF);
		pIntDetDat->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		RtlZeroMemory(&sSpDevInfoDat, sizeof(SP_DEVINFO_DATA));
		sSpDevInfoDat.cbSize = sizeof(SP_DEVINFO_DATA);

		fRes = ::SetupDiGetDeviceInterfaceDetail(
												 hDevInfo, 
												 &sSpDevIntDat, 
												 pIntDetDat, 
												 DK_HID_MAX_BUF, 
												 NULL, 
												 &sSpDevInfoDat
												 );
		if (fRes)
		{
			_hHid = CreateFile(
							   pIntDetDat->DevicePath,
							   GENERIC_READ | GENERIC_WRITE,
							   FILE_SHARE_READ,
							   NULL,
							   OPEN_EXISTING,
							   0,
							   NULL
							   );
			if (_hHid != INVALID_HANDLE_VALUE) 
			{
				RtlZeroMemory(&sHidAttr, sizeof(HIDD_ATTRIBUTES));
				sHidAttr.Size = sizeof(HIDD_ATTRIBUTES);
				fAttr = HidD_GetAttributes(_hHid, &sHidAttr);
				if (fAttr) 
				{
					if ((sHidAttr.ProductID == uProdId) && 
						(sHidAttr.VendorID == uVendId)) 
					{
						fFound = TRUE;
						break;
					}
				}
				if (!fFound) 
				{
					CloseHandle(_hHid);
					_hHid = INVALID_HANDLE_VALUE;
				}
			}
		}

		dwIdx++;
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	GlobalUnlock(hGlob);
	GlobalFree(hGlob);

	if (fFound)
	{
		if (!HidD_GetPreparsedData(_hHid, &_pPrepDat)) 
		{
			CloseHandle(_hHid);
			_hHid = INVALID_HANDLE_VALUE;
			return false;
		}
	}

	return (fFound) ? true : false;
}