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
    unsigned int imm_0_to_4 :5;//bit[11:7]
    unsigned int funct3 :3;//bit[14:12]
    unsigned int rs1 :5;//bit[19:15]
    unsigned int rs2 :5;//bit[24:20]
    unsigned int imm_5_to_11 :7;//bit[31:25]
}s_type_ins;

typedef struct B_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int imm_11 :1;//bit[7]
    unsigned int imm_1_to_4:4;//bit[11:8]
    unsigned int funct3 :3;//bit[14:12]
    unsigned int rs1 :5;//bit[19:15]
    unsigned int rs2 :5;//bit[24:20]
    unsigned int imm_5_to_10 :6;//bit[30:25]
    unsigned int imm_12 :1;//bit[31]
}b_type_ins;

typedef struct U_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int rd :5;//bit[11:7]
    unsigned int imm_12_to_31 :20; //bit[31:12]
}u_type_ins;

typedef struct J_Type
{
    unsigned int op_code :7;//bit [6:0]
    unsigned int rd :5;//bit[11:7]
    unsigned int imm_12_to_19 :8; //bit[19:12]
    unsigned int imm_11 :1;//bit[20]
    unsigned int imm_1_to_10 :10;//bit[30:21]
    unsigned int imm_20 :1;//bit[31]
}j_type_ins;



typedef union RSICV_INS
{
    unsigned int wIns;
    r_type_ins r_Ins;
    i_type_ins i_Ins;
    s_type_ins s_Ins;
    b_type_ins b_Ins;
    u_type_ins u_Ins;
    j_type_ins j_Ins;
}riscv_ins;

#endif