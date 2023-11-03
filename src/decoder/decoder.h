#ifndef _DECODER_H_
#define _DECODER_H_

#include "../typedefs.h"
#include "../memory/registers.h"

#define _16BIT_ADDRESSING_FORM 1
#define _32BIT_ADDRESSING_FORM 2

/* 16-Bit Addressing Forms */

#define _BX_PLUS_SI_ 1
#define _BX_PLUS_DI_ 2
#define _BP_PLUS_SI_ 3
#define _BP_PLUS_DI_ 4
#define _SI_ 5
#define _DI_ 6
#define _DISP16_ 7
#define _BX_ 8

#define _BX_PLUS_SI__PLUS_DISP8 9
#define _BX_PLUS_DI__PLUS_DISP8 10
#define _BP_PLUS_SI__PLUS_DISP8 11
#define _BP_PLUS_DI__PLUS_DISP8 12
#define _SI__PLUS_DISP8 13
#define _DI__PLUS_DISP8 14
#define _BP__PLUS_DISP8 15
#define _BX__PLUS_DISP8 16

#define _BX_PLUS_SI__PLUS_DISP16 17
#define _BX_PLUS_DI__PLUS_DISP16 18
#define _BP_PLUS_SI__PLUS_DISP16 19
#define _BP_PLUS_DI__PLUS_DISP16 20
#define _SI__PLUS_DISP16 21
#define _DI__PLUS_DISP16 22
#define _BP__PLUS_DISP16 23
#define _BX__PLUS_DISP16 24

#define _EAX_AX_AL 25
#define _ECX_CX_CL 26
#define _EDX_DX_DL 27
#define _EBX_BX_BL 28
#define _ESP_SP_AH 29
#define _EBP_BP_CH 30
#define _ESI_SI_DH 31
#define _EDI_DI_BH 32

/* 32-Bit Addressing Forms */

#define _EAX_ 32
#define _ECX_ 33
#define _EDX_ 34
#define _EBX_ 35
#define _SIB_FOLLOWS_ 36
#define _DISP32_ 37
#define _ESI_ 38
#define _EDI_ 39

#define _DISP8_EAX_ 40
#define _DISP8_ECX_ 41
#define _DISP8_EDX_ 42
#define _DISP8_EBX_ 43
#define _DISP8_SIB_FOLLOWS_ 45
#define _DISP8_EBP_ 46
#define _DISP8_ESI_ 47
#define _DISP8_EDI_ 48

#define _DISP32_EAX_ 49
#define _DISP32_ECX_ 50
#define _DISP32_EDX_ 51
#define _DISP32_EBX_ 52
#define _DISP32_SIB_FOLLOWS_ 53
#define _DISP32_EBP_ 54
#define _DISP32_ESI_ 55
#define _DISP32_EDI_ 56

// Same as 16
// #define _EAX_AX_AL 57
// #define _ECX_CX_CL 58
// #define _EDX_DX_DL 59
// #define _EBX_BX_BL 60
// #define _ESP_SP_AH 61
// #define _EBP_BP_CH 62
// #define _ESI_SI_DH 63
// #define _EDI_DI_BH 64

#define DEFAULT_SEGMENT_SIZE_16 0U
#define DEFAULT_SEGMENT_SIZE_32 1U

#define _16BIT_EFFECTIVE_ADDR_SIZE 0U
#define _32BIT_EFFECTIVE_ADDR_SIZE 1U

#define _16BIT_EFFECTIVE_OPERAND_SIZE 0U
#define _32BIT_EFFECTIVE_OPERAND_SIZE 1U

#define ADDRESSE_SIZE_PREFIX_NOT_PRESENT 0U
#define ADDRESSE_SIZE_PREFIX_PRESENT 1U

#define OPERAND_SIZE_PREFIX_NOT_PRESENT 0U
#define OPERAND_SIZE_PREFIX_PRESENT 1U

/* SIB byte */
#define _EAX_SIB_ 1
#define _ECX_SIB_ 2
#define _EDX_SIB_ 3
#define _EBX_SIB_ 4
#define _NONE_SIB 5
#define _EBP_SIB 6
#define _ESI_SIB 7
#define _EDI_SIB 8

#define _EAX_MULT_2_SIB_ 9
#define _ECX_MULT_2_SIB_ 10
#define _EDX_MULT_2_SIB_ 11
#define _EBX_MULT_2_SIB_ 12
#define _EBP_MULT_2_SIB 13
#define _ESI_MULT_2_SIB 14
#define _EDI_MULT_2_SIB 15

#define _EAX_MULT_4_SIB_ 9
#define _ECX_MULT_4_SIB_ 10
#define _EDX_MULT_4_SIB_ 11
#define _EBX_MULT_4_SIB_ 12
#define _EBP_MULT_4_SIB 13
#define _ESI_MULT_4_SIB 14
#define _EDI_MULT_4_SIB 15

#define _EAX_MULT_8_SIB_ 16
#define _ECX_MULT_8_SIB_ 17
#define _EDX_MULT_8_SIB_ 18
#define _EBX_MULT_8_SIB_ 19
#define _EBP_MULT_8_SIB 20
#define _ESI_MULT_8_SIB 21
#define _EDI_MULT_8_SIB 22

unsigned int get_effective_address_size(unsigned int default_seg_size, unsigned int adresse_size_prefix_present);

unsigned int get_effective_operand_size(unsigned int default_seg_size, unsigned int operand_size_prefix_present);

#endif // _DECODER_H_