#include "pch.h"

#include "hidapiw_native.h"

void hidapiw_native::enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID)
{
	_devs = hid_enumerate(vendorID, productID);
	System::Collections::Generic::List<hidDeviceInfo^>^ list = gcnew System::Collections::Generic::List<hidDeviceInfo^>();
	while (_devs->next != nullptr)
	{
		auto tmp = gcnew hidDeviceInfo();
		tmp->interface_number = _devs->interface_number;
		//tmp->manufacturer_string = String(_devs->manufacturer_string);
		//tmp->path = String(_devs->path);
		tmp->product_id = _devs->product_id;
		//tmp->product_string = (String)_devs->product_string;
		tmp->release_number = _devs->release_number;
		//tmp->serial_number = _devs->serial_number;
		devs->Add(tmp);
	}
}
