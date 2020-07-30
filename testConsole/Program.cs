using System;

namespace testConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Hidapiw usbInterface = new Hidapiw(); 
            usbInterface.Enumerate();
            usbInterface.Dispose();
            Console.WriteLine("Hello World!");
        }
    }
}
