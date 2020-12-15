using System;
using System.Runtime.InteropServices;
using System.Text;

namespace fat.FAT
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct FAT12_16_BootSector
    {
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

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 448)]
        private byte[] BS_Empty;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        private byte[] BS_510_511_bytes;
        public FAT12_16_BootSector(string a)
        {
            BS_DrvNum = BitConverter.GetBytes((byte) 0);
            BS_Reserved1 = BitConverter.GetBytes((byte) 0);
            BS_BootSig = BitConverter.GetBytes(0x29);
            BS_VolID = Encoding.ASCII.GetBytes("2a876СE1h");
            BS_VolLab = Encoding.ASCII.GetBytes("X boot disk");
            BS_FilSysType = Encoding.ASCII.GetBytes("FAT16   ");
            BS_Empty = new byte[448];
            BS_510_511_bytes = new[] {(byte)0x55, (byte)0xAA};
        }
    }
}