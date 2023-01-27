#ifndef _REGISTERS_H_
#define _REGISTERS_H_

typedef  unsigned int reg16; 
typedef  unsigned long reg32;

// 32-bit general-perpose register
typedef struct general_registers
{
    struct 
    {
        reg32 AL:8; 
        reg32 AH:8; 
        reg32 msb:16;
    }EAX;
    struct 
    {
        reg32 DL:8; 
        reg32 DH:8; 
        reg32 msb:16;
    }EDX;
    struct 
    {
        reg32 CL:8; 
        reg32 CH:8; 
        reg32 msb:16;
    }ECX;
    struct 
    {
        reg32 BL:8; 
        reg32 BH:8; 
        reg32 msb:16;   
    }EBX;
    struct
    {
        reg32 BP:16; 
        reg32 msb:16;
    }EBP;
    struct
    {
        reg32 SI:16; 
        reg32 msb:16;
    }ESI;
    struct
    {
        reg32 DI:16; 
        reg32 msb:16;
    }EDI;
    struct
    {
        reg32 SP:16; 
        reg32 msb:16;
    }ESP;
}_general_regs;

// 16-bit segement registers
typedef struct segement_registers
{
    reg16 CS; // code segment
    reg16 SS; // stack segment
    // data segments
    reg16 DS;
    reg16 ES;
    reg16 FS;
    reg16 GS;
}_segment_regs;

// EFLAG register._s = status, _c = control, _x= system flag
typedef struct eflag_register
{
    reg32 carry_s:1;
    reg32 RES1:1;
    reg32 parity_s:1;
    reg32 RES3:1;
    reg32 auxilary_carry_s:1;
    reg32 RES5:1;
    reg32 zero_s:1;
    reg32 sign_s:1;
    reg32 trap_s:1;
    reg32 interrupt_enable_x:1;
    reg32 direction_c:1;
    reg32 overflow_s:1;
    reg32 io_previlege_level_x:2;
    reg32 nested_task_s:1;
    reg32 RES15:1;
    reg32 resume_x:1;
    reg32 virtual_8086_mode_x:1;
    reg32 RES18_31:14;

}_eflag_reg;

// instruction register 
typedef struct Instruction_pointer_register
{
    reg32 IP:16; // Inctuction Pointer
    reg32 msb:16; // msb: most segnificant bits
}_eip;

#endif //_REGISTERS_H_