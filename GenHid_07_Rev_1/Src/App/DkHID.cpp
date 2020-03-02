#include "DkHID.h"

CDkHID::CDkHID(void)
{
#ifdef WIN32

	_hHid		= INVALID_HANDLE_VALUE;
	_pPrepDat	= NULL;
	
#elif defined LINUX_GNU

	_pCtx		= NULL;
	_uIdVend	= 0;
	_uIdProd	= 0;

#else
# error No target OS defined!!!
#endif
}

CDkHID::~CDkHID(void)
{
#ifdef LINUX_GNU
	if (_pCtx) {
		libusb_exit(_pCtx);
		_pCtx = NULL;
	}
#endif
}

bool CDkHID::Open()
{
#ifdef WIN32

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
	
#elif defined LINUX_GNU

	int	res = 0;
	libusb_device_handle*	pHDev = NULL;
	
	if (_pCtx == NULL) {
		res = libusb_init(&_pCtx);
		if (res < 0) return false;
	}
	
	pHDev = libusb_open_device_with_vid_pid(_pCtx, _uIdVend, _uIdProd);
	if (pHDev == NULL) return false;
	
	libusb_close(pHDev);
	
	return true;

#else
# error No target OS defined!!!
#endif
}

void CDkHID::Close()
{
#ifdef WIN32

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
	
#elif defined LINUX_GNU

	if (_pCtx) {
		libusb_exit(_pCtx);
		_pCtx = NULL;
	}

#else
# error No target OS defined!!!
#endif
}

#ifdef WIN32
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
#endif

bool CDkHID::WriteReport(LPVOID pDat, ULONG uByteDatLen)
{
#ifdef WIN32

	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pDat == NULL) ||
		(uByteDatLen <= 0))
	{
		return false;
	}

	BOOLEAN	fRes = HidD_SetOutputReport(_hHid, pDat, uByteDatLen);

	return (fRes) ? true : false;
	
#elif defined LINUX_GNU

    libusb_device_handle*       pHDev = NULL;
    int                         res = 0;

    if ((_pCtx == NULL) ||
        (pDat == NULL) ||
        (uByteDatLen == 0) ||
        (_uIdVend == 0) ||
        (_uIdProd == 0)) 
    {
        return false;
    }

    pHDev = libusb_open_device_with_vid_pid(_pCtx, _uIdVend, _uIdProd);
    if (pHDev == NULL) return false;

    res = libusb_control_transfer(
    							  pHDev, 
    							  HID_SET_REPORT_REQUEST_TYPE, 
    							  HID_SET_REPORT_REQUEST, 
    							  (0x1 << 8) | 0,
    							  0,
    							  (unsigned char *)pDat,
    							  uByteDatLen,
    							  10
    							  );

    libusb_close(pHDev);
    
    return (res > 0) ? true : false;

#else
# error No target OS defined!!!
#endif
}

bool CDkHID::ReadReport(LPVOID pDat, ULONG uByteDatLen)
{
#ifdef WIN32

	if ((_hHid == INVALID_HANDLE_VALUE) || 
		(_pPrepDat == NULL) ||
		(pDat == NULL) ||
		(uByteDatLen <= 0))
	{
		return false;
	}

	BOOLEAN	fRes = HidD_GetInputReport(_hHid, pDat, uByteDatLen);

	return (fRes) ? true : false;
	
#elif defined LINUX_GNU

    libusb_device_handle*       pHDev = NULL;
    int                         res = 0;

    if ((_pCtx == NULL) ||
        (pDat == NULL) ||
        (uByteDatLen == 0) ||
        (_uIdVend == 0) ||
        (_uIdProd == 0)) 
    {
        return false;
    }

    pHDev = libusb_open_device_with_vid_pid(_pCtx, _uIdVend, _uIdProd);
    if (pHDev == NULL) return false;

    res = libusb_control_transfer(
    							  pHDev, 
    							  HID_GET_REPORT_REQUEST_TYPE, 
    							  HID_GET_REPORT_REQUEST, 
    							  (0x1 << 8) | 0, 
    							  0, 
    							  (unsigned char *) pDat, 
    							  uByteDatLen, 
    							  10
    							  );

    libusb_close(pHDev);
    return (res > 0) ? true : false;

#else
# error No target OS defined!!!
#endif
}

bool CDkHID::Open(unsigned short uVendId, unsigned short uProdId)
{
#ifdef WIN32

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
	
#elif defined LINUX_GNU

	//int	res = 0;
	//libusb_device_handle*	pHDev = NULL;
	
	if ((uVendId == 0) ||
		(uProdId == 0))
	{
		return false;
	}
	
	_uIdVend = uVendId;
	_uIdProd = uProdId;
	
	//if (_pCtx == NULL) {
	//	res = libusb_init(&_pCtx);
	//	if (res < 0) return false;
	//}
	
	//pHDev = libusb_open_device_with_vid_pid(_pCtx, _uIdVend, _uIdProd);
	//if (pHDev == NULL) return false;
	
	//libusb_close(pHDev);
	
	return this->Open();

#else
# error No target OS defined!!!
#endif
}
