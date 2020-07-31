#pragma once
#include <map>
#include <hidapi.h>
#ifdef NATIVE_CODE
#include <mutex>
#endif

class hidapiw_native
{
private:
	std::map<hid_device*, int> devMap;
#ifdef NATIVE_CODE
	std::recursive_mutex devMap_mutex;
#endif
	struct hid_device_info* _devs;
public:
	hidapiw_native();
	~hidapiw_native();
	void enumerate(struct hid_device_info*& devs, unsigned short vendorID, unsigned short productID);
	void open(int& devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber = nullptr);
};

