#ifndef DK_USBHDR_H
#define DK_USBHDR_H

typedef struct _USB_SETUP {
	unsigned char	bmRequestType;
	unsigned char	bRequest;
	unsigned short	wValue;
	unsigned short	wIndex;
	unsigned short	wLength;
} USB_SETUP, *PUSB_SETUP;

#define REQTYPE_STANDARD					0
#define REQTYPE_CLASS						1
#define REQTYPE_VENDOR						2
#define REQTYPE_RESERVED					3

#define STDREQ_GET_STATUS					0
#define STDREQ_CLEAR_FEATURE				1
#define STDREQ_SET_FEATURE					3
#define STDREQ_SET_ADDRESS					5
#define STDREQ_GET_DESCRIPTOR				6
#define STDREQ_SET_DESCRIPTOR				7
#define STDREQ_GET_CONFIGURATION			8
#define STDREQ_SET_CONFIGURATION			9
#define STDREQ_GET_INTERFACE				10
#define STDREQ_SET_INTERFACE				11
#define STDREQ_SYNCH_FRAME					12

#define DESCTYPE_DEVICE						1
#define DESCTYPE_CONFIGURATION				2
#define DESCTYPE_STRING						3
#define DESCTYPE_INTERFACE					4
#define DESCTYPE_ENDPOINT					5
#define DESCTYPE_DEVICE_QUALIFIER			6
#define DESCTYPE_OTHER_SPEED_CONFIGURATION	7
#define DESCTYPE_INTERFACE_POWER			8
#define DESCTYPE_OTG						9
#define DESCTYPE_DEBUG						10
#define DESCTYPE_INTERFACE_ASSOCIATION		11

typedef struct _USB_DEVICE_DESCRIPTOR {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			bcdUSB;
	unsigned char			bDeviceClass;
	unsigned char			bDeviceSubClass;
	unsigned char			bDeviceProtocol;
	unsigned char			bMaxPacketSize0;
	unsigned short			idVendor;
	unsigned short			idProduct;
	unsigned short			bcdDevice;
	unsigned char			iManufacturer;
	unsigned char			iProduct;
	unsigned char			iSerialNumber;
	unsigned char			bNumConfigurations;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;

typedef struct _USB_DEVICE_QUALIFIER {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			bcdUSB;
	unsigned char			bDeviceClass;
	unsigned char			bDeviceSubClass;
	unsigned char			bDeviceProtocol;
	unsigned char			bMaxPacketSize0;
	unsigned char			bNumConfigurations;
	unsigned char			bReserved;
} USB_DEVICE_QUALIFIER, *PUSB_DEVICE_QUALIFIER;

typedef struct _USB_CONFIGURATION_DESCRIPTOR {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			wTotalLength;
	unsigned char			bNumInterfaces;
	unsigned char			bConfigurationValue;
	unsigned char			iConfiguration;
	unsigned char			bmAttributes;
	unsigned char			bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR, *PUSB_CONFIGURATION_DESCRIPTOR;

typedef struct _USB_OTHER_SPEED_CONFIGURATION {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			wTotalLength;
	unsigned char			bNumInterfaces;
	unsigned char			bConfigurationValue;
	unsigned char			iConfiguration;
	unsigned char			bmAttributes;
	unsigned char			bmMaxPower;
} USB_OTHER_SPEED_CONFIGURATION, *PUSB_OTHER_SPEED_CONFIGURATION;

typedef struct _USB_INTERFACE_DESCRIPTOR {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned char			bInterfaceNumber;
	unsigned char			bAlternateSetting;
	unsigned char			bNumEndPoints;
	unsigned char			bInterfaceClass;
	unsigned char			bInterfaceSubClass;
	unsigned char			bInterfaceProtocol;
	unsigned char			iInterface;
} USB_INTERFACE_DESCRIPTOR, *PUSB_INTERFACE_DESCRIPTOR;

typedef struct _USB_ENDPOINT_DESCRIPTOR {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned char			bEndPointAddress;
	unsigned char			bmAttributes;
	unsigned short			wMaxPacketSize;
	unsigned char			bInterval;
} USB_ENDPOINT_DESCRIPTOR, *PUSB_ENDPOINT_DESCRIPTOR;

#define USB_MAX_SUPPORTED_LANG		3

typedef struct _USB_STRING_DESCRIPTION {
	unsigned char			bLength;
	unsigned char			bDescriptorType;
	unsigned short			wLANGID[USB_MAX_SUPPORTED_LANG];
} USB_STRING_DESCRIPTOR, *PUSB_STRING_DESCRIPTOR;

//typedef struct _USB_STRING_DESCRIPTOR {
//	unsigned char			bLength;
//	unsigned char			bDescriptorType;
//	unsigned 

#endif  // End of DK_USBHDR_H
