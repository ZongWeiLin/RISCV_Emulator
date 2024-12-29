#include <gtest/gtest.h>
#include"../../include/ALISS.h"

TEST(MyTestSuite, MyTestCase) { 
    ASSERT_TRUE(true);
}

                /*IT Day12*/
/*Test lf entry point address load function*/
#if (BUILD_LEVEL == 12)
TEST(MyTestSuite, ELFLoaderTestEntryPoint) {
    const char* test = "../RISCV_elf/hello_world.elf";

    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    EXPECT_EQ(Simulator.pc,0x1014e);
}
#endif


                /*IT Day13*/
/*Test get load adress memory value*/
#if (BUILD_LEVEL == 13)
TEST(MyTestSuite, ELFLoaderTestLoad) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS_CPU Simulator=ALISS_CPU(MEMORY_SIZE);
    Simulator.loadElf(test);
    // EXPECT_EQ(Simulator.get_mem_w(0x1014e),0x3197);
}
#endif

                /*IT Day14*/
/*Test Instruction Fetch*/
#if (BUILD_LEVEL == 14)
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
#if (BUILD_LEVEL == 17)
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
#if (BUILD_LEVEL == 18)
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
#if (BUILD_LEVEL == 19)
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

/*ITDay 20 Add Load/Store Instruction*/
#if (BUILD_LEVEL == 20)

/*-------------------------*/
/*For Test Load Instruction*/
/*-------------------------*/
TEST(ISATESTSuite, LB_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024);; //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    memory64[0x40000 / 8] = 0xffffffff88888888;
    Simulator.reg[10]=0x0;
    Simulator.reg[11]=0x40100;

    uint32_t insn = 0xf0058503; // LB a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(Simulator.reg[10], -120 ); //load -120;
}

TEST(ISATESTSuite, LBU_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024);; //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    memory64[0x40000 / 8] = 0xffffffff88888888;
    Simulator.reg[10]=0x0;
    Simulator.reg[11]=0x40100;

    uint32_t insn = 0xf005c503; // LBU a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(Simulator.reg[10], 0x88 ); //load 0x88;
}

TEST(ISATESTSuite, LH_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024);; //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    memory64[0x40000 / 8] = 0xffffffff88888888;
    Simulator.reg[10]=0x0;
    Simulator.reg[11]=0x40100;

    uint32_t insn = 0xf0059503; // LH a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(Simulator.reg[10], -30584); //load -30584;
}

TEST(ISATESTSuite, LHU_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024); //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    memory64[0x40000 / 8] = 0xffffffff88888888;
    Simulator.reg[10]=0x0;
    Simulator.reg[11]=0x40100;

    uint32_t insn = 0xf005d503; // LHU a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(Simulator.reg[10], 0x8888 ); //load 34952;
}

TEST(ISATESTSuite, LW_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024); //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    memory64[0x40000 / 8] = 0xffffffff88888888;
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x40100;

    uint32_t insn = 0xf005a503; // LHU a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(Simulator.reg[10], -2004318072 ); //load -2004318072;
    
}


/*-------------------------*/
/*For Test Store Instruction*/
/*-------------------------*/
TEST(ISATESTSuite, SB_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024); //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    Simulator.reg[10] = 0xffffffff88888888;
    Simulator.reg[11] = 0x40100;

    memory64[0x40000 / 8 ] =  0x0;
    

    uint32_t insn = 0xf0a58023; // SB a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(memory64[0x40000 /  8], 0x88 ); //store 88 to memory;
    
}

TEST(ISATESTSuite, SH_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024); //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    Simulator.reg[10] = 0xffffffff88888888;
    Simulator.reg[11] = 0x40100;

    memory64[0x40000 / 8 ] =  0x0;
 
    uint32_t insn = 0xf0a59023; // SH a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(memory64[0x40000 / 8], 0x8888 ); //store 8888 to memory;
    
}

TEST(ISATESTSuite, SW_0x40000_0xffffffff88888888)
{
    ALISS_CPU Simulator = ALISS_CPU(4*1024*1024); //4MB size for test
    uint64_t* memory64  = (uint64_t*)Simulator.memory;

    Simulator.reg[10] = 0xffffffff88888888;
    Simulator.reg[11] = 0x40100;

    memory64[0x40000 / 8 ] =  0x0;
 
    uint32_t insn = 0xf0a5a023; // SW a0 -256(a1)
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(memory64[0x40000 / 8], 0x88888888 ); //store 88888888 to memory;
    
}

#endif

/*ITDay 21 Add CSR Instruction*/
#if (BUILD_LEVEL == 21)
TEST(ISATESTSuite, csrrw_0x7cc_0x1234)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x1234;
    uint32_t insn = 0x7cc59573; // csrrw a0 0x7cc a1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x1234 ); //csr write to 1234;
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg  is ori value;
}

TEST(ISATESTSuite, csrrs_0x7cc_0x101)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x101;
    uint32_t insn = 0x7cc5a573; // csrrs a0 0x7cc a1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x1010101010101111 ); //csrset [1], [9];
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg is ori value;
}

TEST(ISATESTSuite, csrrc_0x7cc_0x1010)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x1010;
    uint32_t insn = 0x7cc5b573; // csrrc a0 0x7cc a1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x1010101010100000 ); //csr clear [4], [12];
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg is ori value;
}

TEST(ISATESTSuite, csrrwi_0x7cc_0x2)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    uint32_t insn = 0x7cc15573; // csrrwi x10, 0x7cc, 2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x2 ); //csr write to 2;
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg  is ori value;
}

TEST(ISATESTSuite, csrrsi_0x7cc_0x1)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    uint32_t insn = 0x7cc0e573; // csrrsi x10, 0x7cc, 1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x1010101010101011 ); //csrset [1];
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg is ori value;
}

TEST(ISATESTSuite, csrrci_0x7cc_0x10)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[0x7cc] = 0x1010101010101010;
    Simulator.reg[10] = 0x0;
    uint32_t insn = 0x7cc87573; // csrrci a0 0x7cc 0x10
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x7cc], 0x1010101010101000 ); //csr clear [4];
    EXPECT_EQ(Simulator.reg[10], 0x1010101010101010 ); //reg is ori value;
}
#endif

/*ITDay 22 Add RVI64 Instruction*/
#if (BUILD_LEVEL == 22)
TEST(ISATESTSuite, ADDW0x80000000_0x1)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x80000000;
    Simulator.reg[12] = 0x1;
    uint32_t insn = 0x00c5853b; // addw a0 a1 a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0xFFFFFFFF80000001); //3 + 7 = 10;
}

TEST(ISATESTSuite, ADDIW0x80000000_0x1)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x80000000;
    uint32_t insn = 0x0015851b; // addiw a0 a1 1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0xFFFFFFFF80000001); //3 + 7 = 10;
}
#endif

#if (BUILD_LEVEL == 25)
/*lui instruction test*/
TEST(ISATESTSuite, LUI)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.reg[10] = 0x0;
    uint32_t insn = 0x00001537; // lui,a0, 0x1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0x1000); 
}
/*auipc instruction test*/
TEST(ISATESTSuite, AUIPC)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x1000;
    Simulator.reg[10] = 0x0;
    uint32_t insn = 0x00001517; // auipc a0 0x1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 0x2000); 
}

TEST(ISATESTSuite, EBREAK)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[CSR_MTVEC] = 0x8000;
    Simulator.pc = 0x1000;
    uint32_t insn = 0x00100073; // ebreak;
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x341], 0x1000); 
    EXPECT_EQ(Simulator.next_pc, 0x8000); // jump to mtvec
}

TEST(ISATESTSuite, ECALL)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.csr[CSR_MTVEC] = 0x8000;
    Simulator.pc = 0x1000;
    uint32_t insn = 0x00000073; // ecall;
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.csr[0x341], 0x1000);  //epc = 0x1000
    EXPECT_EQ(Simulator.next_pc, 0x8000); // jump to mtvec
}

TEST(ISATESTSuite, MRET)
{
    ALISS_CPU Simulator = ALISS_CPU();
    Simulator.pc = 0x0;
    Simulator.csr[CSR_MEPC] = 0x1000;
    uint32_t insn = 0x30200073; // mret
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.next_pc, 0x1000);  //ret to epc
}

#endif

#if (BUILD_LEVEL == 26)

TEST(ISATESTSuiteLRSC, LR_W)
{
    ALISS_CPU Simulator = ALISS_CPU(4 * 1024 * 1024);
    uint64_t *memory64 = (uint64_t*) Simulator.memory;
    memory64[0x40000 / 8] = 0xffffffff88888888;

    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0x40000;

    Simulator.reservation = false;
    uint32_t insn = 0x1005a52f; // lr a0, a1
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], -2004318072 ); //load -2004318072;
    EXPECT_EQ(Simulator.reservation, true);
}


TEST(ISATESTSuiteLRSC, SC_W_FAIL)
{
    ALISS_CPU Simulator = ALISS_CPU(4 * 1024 * 1024);
    uint64_t *memory64 = (uint64_t*) Simulator.memory;
 
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0xaaaa;
    Simulator.reg[12] = 0x40000;

    Simulator.reservation = false;
    uint32_t insn = 0x18b6252f; // sc a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(memory64[0x40000 / 8], 0x0); //0 // failure
    EXPECT_EQ(Simulator.reg[10], 1 ); //1 //failure
}

TEST(ISATESTSuiteLRSC, SC_W_SUCCESS)
{
    ALISS_CPU Simulator = ALISS_CPU(4 * 1024 * 1024);
    uint64_t *memory64 = (uint64_t*) Simulator.memory;
 
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 0xaaaa;
    Simulator.reg[12] = 0x40000;

    Simulator.reservation = true;
    uint32_t insn = 0x18b6252f; // sc a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);

    EXPECT_EQ(memory64[0x40000 / 8], 0xaaaa ); 
    EXPECT_EQ(Simulator.reg[10], 0 ); //0 //success
}

#endif

#if (BUILD_LEVEL == 27)
TEST(ISATESTSuiteMPU, MUL_11_N13)
{
    ALISS_CPU Simulator = ALISS_CPU();
    
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 11;
    Simulator.reg[12] = -13;
    uint32_t insn = 0x02c58533; // mul a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], -143); //11 * 13 = -143;
}

TEST(ISATESTSuiteMPU, MULH_11_13)
{
    ALISS_CPU Simulator = ALISS_CPU();
    
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = (int64_t) 11 << 32;
    Simulator.reg[12] = (int64_t) 13 << 32;
    uint32_t insn = 0x02c59533; // mulh a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 143); //11 * 13 = 143;
}

TEST(ISATESTSuiteMPU, DIV_10_5)
{
    ALISS_CPU Simulator = ALISS_CPU();

    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 10;
    Simulator.reg[12] = 5;
    uint32_t insn = 0x02c5c533; // div a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 2); //10 / 5 = 2;
}

TEST(ISATESTSuiteMPU, REM_10_5)
{
    ALISS_CPU Simulator = ALISS_CPU();
    
    Simulator.reg[10] = 0x0;
    Simulator.reg[11] = 11;
    Simulator.reg[12] = 5;
    uint32_t insn = 0x02c5e533; // rem a0, a1, a2
    Simulator.Instruction_Decode_Execution_WriteBack(insn);
    EXPECT_EQ(Simulator.reg[10], 1); //11 % 5 = 1;
}
#endif