#include "pch.h"
#include "hidapiw.h"

hidapiw::hidapiw()
{
	nativePtr = new hidapiw_native();
}

hidapiw::~hidapiw() {
	if (m_isDisposed)
		return;

	// dispose managed data
	//delete m_managedData; 
	this->!hidapiw(); // call finalizer
	m_isDisposed = true;
}

void hidapiw::enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID)
{
	struct hid_device_info* cur_dev, *_devs;
	nativePtr->enumerate(_devs, vendorID, productID);
	devs = gcnew System::Collections::Generic::List<hidDeviceInfo^>();
	cur_dev = _devs;
	while (cur_dev != nullptr)
	{
		auto tmp = gcnew hidDeviceInfo();
		tmp->interface_number = cur_dev->interface_number;
		//tmp->manufacturer_string = String(_devs->manufacturer_string);
		//tmp->path = String(_devs->path);
		tmp->product_id = cur_dev->product_id;
		//tmp->product_string = (String)_devs->product_string;
		tmp->release_number = cur_dev->release_number;
		tmp->vendor_id = cur_dev->vendor_id;
		//tmp->serial_number = _devs->serial_number;
		devs->Add(tmp);
		cur_dev = cur_dev->next;
	}
}

void hidapiw::open(int% devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber)
{
	int _devIdx = 0;
	nativePtr->open(_devIdx, vendorID, productID);
	devIdx = _devIdx;
}
