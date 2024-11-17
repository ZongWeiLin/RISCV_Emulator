#include <gtest/gtest.h>
#include"../../include/ALISS.h"

TEST(MyTestSuite, MyTestCase) { 
    ASSERT_TRUE(true);
}

                /*IT Day12*/
/*Test lf entry point address load function*/
#if (BUILD_LEVLEL == 12)
TEST(MyTestSuite, ELFLoaderTestEntryPoint) {
    const char* test = "../RISCV_elf/hello_world.elf";

    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    EXPECT_EQ(Simulator.pc,0x1014e);
}
#endif


                /*IT Day13*/
/*Test get load adress memory value*/
#if (BUILD_LEVLEL == 13)
TEST(MyTestSuite, ELFLoaderTestLoad) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    // EXPECT_EQ(Simulator.get_mem_w(0x1014e),0x3197);
}
#endif

                /*IT Day14*/
/*Test Instruction Fetch*/
#if (BUILD_LEVLEL == 14)
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
#endif

/*IT Day17 Add R-Type Instruction*/
#if (BUILD_LEVLEL == 17)
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
#endif

/*ITDay 18 Add I-Type Instruction*/
#if (BUILD_LEVLEL == 18)
TEST(MyTestSuite, ADDI0)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[11] = 3;
    uint32_t insn = 0x00758513;// addi a0 a1 7
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0xa); // 3+7=10
}

TEST(MyTestSuite, ADDI1)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0xffffffffffffffff;
    uint32_t insn = 0x00150593;// addi a1 a0 1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[11], 0); // 1+-1=0
}

TEST(MyTestSuite, SLL_1_7)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0x01;
    riscv_ins sll_ins;
    sll_ins.i_Ins.op_code = 0x13;
    sll_ins.i_Ins.rs1 = 10;
    sll_ins.i_Ins.rd =  11;
    sll_ins.i_Ins.imm = 7;
    sll_ins.i_Ins.funct3 = 0x01;
    
    Simulator.Instruction_Decode_Execution_WriteBack(sll_ins.wIns);
    EXPECT_EQ(Simulator.reg[11], 0x80); // 1 << 7
}

TEST(MyTestSuite, SLTI_N1_f)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = (int64_t)-1;
    riscv_ins sll_ins;
    sll_ins.i_Ins.op_code = 0x13;
    sll_ins.i_Ins.rs1 = 10;
    sll_ins.i_Ins.rd =  11;
    sll_ins.i_Ins.imm = 0xf;
    sll_ins.i_Ins.funct3 = 0x02;
    
    Simulator.Instruction_Decode_Execution_WriteBack(sll_ins.wIns);
    EXPECT_EQ(Simulator.reg[11], 1); // -1 < f (True)
}

TEST(MyTestSuite, SLTI_f_1)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0xf;
    riscv_ins sll_ins;
    sll_ins.i_Ins.op_code = 0x13;
    sll_ins.i_Ins.rs1 = 10;
    sll_ins.i_Ins.rd =  11;
    sll_ins.i_Ins.imm = 0x1;
    sll_ins.i_Ins.funct3 = 0x02;
    
    Simulator.Instruction_Decode_Execution_WriteBack(sll_ins.wIns);
    EXPECT_EQ(Simulator.reg[11], 0); // f < 1 (False)
}

#endif

/*ITDay 19 Add I-Type Instruction*/
#if (BUILD_LEVLEL == 19)
TEST(ISATESTSuite, JALR_0x100_0x50)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x100;
    uint32_t insn = 0xf8058567; // jalr a0, -128(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0x104 ); //return address = 104;
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

TEST(ISATESTSuite, JAL_0x100_0x50)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x0;
    uint32_t insn = 0xf81ff56f; // jal a0, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0x104 ); //return address = 104;
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}


TEST(ISATESTSuite, BEQ_0x100_N128)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x1234;
    Simulator.reg[11] = 0x1234;
    uint32_t insn = 0xf8b500e3; // beq a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

TEST(ISATESTSuite, BNE_0x100_N128)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10]= 0x1234;
    Simulator.reg[11] = 0x5678;
    uint32_t insn = 0xf8b510e3; // bne a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

TEST(ISATESTSuite, BLT_0x100_N128)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x1234;
    Simulator.reg[11] = 0x5678;
    uint32_t insn = 0xf8b540e3; // blt a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

TEST(ISATESTSuite, BGE_0x100_N128)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x1234;
    Simulator.reg[11] = 0x1234;
    uint32_t insn = 0xf8b550e3; // bge a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

TEST(ISATESTSuite, BLTU_0x100_N128)//less than
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = 0x5678;
    Simulator.reg[11] = -1;
    uint32_t insn = 0xf8b560e3; // bltu a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}


TEST(ISATESTSuite, BGEU_0x100_N128)//greater or equal
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x100;

    Simulator.reg[10] = -1;
    Simulator.reg[11] = 0x1234;
    uint32_t insn = 0xf8b570e3; // bgeu a0, a1, -128
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x80 ); //pc = 0x80;
}

#endif