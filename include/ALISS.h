#ifndef ALISS_H
#define ALISS_H

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<elf.h>

namespace ALISS
{
    extern uint32_t pc;//program counter

    void loadElf(const char* filename);
} // namespace ALISS

#endif