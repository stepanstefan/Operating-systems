using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Text;

namespace fat.FAT
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct FAT32_BootSector
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        private byte[] BPB_FATSz32;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BPB_ExtFlags;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BPB_FSVer;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        private byte[] BPB_RootClus;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BPB_FSInfo;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BPB_BkBootSec;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        private byte[] BPB_Reserved;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
        private byte[] BS_DrvNum;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
        private byte[] BS_Reserved1;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
        private byte[] BS_BootSig;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        private byte[] BS_VolID;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 11)]
        private byte[] BS_VolLab;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        private byte[] BS_FilSysType;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 420)]
        private byte[] BS_Empty;
        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BS_510_511_bytes;
        
        public FAT32_BootSector(string a)
        {
            BPB_FATSz32 = BitConverter.GetBytes((int) 32);
            BPB_ExtFlags = BitConverter.GetBytes((short) 4);
            BPB_FSVer = new byte[2];
            BPB_RootClus = BitConverter.GetBytes((int) 2);
            BPB_FSInfo = BitConverter.GetBytes((short) 1);
            BPB_BkBootSec = BitConverter.GetBytes((short) 6);
            BPB_Reserved = new byte[12];
            BS_DrvNum = BitConverter.GetBytes((byte) 0);
            BS_Reserved1 = BitConverter.GetBytes((byte) 0);
            BS_BootSig = BitConverter.GetBytes(0x29);
            BS_VolID = Encoding.ASCII.GetBytes("2a876СE1h");
            BS_VolLab = Encoding.ASCII.GetBytes("X boot disk");
            BS_FilSysType = Encoding.ASCII.GetBytes("FAT32   ");
            BS_Empty = new byte[420];
            BS_510_511_bytes = new[] {(byte)0x55, (byte)0xAA};
        }
    }
}