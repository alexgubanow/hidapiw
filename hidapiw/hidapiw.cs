using System;
using System.Collections.Generic;

public class Hidapiw : IDisposable
{
    private readonly hidapiw_native _hidapiw_native;
    private List<hidDeviceInfo> devs;
    private bool disposedValue;

    public Hidapiw()
    { _hidapiw_native = new hidapiw_native(); }
    public void Enumerate(ushort vendorID = 0, ushort productID = 0)
    {
        _hidapiw_native.enumerate(ref devs, vendorID, productID);
    }

    protected virtual void Dispose(bool disposing)
    {
        if (!disposedValue)
        {
            if (disposing)
            {
                // TODO: dispose managed state (managed objects)
                devs.Clear();
            }

            // TODO: free unmanaged resources (unmanaged objects) and override finalizer
            _hidapiw_native.Dispose();
            // TODO: set large fields to null
            disposedValue = true;
        }
    }

    // // TODO: override finalizer only if 'Dispose(bool disposing)' has code to free unmanaged resources
    // ~Hidapiw()
    // {
    //     // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
    //     Dispose(disposing: false);
    // }

    public void Dispose()
    {
        // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
        Dispose(disposing: true);
        GC.SuppressFinalize(this);
    }
}