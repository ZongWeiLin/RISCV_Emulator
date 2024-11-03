#include <gtest/gtest.h>
#include"../../include/ALISS.h"

TEST(MyTestSuite, MyTestCase) { 
    ASSERT_TRUE(true);
}

                /*IT Day12*/
/*Test lf entry point address load function*/

TEST(MyTestSuite, ELFLoaderTestEntryPoint) {
    const char* test = "../RISCV_elf/hello_world.elf";

    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    EXPECT_EQ(Simulator.pc,0x1014e);
}


                /*IT Day13*/
/*Test get load adress memory value*/

TEST(MyTestSuite, ELFLoaderTestLoad) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    // EXPECT_EQ(Simulator.get_mem_w(0x1014e),0x3197);
}

                /*IT Day14*/
/*Test Instruction Fetch*/

TEST(MyTestSuite, InstFetchTest) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    EXPECT_EQ(Simulator.Instruction_Fetch(),0x3197);
}