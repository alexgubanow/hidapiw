#pragma once
using namespace System;

public ref class hidDeviceInfo
{
public:
	hidDeviceInfo() : path(""), serial_number(""), manufacturer_string(""), product_string("") {}
	/** Platform-specific device path */
	String^ path;
	/** Device Vendor ID */
	unsigned short vendor_id;
	/** Device Product ID */
	unsigned short product_id;
	/** Serial Number */
	String^ serial_number;
	/** Device Release Number in binary-coded decimal,
		also known as Device Version Number */
	unsigned short release_number;
	/** Manufacturer String */
	String^ manufacturer_string;
	/** Product string */
	String^ product_string;
	/** Usage Page for this Device/Interface
		(Windows/Mac only). */
	unsigned short usage_page;
	/** Usage for this Device/Interface
		(Windows/Mac only).*/
	unsigned short usage;
	/** The USB interface which this logical device
		represents.

		* Valid on both Linux implementations in all cases.
		* Valid on the Windows implementation only if the device
		  contains more than one interface.
		* Valid on the Mac implementation if and only if the device
		  is a USB HID device. */
	int interface_number;
};

