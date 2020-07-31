#define NATIVE_CODE
#include "hidapiw_native.h"

hidapiw_native::hidapiw_native()
{
	if (hid_init())
	{
		throw "failed to init hidapi";
	}
}

hidapiw_native::~hidapiw_native()
{
	hid_exit();
}

void hidapiw_native::enumerate(hid_device_info*& devs, unsigned short vendorID, unsigned short productID)
{
	devs = hid_enumerate(vendorID, productID);
}

void hidapiw_native::freeEnumerate(hid_device_info*& devs)
{
	hid_free_enumeration(devs);
}

void hidapiw_native::open(int& devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber)
{
	auto _dev = hid_open(vendorID, productID, serialNumber);
	if (_dev == nullptr)
	{
		throw hid_error(_dev);
	}
	addDevice(_dev, devIdx);
}

void hidapiw_native::openByPath(int& devIdx, const char* path)
{
	auto _dev = hid_open_path(path);
	if (_dev == nullptr)
	{
		throw hid_error(_dev);
	}
	addDevice(_dev, devIdx);
}

void hidapiw_native::close(int devIdx)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		hid_close(_dev);
		devMap.erase(devIdx);
	}
}

int hidapiw_native::findDeviceInMap(int devIdx, hid_device*& _dev)
{
	//std::lock_guard<std::recursive_mutex> guard(devMap_mutex);
	auto itr = devMap.find(devIdx);
	if (itr != devMap.end())
	{
		_dev = itr->second;
		return 1;
	}
	return 0;
}

int hidapiw_native::write(int devIdx, const unsigned char* data, size_t length)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		return hid_write(_dev, data, length);
	}
	return 1;
}

int hidapiw_native::read_timeout(int devIdx, unsigned char*& data, size_t length, int milliseconds)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		int ret = hid_read_timeout(_dev, data, length, milliseconds);
		int ver = data[1];
		return ret;
	}
	return 1;
}

int hidapiw_native::read(int devIdx, unsigned char*& data, size_t length)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		return hid_read(_dev, data, length);
	}
	return 1;
}

int hidapiw_native::set_nonblocking(int devIdx, int nonblock)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		return hid_set_nonblocking(_dev, nonblock);
	}
	return 1;
}

int hidapiw_native::send_feature_report(int devIdx, const unsigned char* data, size_t length)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		return hid_send_feature_report(_dev, data, length);
	}
	return 1;
}

int hidapiw_native::get_feature_report(int devIdx, unsigned char*& data, size_t length)
{
	hid_device* _dev;
	if (findDeviceInMap(devIdx, _dev))
	{
		return hid_get_feature_report(_dev, data, length);
	}
	return 1;
}

void hidapiw_native::addDevice(hid_device* _dev, int& devIdx)
{
	/*std::lock_guard<std::recursive_mutex> guard(devMap_mutex);*/
	devIdx = (int)devMap.size();
	devMap.insert(std::pair<int, hid_device*>(devIdx, _dev));
}
