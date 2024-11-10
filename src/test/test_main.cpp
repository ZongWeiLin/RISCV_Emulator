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

/*Test Run Pipe*/
TEST(MyTestSuite, PCNextTest) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    Simulator.run_pipe();
    EXPECT_EQ(Simulator.pc,0x10152);
}

/*IT Day17 R-Type Add Function*/
TEST(MyTestSuite, ADD0) {
    ALISS_CPU Simulator=ALISS_CPU();
    Simulator.reg[11] = 3;
    Simulator.reg[12] = 7;
    uint32_t insn = 0x00c58533; // add a0 a1 a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0xa); //3 + 7 = 10
}

TEST(MyTestSuite, ADD1) {
    ALISS_CPU Simulator=ALISS_CPU();
    Simulator.reg[10] = 0xffffffffffffffff;
    Simulator.reg[12] = 0x01;
    uint32_t insn = 0x00c505b3; // add a1 a0 a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[11], 0); //3 + 7 = 10
}

TEST(MyTestSuite, SLL)
{
    ALISS_CPU Simulator=ALISS_CPU();
    Simulator.reg[11] = 16;
    Simulator.reg[12] = 2;
    riscv_ins sll_ins;
    sll_ins.r_Ins.rs1 = 11;
    sll_ins.r_Ins.rs2 = 12;
    sll_ins.r_Ins.rd = 10;
    sll_ins.r_Ins.op_code = 0x33;
    sll_ins.r_Ins.funct3 = 0x1;
    sll_ins.r_Ins.funct7 = 0;

    uint32_t insn = sll_ins.wIns;
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 64); // 16<<2
}

