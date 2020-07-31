#include "pch.h"
#define NATIVE_CODE
#include "hidapiw_native.h"

hidapiw_native::hidapiw_native() : _devs(nullptr)
{
	if (hid_init())
	{
		throw "failed to init hidapi";
	}
}

hidapiw_native::~hidapiw_native()
{
	if (_devs != nullptr)
	{
		hid_free_enumeration(_devs);
	}
	if (hid_exit())
	{
		throw "failed to exit hidapi";
	}
}

void hidapiw_native::enumerate(hid_device_info*& devs, unsigned short vendorID, unsigned short productID)
{
	_devs = hid_enumerate(vendorID, productID);
	devs = _devs;
}

void hidapiw_native::open(int& devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber)
{
	auto _dev = hid_open(vendorID, productID, serialNumber);
	if (_dev == nullptr)
	{
		throw hid_error(_dev);
	}
	std::lock_guard<std::recursive_mutex> lk(devMap_mutex);
	devIdx = devMap.size();
	devMap.insert(std::pair<hid_device*, int>(_dev, devIdx));
}
