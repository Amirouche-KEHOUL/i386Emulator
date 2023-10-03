#include "interrupts.h"

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
#ifdef VERBOSE
    printf("Div/0 fault exception\n");
#endif
  }

  if (interrupts_flags_st.exceptions.fault.bond_check == 1)
  {
#ifdef VERBOSE
    printf("Bond check fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.invalid_opcode == 1)
  {
#ifdef VERBOSE
    printf("invalid opcode fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_not_available == 1)
  {
#ifdef VERBOSE
    printf("Coprocessor not available fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.invalid_tss == 1)
  {
#ifdef VERBOSE
    printf("Invalid tss fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.segment_not_present == 1)
  {
#ifdef VERBOSE
    printf("Segment not present fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.stack == 1)
  {
#ifdef VERBOSE
    printf("Stack fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.general_protection == 1)
  {
#ifdef VERBOSE
    printf("General protection fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.page == 1)
  {
#ifdef VERBOSE
    printf("Page fault exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_error == 1)
  {
#ifdef VERBOSE
    printf("Coprocessor fault exception\n");
#endif
  }

  // Traps
  if (interrupts_flags_st.exceptions.trap.breakpoint == 1)
  {
#ifdef VERBOSE
    printf("Breakpoint trap exception\n");
#endif
  }
  if (interrupts_flags_st.exceptions.trap.overflow == 1)
  {
#ifdef VERBOSE
    printf("Overflow trap exception\n");
#endif
  }

  // Non Maskable Interrupt via NMI PIN
  if (interrupts_flags_st.interrupts.NMI == 1)
  {
#ifdef VERBOSE
    printf("NMI interruption\n");
#endif
  }

  // Maskable Interrupts via INTR PIN
  if (eflag_reg_st.interrupt_enable_x == ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN)
  {
#ifdef VERBOSE
    printf("Maskable interrupts enabled !\n");
#endif
  }
}