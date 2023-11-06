#include "prefetch_queue.h"
// main.c
extern _physical_memory_ptr physical_memory_ptr;
extern _segment_regs_st segment_regs_st;

// decoder.c
extern _ModRM_st ModRM_st;
extern _prefetch_queue_st prefetch_queue_st;
extern void (*one_byte_opcode_map[16][16])(void); // Page 414
extern void (*two_byte_opcode_map[16][16])(void); // Page 415
extern void (*ModRM_opcode_map[8][8])(void);      // Page 416

void fetch_prefetch_queue(void)
{
    unsigned char i = 0;
    _32_physical_addr physical_addr = 0;

    for (i = 0; i < 16; i++)
    {
        physical_addr = logical_to_physical_addr((get_EIP() + i), segment_regs_st.CS_hidden_code_segment_descriptor, _CODE_SEGMENT_DESCRIPTOR);
        prefetch_queue_st.queue[i] = physical_memory_read_byte(physical_memory_ptr, physical_addr);
    }
    prefetch_queue_st.index = 0;
}

// Reads byte from prefetch queue and increments the read index
_byte stream_byte_prefetch_queue(void)
{
    _byte ret = prefetch_queue_st.queue[prefetch_queue_st.index];
    if (prefetch_queue_st.index == 15U) // If end of the queue prefetch the next 16 bytes
    {
        fetch_prefetch_queue();
        return ret;
    }
    prefetch_queue_st.index++;
    return ret;
}

void read_ModRM_byte_to_st(void)
{
    _byte byte = stream_byte_prefetch_queue();
    ModRM_st.RM = (_byte)(byte & 0x07);
    ModRM_st.REG_OPCODE = (_byte)((byte & 0x38) >> 3);
    // TODO: confirm the conversion warning (should be ok )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    ModRM_st.MOD = (_byte)((byte & 0xC0) >> 6);
#pragma GCC diagnostic pop
}
