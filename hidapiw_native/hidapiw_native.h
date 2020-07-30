#pragma once

using namespace System;
#include <cliext/list>
#include "hidapi.h"
#include "hidDeviceInfo.hpp"
public ref class hidapiw_native : IDisposable
{
private:
	struct hid_device_info* _devs;
	bool m_isDisposed; // must be set to false
public:
	hidapiw_native();
	~hidapiw_native();

	// Finalizer
	!hidapiw_native() {
		// free unmanaged data
		if (_devs != nullptr)
		{
			hid_free_enumeration(_devs);
		}
		if (hid_exit())
		{
			throw "failed to exit hidapi";
		} 
	}
	void enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID);
};