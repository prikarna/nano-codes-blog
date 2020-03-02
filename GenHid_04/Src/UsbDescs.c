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
	/* idVendor				*/	0x17, 0x6A,
	/* idProduct			*/	0x0A, 0x01,
	/* bcdDevice			*/	0x01, 0x01,
	/* iManufacturer		*/	0x01,
	/* iProduct				*/	0x02,
	/* iSerialNumber		*/	0x03,
	/* bNumConfigurations	*/	0x01
};