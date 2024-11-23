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
