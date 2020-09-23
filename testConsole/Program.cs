using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Threading;

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
                    if (device.VendorId == 1155 && device.ProductId == 22352)
                    {
                        Console.WriteLine("VID 0x{0:X} PID 0x{1:X} Manufacturer \"{2}\" Product \"{3}\"",
                            device.VendorId, device.ProductId, device.Manufacturer, device.Product);
                        int devIdx = -1;
                        _hidapiw_native.Open(ref devIdx, device.VendorId, device.ProductId);
                        if (devIdx != -1)
                        {
                            _hidapiw_native.SetBlockingMode(devIdx, false);
                            int val = 0xD0006;
                            data[0] = 3;
                            data[1] = (byte)(val & 0xFF);
                            data[2] = (byte)((val >> 8) & 0xFF);
                            data[3] = (byte)((val >> 16) & 0xF);
                            _hidapiw_native.SendFeatureReport(devIdx, data);
                            //Console.WriteLine("{0} << Data written", BitConverter.ToString(data));
                            //data[0] = 3;
                            //_hidapiw_native.GetFeatureReport(devIdx, ref data);
                            //Console.WriteLine("Data received >> {0}", BitConverter.ToString(data));
                            //data[1] = 0;
                            //_hidapiw_native.SendFeatureReport(devIdx, data);
                            //Console.WriteLine("{0} << Data written", BitConverter.ToString(data));
                            //_hidapiw_native.GetFeatureReport(devIdx, ref data);
                            //Console.WriteLine("Data received >> {0}", BitConverter.ToString(data));
                            //Console.WriteLine("Sleep for 1 second.");
                            //Thread.Sleep(1000);
                            //data[1] = 3;
                            //_hidapiw_native.SendFeatureReport(devIdx, data);
                            //Console.WriteLine("{0} << Data written", BitConverter.ToString(data));
                            //_hidapiw_native.GetFeatureReport(devIdx, ref data);
                            //Console.WriteLine("Data received >> {0}", BitConverter.ToString(data));
                            //Console.WriteLine("Sleep for 1 second.");
                            //Thread.Sleep(1000);
                            //data[1] = 0;
                            //_hidapiw_native.SendFeatureReport(devIdx, data);
                            //Console.WriteLine("{0} << Data written", BitConverter.ToString(data));
                            //_hidapiw_native.GetFeatureReport(devIdx, ref data);
                            //Console.WriteLine("Data received >> {0}", BitConverter.ToString(data));
                            _hidapiw_native.Close(devIdx);
                        }
                    }
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
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.ReadKey();
        }
    }
}
