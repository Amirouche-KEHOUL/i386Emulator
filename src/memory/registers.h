#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include "../status/status.h"
#include "../config.h"
#include "../sys/sys.h"

typedef  unsigned int _reg16; 
typedef  unsigned long _reg32;

// 32-bit general-perpose register
typedef struct general_reg_st
{
    struct 
    {
        _reg32 AL:8; 
        _reg32 AH:8; 
        _reg32 msb:16;
    }EAX;
    struct 
    {
        _reg32 DL:8; 
        _reg32 DH:8; 
        _reg32 msb:16;
    }EDX;
    struct 
    {
        _reg32 CL:8; 
        _reg32 CH:8; 
        _reg32 msb:16;
    }ECX;
    struct 
    {
        _reg32 BL:8; 
        _reg32 BH:8; 
        _reg32 msb:16;   
    }EBX;
    struct
    {
        _reg32 BP:16; 
        _reg32 msb:16;
    }EBP;
    struct
    {
        _reg32 SI:16; 
        _reg32 msb:16;
    }ESI;
    struct
    {
        _reg32 DI:16; 
        _reg32 msb:16;
    }EDI;
    struct
    {
        _reg32 SP:16; 
        _reg32 msb:16;
    }ESP;
}_general_regs_st;

// 16-bit segement registers
typedef struct segment_reg_st
{
    _reg16 CS; // code segment
    _reg16 SS; // stack segment
    /* data segments */
    _reg16 DS;
    _reg16 ES;
    _reg16 FS;
    _reg16 GS;
}_segment_regs_st;

// EFLAG register._s = status, _c = control, _x= system flag
typedef struct eflag_reg_st
{
    _reg32 carry_s:1;
    _reg32 RES1:1;
    _reg32 parity_s:1;
    _reg32 RES3:1;
    _reg32 auxilary_carry_s:1;
    _reg32 RES5:1;
    _reg32 zero_s:1;
    _reg32 sign_s:1;
    _reg32 trap_s:1;
    _reg32 interrupt_enable_x:1;
    _reg32 direction_c:1;
    _reg32 overflow_s:1;
    _reg32 io_previlege_level_x:2;
    _reg32 nested_task_s:1;
    _reg32 RES15:1;
    _reg32 resume_x:1;
    _reg32 virtual_8086_mode_x:1;
    _reg32 RES18_31:14;

}_eflag_reg_st;

// instruction register 
typedef struct eip_st
{
    _reg32 IP:16; // Inctuction Pointer
    _reg32 msb:16; // msb: most segnificant bits
}_eip_st;

// Memory management registers
typedef _reg32 _gdtr_reg; // Global Descriptor Table Register. TODO : should store base + limit addresses. size TBC
typedef _reg32 _ldtr_reg; // Local Descriptor Table Register. TODO : should store base + limit addresses. size TBC
typedef _reg32 _idtr_reg; // Interrupt Descriptor Table Register
typedef struct task_reg_st
{
    unsigned int selector : 16 ;
    unsigned int base : 16 ; // TODO : size TBC 
    unsigned int limi : 16 ; // TODO : size TBC 
}_task_reg_st;

// Control registers
typedef struct cr0_reg_st  
{
    unsigned int PE : 1; // Protection Enable
    unsigned int MP : 1; // Math Present
    unsigned int EM : 1; // EMulation
    unsigned int TS : 1; // Task Switched 
    unsigned int ET : 1; // Extension Type
    unsigned int PG : 1; // Paging
} _cr0_reg_st;
typedef _reg32 _cr2_reg ; // Page fault linear address 
typedef _reg32 _cr3_reg_pdbr ; // Page directory base register

// TLB Translation lookaside Buffer 
typedef struct tlb_reg_st
 {
    struct
    {
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag0;
        struct
        {
            unsigned int physical_addr:20;
        }data0;
        
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag1;
        struct
        {
            unsigned int physical_addr:20;
        }data1;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag2;
        struct
        {
            unsigned int physical_addr:20;
        }data2;
            
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag3;
        struct
        {
            unsigned int physical_addr:20;
        }data3;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag4;        
        struct
        {
            unsigned int physical_addr:20;
        }data4;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag5;
        struct
        {
            unsigned int physical_addr:20;
        }data5;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag6;
        struct
        {
            unsigned int physical_addr:20;
        }data6;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag7;
        struct
        {
            unsigned int physical_addr:20;
        }data7;
    }set00;
    
    struct
    {
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag0;
        struct
        {
            unsigned int physical_addr:20;
        }data0;
        
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag1;
        struct
        {
            unsigned int physical_addr:20;
        }data1;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag2;
        struct
        {
            unsigned int physical_addr:20;
        }data2;
            
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag3;
        struct
        {
            unsigned int physical_addr:20;
        }data3;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag4;        
        struct
        {
            unsigned int physical_addr:20;
        }data4;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag5;
        struct
        {
            unsigned int physical_addr:20;
        }data5;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag6;
        struct
        {
            unsigned int physical_addr:20;
        }data6;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag7;
        struct
        {
            unsigned int physical_addr:20;
        }data7;
    }set01;
    
    struct
    {
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag0;
        struct
        {
            unsigned int physical_addr:20;
        }data0;
        
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag1;
        struct
        {
            unsigned int physical_addr:20;
        }data1;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag2;
        struct
        {
            unsigned int physical_addr:20;
        }data2;
            
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag3;
        struct
        {
            unsigned int physical_addr:20;
        }data3;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag4;        
        struct
        {
            unsigned int physical_addr:20;
        }data4;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag5;
        struct
        {
            unsigned int physical_addr:20;
        }data5;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag6;
        struct
        {
            unsigned int physical_addr:20;
        }data6;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag7;
        struct
        {
            unsigned int physical_addr:20;
        }data7;
    }set10;
 
    struct
    {
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag0;
        struct
        {
            unsigned int physical_addr:20;
        }data0;
        
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag1;
        struct
        {
            unsigned int physical_addr:20;
        }data1;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag2;
        struct
        {
            unsigned int physical_addr:20;
        }data2;
            
        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag3;
        struct
        {
            unsigned int physical_addr:20;
        }data3;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag4;        
        struct
        {
            unsigned int physical_addr:20;
        }data4;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag5;
        struct
        {
            unsigned int physical_addr:20;
        }data5;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag6;
        struct
        {
            unsigned int physical_addr:20;
        }data6;

        struct
        {
            unsigned int attribute:3;
            unsigned int valid:1;
            unsigned int linear_addr:20;
        }tag7;
        struct
        {
            unsigned int physical_addr:20;
        }data7;

    }set11;
 
 }_tlb_reg_st;

// #### Functions ####
void reg_init_seg (_segment_regs_st* segment_reg_st, _status* status);
void reg_init_eip (_eip_st* eip_st, _status* status);
void reg_init_gen (_general_regs_st* _general_regs_st, _pins* pins,_sys_cond_st* sys_cond_st, _status* status);
void reg_init_eflags(_eflag_reg_st* eflag_register, _status* status);
void reg_init_cr0 (_cr0_reg_st* cr0_reg_st,_status* status);

#endif //_REGISTERS_H_