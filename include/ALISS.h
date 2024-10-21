#ifndef ALISS_H
#define ALISS_H

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<elf.h>

#define MEMORY_SIZE 64*1024*1024 //64MB

namespace ALISS
{
    extern uint32_t pc;//program counter
    extern uint8_t memory[MEMORY_SIZE];

    void loadElf(const char* filename);
} // namespace ALISS

#endif