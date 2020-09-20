#pragma once
using namespace System;

public ref class hidDeviceInfo
{
	String^ _path;
	unsigned short _vendor_id;
	unsigned short _product_id;
	String^ _serial_number;
	unsigned short _release_number;
	String^ _manufacturer_string;
	String^ _product_string;
	unsigned short _usage_page;
	unsigned short _usage;
	int _interface_number;
public:
	hidDeviceInfo() : _path(""), _serial_number(""), _manufacturer_string(""), _product_string("") {}
	/** Platform-specific device path */
	property String^ Path
	{
		String^ get() { return _path; };
		void set(String^ value) { _path = value; };
	}
	/** Device Vendor ID */
	property unsigned short VendorId
	{
		unsigned short get() { return _vendor_id; };
		void set(unsigned short value) { _vendor_id = value; };
	}
	/** Device Product ID */
	property unsigned short ProductId
	{
		unsigned short get() { return _product_id; };
		void set(unsigned short value) { _product_id = value; };
	}
	/** Serial Number */
	property String^ SerialNumber
	{
		String^ get() { return _serial_number; };
		void set(String^ value) { _serial_number = value; };
	}
	/** Device Release Number in binary-coded decimal,
		also known as Device Version Number */
	property unsigned short ReleaseNumber
	{
		unsigned short get() { return _release_number; };
		void set(unsigned short value) { _release_number = value; };
	}
	/** Manufacturer String */
	property String^ Manufacturer
	{
		String^ get() { return _manufacturer_string; };
		void set(String^ value) { _manufacturer_string = value; };
	}
	/** Product string */
	property String^ Product
	{
		String^ get() { return _product_string; };
		void set(String^ value) { _product_string = value; };
	}
	/** Usage Page for this Device/Interface
		(Windows/Mac only). */
	property unsigned short UsagePage
	{
		unsigned short get() { return _usage_page; };
		void set(unsigned short value) { _usage_page = value; };
	}
	/** Usage for this Device/Interface
		(Windows/Mac only).*/
	property unsigned short Usage
	{
		unsigned short get() { return _usage; };
		void set(unsigned short value) { _usage = value; };
	}
	/** The USB interface which this logical device
		represents.

		* Valid on both Linux implementations in all cases.
		* Valid on the Windows implementation only if the device
		  contains more than one interface.
		* Valid on the Mac implementation if and only if the device
		  is a USB HID device. */
	property int InterfaceNumber
	{
		int get() { return _interface_number; };
		void set(int value) { _interface_number = value; };
	}
};

