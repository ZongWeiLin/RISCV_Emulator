typedef struct Machine_Information_Reg
{
    unsigned long long mvendorid;
    unsigned long long marchid;
    unsigned long long mimpid;
    unsigned long long mhartid;
}machine_infor_reg;

typedef struct Machine_Trap_Setup
{
    unsigned long long mstatus;
    unsigned long long misa;
    unsigned long long medelg;
    unsigned long long midelg;
    unsigned long long mie;
    unsigned long long mtvec;
    unsigned long long mcounteren;
}machine_trap_setup_reg;

typedef struct Machine_Trap_Handling
{
    unsigned long long mscratch;
    unsigned long long mepc;
    unsigned long long mcause;
    unsigned long long mtval;
    unsigned long long mip;
}machine_trap_handling_reg;

typedef struct Machine_Memory_Protection
{
    unsigned long long pmpcfg[16];
}machine_memory_protection_reg;

typedef struct CSR
{
    machine_infor_reg mach_infor_reg;
    machine_trap_setup_reg mach_trap_setup_reg;
    machine_trap_handling_reg mach_trap_handle_reg;
    machine_memory_protection_reg mach_mem_protect_reg;
}csr;


typedef union CSR_Reg
{
    unsigned long long dW_csr[32];
    csr strcut_csr;
}csr_reg;


// Machine-Level CSR Address Macros
#define CSR_MSTATUS         0x300  // Machine Status
#define CSR_MISA            0x301  // Machine ISA
#define CSR_MEDELEG         0x302  // Machine Exception Delegation
#define CSR_MIDELEG         0x303  // Machine Interrupt Delegation
#define CSR_MIE             0x304  // Machine Interrupt Enable
#define CSR_MTVEC           0x305  // Machine Trap-Vector Base Address
#define CSR_MCOUNTEREN      0x306  // Machine Counter Enable
#define CSR_MSCRATCH        0x340  // Machine Scratch Register
#define CSR_MEPC            0x341  // Machine Exception Program Counter
#define CSR_MCAUSE          0x342  // Machine Trap Cause
#define CSR_MTVAL           0x343  // Machine Trap Value
#define CSR_MIP             0x344  // Machine Interrupt Pending
#define CSR_MTINST          0x34A  // Machine Trap Instruction (Optional)
#define CSR_MTVAL2          0x34B  // Machine Trap Value 2 (Optional)

// Performance Counter Macros
#define CSR_MCYCLE          0xB00  // Machine Cycle Counter
#define CSR_MINSTRET        0xB02  // Machine Instructions Retired Counter
#define CSR_MHPMCOUNTER3    0xB03  // Performance Monitoring Counter 3
#define CSR_MHPMCOUNTER4    0xB04  // Performance Monitoring Counter 4
#define CSR_MHPMCOUNTER5    0xB05  // Performance Monitoring Counter 5
#define CSR_MHPMCOUNTER6    0xB06  // Performance Monitoring Counter 6
#define CSR_MHPMCOUNTER7    0xB07  // Performance Monitoring Counter 7
#define CSR_MHPMCOUNTER8    0xB08  // Performance Monitoring Counter 8
#define CSR_MHPMCOUNTER9    0xB09  // Performance Monitoring Counter 9
#define CSR_MHPMCOUNTER10   0xB0A  // Performance Monitoring Counter 10
#define CSR_MHPMCOUNTER11   0xB0B  // Performance Monitoring Counter 11
#define CSR_MHPMCOUNTER12   0xB0C  // Performance Monitoring Counter 12
#define CSR_MHPMCOUNTER13   0xB0D  // Performance Monitoring Counter 13
#define CSR_MHPMCOUNTER14   0xB0E  // Performance Monitoring Counter 14
#define CSR_MHPMCOUNTER15   0xB0F  // Performance Monitoring Counter 15
#define CSR_MHPMCOUNTER16   0xB10  // Performance Monitoring Counter 16
#define CSR_MHPMCOUNTER17   0xB11  // Performance Monitoring Counter 17
#define CSR_MHPMCOUNTER18   0xB12  // Performance Monitoring Counter 18
#define CSR_MHPMCOUNTER19   0xB13  // Performance Monitoring Counter 19
#define CSR_MHPMCOUNTER20   0xB14  // Performance Monitoring Counter 20
#define CSR_MHPMCOUNTER21   0xB15  // Performance Monitoring Counter 21
#define CSR_MHPMCOUNTER22   0xB16  // Performance Monitoring Counter 22
#define CSR_MHPMCOUNTER23   0xB17  // Performance Monitoring Counter 23
#define CSR_MHPMCOUNTER24   0xB18  // Performance Monitoring Counter 24
#define CSR_MHPMCOUNTER25   0xB19  // Performance Monitoring Counter 25
#define CSR_MHPMCOUNTER26   0xB1A  // Performance Monitoring Counter 26
#define CSR_MHPMCOUNTER27   0xB1B  // Performance Monitoring Counter 27
#define CSR_MHPMCOUNTER28   0xB1C  // Performance Monitoring Counter 28
#define CSR_MHPMCOUNTER29   0xB1D  // Performance Monitoring Counter 29
#define CSR_MHPMCOUNTER30   0xB1E  // Performance Monitoring Counter 30
#define CSR_MHPMCOUNTER31   0xB1F  // Performance Monitoring Counter 31

// Performance Event Selector Macros
#define CSR_MHPMEVENT3      0x323  // Performance Event Selector 3
#define CSR_MHPMEVENT4      0x324  // Performance Event Selector 4
#define CSR_MHPMEVENT5      0x325  // Performance Event Selector 5
#define CSR_MHPMEVENT6      0x326  // Performance Event Selector 6
#define CSR_MHPMEVENT7      0x327  // Performance Event Selector 7
#define CSR_MHPMEVENT8      0x328  // Performance Event Selector 8
#define CSR_MHPMEVENT9      0x329  // Performance Event Selector 9
#define CSR_MHPMEVENT10     0x32A  // Performance Event Selector 10
#define CSR_MHPMEVENT11     0x32B  // Performance Event Selector 11
#define CSR_MHPMEVENT12     0x32C  // Performance Event Selector 12
#define CSR_MHPMEVENT13     0x32D  // Performance Event Selector 13
#define CSR_MHPMEVENT14     0x32E  // Performance Event Selector 14
#define CSR_MHPMEVENT15     0x32F  // Performance Event Selector 15
#define CSR_MHPMEVENT16     0x330  // Performance Event Selector 16
#define CSR_MHPMEVENT17     0x331  // Performance Event Selector 17
#define CSR_MHPMEVENT18     0x332  // Performance Event Selector 18
#define CSR_MHPMEVENT19     0x333  // Performance Event Selector 19
#define CSR_MHPMEVENT20     0x334  // Performance Event Selector 20
#define CSR_MHPMEVENT21     0x335  // Performance Event Selector 21
#define CSR_MHPMEVENT22     0x336  // Performance Event Selector 22
#define CSR_MHPMEVENT23     0x337  // Performance Event Selector 23
#define CSR_MHPMEVENT24     0x338  // Performance Event Selector 24
#define CSR_MHPMEVENT25     0x339  // Performance Event Selector 25
#define CSR_MHPMEVENT26     0x33A  // Performance Event Selector 26
#define CSR_MHPMEVENT27     0x33B  // Performance Event Selector 27
#define CSR_MHPMEVENT28     0x33C  // Performance Event Selector 28
#define CSR_MHPMEVENT29     0x33D  // Performance Event Selector 29
#define CSR_MHPMEVENT30     0x33E  // Performance Event Selector 30
#define CSR_MHPMEVENT31     0x33F  // Performance Event Selector 31
