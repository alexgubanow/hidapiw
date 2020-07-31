using System;
using System.Collections.Generic;
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
            try
            {
                _hidapiw_native = new hidapiw();
                _hidapiw_native.enumerate(ref devs, 0, 0);

                foreach (var device in devs)
                {
                    Console.WriteLine("VID 0x{0:X} PID 0x{1:X}", device.vendor_id, device.product_id);
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
            Console.ReadKey();
        }
    }
}
