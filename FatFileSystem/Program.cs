﻿using System;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using fat.FAT;
using fat.utils;

namespace fat
{
    class Program
    {
        static void Main()
        {
            byte[] BootSector = MarshallingHelper.StructToBytes(new BootSector_BPBStructure(FatType.Fat16));
            byte[] Fat12_16 = MarshallingHelper.StructToBytes(new FAT12_16_BootSector(""));
            
            File.WriteAllBytes("test.img", BootSector.Concat(Fat12_16).ToArray());
        }
    }
}