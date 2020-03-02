#include "DkSys.h"
#include "Usb\HidHdr.h"

const uint8_t	gDevDesc[] =
{
	/*
		USB Device descriptor
	*/
	/* bLength				*/	0x12,
	/* bDescriptorType		*/	DESCTYPE_DEVICE,
	/* bcdUSB				*/	0x00, 0x02,
	/* bDeviceClass			*/	0x00,
	/* bDeviceSubClass		*/	0x00,
	/* bDeviceProtocol		*/	0x00,
	/* bMaxPacketSize		*/	0x40,
	/* idVendor				*/	0x16, 0x6A,
	/* idProduct			*/	0x51, 0x01,
	/* bcdDevice			*/	0x01, 0x01,
	/* iManufacturer		*/	0x01,
	/* iProduct				*/	0x02,
	/* iSerialNumber		*/	0x03,
	/* bNumConfigurations	*/	0x01
};

const uint8_t	gCfgDesc[] =
{
	/*
	  Configuration descriptor
	*/
	/* bLength					*/	0x09,
	/* bDescriptorType			*/	DESCTYPE_CONFIGURATION,
	/* wTotalLength				*/	0x22, 0x00,			/* 0x9(cfg) + 0x9(int) + 0x9(hid) + 0x7(Ep1) */
	/* bNumInterfaces			*/	0x01,
	/* bConfigurationValue		*/	0x01,
	/* iConfiguration			*/	0x00,
	/* bmAttributes				*/	0xE0,
	/* bMaxPower				*/	0x50,

	/*
	  Interface descriptor
	*/
	/* bLength					*/	0x09,
	/* bDescriptorType			*/	DESCTYPE_INTERFACE,
	/* bInterfaceNumber			*/	0x00,
	/* bAlternateSetting		*/	0x00,
	/* bNumEndPoints			*/	0x01,
	/* bInterfaceClass			*/	0x03,	/*** HID Interface class ***/
	/* bInterfaceSubClass		*/	0x00,
	/* bInterfaceProtocol		*/	0x00,
	/* iInterface				*/	0x00,

	/*
	  HID descriptor
	*/
	/* bLength				*/	0x09,
	/* bDescriptorType		*/	DESCTYPE_HID,	/*** HID descriptor type ***/
	/* bcdHID				*/	0x0B, 0x01,
	/* bCountryCode			*/	0x00,
	/* bNumDescriptors		*/	0x01,
	/* bDescriptorType		*/	DESCTYPE_HID_REPORT,	/*** HID Report descriptor type ***/
	/* wDescriptorLength	*/	0x1D, 0x00,				/*** 29 Decimal ***/

	/*
	  EndPoint descriptor 1
	*/
	/* bLength				*/	0x07,
	/* bDescriptorType		*/	DESCTYPE_ENDPOINT,
	/* bEndPointAddress		*/	0x81,		/* 10000001B -> EndPoint = 1, Dir. = IN */
	/* bmAttributes			*/	0x03,		/* Interupt transfer type */
	/* wMaxPacketSize		*/	0x40, 0x00,
	/* bInterval			*/	0xFF
};

const uint8_t gLangId[] =
{
	/*
	  String lang. ID
	*/
	/* bLength		*/	0x04,
	/* bDescType	*/	DESCTYPE_STRING,
	/* bString		*/	0x09, 0x04
};

const uint8_t gMfcStr[] =
{
	/*
	  String manufacturer
    */
	/* bLength		*/	16,
	/* bDescType	*/	DESCTYPE_STRING,
	/* bString		*/	
	'M', 0,
	'a', 0, 
	'p', 0, 
	'a', 0, 
	'g', 0,
	'a', 0, 
	'n', 0
};

const uint8_t gProdStr[] =
{
	/*
	  String product
	*/
	/* bLength		*/	32,
	/* bDescType	*/	DESCTYPE_STRING,
	/* bString		*/
	'D', 0,
	'e', 0,
	'k', 0,
	'a', 0,
	'\'', 0,
	's', 0,
	' ', 0,
	'G', 0,
	'a', 0,
	'm', 0,
	'e', 0,
	' ', 0,
	'P', 0,
	'a', 0,
	'd', 0
};

const uint8_t gSerStr[] =
{
	/*
	  String serial
	*/
	/* bLength		*/	18,
	/* bDescType	*/	DESCTYPE_STRING,
	/* bString		*/
	'D', 0, 
	'K', 0, 
	'2', 0, 
	'0', 0, 
	'1', 0, 
	'7', 0, 
	'9', 0, 
	'1', 0
};

const uint8_t gGamePadRepDesc[29] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x95, 0x04,                    //   REPORT_COUNT (4)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x04,                    //   USAGE_MAXIMUM (Button 4)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x04,                    //   REPORT_SIZE (4)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0xc0                           // END_COLLECTION
};
