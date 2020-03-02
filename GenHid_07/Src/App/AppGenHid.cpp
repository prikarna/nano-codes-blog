#include <stdio.h>
#include <stdlib.h>

#include "DkHID.h"

#define HID_PRODUCT_ID			0x0144
#define HID_VENDOR_ID			0x6A16

int __cdecl main(int argc, char* argv[])
{
	printf("Program to test Generic HID, Ver. 1.0.1.1\r\n");
	
	CDkHID	Hid;
	HIDD_ATTRIBUTES	sAttr = {0};
	HIDP_CAPS		sCap = {0};
	char			buf[65] = {0};

	bool fRes = Hid.Open(HID_VENDOR_ID, HID_PRODUCT_ID);
	if (!fRes) {
		printf("Error open Generic HID!\r\n");
		getchar();
		return -1;
	}

	fRes = Hid.GetAttributes(&sAttr);
	if (!fRes) {
		printf("Error get device attributes!\r\n");
		goto Cleanup;
	}
	printf("******** Attributes\r\n");
	printf("\tVendor ID\t: %d (0x%X)\r\n", sAttr.VendorID, sAttr.VendorID);
	printf("\tProduct ID\t: %d (0x%X)\r\n", sAttr.ProductID, sAttr.ProductID);
	printf("\tVersion Number\t: %d (0x%X)\r\n", sAttr.VersionNumber, sAttr.VersionNumber);
	printf("----------------------------------------------------\r\n");

	fRes = Hid.GetDevCaps(&sCap);
	if (!fRes) {
		printf("Error get device capabilities!\r\n");
		goto Cleanup;
	}
	printf("******** Capabilities\r\n");
	printf("\tUsagePage\t\t\t: %d (0x%X)\r\n", sCap.UsagePage, sCap.UsagePage);
	printf("\tUsage\t\t\t\t: %d (0x%X)\r\n", sCap.Usage, sCap.Usage);
	printf("\tInputReportByteLength\t\t: %d (0x%X)\r\n", sCap.InputReportByteLength, sCap.InputReportByteLength);
	printf("\tOutputReportByteLength\t\t: %d (0x%X)\r\n", sCap.OutputReportByteLength, sCap.OutputReportByteLength);
	printf("\tFeatureReportByteLength\t\t: %d (0x%X)\r\n", sCap.FeatureReportByteLength, sCap.FeatureReportByteLength);
	printf("\tNumberLinkCollectionNodes\t: %d (0x%X)\r\n", sCap.NumberLinkCollectionNodes, sCap.NumberLinkCollectionNodes);
	printf("\tNumberInputButtonCaps\t\t: %d (0x%X)\r\n", sCap.NumberInputButtonCaps, sCap.NumberInputButtonCaps);
	printf("\tNumberInputValueCaps\t\t: %d (0x%X)\r\n", sCap.NumberInputValueCaps, sCap.NumberInputValueCaps);
	printf("\tNumberInputDataIndices\t\t: %d (0x%X)\r\n", sCap.NumberInputDataIndices, sCap.NumberInputDataIndices);
	printf("\tNumberOutputButtonCaps\t\t: %d (0x%X)\r\n", sCap.NumberOutputButtonCaps, sCap.NumberOutputButtonCaps);
	printf("\tNumberOutputValueCaps\t\t: %d (0x%X)\r\n", sCap.NumberOutputValueCaps, sCap.NumberOutputValueCaps);
	printf("\tNumberOutputDataIndices\t\t: %d (0x%X)\r\n", sCap.NumberOutputDataIndices, sCap.NumberOutputDataIndices);
	printf("\tNumberFeatureButtonCaps\t\t: %d (0x%X)\r\n", sCap.NumberFeatureButtonCaps, sCap.NumberFeatureButtonCaps);
	printf("\tNumberFeatureValueCaps\t\t: %d (0x%X)\r\n", sCap.NumberFeatureValueCaps, sCap.NumberFeatureValueCaps);
	printf("\tNumberFeatureDataIndices\t: %d (0x%X)\r\n", sCap.NumberFeatureDataIndices, sCap.NumberFeatureDataIndices);
	printf("----------------------------------------------------\r\n");

	buf[0] = 0;
	sprintf_s(&buf[1], (sizeof(buf) - 1), "This is comming from HOST (0123456789)\0");
	fRes = Hid.WriteReport((LPVOID) &buf[0], sizeof(buf));
	if (!fRes) {
		printf("Error write report to generic HID! (sizeof(buf) = %d)\r\n", sizeof(buf));
		goto Cleanup;
	}
	printf("Successfuly write report to generic HID!\r\n");

	RtlZeroMemory(&buf[0], sizeof(buf));
	fRes = Hid.ReadReport((LPVOID) &buf[0], sizeof(buf));
	if (!fRes) {
		printf("Error read report from generic HID! (sizeof(buf) = %d)\r\n", sizeof(buf));
		goto Cleanup;
	}
	printf("Successfuly read report from generic HID!\r\n");
	printf("Generic HID sent: %s\r\n", &buf[1]);

Cleanup:
	Hid.Close();
	getchar();
	return 0;
}