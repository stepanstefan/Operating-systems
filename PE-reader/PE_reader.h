#include <iostream>
#include <fstream>
#include <cstring>

typedef struct PE_Data_Directory {
    uint32_t RVA;
    uint32_t Size;
}PE_Data_Directory;

struct PE_OPTIONAL_HEADER {
    // Standard fields.

    uint16_t    Magic;
    char    MajorLinkerVersion;
    char    MinorLinkerVersion;
    uint32_t   SizeOfCode;
    uint32_t   SizeOfInitializedData;
    uint32_t   SizeOfUninitializedData;
    uint32_t   AddressOfEntryPoint;
    uint32_t   BaseOfCode;
    uint32_t   BaseOfData;

    // NT additional fields.

    uint32_t   ImageBase;
    uint32_t   SectionAlignment;
    uint32_t   FileAlignment;
    uint16_t    MajorOperatingSystemVersion;
    uint16_t    MinorOperatingSystemVersion;
    uint16_t    MajorImageVersion;
    uint16_t    MinorImageVersion;
    uint16_t    MajorSubsystemVersion;
    uint16_t    MinorSubsystemVersion;
    uint32_t   Win32VersionValue;
    uint32_t   SizeOfImage;
    uint32_t   SizeOfHeaders;
    uint32_t   CheckSum;
    uint16_t    Subsystem;
    uint16_t    DllCharacteristics;
    uint32_t   SizeOfStackReserve;
    uint32_t   SizeOfStackCommit;
    uint32_t   SizeOfHeapReserve;
    uint32_t   SizeOfHeapCommit;
    uint32_t   LoaderFlags;
    uint32_t   NumberOfRvaAndSizes;

    //DataDirectories
    PE_Data_Directory ExportTable;
    PE_Data_Directory ImportTable;
    PE_Data_Directory ResourceTable;
    PE_Data_Directory ExceptionTable;
    PE_Data_Directory CertificateTable;
    PE_Data_Directory BaseRelocationTable;
    PE_Data_Directory DebugTable;
    PE_Data_Directory ArchitectureTable;
    PE_Data_Directory GlobalTable;
    PE_Data_Directory ThreadTable;
    PE_Data_Directory LoadTable;
    PE_Data_Directory BoundTable;
    PE_Data_Directory ImportAddressTable;
    PE_Data_Directory DelayTable;
    PE_Data_Directory CLRTable;
    PE_Data_Directory Reserved;

};

struct PE_OPTIONAL_HEADER64 {
    // Standard fields.

    uint16_t        Magic;
    char        MajorLinkerVersion;
    char        MinorLinkerVersion;
    uint32_t       SizeOfCode;
    uint32_t       SizeOfInitializedData;
    uint32_t       SizeOfUninitializedData;
    uint32_t       AddressOfEntryPoint;
    uint32_t       BaseOfCode;
    uint32_t       BaseOfData;

    // NT additional fields.

    uint64_t   ImageBase;
    uint32_t       SectionAlignment;
    uint32_t       FileAlignment;
    uint16_t        MajorOperatingSystemVersion;
    uint16_t        MinorOperatingSystemVersion;
    uint16_t        MajorImageVersion;
    uint16_t        MinorImageVersion;
    uint16_t        MajorSubsystemVersion;
    uint16_t        MinorSubsystemVersion;
    uint32_t       Win32VersionValue;
    uint32_t       SizeOfImage;
    uint32_t       SizeOfHeaders;
    uint32_t       CheckSum;
    uint16_t        Subsystem;
    uint16_t        DllCharacteristics;
    uint64_t   SizeOfStackReserve;
    uint64_t   SizeOfStackCommit;
    uint64_t   SizeOfHeapReserve;
    uint64_t   SizeOfHeapCommit;
    uint32_t       LoaderFlags;
    uint32_t       NumberOfRvaAndSizes;

    //DataDirectories
    PE_Data_Directory ExportTable;
    PE_Data_Directory ImportTable;
    PE_Data_Directory ResourceTable;
    PE_Data_Directory ExceptionTable;
    PE_Data_Directory CertificateTable;
    PE_Data_Directory BaseRelocationTable;
    PE_Data_Directory DebugTable;
    PE_Data_Directory ArchitectureTable;
    PE_Data_Directory GlobalTable;
    PE_Data_Directory ThreadTable;
    PE_Data_Directory LoadTable;
    PE_Data_Directory BoundTable;
    PE_Data_Directory ImportAddressTable;
    PE_Data_Directory DelayTable;
    PE_Data_Directory CLRTable;
    PE_Data_Directory Reserved;

};

struct PE_header {
    uint32_t Sig;
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct PE_SECTION_HEADER {
    int64_t Name;
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
};

struct PE_SYMBOL_TABLE{
    int64_t Name;
    uint32_t Value;
    uint16_t SectionNumber;
    uint16_t Type;
    char StorageClass;
    char NumberOfAusSymbols;
};

struct BASE_RELOCATION_BLOCK {
    uint32_t PageRVA;
    uint32_t BlockSize;
};

struct PE_EXPORT_DIRECTORY_TABLE {
    uint32_t ExportFlags;
    uint32_t Time;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint32_t NameRVA;
    uint32_t OrdinalBase;
    uint32_t AddressTableEntries;
    uint32_t NumberOfNamePointers;
    uint32_t ExportAddressTableRva;
    uint32_t NamePointerRVA;
    uint32_t OrdinalTableRVA;
};

class PE_reader {
public:
    explicit PE_reader(const char* path_name);
    ~PE_reader() = default;

    void get_pe_header() const;
    void get_pe_sections();
    void get_pe_symbols();
    void get_pe_relocations();
    void get_pe_edata();

    uint32_t defSection(uint32_t rva);
    uint32_t align_up(uint32_t x, uint32_t align);
    uint32_t align_down(uint32_t x, uint32_t align);
    uint32_t rvaToOff(uint32_t rva);

    union {
        char* e_lfanew;
        int* num;
    }Dos_Head{};

    union {
        PE_header* PeHeader;
        char* ntData;
    }Pe_NtHeader{};

    union
    {
        PE_OPTIONAL_HEADER* PeOpHeader;
        char* ntData;
    }Pe_Optional{};

    union
    {
        PE_OPTIONAL_HEADER64* PeOpHeader;
        char* ntData;
    }Pe_Optional64{};

    union {
        PE_SECTION_HEADER* PeSecHeader;
        char* ntData;
    }Pe_Section{};

    union {
        PE_SYMBOL_TABLE* PeSymbolTable;
        char* ntData;
    }Pe_Symbol{};

    union {
        PE_EXPORT_DIRECTORY_TABLE* PeExportTable;
        char* ntData;
    }Pe_Export_Table;


    char* _data_buffer;
private:
    FILE* _file;
    std::string _file_name;
    long _file_size;
    int _type;
    uint32_t alingment;

public:
    long getFileSize() const;
    void checkFileFormat();
};