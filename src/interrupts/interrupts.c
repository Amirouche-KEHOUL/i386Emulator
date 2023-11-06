#include "interrupts.h"

extern _eflag_reg_st eflag_reg_st;               // Global main.c
extern _pins pins;                               // Global main.c
extern _interrupts_flags_st interrupts_flags_st; // Global main.c
extern _cr0_reg_st cr0_reg_st;
extern _idtr_st idtr_st;

void check_and_service_interrupts(void)
{

  /**
   * Priority among simultanious Interrupts and Exceptions
   * Faults except debug faults                 <--- Highest
   * Trap instructions INTO, INT n, INT 3
   * Debug traps for this instruction
   * Debug faults for next instruction
   * NMI interrupt
   * INTR interrupt                             <--- Lowest
   */

  // while in protection mode (interrupts Off) and if the "limit" value of the IDTR == 0, then cause shutdown.
  if ((cr0_reg_st.PE == 0UL) && (idtr_st.limit == 0UL))
  {
    sys_shutdown();
  }

  //  Faults (except debug faults)
  if (interrupts_flags_st.exceptions.fault.devide == 1)
  {
#ifdef DBG
    printf("Div/0 fault exception\n");
#endif
  }

  if (interrupts_flags_st.exceptions.fault.bond_check == 1)
  {
#ifdef DBG
    printf("Bond check fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.invalid_opcode == 1)
  {
#ifdef DBG
    printf("invalid opcode fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_not_available == 1)
  {
#ifdef DBG
    printf("Coprocessor not available fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.invalid_tss == 1)
  {
#ifdef DBG
    printf("Invalid tss fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.segment_not_present == 1)
  {
#ifdef DBG
    printf("Segment not present fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.stack == 1)
  {
#ifdef DBG
    printf("Stack fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.general_protection == 1)
  {
#ifdef DBG
    printf("General protection fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.page == 1)
  {
#ifdef DBG
    printf("Page fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_error == 1)
  {
#ifdef DBG
    printf("Coprocessor fault exception\n");
#endif
  }

  // Traps
  if (interrupts_flags_st.exceptions.trap.breakpoint == 1)
  {
#ifdef DBG
    printf("Breakpoint trap exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.trap.overflow == 1)
  {
#ifdef DBG
    printf("Overflow trap exception\n");
#endif
  }

  // Non Maskable Interrupt via NMI PIN
  if (interrupts_flags_st.interrupts.NMI == 1)
  {
#ifdef DBG
    printf("NMI interruption\n");
#endif
  }

  // Maskable Interrupts via INTR PIN
  if (eflag_reg_st.interrupt_enable_x == ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN)
  {
#ifdef DBG
    printf("Maskable interrupts enabled !\n");
#endif
  }
}