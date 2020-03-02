#ifndef DK_HIDHDR_H
#define DK_HIDHDR_H

#include "USBHdr.h"

#define DESCTYPE_HID			0x21
#define DESCTYPE_HID_REPORT		0x22
#define DESCTYPE_HID_PHYSICAL	0x23

#define REQTYPE_HID_GET_REPORT		0x01
#define REQTYPE_HID_GET_IDLE		0x02
#define REQTYPE_HID_GET_PROTOCOL	0x03
#define REQTYPE_HID_SET_REPORT		0x09
#define REQTYPE_HID_SET_IDLE		0x0A
#define REQTYPE_HID_SET_PROTOCOL	0x0B

typedef struct _HID_DESCRIPTOR {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			bcdHID;
	unsigned char			bCountryCode;
	unsigned char			bNumDescriptors;
	unsigned char			bDescriptorType0;
	unsigned short			wDescriptorLength;			
} HID_DESCRIPTOR, *PHID_DESCRIPTOR;

#endif   // End of DK_HIDHDR_H
