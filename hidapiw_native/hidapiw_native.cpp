#include "pch.h"

#include "hidapiw_native.h"

inline hidapiw_native::hidapiw_native()
{
	if (hid_init())
	{
		throw "failed to init hidapi";
	}
}

inline hidapiw_native::~hidapiw_native() {
	if (m_isDisposed)
		return;

	// dispose managed data
	//delete m_managedData; 
	this->!hidapiw_native(); // call finalizer
	m_isDisposed = true;
}

void hidapiw_native::enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID)
{
	_devs = hid_enumerate(vendorID, productID);
	devs = gcnew System::Collections::Generic::List<hidDeviceInfo^>();
	struct hid_device_info* cur_dev = _devs;
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
