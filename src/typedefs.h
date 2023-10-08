#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

// TODO: change the location of these defines?
#define _GDT 0
#define _LDT 1

typedef unsigned char _8reg;
typedef unsigned int _16reg;
typedef unsigned long _32reg;
typedef unsigned int _16bus;
typedef unsigned char _byte;
typedef unsigned char _16addr;
typedef unsigned long _32addr;

// 32-bit general-perpose register
typedef struct general_reg_st
{
    struct
    {
        _32reg AL : 8;
        _32reg AH : 8;
        _32reg msb : 16;
    } EAX;
    struct
    {
        _32reg DL : 8;
        _32reg DH : 8;
        _32reg msb : 16;
    } EDX;
    struct
    {
        _32reg CL : 8;
        _32reg CH : 8;
        _32reg msb : 16;
    } ECX;
    struct
    {
        _32reg BL : 8;
        _32reg BH : 8;
        _32reg msb : 16;
    } EBX;
    struct
    {
        _32reg BP : 16;
        _32reg msb : 16;
    } EBP;
    struct
    {
        _32reg SI : 16;
        _32reg msb : 16;
    } ESI;
    struct
    {
        _32reg DI : 16;
        _32reg msb : 16;
    } EDI;
    struct
    {
        _32reg SP : 16;
        _32reg msb : 16;
    } ESP;
} _general_regs_st;

// Data segment descriptor
typedef struct data_segment_descriptor_st
{
    _32reg base;
    _16reg limit : 20;
    _8reg segment_present : 1;               // P
    _8reg granularity : 1;                   // G
    _8reg descriptor_privilege_level : 1;    // DPL
    _8reg available_for_programmer_user : 1; // AVL
    _8reg big : 1;                           // B
    _8reg expand_down : 1;                   // E
    _8reg writable : 1;                      // W : specifies whether instructions can write into the segment
    _8reg accessed : 1;                      // A
} _data_segment_descriptor_st;

// Code segment descriptor
typedef struct code_segment_descriptor_st
{
    _32reg base;
    _16reg limit : 20;
    _8reg segment_present : 1;               // P
    _8reg granularity : 1;                   // G
    _8reg descriptor_privilege_level : 1;    // DPL
    _8reg available_for_programmer_user : 1; // AVL
    _8reg DEFAULT : 1;                       // D
    _8reg conforming : 1;                    // C
    _8reg readable : 1;                      // R : specifies whether instructions are allowed to read from the segment
    _8reg accessed : 1;                      // A
} _code_segment_descriptor_st;

// System segment descriptor
typedef struct system_segment_descriptor_st
{
    _32reg base;
    _16reg limit : 20;
    _8reg segment_present : 1;               // P
    _8reg granularity : 1;                   // G
    _8reg descriptor_privilege_level : 1;    // DPL
    _8reg available_for_programmer_user : 1; // AVL
    // TODO: add TYPE field ?
} _system_segment_descriptor_st;

// 16-bit segement registers
typedef struct segment_regs_st
{
    _16reg CS; // Code segmment : The segment containing the currently executing sequence of instructions.
    _16reg SS; // Stack segment
    /* data segments */
    _16reg DS;
    _16reg ES;
    _16reg FS;
    _16reg GS;
    // Hidden part (seen only by the processor)
    _code_segment_descriptor_st *CS_hidden_code_segment_descriptor;
    _system_segment_descriptor_st *SS_hidden_stack_segment_descriptor; // TODO: TBC the the type of the descriptor
    _data_segment_descriptor_st *DS_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *ES_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *FS_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *GS_hidden_data_segment_descriptor;

} _segment_regs_st;

// Page table entry
typedef struct page_table_entry_st
{
    _32reg present : 1;                          // p : P=1 indicates that the entry can be used  can be used in address translation
    _32reg read_write : 1;                       // R/W
    _32reg user_suppervisor : 1;                 // U/S
    _32reg accessed : 1;                         // A
    _32reg dirty : 1;                            // D
    _32reg available_for_sys_programmer_use : 3; // AVAIL
    _32reg page_frame_address : 20;
} _page_table_entry_st;

// EFLAG register._s = status, _c = control, _x= system flag
typedef struct eflag_reg_st
{
    _32reg carry_s : 1;
    _32reg RES1 : 1;
    _32reg parity_s : 1;
    _32reg RES3 : 1;
    _32reg auxilary_carry_s : 1;
    _32reg RES5 : 1;
    _32reg zero_s : 1;
    _32reg sign_s : 1;
    _32reg trap_s : 1;
    _32reg interrupt_enable_x : 1; // Controls the acceptance of external interrupts signalled via the INTR pin
    _32reg direction_c : 1;
    _32reg overflow_s : 1;
    _32reg io_previlege_level_x : 2;
    _32reg nested_task_s : 1;
    _32reg RES15 : 1;
    _32reg resume_x : 1;
    _32reg virtual_8086_mode_x : 1;
    _32reg RES18_31 : 14;

} _eflag_reg_st;

// Instruction register.It is not directly visible to the programmer.
typedef struct eip_st
{
    _32reg IP : 16;  // Inctuction Pointer
    _32reg msb : 16; // msb: most segnificant bits
} _eip_st;

// Memory management registers
typedef struct dtr_reg_st // Descriptor Table Register. TODO : should store base + limit addresses. size TBC
{
    _32addr DTR;
    int type; // _GDT or _LDT
} _dtr_reg_st;

// Interrupt Descriptor Table Register
typedef struct idtr_st
{
    _32reg base;
    _16reg limit;

} _idtr_st;

typedef struct task_reg_st
{
    unsigned int selector : 16;
    unsigned int base : 16; // TODO : size TBC
    unsigned int limi : 16; // TODO : size TBC
} _task_reg_st;

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

typedef _32reg _cr2_reg;      // Page fault linear address
typedef _32reg _cr3_reg_pdbr; // Page directory base register. Stores the physical address of the current page directory

// TLB Translation lookaside Buffer
typedef struct tlb_reg_st
{
    struct
    {
        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag0;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data0;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag1;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data1;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag2;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data2;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag3;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data3;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag4;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data4;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag5;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data5;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag6;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data6;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag7;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data7;
    } set00;

    struct
    {
        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag0;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data0;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag1;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data1;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag2;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data2;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag3;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data3;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag4;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data4;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag5;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data5;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag6;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data6;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag7;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data7;
    } set01;

    struct
    {
        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag0;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data0;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag1;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data1;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag2;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data2;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag3;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data3;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag4;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data4;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag5;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data5;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag6;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data6;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag7;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data7;
    } set10;

    struct
    {
        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag0;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data0;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag1;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data1;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag2;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data2;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag3;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data3;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag4;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data4;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag5;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data5;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag6;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data6;

        struct
        {
            unsigned int attribute : 3;
            unsigned int valid : 1;
            unsigned int linear_32b_addr : 20;
        } tag7;
        struct
        {
            unsigned int physical_32b_addr : 20;
        } data7;

    } set11;

} _tlb_reg_st;

/**
 * @brief Debug registers
 */
typedef struct debug_reg_st
{
    struct
    {
        _32reg L0 : 1;
        _32reg G0 : 1;
        _32reg L1 : 1;
        _32reg G1 : 1;
        _32reg L2 : 1;
        _32reg G2 : 1;
        _32reg L3 : 1;
        _32reg G3 : 1;
        _32reg LE : 1;
        _32reg GE : 1;
        _32reg reserved : 6; // TODO: reserved ? => TBC
        _32reg RW0 : 2;
        _32reg LEN0 : 2;
        _32reg RW1 : 2;
        _32reg LEN1 : 2;
        _32reg RW2 : 2;
        _32reg LEN2 : 2;
        _32reg RW3 : 2;
        _32reg LEN3 : 2;

    } DR7; // Debug control register
    struct
    {
        _32reg B0 : 1;
        _32reg B1 : 1;
        _32reg B2 : 1;
        _32reg B3 : 1;
        _32reg reserved : 9; // TODO: reserved ? => TBC
        _32reg BD : 1;
        _32reg BS : 1;
        _32reg BT : 1;

    } DR6; // Debug status register

    _32reg DR3; // Breakpoint 3 linear address
    _32reg DR2; // Breakpoint 2 linear address
    _32reg DR1; // Breakpoint 1 linear address
    _32reg DR0; // Breakpoint 0 linear address

    /*
    struct
    {

    } DR5; // Reserved
    struct
    {

    } DR4; // Reserved
    */
} _debug_reg_st;

/* Chip pins data structure */ // TODO confirm how to limit enum to a given values

typedef unsigned int _pins;

typedef enum pin_name_enum
{
    pin_reset = 0,
    pin_busy = 1,
    pin_error = 2,
    pin_INTR = 3, // used to signal Maskable interrupts
    pin_NMI = 4,  // used to signal Non Maskable Interrupts

} _pin_name_enum;

typedef enum pin_state_enum
{
    OFF = 0,
    ON = 1
} _pin_state_enum;

/* memory */
typedef _byte *_physical_memory_ptr;
typedef _byte *_IO_ptr;

typedef struct selector_st
{
    _16reg index : 13;
    _16reg table_indicator : 1;           //  If 0 -> _GDT. If 1 -> _LDT
    _16reg requestor_privilege_level : 2; // 0->3 : 0 == highest privilege

} _selector_st;

/* INterrupts */
typedef struct interrupts_flags_st
{
    struct
    {
        struct
        {
            _16reg devide : 1;                    // ID 0
            _16reg bond_check : 1;                // ID 5
            _16reg invalid_opcode : 1;            // ID 6
            _16reg coprocessor_not_available : 1; // ID 7
            _16reg invalid_tss : 1;               // ID 10
            _16reg segment_not_present : 1;       // ID 11
            _16reg stack : 1;                     // ID 12
            _16reg general_protection : 1;        // ID 13
            _16reg page : 1;                      // ID 14
            _16reg coprocessor_error : 1;         // ID 16

        } fault;
        struct
        {
            _16reg breakpoint : 1; // ID 3
            _16reg overflow : 1;   // ID 4

        } trap;
        struct
        {
            _16reg double_fault : 1; // ID 8
        } abort;
    } exceptions;
    struct
    {
        _16reg NMI : 1;  // Signaled by NMI (Non Maskable Interrpts)pin
        _16reg maskable; // Signaled by INTR pin
    } interrupts;
    // TODO: add debug and  software interrupts
} _interrupts_flags_st;

/* system */
typedef struct sys_cond_st
{
    int unit_faulty : 1;
} _sys_cond_st;

#endif // _TYPEDEFS_H_