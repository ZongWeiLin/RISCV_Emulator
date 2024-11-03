#ifndef ALISS_H
#define ALISS_H

#include<iostream>
#include<memory>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<elf.h>

#define MEMORY_SIZE 64*1024*1024 //64MB

class ALISS_CPU
{
private:
    /* data */
public:
    uint32_t pc;
    char *memory;

    ALISS_CPU(uint32_t memory_size);
    ~ALISS_CPU();

    void loadElf(const char* filename);
    uint32_t get_mem_w(uint32_t addr);
};

#endif