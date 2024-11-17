#ifndef ALISS_H
#define ALISS_H

#include<iostream>
#include<memory>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<elf.h>
#include"../include/Ins.h"

#define BUILD_LEVLEL 19

#define MEMORY_SIZE 64*1024*1024 //64MB

class ALISS_CPU
{
private:
    /* data */
public:
    uint32_t pc;
    uint32_t next_pc;
    uint64_t reg[32];
    char *memory;

    ALISS_CPU();
    ALISS_CPU(uint32_t memory_size);
    ~ALISS_CPU();

    void loadElf(const char* filename);
    uint32_t get_mem_w(uint32_t addr);
    int64_t set_sign_extension(uint64_t input,int lens);
    uint32_t Instruction_Fetch(void);
    void Instruction_Decode_Execution_WriteBack(uint32_t insn);
    void run_pipe(void);
    void Op_R_Type_Implement(uint32_t insn);
    void Op_I_Type_Implement(uint32_t insn);
    void Op_B_Type_Implement(uint32_t insn);
    void Op_JAL_Ins_Implement(uint32_t insn);
    void Op_JALR_Ins_Implement(uint32_t insn);
};

#endif