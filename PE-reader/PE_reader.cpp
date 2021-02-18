//
// Created by Freel on 26.12.2020.
//

#include <cmath>
#include "PE_reader.h"

PE_reader::PE_reader(const char *path_name) {
    _file = fopen(path_name, "rb");
    _file_name = path_name;

    fseek(_file, 0, SEEK_END);
    _file_size = ftell(_file);
    rewind(_file);
    _data_buffer = new char[_file_size];
    fread(_data_buffer,sizeof(char), _file_size, _file);

    char PE_Dos_Sig[3] = { _data_buffer[0], _data_buffer[1] };


    Dos_Head.e_lfanew = &_data_buffer[60];

    Pe_NtHeader.ntData = &_data_buffer[*Dos_Head.num];

    if (strcmp(Pe_NtHeader.ntData, "PE") != 0 || strcmp(PE_Dos_Sig, "MZ") != 0) {
        fprintf(stderr, "Not a PE file\n");
        exit(EXIT_FAILURE);
    }

    this->checkFileFormat();

    if (_type == 32) {
        Pe_Optional.ntData = &_data_buffer[*Dos_Head.num + (24 * sizeof(char))];
        Pe_Section.ntData = &_data_buffer[*Dos_Head.num + sizeof(PE_header) + sizeof(PE_OPTIONAL_HEADER)];
        Pe_Symbol.ntData = &_data_buffer[*Dos_Head.num + sizeof(PE_header) + sizeof(PE_OPTIONAL_HEADER) + Pe_NtHeader.PeHeader->NumberOfSections * sizeof(PE_SECTION_HEADER)];
        alingment = Pe_Optional.PeOpHeader->SectionAlignment;
    }
    else if (_type == 64) {
        Pe_Optional64.ntData = &_data_buffer[*Dos_Head.num + (24 * sizeof(char))];
        Pe_Section.ntData = &_data_buffer[*Dos_Head.num + sizeof(PE_header) + sizeof(PE_OPTIONAL_HEADER64)];
        Pe_Symbol.ntData = &_data_buffer[*Dos_Head.num + sizeof(PE_header) + sizeof(PE_OPTIONAL_HEADER) + Pe_NtHeader.PeHeader->NumberOfSections * sizeof(PE_SECTION_HEADER)];
        alingment = Pe_Optional64.PeOpHeader->SectionAlignment;
    }
}



long PE_reader::getFileSize() const {
    return _file_size;
}

void PE_reader::get_pe_header() const {
    std::cout << _file_name << ":      file-format ";
    switch (Pe_NtHeader.PeHeader->Machine) {
        case 332:{
            printf("pei-x86\narchitecture: IMAGE_FILE_MACHINE_I386, ");
            break;
        }
        case 512:{
            printf("pei-x86\narchitecture: IMAGE_FILE_MACHINE_IA64, ");
            break;
        }
        case 34404:{
            printf("pei-x86\narchitecture: IMAGE_FILE_MACHINE_AMD64, ");
            break;
        }
        default: {
            printf("pei-x86\narchitecture: IMAGE_FILE_MACHINE_UNDEFINED, ");
            break;
        }
    }



    printf("\t flags:%X\n", Pe_NtHeader.PeHeader->Characteristics);
    if (_type == 32) {
        printf("start address: 0x%#x\n", Pe_Optional.PeOpHeader->AddressOfEntryPoint);
    }
    else {
        printf("start address: 0x%#x\n", Pe_Optional64.PeOpHeader->AddressOfEntryPoint);
    }
}

void PE_reader::checkFileFormat(){
    int *characteristics = new int[16];
    for (int i = 0; i < 16; i++) {
        if ((Pe_NtHeader.PeHeader->Characteristics & (1 << i)) == 1 << i) {
            characteristics[i] = 1;
        }
    }

    if (characteristics[(int)log2(256)] == 1)
        _type = 32;
    else
        _type = 64;
}

void PE_reader::get_pe_sections() {
    for (int i = 0; i < Pe_NtHeader.PeHeader->NumberOfSections; i++) {
        printf("Name: ");
        union {
            int64_t* name;
            char* seq;
        }name_seq;

        name_seq.name = &Pe_Section.PeSecHeader[i].Name;
        for (int j = 0; j < 8; j++)
            printf("%c", name_seq.seq[j]);
        printf("\n");
//        std::cout << Pe_Section.PeSecHeader[i].Name << "\n";

        printf("VirtualSize:%d\n", Pe_Section.PeSecHeader[i].VirtualSize);
        printf("VirtualAddress:%#x\n", Pe_Section.PeSecHeader[i].VirtualAddress);
        printf("SizeOfRawData:%d\n", Pe_Section.PeSecHeader[i].SizeOfRawData);
        printf("PointerToRawData:%#x\n", Pe_Section.PeSecHeader[i].PointerToRawData);
        printf("PointerToRelocations:%#x\n", Pe_Section.PeSecHeader[i].PointerToRelocations);
        printf("PointerToLinenumbers:%#x\n", Pe_Section.PeSecHeader[i].PointerToLinenumbers);
        printf("NumberOfRelocations:%d\n", Pe_Section.PeSecHeader[i].NumberOfRelocations);
        printf("NumberOfLinenumbers:%d\n", Pe_Section.PeSecHeader[i].NumberOfLinenumbers);
        printf("Characteristics:%X\n", Pe_Section.PeSecHeader[i].Characteristics);
        printf("\n");
    }
}

void PE_reader::get_pe_symbols() {
    std::cout << _file_name << ": \t" << "file format: ";
    switch (Pe_NtHeader.PeHeader->Machine) {
        case 332:{
            std::cout << "pei-x86";
            break;
        }
        case 512:{
            std::cout << "pei-x86-64";
            break;
        }
        case 34404:{
            std::cout << "pei-x86-64";
            break;
        }
        default: {
            std::cout << "architecture: IMAGE_FILE_MACHINE_UNDEFINED, ";
            break;
        }
    }

    std::cout << "\nSYMBOL TABLE:\n";
    if (Pe_NtHeader.PeHeader->NumberOfSymbols == 0){
        std::cout << "no symbols";
        return;
    }
    for (int i = 0; i < Pe_NtHeader.PeHeader->NumberOfSymbols; i++) {
        printf("Name:");
        union {
            int64_t* name;
            char* seq;
        }name_seq;

        name_seq.name = &Pe_Symbol.PeSymbolTable[i].Name;
        for (int j = 0; j < 8; j++)
            printf("%c", name_seq.seq[j]);
        printf("\n");
//        std::cout << Pe_Section.PeSecHeader[i].Name << "\n";

        printf("Value:%d\n", Pe_Symbol.PeSymbolTable[i].Value);
        printf("Section number:%#x\n", Pe_Symbol.PeSymbolTable[i].SectionNumber);
        printf("Type:%#x\n", Pe_Symbol.PeSymbolTable[i].Type);
        printf("Storage class:%c\n", Pe_Symbol.PeSymbolTable[i].StorageClass);
        printf("Number of aus symbols:%c\n", Pe_Symbol.PeSymbolTable[i].NumberOfAusSymbols);
        printf("\n");
    }
}

void PE_reader::get_pe_relocations() {
    std::cout << _file_name << ": \t" << "file format: ";
    switch (Pe_NtHeader.PeHeader->Machine) {
        case 332:{
            printf("pei-x86");
            break;
        }
        case 512:{
            printf("pei-x86-64");
            break;
        }
        case 34404:{
            printf("pei-x86-64");
            break;
        }
        default: {
            printf("architecture: IMAGE_FILE_MACHINE_UNDEFINED, ");
            break;
        }
    }

    PE_Data_Directory tmp;

    if (_type == 32) {
        tmp = Pe_Optional.PeOpHeader->BaseRelocationTable;
    } else{
        tmp = Pe_Optional64.PeOpHeader->BaseRelocationTable;
    }
    uint32_t size = tmp.Size;
    uint32_t RAW = rvaToOff(tmp.RVA);

    printf("\n");

    for (int i = 0; i <= size; ) {
        union {
            BASE_RELOCATION_BLOCK* BaseRelocationBlock;
            char* ntData;
        }Base_Relocation{};
        Base_Relocation.ntData = &_data_buffer[RAW + i];
        if (Base_Relocation.BaseRelocationBlock->BlockSize == 0)
            break;
        RAW += sizeof(BASE_RELOCATION_BLOCK);
        uint32_t length = (Base_Relocation.BaseRelocationBlock->BlockSize - 8) / 2;
        auto *words = new short[length];
        fseek(_file, 0, SEEK_SET);
        fseek(_file, RAW + i, SEEK_CUR);
        for (int j = 0; j < length; j ++) {
            fread(&(words[j]), sizeof(short), 1, _file);
        }
        i += Base_Relocation.BaseRelocationBlock->BlockSize - 8;
        printf("Virtual address: %d\n", Base_Relocation.BaseRelocationBlock->PageRVA);
        printf("Block size: %d\n", Base_Relocation.BaseRelocationBlock->BlockSize);
        printf("Number of words: %d\n", length);
        for (int j = 0; j < length; j++) {
            printf("Word number: %d, ", j);
            printf("Offset: %d, ", words[j] & 0xFFF);
            printf("Type: %d, ", (words[j] & 0xF000) >> 12);
            switch ((words[j] & 0xF000) >> 12) {
                case 0: {
                    printf(" IMAGE_REL_BASED_ABSOLUTE");
                    break;
                }
                case 1: {
                    printf(" IMAGE_REL_BASED_HIGH");
                    break;
                }
                case 2: {
                    printf(" IMAGE_REL_BASED_LOW");
                    break;
                }
                case 3: {
                    printf(" IMAGE_REL_BASED_HIGHLOW");
                    break;
                }
                case 4: {
                    printf(" IMAGE_REL_BASED_HIGHADJ");
                    break;
                }
                case 5: {
                    printf(" IMAGE_REL_BASED_ARM_MOV32");
                    break;
                }
                case 6: {
                    printf(" Reserved, must be zero");
                    break;
                }
                case 7: {
                    printf(" IMAGE_REL_BASED_THUMB_MOV32");
                    break;
                }
                case 8: {
                    printf(" IMAGE_REL_BASED_RISCV_LOW12S");
                    break;
                }
                case 9: {
                    printf(" IMAGE_REL_BASED_MIPS_JMPADDR16");
                    break;
                }
                case 10: {
                    printf(" IMAGE_REL_BASED_DIR64");
                    break;
                }
                default: {
                    printf(" undefined");
                    break;
                }
            }
            printf("\n");
        }
    }

}

uint32_t PE_reader::defSection(uint32_t rva) {
    for (int i = 0; i < Pe_NtHeader.PeHeader->NumberOfSections; i++){
        uint32_t start = Pe_Section.PeSecHeader[i].VirtualAddress;
        uint32_t end = start + align_up(Pe_Section.PeSecHeader[i].VirtualAddress, alingment);

        if (rva >= start && rva < end)
            return i;
    }
    return -1;
}

uint32_t PE_reader::align_up(uint32_t x, uint32_t align) {
    if ((x & (align - 1)) == 1) {
        return align_down(x, align) + align;
    }
    return x;
}

uint32_t PE_reader::align_down(uint32_t x, uint32_t align) {
    return (x & ~(align - 1));
}

uint32_t PE_reader::rvaToOff(uint32_t rva) {
    long indexSection = defSection(rva);
    if (indexSection != -1)
        return rva - Pe_Section.PeSecHeader[indexSection].VirtualAddress + Pe_Section.PeSecHeader[indexSection].PointerToRawData;
    return 0;
}

void PE_reader::get_pe_edata() {
    PE_Data_Directory tmp;

    if (_type == 32) {
        tmp = Pe_Optional.PeOpHeader->ExportTable;
    } else{
        tmp = Pe_Optional64.PeOpHeader->ExportTable;
    }
    uint32_t size = tmp.Size;
    uint32_t RAW = rvaToOff(tmp.RVA);

    Pe_Export_Table.ntData = &_data_buffer[RAW];
    uint32_t rawAddressTable = rvaToOff(Pe_Export_Table.PeExportTable->ExportAddressTableRva);
    uint32_t *addressEntries = new uint32_t[Pe_Export_Table.PeExportTable->AddressTableEntries];
    fseek(_file, 0, SEEK_SET);
    fseek(_file, rawAddressTable, SEEK_CUR);
    for (int i = 0; i < Pe_Export_Table.PeExportTable->AddressTableEntries; i++) {
        fread(&(addressEntries[i]), sizeof(uint32_t), 1, _file);
        printf("Index: %d, Base: %d, Virtual address: %d\n", i, Pe_Export_Table.PeExportTable->OrdinalBase, addressEntries[i]);
    }

    uint32_t rawNameTable = rvaToOff(Pe_Export_Table.PeExportTable->NamePointerRVA);
    uint32_t *nameEntries = new uint32_t[Pe_Export_Table.PeExportTable->NumberOfNamePointers];
    fseek(_file, 0, SEEK_SET);
    fseek(_file, rawNameTable, SEEK_CUR);
    for (int i = 0; i < Pe_Export_Table.PeExportTable->NumberOfNamePointers; i++) {
        fread(&(nameEntries[i]), sizeof(uint32_t), 1, _file);
    }

    uint32_t rawOrdinalTable = rvaToOff(Pe_Export_Table.PeExportTable->OrdinalTableRVA);
    uint32_t *ordinalEntries = new uint32_t[Pe_Export_Table.PeExportTable->AddressTableEntries];
    fseek(_file, 0, SEEK_SET);
    fseek(_file, rawOrdinalTable, SEEK_CUR);
    for (int i = 0; i < Pe_Export_Table.PeExportTable->AddressTableEntries; i++) {
        fread(&(ordinalEntries[i]), sizeof(uint32_t), 1, _file);
    }


}


