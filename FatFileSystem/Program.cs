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
            byte[] BPB_RootEntCnt, BPB_BytsPerSec, FATSz, TotSec, BPB_ResvdCnt, BPB_NumFATs;
            
            byte[] BootSector = MarshallingHelper.StructToBytes(new BootSector_BPBStructure(FatType.Fat16));
            byte[] Fat12_16 = MarshallingHelper.StructToBytes(new FAT12_16_BootSector(""));
            File.WriteAllBytes("fat16.img", BootSector.Concat(Fat12_16).ToArray());
            
            byte[] BootSector1 = MarshallingHelper.StructToBytes(new BootSector_BPBStructure(FatType.Fat32));
            byte[] Fat32 = MarshallingHelper.StructToBytes(new FAT32_BootSector(""));
            File.WriteAllBytes("fat32.img", BootSector.Concat(Fat32).ToArray());
        }
    }
}