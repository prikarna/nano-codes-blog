#ifdef WIN32
#pragma once

#define HID_TGT_VID			0x6A16
#define HID_TGT_PID			0x0144
#define DK_HID_MAX_BUF		2048

#include "TChar.h"
#include "Windows.h"
#include "SetupApi.h"
#include "ObjBase.h"

extern "C" 
{
	typedef struct _HIDD_ATTRIBUTES {
		ULONG  Size;
		USHORT  VendorID;
		USHORT  ProductID;
		USHORT  VersionNumber;
	} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

	typedef struct _HIDP_PREPARSED_DATA * PHIDP_PREPARSED_DATA;

	typedef struct _HIDP_CAPS {
		USHORT  Usage;
		USHORT  UsagePage;
		USHORT  InputReportByteLength;
		USHORT  OutputReportByteLength;
		USHORT  FeatureReportByteLength;
		USHORT  Reserved[17];
		USHORT  NumberLinkCollectionNodes;
		USHORT  NumberInputButtonCaps;
		USHORT  NumberInputValueCaps;
		USHORT  NumberInputDataIndices;
		USHORT  NumberOutputButtonCaps;
		USHORT  NumberOutputValueCaps;
		USHORT  NumberOutputDataIndices;
		USHORT  NumberFeatureButtonCaps;
		USHORT  NumberFeatureValueCaps;
		USHORT  NumberFeatureDataIndices;
	} HIDP_CAPS, *PHIDP_CAPS;

	void __stdcall 
		HidD_GetHidGuid(OUT LPGUID  HidGuid);

	BOOLEAN __stdcall 
		HidD_GetAttributes(IN HANDLE  HidDeviceObject, OUT PHIDD_ATTRIBUTES  Attributes);

	BOOLEAN __stdcall 
		HidD_GetPreparsedData(IN HANDLE  HidDeviceObject, OUT PHIDP_PREPARSED_DATA  *PreparsedData);

	BOOLEAN __stdcall 
		HidD_FreePreparsedData(IN PHIDP_PREPARSED_DATA  PreparsedData);

	NTSTATUS __stdcall 
		HidP_GetCaps(IN PHIDP_PREPARSED_DATA  PreparsedData, OUT PHIDP_CAPS  Capabilities);

	BOOLEAN __stdcall 
		HidD_GetProductString(IN HANDLE  HidDeviceObject, OUT PVOID  Buffer, IN ULONG  BufferLength);

	BOOLEAN __stdcall 
		HidD_GetManufacturerString(IN HANDLE  HidDeviceObject, OUT PVOID  Buffer, IN ULONG  BufferLength);

	BOOLEAN __stdcall 
		HidD_GetSerialNumberString(IN HANDLE  HidDeviceObject, OUT PVOID  Buffer, IN ULONG  BufferLength);

	BOOLEAN __stdcall 
		HidD_SetOutputReport(IN HANDLE  HidDeviceObject, IN PVOID  ReportBuffer, IN ULONG  ReportBufferLength);

	BOOLEAN __stdcall 
		HidD_GetInputReport(IN HANDLE  HidDeviceObject, IN OUT  PVOID  ReportBuffer, IN ULONG  ReportBufferLength);
}

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "hid.lib")

#elif defined LINUX_GNU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libusb-1.0/libusb.h>

#define HID_TGT_VID			0x6A16
#define HID_TGT_PID			0x0144

#define HID_GET_REPORT_REQUEST_TYPE		0xA0	// bmRequestType for HID Get_Report
#define HID_GET_REPORT_REQUEST			0x01	// bRequest for HID Get_Report
#define HID_SET_REPORT_REQUEST_TYPE		0x20	// bmRequestType for HID Set_Report
#define HID_SET_REPORT_REQUEST			0x09	// bRequest for HID Set_Report

/*
#ifndef LPVOID
# define LPVOID			void*
#endif

#ifndef ULONG
# define ULONG			unsigned long
#endif
*/
typedef void*			LPVOID;
typedef unsigned long	ULONG;

#else
# error No target OS defined!!!
#endif   // End of WIN32

class CDkHID
{
private:
#ifdef WIN32
	
	HANDLE					_hHid;
	PHIDP_PREPARSED_DATA	_pPrepDat;
	
#elif defined LINUX_GNU

	libusb_context*			_pCtx;
	unsigned short			_uIdVend;
	unsigned short			_uIdProd;

#else
# error No target OS defined!!!
#endif
	
public:
	CDkHID(void);
	~CDkHID(void);

	bool Open();
	bool Open(unsigned short uVendId, unsigned short uProdId);
	void Close();
	
#ifdef WIN32
	bool GetAttributes(PHIDD_ATTRIBUTES	pHidAttr);	
	bool GetDevCaps(PHIDP_CAPS	pHidCaps);
#endif
	
	bool WriteReport(LPVOID pDat, ULONG uByteDatLen);
	bool ReadReport(LPVOID pDat, ULONG uButeDatLen);
};
