using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace testConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Hidapiw usbInterface;
            try
            {
                usbInterface = new Hidapiw();
                usbInterface.Enumerate();

                foreach (var device in usbInterface.devs)
                {
                    Console.WriteLine("VID 0x{0:X} PID 0x{1:X}", device.vendor_id, device.product_id);
                }
                usbInterface.Dispose();
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
