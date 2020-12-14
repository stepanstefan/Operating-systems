﻿using System;
using System.Runtime.InteropServices;
using System.Text;

namespace fat.FAT
{

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
        public struct BootSector_BPBStructure
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            private byte[] BS_jmpBoot;
 
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            private byte[] BS_OEMName;
 
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_BytsPerSec;
 
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
            private byte[] BPB_SecPerClus;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_RsvdSecCnt;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
            private byte[] BPB_NumFATs;
 
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_RootEntCnt;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_TotSec16;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
            private byte[] BPB_Media;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_FATSz16;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_SecPerTrk;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
            private byte[] BPB_NumHeads;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            private byte[] BPB_HiddSec;
            
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            private byte[] BPB_TotSec32;

            public BootSector_BPBStructure(FatType fatType)
              {
                  BS_jmpBoot = new byte[]{0xEB, 0x3C, 0x90};
                  BS_OEMName = Encoding.ASCII.GetBytes("MSWIN4.1");
                  BPB_BytsPerSec = BitConverter.GetBytes((short) 512);
                  BPB_SecPerClus = BitConverter.GetBytes((byte) 2);
                  BPB_NumFATs = BitConverter.GetBytes((byte) 2);
                  BPB_Media = new byte[] {0xF8};
                  BPB_SecPerTrk = BitConverter.GetBytes((short) 18);
                  BPB_NumHeads = BitConverter.GetBytes((short) 2);
                  BPB_HiddSec = BitConverter.GetBytes((int) 0);
                  if (fatType == FatType.Fat12 || fatType == FatType.Fat16)
                  {
                      BPB_RsvdSecCnt = BitConverter.GetBytes((short) 1); //1 - для fat16/12, 32 - для fat32
                      BPB_RootEntCnt = BitConverter.GetBytes((short) 224); //0 для fat32, значение * 32 || BPB_BytsPerSec для fat16/12
                      BPB_TotSec16 = BitConverter.GetBytes((short) 2880); //если 0, то BPB_TotSec32 != 0
                      BPB_FATSz16 = BitConverter.GetBytes((short) 9); //для FAT32 => 0
                      BPB_TotSec32 = BitConverter.GetBytes((int) 0); //Если BPB_TotSec16 != 0  - > BPB_TotSec32 = 0
                  }
                  else
                  {
                      BPB_RsvdSecCnt = BitConverter.GetBytes((short) 32); //1 - для fat16/12, 32 - для fat32
                      BPB_RootEntCnt = BitConverter.GetBytes((short) 0); //0 для fat32, значение * 32 || BPB_BytsPerSec для fat16/12
                      BPB_TotSec16 = BitConverter.GetBytes((short) 0); //если 0, то BPB_TotSec32 != 0
                      BPB_FATSz16 = BitConverter.GetBytes((short) 0); //для FAT32 => 0
                      BPB_TotSec32 = BitConverter.GetBytes((int) 2880); //Если BPB_TotSec16 != 0  - > BPB_TotSec32 = 0
                  }
              }
        }
}