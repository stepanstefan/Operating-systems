#include <iostream>
#include "PE_reader.h"

int main() {
    PE_reader reader("dota2_32.exe");

    reader.get_pe_header();
    reader.get_pe_sections();
    reader.get_pe_symbols();
    reader.get_pe_relocations();
    reader.get_pe_edata();

}
