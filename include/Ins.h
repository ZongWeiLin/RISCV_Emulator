#ifndef INS_H
#define INS_H


typedef struct R_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int rd :5;//bit[11:7]
    unsigned int funct3 :3;//bit[14:12]
    unsigned int rs1 :5;//bit[19:15]
    unsigned int rs2 :5;//bit[24:20]
    unsigned int funct7 :7;//bit[31:25]
}r_type_ins;

typedef struct I_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int rd :5;//bit[11:7]
    unsigned int funct3 :3;//bit[14:12]
    unsigned int rs1 :5;//bit[19:15]
    unsigned int imm :12;//bit[31:20]
}i_type_ins;

typedef struct S_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int rd :5;//bit[11:7]
    unsigned int funct3 :3;//bit[14:12]
    unsigned int rs1 :5;//bit[19:15]
    unsigned int rs2 :5;//bit[24:20]
    unsigned int imm :7;//bit[31:25]
}s_type_ins;


typedef union RSICV_INS
{
    unsigned int wIns;
    r_type_ins r_Ins;
    i_type_ins i_Ins;
    s_type_ins s_Ins;
}riscv_ins;

#endif