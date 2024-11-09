#ifndef INS_H
#define INS_H


typedef struct R_Type
{
    unsigned int op_code :7;
    unsigned int rd :5;
    unsigned int funct3 :3;
    unsigned int rs1 :5;
    unsigned int rs2 :5;
    unsigned int funct7 :7;
}r_type_ins;


typedef union RSICV_INS
{
    unsigned int wIns;
    r_type_ins r_Ins;
}riscv_ins;

#endif