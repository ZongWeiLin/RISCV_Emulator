#include"../include/ALISS.h"

namespace ALISS
{
    uint32_t pc = 0; // initial program counter
    uint8_t memory[MEMORY_SIZE];
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


    for (int i = 0; i < elfHeader.e_phnum; i++) {
        file.seekg(elfHeader.e_phoff + i * sizeof(Elf64_Phdr));

        Elf64_Phdr programHeader;
        file.read(reinterpret_cast<char*>(&programHeader), sizeof(Elf64_Phdr));

        // Check if this is a loadable segment
        if (programHeader.p_type == PT_LOAD) {
            // Save flags, address, and size
            Elf64_Word flags = programHeader.p_flags;
            Elf64_Addr addr = programHeader.p_vaddr;
            Elf64_Xword size = programHeader.p_memsz;

            // Seek to the segment's file offset
            file.seekg(programHeader.p_offset);

            // Read the segment data to memory
            file.read(reinterpret_cast<char*>(ALISS::memory + addr), size);
        }
    }
    
    // Add more code here to load and work with program segments, sections, etc.
    file.close();
	return;
}

