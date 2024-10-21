#include"../include/ALISS.h"

namespace ALISS
{
    uint32_t pc = 0; // initial program counter
}


void ALISS::loadElf(const char* filename)
{
    // ELF loader function
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    // Read the ELF header
    Elf64_Ehdr elfHeader;
    file.read(reinterpret_cast<char*>(&elfHeader), sizeof(Elf64_Ehdr));
    // Check ELF magic number
    if (memcmp(elfHeader.e_ident, ELFMAG, SELFMAG) != 0) {
        std::cerr << "Not a valid ELF file: " << filename << std::endl;
        return;
    }
    // Check ELF class (32-bit or 64-bit)
    if (elfHeader.e_ident[EI_CLASS] != ELFCLASS64) {
        std::cerr << "Only 64-bit ELF files are supported: " << filename << std::endl;
        return;
    }
    // Check ELF data encoding (little-endian or big-endian)
    if (elfHeader.e_ident[EI_DATA] != ELFDATA2LSB) {
        std::cerr << "Only little-endian ELF files are supported: " << filename << std::endl;
        return;
    }
    // Get the entry point address
    Elf64_Addr entryPoint = elfHeader.e_entry;
    ALISS::pc = entryPoint;
    
    // Add more code here to load and work with program segments, sections, etc.
    file.close();
	return;
}

