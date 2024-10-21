#include <gtest/gtest.h>
#include"../../include/ALISS.h"

TEST(MyTestSuite, MyTestCase) { 
    ASSERT_TRUE(true);
}

                /*IT Day12*/
/*Test lf entry point address load function*/

TEST(MyTestSuite, ELFLoaderTestEntryPoint) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS::loadElf(test);
    EXPECT_EQ(ALISS::pc, 0x1014e);
}


                /*IT Day13*/
/*Test get load adress memory value*/
uint32_t get_mem_w(uint32_t addr)
{
    return *(uint32_t*)(ALISS::memory + addr);
}


TEST(MyTestSuite, ELFLoaderTestLoad) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS::loadElf(test);
    EXPECT_EQ( get_mem_w(0x1014e), 0x3197);
}