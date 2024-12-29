#include"../include/ALISS.h"


//ALISS_CPU

//Constructor
ALISS_CPU::ALISS_CPU()
{
    /*initialize program counter*/
    pc = 0;
    next_pc = 0;

    /*Assign CPU memory*/
    memory = NULL;

    /*Initial Reserved bit*/
    reservation = false;
}

ALISS_CPU::ALISS_CPU(uint32_t memory_size)
{
    /*initialize program counter*/
    pc = 0;
    next_pc = 0;

    /*Assign CPU memory*/
    memory = new char[memory_size];

    /*Initial Reserved bit*/
    reservation = false;
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

/*Implement get memory function*/
uint8_t ALISS_CPU::get_mem_b(uint64_t addr)
{
    return *(uint8_t*)(memory + addr);
}

uint16_t ALISS_CPU::get_mem_h(uint64_t addr)
{
    return *(uint16_t*)(memory + addr);
}

uint32_t ALISS_CPU::get_mem_w(uint64_t addr)
{
    return *(uint32_t*)(memory + addr);
}

uint64_t ALISS_CPU::get_mem_dw(uint64_t addr)
{
    return *(uint64_t*)(memory + addr);
}

/*Implement load memory function*/

void ALISS_CPU::set_mem_b(uint64_t addr,uint8_t val)
{
    uint8_t* mem_b = (uint8_t*)(&memory[addr]);
    *mem_b = val;
}

void ALISS_CPU::set_mem_h(uint64_t addr,uint16_t val)
{
    uint16_t* mem_h = (uint16_t*)(&memory[addr]);
    *mem_h = val;
}

void ALISS_CPU::set_mem_w(uint64_t addr,uint32_t val)
{
    uint32_t* mem_w = (uint32_t*)(&memory[addr]);
    *mem_w = val;
}

void ALISS_CPU::set_mem_dw(uint64_t addr,uint64_t val)
{
    uint64_t* mem_dw = (uint64_t*)(&memory[addr]);
    *mem_dw = val;
}

/*Implement Mulitification function*/
uint64_t ALISS_CPU:: mulhu(uint64_t a, uint64_t b)
{
    uint64_t t;           // Temporary variable for intermediate calculations
    uint32_t y1, y2, y3;  // Intermediate 32-bit results
    uint64_t a0 = (uint32_t)a, a1 = a >> 32; // Split `a` into lower 32 bits (a0) and upper 32 bits (a1)
    uint64_t b0 = (uint32_t)b, b1 = b >> 32; // Split `b` into lower 32 bits (b0) and upper 32 bits (b1)

    // Compute the partial product of upper half of `a` and lower half of `b`, plus high bits from lower halves
    t = a1 * b0 + ((a0 * b0) >> 32);
    y1 = t;          // Lower 32 bits of the partial sum
    y2 = t >> 32;    // Upper 32 bits of the partial sum

    // Add the partial product of lower half of `a` and upper half of `b`
    t = a0 * b1 + y1;

    // Compute the final upper 64 bits, including the full upper half of both numbers
    t = a1 * b1 + y2 + (t >> 32);
    y2 = t;          // Lower 32 bits of the final result
    y3 = t >> 32;    // Upper 32 bits of the final result

    // Combine the upper and lower halves to return the final result    
    return ((uint64_t)y3 << 32) | y2;
}

int64_t ALISS_CPU:: mulh(int64_t a, int64_t b)
{
    int negate = (a < 0) != (b < 0);  // Determine if the result should be negative
    printf("a:%lx,b:%lx\n",a,b);
    uint64_t res = mulhu(a < 0 ? -a : a, b < 0 ? -b : b); // Calculate the unsigned product of the absolute values
    // Adjust the result for negative values if needed
    return negate ? ~res + (a * b == 0) : res;
}

int64_t ALISS_CPU:: mulhsu(int64_t a, uint64_t b)
{
    int negate = a < 0;               // Determine if the result should be negative
    uint64_t res = mulhu(a < 0 ? -a : a, b); // Calculate the unsigned product of absolute value of `a` and `b`
    // Adjust the result for negative values if needed
    return negate ? ~res + (a * b == 0) : res;
}

/*Implemnt set sign extension function*/

int64_t ALISS_CPU::set_sign_extension(uint64_t input,int lens)
{
    return ((int64_t)input<<(64-lens))>>(64-lens);
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

    //fetch next command to pc
    next_pc=pc+4;

    ////implement insn here
    switch (opcode_val)
    {
        case 0x33: //OP-R type
        {
            uint8_t funct7 = n_ins.r_Ins.funct7;
            if (funct7 == 0x01)
            {
                Op_M_Type_Ins_Implement(insn);
            }
            else
            {
                Op_R_Type_Implement(insn);
            }
            break;
        }
        case 0x13: //OP-I type
            Op_I_Type_Implement(insn);
            break;
        case 0x3: //Load Ins
            Op_Load_Ins_Imlpement(insn);
            break;
        case 0x23:
            Op_Store_Ins_Implement(insn);
            break;
        case 0x63://branch ins
            Op_B_Type_Implement(insn);
            break;
        case 0x67://JALR
            Op_JALR_Ins_Implement(insn);
            break;
        case 0x6f://JAL
            Op_JAL_Ins_Implement(insn);
            break;
        case 0x73:
            Op_CSRs_Ins_Implement(insn);
            break;
        case 0x3b:
            Op_RV64I_R_Type_Ins_Implement(insn);
            break;
        case 0x1b:
            Op_RV64I_I_Type_Ins_Implement(insn);
            break;
        case 0x37:
            Op_Lui_Ins_Implement(insn);
            break;
        case 0x17:
            Op_Auipc_Ins_Implement(insn);
            break;
        case 0x2f:
            Op_Atomic_Ins_Implement(insn);
            break;
        default:
            break;
    }
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

void ALISS_CPU::Op_I_Type_Implement(uint32_t insn)
{
    riscv_ins i_ins;
    i_ins.wIns = insn;

    /*Get instruction field value*/
    uint8_t funct3 = i_ins.i_Ins.funct3;
    uint64_t imm = i_ins.i_Ins.imm;
    uint64_t rd = i_ins.i_Ins.rd;
    uint64_t rs1 = i_ins.i_Ins.rs1;

    switch (funct3)
    {
    case 0x0: //ADDI
    {
        reg[rd] =  reg[rs1] +  set_sign_extension(imm, 12);
        break;
    }
    case 0x1: //SLLI
    {
        uint64_t shamt = imm & 0x1f; //[24:20]
        reg[rd] = reg[rs1] << shamt;
        break;
    }
    case 0x2: //SLTI
    {
        
        reg[rd] = ((int64_t)reg[rs1] < set_sign_extension(imm, 12));
        break;
    }
    case 0x3: //SLTUI
    {
        reg[rd] = (reg[rs1] < imm);
        break;
    }
    case 0x4: //XORI
    {
        reg[rd] = (reg[rs1] ^ set_sign_extension(imm, 12));
        break;
    }
    case 0x5: //SRLI & SRAI
    {
        uint64_t shamt = imm & 0x1f; //[24:20]
        switch ((insn >> 25) & 0x7f)
        {
            case 0x0 : //SRLI
            {
                reg[rd] =  reg[rs1] >> shamt;
                break;
            }
            case 0x20 : //SRAI
            {
                reg[rd] =  (int64_t)reg[rs1] >> shamt;
                break;
            }
            default:
            {
                printf("Illegal instruction");
                printf("%x\n",insn);
                break;
            }
        }
        break;
    }
    case 0x6: //ORI
    {
        reg[rd] = (reg[rs1] | set_sign_extension(imm, 12));
        break;
    }
    case 0x7: //ANDI
    {
        reg[rd] = (reg[rs1] & set_sign_extension(imm, 12));
        break;
    }
    default:
    {
        printf("Illegal instruction");
        printf("%x\n",insn);
        break;
    }
    } 
}

void ALISS_CPU::Op_JAL_Ins_Implement(uint32_t insn)
{
    riscv_ins jal_ins;//JAL is J-Type Ins;
    jal_ins.wIns = insn;
    uint8_t rd = jal_ins.j_Ins.rd;
    uint64_t imm = ((jal_ins.j_Ins.imm_1_to_10<<1)|
                    (jal_ins.j_Ins.imm_11<<11) |
                    (jal_ins.j_Ins.imm_12_to_19<<12)|
                    (jal_ins.j_Ins.imm_20<<20));


    reg[rd] = pc + 4;
    next_pc = pc + set_sign_extension(imm,21);
}

void ALISS_CPU::Op_JALR_Ins_Implement(uint32_t insn)
{
    riscv_ins jalr_ins;
    jalr_ins.wIns = insn;
    uint8_t rs1 = jalr_ins.i_Ins.rs1;
    uint8_t rd = jalr_ins.i_Ins.rd;
    uint64_t offset = jalr_ins.i_Ins.imm;

    reg[rd] = pc + 4;
    next_pc = reg[rs1] + set_sign_extension(offset,12);
}

void ALISS_CPU::Op_B_Type_Implement(uint32_t insn)
{
    riscv_ins b_ins;
    b_ins.wIns = insn;
    uint8_t rs1 = b_ins.b_Ins.rs1;
    uint8_t rs2 = b_ins.b_Ins.rs2;
    uint8_t funct3 = b_ins.b_Ins.funct3;
    uint64_t imm = ( (b_ins.b_Ins.imm_1_to_4<<1)|
                        (b_ins.b_Ins.imm_5_to_10<<5)|
                        (b_ins.b_Ins.imm_11<<11)|
                        (b_ins.b_Ins.imm_12<<12));
    switch (funct3)
    {
        case 0: //BEQ
        {
            if(reg[rs1] == reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        case 1: //BNE
        {
            if(reg[rs1] != reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        case 4: //BLT
        {
            if((int64_t)reg[rs1] < (int64_t)reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        case 5: //BGE
        {
            if((int64_t)reg[rs1] >= (int64_t)reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        case 6: //BLTU
        {
            if(reg[rs1] < reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        case 7: //BGEU
        {
            if(reg[rs1] >= reg[rs2])
                next_pc = pc + set_sign_extension(imm,13);
            break;
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    }

}

void ALISS_CPU::Op_Load_Ins_Imlpement(uint32_t insn)
{
    riscv_ins Load_Ins;
    Load_Ins.wIns = insn;

    uint8_t rs1 = Load_Ins.i_Ins.rs1;
    uint8_t rd =  Load_Ins.i_Ins.rd;
    uint8_t funct3 = Load_Ins.i_Ins.funct3;
    uint64_t imm = Load_Ins.i_Ins.imm;

    switch (funct3)
    {
        case 0: //LB
        {
            reg[rd] = set_sign_extension(get_mem_b(reg[rs1] + set_sign_extension(imm,12)),8);
            break;
        }
        case 1:  //LH
        {
            reg[rd] = set_sign_extension(get_mem_h(reg[rs1] + set_sign_extension(imm,12)),16);
            break;
        }
        case 2: //LW
        {
            reg[rd] = set_sign_extension(get_mem_w(reg[rs1] + set_sign_extension(imm,12)),32);
            break;
        }
        case 3: //LDW
        {
            reg[rd] = get_mem_dw(reg[rs1]+set_sign_extension(imm,12));
        }
        case 4: //LBU
        {
            reg[rd] = get_mem_b(reg[rs1] + set_sign_extension(imm,12));
            break;
        }
        case 5:  //LHU
        {
            reg[rd] = get_mem_h(reg[rs1] + set_sign_extension(imm,12));
            break;
        }
        case 6: //LWU
        {
            reg[rd] = get_mem_w(reg[rs1] + set_sign_extension(imm,12));
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    }

}

void ALISS_CPU::Op_Store_Ins_Implement(uint32_t insn)
{
    riscv_ins Store_Ins;
    Store_Ins.wIns = insn;

    uint8_t rs1 = Store_Ins.s_Ins.rs1;
    uint8_t rs2 = Store_Ins.s_Ins.rs2;
    uint8_t funct3 = Store_Ins.s_Ins.funct3;
    uint64_t imm = ((Store_Ins.s_Ins.imm_0_to_4)|
                    (Store_Ins.s_Ins.imm_5_to_11<<5));
    
    switch (funct3)
    {
    case 0: //SB
    {
        set_mem_b(reg[rs1] + set_sign_extension(imm,12), (uint8_t)reg[rs2]);
        break;
    }
    case 1:  //SH
    {
        set_mem_h(reg[rs1] + set_sign_extension(imm,12), (uint16_t)reg[rs2]);
        break;
    }
    case 2: //SW
    {
        set_mem_w(reg[rs1] + set_sign_extension(imm,12), (uint32_t)reg[rs2]);
        break;
    }
    case 3: //SD
    {
        set_mem_dw(reg[rs1] + set_sign_extension(imm,12),(uint64_t)reg[rs2]);
        break;
    }
    default:
    {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
    }
    }

}

void ALISS_CPU::Op_CSRs_Ins_Implement(uint32_t insn)
{
    riscv_ins   csr_ins;
    csr_ins.wIns = insn;

    uint8_t rd = csr_ins.i_Ins.rd;
    uint8_t rs1 = csr_ins.i_Ins.rs1;
    uint8_t funct3 = csr_ins.i_Ins.funct3;
    uint64_t csr_no = csr_ins.i_Ins.imm;

    switch (funct3)
    {
        case 0:
        {
            Op_Sys_Ins_Implement(insn);
            break;
        }
        case 1: //csrrw
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = reg[rs1];
            break;
        }
        case 2: //csrrs
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = reg[rd] | reg[rs1];
            break;
        }
        case 3: //csrrc
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = reg[rd] & ~reg[rs1];
            break;
        }
        case 5: //csrrwi
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = rs1;
            break;
        }
        case 6: //csrrsi
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = reg[rd] | rs1;
            break;
        }
        case 7: //csrrci
        {
            reg[rd]  = csr[csr_no];
            csr[csr_no] = reg[rd] & ~rs1;
            break;
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    }
}

void ALISS_CPU::Op_RV64I_R_Type_Ins_Implement(uint32_t insn)
{
    riscv_ins rv64_r_type_ins;
    rv64_r_type_ins.wIns = insn;

    uint8_t rs1 = rv64_r_type_ins.r_Ins.rs1;
    uint8_t rs2 = rv64_r_type_ins.r_Ins.rs2;
    uint8_t rd = rv64_r_type_ins.r_Ins.rd;
    uint8_t funct3 = rv64_r_type_ins.r_Ins.funct3;
    uint8_t funct7 = rv64_r_type_ins.r_Ins.funct7;

    switch (funct3)
    {
        case 0x0: //ADDW or SUBW
        {
            switch (funct7)
            {
               case 0x0 : //ADDW
               {
                    reg[rd] =  set_sign_extension((reg[rs1] + reg[rs2]) & 0xffffffff,32);
                    break;
               }
               case 0x20 :  //SUBW
               {
                    reg[rd] = set_sign_extension((reg[rs1] - reg[rs2]) &  0xffffffff,32);
                    break;
               }
               default:
               {

                    printf("Illegal instruction");
                    printf("%x\n",insn);
                    break;
               }
            }
            break;
        }
        case 0x1: //SLLW
        {
            reg[rd] = set_sign_extension((reg[rs1] << reg[rs2])  & 0xffffffff,32);
            break;
        }
        case 0x5: //SRLW or SRAW
        {
            switch (funct7)
            {
               case 0x0 : //SRLW
               {
                    reg[rd] =  set_sign_extension((reg[rs1] >> reg[rs2]) &  0xffffffff,32);
                    break;
               }
               case 0x20 : //SRAW
               {
                    reg[rd] = set_sign_extension(((int64_t)reg[rs1] >> reg[rs2]) & 0xffffffff,32);
                    break;
               }
               default:
               {
                    printf("Illegal instruction");
                    printf("%x\n",insn);
                    break;
               }
            }
            break;
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    } 

}

void ALISS_CPU::Op_RV64I_I_Type_Ins_Implement(uint32_t insn)
{
    riscv_ins rv64_i_type_ins;
    rv64_i_type_ins.wIns = insn;

    uint8_t rs1 = rv64_i_type_ins.i_Ins.rs1;
    uint8_t rd = rv64_i_type_ins.i_Ins.rd;
    uint8_t funct3 = rv64_i_type_ins.i_Ins.funct3;
    uint32_t imm = rv64_i_type_ins.i_Ins.imm;
    uint8_t shamt = imm & 0x1f;

    switch (funct3)
    {
        case 0x0: //ADDIW
        {
            reg[rd] = set_sign_extension((reg[rs1]+set_sign_extension(imm,12)) & 0xffffffff,32);
            break;
        }
        case 0x1: //SLLIW
        {
            reg[rd] = set_sign_extension((reg[rs1] << shamt)  & 0xffffffff,32);
            break;
        }
        case 0x5: //SRLIW or SRAIW
        {
            uint8_t bit31_27=  imm >> 7;
            switch (bit31_27)
            {
            case 0x0:
                set_sign_extension(reg[rs1] >> shamt,32);
                break;
            case 0x8:
                set_sign_extension(((int64_t)reg[rs1]) >> shamt,32);
                break;
            default:
                printf("Illegal instruction");
                printf("%x\n",insn);
                break;
            }
            break;
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    } 
}

void ALISS_CPU::Op_Lui_Ins_Implement(uint32_t insn)
{
    riscv_ins lui_ins;
    lui_ins.wIns = insn;

    uint8_t rd = lui_ins.u_Ins.rd;
    uint32_t imm_12_to_31 =(lui_ins.u_Ins.imm_12_to_31 << 12);

    reg[rd] = set_sign_extension(imm_12_to_31,32);
}

void ALISS_CPU::Op_Auipc_Ins_Implement(uint32_t insn)
{
    riscv_ins auipc_ins;
    auipc_ins.wIns = insn;

    uint8_t rd = auipc_ins.u_Ins.rd;
    uint32_t imm_12_to_31 =(auipc_ins.u_Ins.imm_12_to_31 << 12);

    reg[rd] = pc + set_sign_extension(imm_12_to_31,32);
}

void ALISS_CPU::Op_Sys_Ins_Implement(uint32_t insn)
{
    riscv_ins sys_ins;
    sys_ins.wIns = insn;

    uint16_t sys_op = sys_ins.i_Ins.imm;

    switch (sys_op)
    {
        case 0x0: //ecall
        {
            csr[CSR_MEPC] = pc; //epc = pc
            next_pc = csr[CSR_MTVEC]; //mtvec = 0x305
            break;
        }
        case 0x1: //ebreak
        {
            csr[CSR_MEPC] = pc;
            next_pc = csr[CSR_MTVEC]; // mtvec = 0x305
            break;
        }
        case 0x105: // wfi
        {
            //implement as nop ...
            break;
        }
        case 0x302: //mret
        {
            next_pc = csr[CSR_MEPC]; //epc = 0x341
            break;
        }
        default:
        {
            printf("Illegal instruction");
            printf("%x\n",insn);
            break;
        }
    }
}

void ALISS_CPU::Op_Atomic_Ins_Implement(uint32_t insn)
{
    riscv_ins atomic_insn;
    atomic_insn.wIns = insn;

    uint8_t rs1 = atomic_insn.r_Ins.rs1;
    uint8_t rs2 = atomic_insn.r_Ins.rs2;
    uint8_t rd = atomic_insn.r_Ins.rd;
    uint8_t funct7 = atomic_insn.r_Ins.funct7; 
    uint8_t atomic_op = funct7 >> 2;

    switch (atomic_op)
    {
        case 0x2: //LR.W
        {
            reg[rd] = set_sign_extension(get_mem_w(reg[rs1]),32);
            reservation = true;
            break;
        }
        case 0x3: //SC.W
        {
            if(reservation)
            {
                set_mem_w(reg[rs1], (uint32_t)reg[rs2]);
                reg[rd] = 0;
            }
            else
            {
                reg[rd] = 1;
            }
            reservation = false;
            break;
        }
        case 0x1: //AMOSWP.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2]);
            break;
        }
        case 0x0: //AMOADD.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] + reg[rd]);
            break;
        }
        case 0x4: //AMOXOR.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] ^ reg[rd]);
            break;
            }
        case 0xc: //AMOAND.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] & reg[rd]);
            break;
        }
        case 0x8: //AMOOR.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] | reg[rd]);
            break;
        }
        case 0x10: //AMOMIN.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], (int64_t)reg[rs2] < (int64_t)reg[rd] ? reg[rs2] : reg[rd] );
            break;
        }
        case 0x14: //AMOMAX.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], (int64_t)reg[rs2] > (int64_t)reg[rd] ? reg[rs2] : reg[rd] );
            break;
        }
        case 0x18: //AMOMINU.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] < reg[rd] ? reg[rs2] : reg[rd] );
            break;
        }
        case 0x1c: //AMOMAXU.D
        {
            reg[rd] = get_mem_dw(reg[rs1]);
            set_mem_dw(reg[rs1], reg[rs2] > reg[rd] ? reg[rs2] : reg[rd] );
            break;
        }
    }
}

void ALISS_CPU::Op_M_Type_Ins_Implement(uint32_t insn)
{
    riscv_ins m_type_insn;
    m_type_insn.wIns = insn;

    uint8_t rs1 = m_type_insn.r_Ins.rs1;
    uint8_t rs2 = m_type_insn.r_Ins.rs2;
    uint8_t rd = m_type_insn.r_Ins.rd;
    uint8_t funct3 = m_type_insn.r_Ins.funct3;

    switch (funct3)
    {
        case 0x0: //MUL
        {
            reg[rd] = (int64_t)reg[rs1] * (int64_t)reg[rs2];
            break;
        }
        case 0x1: //MULH
        {
            reg[rd] = mulh(reg[rs1],reg[rs2]);
            break;
        }
        case 0x2: //MULHSU
        {
            reg[rd] = mulhsu(reg[rs1],reg[rs2]);
            break;
        }
        case 0x3: //MULHU
        {
            reg[rd] = mulhu(reg[rs1],reg[rs2]);
            break;
        }
        case 0x4: //DIV
        {
            if(reg[rs2] == 0) //can't div 0
            {
                reg[rd] = -1;
            }
            else if((int64_t)reg[rs1] == INT64_MIN && (int64_t)reg[rs2] == -1) // may overflow
            {
                reg[rd] = reg[rs1];
            }
            else
            {
                reg[rd] = (int64_t)reg[rs1] / (int64_t)reg[rs2];
            }
            break;
        }
        case 0x5: //DIVU
        {
            if(reg[rs2] == 0) //can't div 0
            {
                reg[rd] = -1;
            }
            else
            {
                reg[rd] = reg[rs1] / reg[rs2];
            }
            break;
        }
        case 0x6: //REM
        {
            if(reg[rs2] == 0) //can't div 0
            {
                reg[rd] = reg[rs1];
            }
            else if((int64_t)reg[rs1] == INT64_MIN && (int64_t)reg[rs2] == -1) // may overflow
            {
                reg[rd] = 0;
            }
            else
            {
                reg[rd] = (int64_t)reg[rs1] % (int64_t)reg[rs2];
            }
            break;
        }
        case 0x7: //REMU
        {
            if(reg[rs2] == 0) //can't div 0
            {
                reg[rd] = reg[rs1];
            }
            else
            {
                reg[rd] = reg[rs1] % reg[rs2];
            }
            break;
        }
        default:
        {
                printf("Illegal instruction");
                printf("%x\n",insn);
                break;
        }
    }

}