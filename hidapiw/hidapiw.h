#pragma once

using namespace System;
#include "hidDeviceInfo.hpp"
#include "..\hidapiw_native\hidapiw_native.h"

public ref class hidapiw : IDisposable
{
private:
	hidapiw_native* nativePtr;
	bool m_isDisposed; // must be set to false
public:
	hidapiw();
	~hidapiw();

	// Finalizer
	!hidapiw() {
		// free unmanaged data
		if (nativePtr != nullptr)
		{
			delete nativePtr;
			nativePtr = nullptr;
		} 
	}
	void enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID);
	void open(int% devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber);
};