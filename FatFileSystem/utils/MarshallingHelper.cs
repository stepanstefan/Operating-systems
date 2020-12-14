﻿using System;
using System.Runtime.InteropServices;

namespace fat.utils
{
    public class MarshallingHelper
    {
        public static byte[] StructToBytes<T>(T data) where T: struct
        {
            byte[] rawData = new byte[Marshal.SizeOf(data)];
            GCHandle handle = GCHandle.Alloc(rawData, GCHandleType.Pinned);
            try
            {
                IntPtr rawDataPtr = handle.AddrOfPinnedObject();
                Marshal.StructureToPtr(data, rawDataPtr, false);
            }
            finally
            {
                handle.Free();
            }
            return rawData;
        }
    }
}