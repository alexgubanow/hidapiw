using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace testConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            List<hidDeviceInfo> devs = new List<hidDeviceInfo>();
            hidapiw _hidapiw_native;
            byte[] data = new byte[5];
            try
            {
                _hidapiw_native = new hidapiw();
                _hidapiw_native.Enumerate(ref devs, 0, 0);

                foreach (var device in devs)
                {
                    Console.WriteLine("VID 0x{0:X} PID 0x{1:X} Manufacturer \"{2}\" Product \"{3}\"", 
                        device.vendor_id, device.product_id, device.manufacturer_string, device.product_string);
                }
                int devIdx = -1;
                _hidapiw_native.Open(ref devIdx, devs.First().vendor_id, devs.First().product_id);
                if (devIdx != -1)
                {
                    _hidapiw_native.Read(devIdx, ref data);
                    _hidapiw_native.Close(devIdx);
                }


                _hidapiw_native.Dispose();
            }
            catch (SEHException e)
            {
                if (e.StackTrace is string s)
                {
                    Console.WriteLine(s);
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.ReadKey();
        }
    }
}
