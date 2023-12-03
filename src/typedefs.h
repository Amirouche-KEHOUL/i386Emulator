#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

// TODO: change the location of these defines?
#define _GDT 0U
#define _LDT 1U

// segment_descriptor_type
#define _CODE_SEGMENT_DESCRIPTOR 1U
#define _DATA_SEGMENT_DESCRIPTOR 2U
#define _SYS_SEGMENT_DESCRIPTOR 3U

// System and Gate Descriptor Types
#define _AVAILABLE_286_TSS_SYS_DESCRIPTOR_TYPE 0x1
#define _LDT_SYS_DESCRIPTOR_TYPE 0x2
#define _BUSY_286_TSS_SYS_DESCRIPTOR_TYPE 0x3
#define _CALL_GATE_DESCRIPTOR_TYPE 0x4
#define _TASK_GATE_DESCRIPTOR_TYPE 0x5
#define _286_INTERRUPT_GATE_DESCRIPTOR_TYPE 0x6
#define _286_TRAP_GATE_DESCRIPTOR_TYPE 0x7
#define _AVAILABLE_386_TSS_SYS_DESCRIPTOR_TYPE 0x9
#define _BUSY_386_TSS_SYS_DESCRIPTOR_TYPE 0xB
#define _386_CALL_GATE_DESCRIPTOR_TYPE 0xC
#define _386_INTERRUPT_GATE_DESCRIPTOR_TYPE 0xE
#define _386_TRAP_GATE_DESCRIPTOR_TYPE 0xF

#define _CS_REG 0
#define _SS_REG 1
#define _DS_REG 2
#define _ES_REG 3
#define _FS_REG 4
#define _GS_REG 5
#define _TEMP_CODE_SEG 6
#define _TEMP_DATA_SEG 7

#define _NOT_READABLE_CODE_SEGMENT 0U
#define _NOT_WRITABLE_CODE_SEGMENT 0U
#define _READABLE_CODE_SEGMENT 1U
#define _WRITABLE_CODE_SEGMENT 1U

#define _EXECUTABLE__BIT_LOCATION 3U
#define _CODE_DATA_OR_SYSTEM_SEG__BIT_LOCATION 4U
#define _SEGMENT_PRESENT__BIT_LOCATION 7U

typedef unsigned char _byte;
typedef unsigned short _word;
typedef unsigned int _double_word;

typedef unsigned char _8_index;
typedef char _8_displacement;

typedef unsigned short _16_reg;
typedef unsigned short _16_index;
typedef unsigned short _16_offset;
typedef unsigned short _16_bus;
typedef short _16_displacement;

typedef unsigned int _32_reg;
typedef unsigned int _32_index;
typedef unsigned int _32_offset;
typedef unsigned int _32_linear_addr;
typedef unsigned int _32_physical_addr;
typedef int _32_displacement;

#define _16BIT_EFFECT_OPR_SIZE 0
#define _32BIT_EFFECT_OPR_SIZE 1
#define _16BIT_EFFECT_OPR_ADDR_SIZE 0
#define _32BIT_EFFECT_OPR_ADDR_SIZE 1
typedef int _effec_opr_size;
typedef int _effec_opr_addr_size;

// For r8
#define AL_REG_DEF 0
#define CL_REG_DEF 1
#define DL_REG_DEF 2
#define BL_REG_DEF 3
#define AH_REG_DEF 4
#define CH_REG_DEF 5
#define DH_REG_DEF 6
#define BH_REG_DEF 7

// For r16
#define AX_REG_DEF 8
#define CX_REG_DEF 9
#define DX_REG_DEF 10
#define BX_REG_DEF 11
#define SP_REG_DEF 12
#define BP_REG_DEF 13
#define SI_REG_DEF 14
#define DI_REG_DEF 15

// For r32
#define EAX_REG_DEF 16
#define ECX_REG_DEF 17
#define EDX_REG_DEF 18
#define EBX_REG_DEF 19
#define ESP_REG_DEF 20
#define EBP_REG_DEF 21
#define ESI_REG_DEF 22
#define EDI_REG_DEF 23

// 32-bit general-perpose register
typedef struct general_regs_st
{
    struct
    {
        _32_reg AL : 8;
        _32_reg AH : 8;
        _32_reg msb : 16;
    } EAX;
    struct
    {
        _32_reg DL : 8;
        _32_reg DH : 8;
        _32_reg msb : 16;
    } EDX;
    struct
    {
        _32_reg CL : 8;
        _32_reg CH : 8;
        _32_reg msb : 16;
    } ECX;
    struct
    {
        _32_reg BL : 8;
        _32_reg BH : 8;
        _32_reg msb : 16;
    } EBX;
    struct
    {
        _32_reg BP : 16;
        _32_reg msb : 16;
    } EBP;
    struct
    {
        _32_reg SI : 16;
        _32_reg msb : 16;
    } ESI;
    struct
    {
        _32_reg DI : 16;
        _32_reg msb : 16;
    } EDI;
    struct
    {
        _32_reg SP : 16;
        _32_reg msb : 16;
    } ESP;
} _general_regs_st;

typedef struct selector_st
{
    _16_reg requestor_privilege_level : 2; // 0->3 : 0 == highest privilege
    _16_reg table_indicator : 1;           //  If 0 -> _GDT. If 1 -> _LDT
    _16_reg index : 13;                    // Selects one of 8192 descriptors in a descriptor table. The processor multiplies this index value by 8(the length of a descriptor)

} _selector_st;

// Data segment descriptor
typedef struct data_segment_descriptor_st
{
    _32_reg base;
    _32_reg limit : 20;                        // Related to granularity below
    _32_reg segment_present : 1;               // P
    _32_reg descriptor_privilege_level : 2;    // DPL
    _32_reg Code_data_OR_sys_segment : 1;      // CODE/DATA OR system.Must be set to (1) here.
    _32_reg executable : 1;                    // Must be set to (0) here.
    _32_reg available_for_programmer_user : 1; // AVL
    _32_reg granularity : 1;                   // G: If clear (0), the Limit is in 1 Byte blocks (byte granularity). If set (1), the Limit is in 4 KiB blocks (page granularity).
    _32_reg big : 1;                           // B:if clear (0), the descriptor defines a 16-bit protected mode segment. If set (1) it defines a 32-bit protected mode segment. A GDT can have both 16-bit and 32-bit selectors at once.
    _32_reg expand_down : 1;                   // E: is clear (0), segments expands grows UP is set (1) it grows down.
    _32_reg writable : 1;                      // W : specifies whether instructions can write into the segment
    _32_reg accessed : 1;                      // A: accessed bit. The CPU will set it when the segment is accessed unless set to 1 in advance. This means that in case the GDT descriptor is stored in read only pages and this bit is set to 0, the CPU trying to set this bit will trigger a page fault. Best left set to 1 unless otherwise needed.
} _data_segment_descriptor_st;

// Code segment descriptor
typedef struct code_segment_descriptor_st
{
    _32_reg base;
    _32_reg limit : 20;                        // Related to granularity below
    _32_reg segment_present : 1;               // P
    _32_reg descriptor_privilege_level : 2;    // DPL
    _32_reg Code_data_OR_sys_segment : 1;      // CODE/DATA OR system.Must be set to (1) here.
    _32_reg executable : 1;                    // Must be set to (1) here.
    _32_reg granularity : 1;                   // G: If clear (0), the Limit is in 1 Byte blocks (byte granularity). If set (1), the Limit is in 4 KiB blocks (page granularity).
    _32_reg available_for_programmer_user : 1; // AVL
    _32_reg DEFAULT : 1;                       // D: if clear (0), the descriptor defines a 16-bit protected mode segment. If set (1) it defines a 32-bit protected mode segment. A GDT can have both 16-bit and 32-bit selectors at once.(TODO : confirm the comment)
    _32_reg conforming : 1;                    // C: If clear (0) code in this segment can only be executed from the ring set in DPL.If set (1) code in this segment can be executed from an equal or lower privilege level
    _32_reg readable : 1;                      // R : if (1) segment is readable. Specifies whether instructions are allowed to read from the segment
    _32_reg accessed : 1;                      // A : Accessed bit. The CPU will set it when the segment is accessed unless set to 1 in advance. This means that in case the GDT descriptor is stored in read only pages and this bit is set to 0, the CPU trying to set this bit will trigger a page fault. Best left set to 1 unless otherwise needed.
} _code_segment_descriptor_st;

// System segment descriptor
typedef struct system_segment_descriptor_st
{
    _32_reg base;
    _32_reg limit : 20;                        // Related to granularity below
    _32_reg segment_present : 1;               // P
    _32_reg descriptor_privilege_level : 1;    // DPL
    _32_reg Code_data_OR_sys_segment : 1;      // CODE/DATA OR system.Must be set to (0) here.
    _32_reg granularity : 1;                   // G: If clear (0), the Limit is in 1 Byte blocks (byte granularity). If set (1), the Limit is in 4 KiB blocks (page granularity).
    _32_reg available_for_programmer_user : 1; // AVL
    _32_reg type : 4;                          // Value must be
} _system_segment_descriptor_st;

// Call gate descriptor
typedef struct call_gate_descriptor_st
{
    _selector_st selector;                  // Selects a code segments
    _32_reg offset;                         // Points to an entry point of a procedure in the selected code segment (a code segment may contain serveral procedures pointed by call gates)
    _32_reg segment_present : 1;            // P
    _32_reg descriptor_privilege_level : 1; // DPL
    _32_reg Code_data_OR_sys_segment : 1;   // CODE/DATA OR system.Must be set to (0) here.
    _32_reg type : 4;                       // Must be equal to _386_CALL_GATE_DESCRIPTOR_TYPE
    _32_reg count : 5;                      // TODO : confirm role
} _call_gate_descriptor_st;

// 16-bit segement registers
typedef struct segment_regs_st
{
    _selector_st CS; // Code segmment : The segment containing the currently executing sequence of instructions.
    _selector_st SS; // Stack segment
    /* data segments */
    _selector_st DS;
    _selector_st ES;
    _selector_st FS;
    _selector_st GS;
    /* Hidden part (seen only by the processor) */
    _code_segment_descriptor_st *CS_hidden_code_segment_descriptor;
    _data_segment_descriptor_st *SS_hidden_stack_segment_descriptor;
    _data_segment_descriptor_st *DS_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *ES_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *FS_hidden_data_segment_descriptor;
    _data_segment_descriptor_st *GS_hidden_data_segment_descriptor;

    /**/
    _16_reg current_privilege_level : 3; // CPL. Normally Equals to Target DPL ()

} _segment_regs_st;

// Page table entry
typedef struct page_table_entry_st
{
    _32_reg present : 1;                          // p : P=1 indicates that the entry can be used  can be used in address translation
    _32_reg read_write : 1;                       // R/W
    _32_reg user_suppervisor : 1;                 // U/S
    _32_reg accessed : 1;                         // A
    _32_reg dirty : 1;                            // D
    _32_reg available_for_sys_programmer_use : 3; // AVAIL
    _32_reg page_frame_address : 20;
} _page_table_entry_st;

// EFLAG register._s = status, _c = control, _x= system flag
typedef struct eflag_reg_st
{
    _32_reg carry_s : 1;
    _32_reg RES1 : 1;
    _32_reg parity_s : 1;
    _32_reg RES3 : 1;
    _32_reg auxilary_carry_s : 1;
    _32_reg RES5 : 1;
    _32_reg zero_s : 1;
    _32_reg sign_s : 1;
    _32_reg trap_s : 1;
    _32_reg interrupt_enable_x : 1; // Controls the acceptance of external interrupts signalled via the INTR pin
    _32_reg direction_c : 1;
    _32_reg overflow_s : 1;
    _32_reg io_previlege_level_x : 2;
    _32_reg nested_task_s : 1;
    _32_reg RES15 : 1;
    _32_reg resume_x : 1;
    _32_reg virtual_8086_mode_x : 1;
    _32_reg RES18_31 : 14;

} _eflag_reg_st;

// Instruction register.It is not directly visible to the programmer.
typedef struct eip_st
{
    _32_reg IP : 16;  // Inctuction Pointer
    _32_reg msb : 16; // msb: most segnificant bits
} _eip_st;

// Memory management registers
typedef struct dtr_reg_st // Descriptor Table Register.
{
    _32_linear_addr DTR; //
    int type;            // _GDT or _LDT
} _dtr_reg_st;

// Interrupt Descriptor Table Register
typedef struct idtr_st
{
    _32_reg base;
    _16_reg limit;

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

typedef _32_reg _cr2_reg;      // Page fault linear address
typedef _32_reg _cr3_reg_pdbr; // 20 MSB bits (12 LSB bit always 0 - 4K pages) Page directory base register. Stores the physical address of the current page directory

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
        _32_reg L0 : 1;
        _32_reg G0 : 1;
        _32_reg L1 : 1;
        _32_reg G1 : 1;
        _32_reg L2 : 1;
        _32_reg G2 : 1;
        _32_reg L3 : 1;
        _32_reg G3 : 1;
        _32_reg LE : 1;
        _32_reg GE : 1;
        _32_reg reserved : 6; // TODO: reserved ? => TBC
        _32_reg RW0 : 2;
        _32_reg LEN0 : 2;
        _32_reg RW1 : 2;
        _32_reg LEN1 : 2;
        _32_reg RW2 : 2;
        _32_reg LEN2 : 2;
        _32_reg RW3 : 2;
        _32_reg LEN3 : 2;

    } DR7; // Debug control register
    struct
    {
        _32_reg B0 : 1;
        _32_reg B1 : 1;
        _32_reg B2 : 1;
        _32_reg B3 : 1;
        _32_reg reserved : 9; // TODO: reserved ? => TBC
        _32_reg BD : 1;
        _32_reg BS : 1;
        _32_reg BT : 1;

    } DR6; // Debug status register

    _32_reg DR3; // Breakpoint 3 linear address
    _32_reg DR2; // Breakpoint 2 linear address
    _32_reg DR1; // Breakpoint 1 linear address
    _32_reg DR0; // Breakpoint 0 linear address

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
    pin_reset = 0U,
    pin_busy = 1U,
    pin_error = 2U,
    pin_INTR = 3U, // used to signal Maskable interrupts
    pin_NMI = 4U,  // used to signal Non Maskable Interrupts

} _pin_name_enum;

typedef enum pin_state_enum
{
    OFF = 0U,
    ON = 1U,
} _pin_state_enum;

/* memory */
typedef _byte *_physical_memory_ptr;
typedef _byte *_IO_ptr;

/* INterrupts */
typedef struct interrupts_flags_st
{
    struct
    {
        struct
        {
            _16_reg devide : 1;                    // ID 0
            _16_reg bond_check : 1;                // ID 5
            _16_reg invalid_opcode : 1;            // ID 6
            _16_reg coprocessor_not_available : 1; // ID 7
            _16_reg invalid_tss : 1;               // ID 10
            _16_reg segment_not_present : 1;       // ID 11
            _16_reg stack : 1;                     // ID 12
            _16_reg general_protection : 1;        // ID 13
            _16_reg page : 1;                      // ID 14
            _16_reg coprocessor_error : 1;         // ID 16

        } fault;
        struct
        {
            _16_reg breakpoint : 1; // ID 3
            _16_reg overflow : 1;   // ID 4

        } trap;
        struct
        {
            _16_reg double_fault : 1; // ID 8
        } abort;
    } exceptions;
    struct
    {
        _16_reg NMI : 1;  // Signaled by NMI (Non Maskable Interrpts)pin
        _16_reg maskable; // Signaled by INTR pin
    } interrupts;
    // TODO: add debug and  software interrupts
} _interrupts_flags_st;

/* system */
typedef struct sys_cond_st
{
    int unit_faulty : 1;
} _sys_cond_st;

/* Decoder*/
typedef struct ModRM_st
{
    _byte RM : 3;
    _byte REG_OPCODE : 3;
    _byte MOD : 2;
} _ModRM_st;

typedef struct SIB_st
{
    _byte BASE : 3;  // Stores the regitser number to be used as a Base
    _byte INDEX : 3; // Stores the register number to be used as an Index
    _byte SS : 2;    // Sotores the Sacle factor for the index
} _SIB_st;

typedef struct prefetch_queue_st
{
    _byte queue[16];
    _8_index index; // managed by queue read and write functions
} _prefetch_queue_st;

#endif // _TYPEDEFS_H_