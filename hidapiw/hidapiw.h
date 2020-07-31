#pragma once

using namespace System;
#include "hidDeviceInfo.hpp"
#include "..\hidapiw_native\hidapiw_native.h"

public ref class hidapiw : IDisposable
{
private:
	hidapiw_native* hidapiw_nativeInst;
	bool m_isDisposed; // must be set to false
public:
	hidapiw();
	~hidapiw();

	// Finalizer
	!hidapiw() {
		// free unmanaged data
		if (hidapiw_nativeInst != nullptr)
		{
			try
			{
				delete hidapiw_nativeInst;
				hidapiw_nativeInst = nullptr;
			}
			catch (const char* msg)
			{
				throw msg;
			}
		} 
	}
	void Enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID);
	void Open(int% devIdx, unsigned short vendorID, unsigned short productID, const wchar_t* serialNumber);
	void Open(int% devIdx, unsigned short vendorID, unsigned short productID);
	void Close(int devIdx);
	void Read(int devIdx, array<unsigned char>^% data);
	void Write(int devIdx, array<unsigned char>^ data);
};