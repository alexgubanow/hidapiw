#include "hidapiw.h"
#include <string>

hidapiw::hidapiw()
{
	try
	{
		hidapiw_nativeInst = new hidapiw_native();
	}
	catch (const char* msg)
	{
		throw msg;
	}
}

hidapiw::~hidapiw() {
	if (m_isDisposed)
		return;

	// dispose managed data
	//delete m_managedData; 
	this->!hidapiw(); // call finalizer
	m_isDisposed = true;
}
void MarshalString(String^ src, std::wstring& dst) {
	const wchar_t* chars =
		(const wchar_t*)(Runtime::InteropServices::Marshal::StringToHGlobalUni(src)).ToPointer();
	dst = chars;
	Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
}
void hidapiw::Enumerate(System::Collections::Generic::List<hidDeviceInfo^>^% devs, unsigned short vendorID, unsigned short productID)
{
	struct hid_device_info* cur_dev, * _devs;
	hidapiw_nativeInst->enumerate(_devs, vendorID, productID);
	devs = gcnew System::Collections::Generic::List<hidDeviceInfo^>();
	cur_dev = _devs;
	while (cur_dev != nullptr)
	{
		auto tmp = gcnew hidDeviceInfo();
		tmp->InterfaceNumber = cur_dev->interface_number;
		tmp->Manufacturer = gcnew String(cur_dev->manufacturer_string);
		tmp->Path = gcnew String(cur_dev->path);
		tmp->ProductId = cur_dev->product_id;
		tmp->Product = gcnew String(cur_dev->product_string);
		tmp->ReleaseNumber = cur_dev->release_number;
		tmp->VendorId = cur_dev->vendor_id;
		tmp->SerialNumber = gcnew String(cur_dev->serial_number);
		devs->Add(tmp);
		cur_dev = cur_dev->next;
	}
	hidapiw_nativeInst->freeEnumerate(_devs);
}

void hidapiw::Open(int% devIdx, unsigned short vendorID, unsigned short productID, String^ serialNumber)
{
	int _devIdx = 0;
	try
	{
		if (serialNumber && serialNumber->Length > 0)
		{
			std::wstring wstr;
			MarshalString(serialNumber, wstr);
			hidapiw_nativeInst->open(_devIdx, vendorID, productID, wstr.c_str());
		}
		else
		{
			hidapiw_nativeInst->open(_devIdx, vendorID, productID);
		}
		devIdx = _devIdx;
	}
	catch (const char* msg)
	{
		throw msg;
	}
}

void hidapiw::Open(int% devIdx, unsigned short vendorID, unsigned short productID)
{
	Open(devIdx, vendorID, productID, nullptr);
}

void hidapiw::Close(int devIdx)
{
	hidapiw_nativeInst->close(devIdx);
}

void hidapiw::SetBlockingMode(int devIdx, bool isBlocking)
{
	hidapiw_nativeInst->set_nonblocking(devIdx, isBlocking ? 0 : 1);
}

void hidapiw::Read(int devIdx, array<unsigned char>^% data)
{
	pin_ptr<unsigned char> pinnedPtr = &data[0];
	unsigned char* nativePtr = pinnedPtr;
	hidapiw_nativeInst->read(devIdx, nativePtr, data->Length);
}

void hidapiw::ReadTimeout(int devIdx, array<unsigned char>^% data, int milliseconds)
{
	pin_ptr<unsigned char> pinnedPtr = &data[0];
	unsigned char* nativePtr = pinnedPtr;
	hidapiw_nativeInst->read_timeout(devIdx, nativePtr, data->Length, milliseconds);
}

void hidapiw::Write(int devIdx, array<unsigned char>^ data)
{
	pin_ptr<unsigned char> pinnedPtr = &data[0];
	unsigned char* nativePtr = pinnedPtr;
	hidapiw_nativeInst->write(devIdx, nativePtr, data->Length);
}

int hidapiw::SendFeatureReport(int devIdx, array<unsigned char>^ data)
{
	pin_ptr<unsigned char> pinnedPtr = &data[0];
	unsigned char* nativePtr = pinnedPtr;
	return hidapiw_nativeInst->send_feature_report(devIdx, nativePtr, data->Length);
}

int hidapiw::GetFeatureReport(int devIdx, array<unsigned char>^% data)
{
	pin_ptr<unsigned char> pinnedPtr = &data[0];
	unsigned char* nativePtr = pinnedPtr;
	return hidapiw_nativeInst->get_feature_report(devIdx, nativePtr, data->Length);
}
