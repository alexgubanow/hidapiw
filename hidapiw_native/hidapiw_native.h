#pragma once
#include <map>
#include <hidapi.h>
#ifdef NATIVE_CODE
#include <mutex>
#endif

class hidapiw_native
{
private:
	std::map<int, hid_device*> devMap;
#ifdef NATIVE_CODE
	//std::recursive_mutex devMap_mutex;
#endif

	void addDevice(hid_device* _dev, int& devIdx);
	int findDeviceInMap(int devIdx, hid_device*& _dev);
public:
	hidapiw_native();
	~hidapiw_native();
	void enumerate(struct hid_device_info*& devs, unsigned short vendorID, unsigned short productID);
	void freeEnumerate(hid_device_info*& devs);
	void open(int& devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber = nullptr);
	void openByPath(int& devIdx, const char* path);
	void close(int devIdx);


	int  write(int devIdx, const unsigned char* data, size_t length);
	int read_timeout(int devIdx, unsigned char*& data, size_t length, int milliseconds);
	int  read(int devIdx, unsigned char*& data, size_t length);
	int  set_nonblocking(int devIdx, int nonblock);
	int send_feature_report(int devIdx, const unsigned char* data, size_t length);
	int get_feature_report(int devIdx, unsigned char*& data, size_t length);
};

