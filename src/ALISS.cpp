#include"../include/ALISS.h"


//ALISS_CPU

//Constructor
ALISS_CPU::ALISS_CPU()
{
    pc = 0;//initialize program counter
    memory = NULL;//initialize memory address
}

ALISS_CPU::ALISS_CPU(uint32_t memory_size)
{
    pc=0;//initialize program counter
    memory = new char[memory_size];//Assign CPU memory
}

//
ALISS_CPU::~ALISS_CPU()
{
    if (memory != NULL)
    {
        delete memory;
    }
}

void ALISS_CPU::loadElf(const char* filename)
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
    pc = entryPoint;


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
            file.read(reinterpret_cast<char*>(memory + addr), size);
        }
    }
    
    // Add more code here to load and work with program segments, sections, etc.
    file.close();
	return;
}

uint32_t ALISS_CPU::get_mem_w(uint32_t addr)
{
    return *(uint32_t*)(memory + addr);
}

uint32_t ALISS_CPU::Instruction_Fetch(void)
{
    return get_mem_w(pc);
}

void ALISS_CPU::Instruction_Decode_Execution_WriteBack(uint32_t insn)
{
    riscv_ins n_ins;
    n_ins.wIns = insn;
    uint8_t opcode_val = n_ins.wIns & 0x7f;

    switch (opcode_val)
    {
        case 0x33: //OP-R type
            Op_R_Type_Implement(insn);
            break;
        
        default:
            break;
    }
    

    ////implement insn here
    next_pc=pc+4;
}

void ALISS_CPU::run_pipe(void)
{
    uint32_t ins = Instruction_Fetch();
    Instruction_Decode_Execution_WriteBack(ins);

    pc=next_pc;//jump to next instruction
}

void ALISS_CPU:: Op_R_Type_Implement (uint32_t insn)
{
    riscv_ins r_ins;
    r_ins.wIns=insn;

    uint8_t funct3 = r_ins.r_Ins.funct3;
    uint8_t funct7 = r_ins.r_Ins.funct7;
    uint64_t rd = r_ins.r_Ins.rd;
    uint64_t rs1 = r_ins.r_Ins.rs1;
    uint64_t rs2 = r_ins.r_Ins.rs2;


    switch (funct3)//funct 3 decode to determine operation
    {
    case 0x0:
        switch (funct7)//funct 7 decode to determine +/-
        {
            case 0x0 :
            {
                reg[rd] =  reg[rs1] + reg[rs2];
                break;
            }
            case 0x20 :
            {
                reg[rd] = reg[rs1] - reg[rs2];
                break;
            }
            default:
            {
                printf("no insn or not implement :");
                printf("%d\n",(insn >> 25) & 0x7f);
                break;
            }
        }
        break;
    case 0x1: //SLL
        reg[rd] = reg[rs1] << reg[rs2];
        break;
    case 0x2: //SLT
        reg[rd] = ((int64_t)reg[rs1] < (int64_t)reg[rs2]);
        break;
    case 0x3: //SLTU
        reg[rd] = (reg[rs1] < reg[rs2]);
        break;
    case 0x4: //XOR
        reg[rd] = reg[rs1] ^ reg[rs2];
        break;
    case 0x5: //SRL or SRA
        switch (funct7)
        {
            case 0x0 : //SRL
            {
                reg[rd] =  reg[rs1] >> reg[rs2];
                break;
            }
            case 0x20 : //SRA
            {
                reg[rd] = (int64_t)reg[rs1] >> reg[rs2];
                break;
            }
            default:
            {
                printf("no insn or not implement :");
                printf("%d\n",(insn >> 25) & 0x7f);
                break;
            }
        }
        break;
    case 0x6: //OR
        reg[rd] = reg[rs1] | reg[rs2];
        break;
    case 0x7: //AND
        reg[rd] = reg[rs1] & reg[rs2];
        break;
    default:
        printf("no insn or not implement :");
        break;
    }
}
