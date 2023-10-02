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

  //  Faults (except debug faults)
  if (interrupts_flags_st.exceptions.fault.devide == 1)
  {
    printf("Div/0 fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.bond_check == 1)
  {
    printf("Bond check fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.invalid_opcode == 1)
  {
    printf("invalid opcode fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_not_available == 1)
  {
    printf("Coprocessor not available fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.invalid_tss == 1)
  {
    printf("Invalid tss fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.segment_not_present == 1)
  {
    printf("Segment not present fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.stack == 1)
  {
    printf("Stack fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.general_protection == 1)
  {
    printf("General protection fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.page == 1)
  {
    printf("Page fault exception\n");
  }
  if (interrupts_flags_st.exceptions.fault.coprocessor_error == 1)
  {
    printf("Coprocessor fault exception\n");
  }

  // Traps
  if (interrupts_flags_st.exceptions.trap.breakpoint == 1)
  {
    printf("Breakpoint trap exception\n");
  }
  if (interrupts_flags_st.exceptions.trap.overflow == 1)
  {
    printf("Overflow trap exception\n");
  }

  // Non Maskable Interrupt via NMI PIN
  if (interrupts_flags_st.interrupts.NMI == 1)
  {
    printf("NMI interruption\n");
  }

  // Maskable Interrupts via INTR PIN
  if (eflag_reg_st.interrupt_enable_x == ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN)
  {
    printf("Maskable interrupts enabled !\n");
  }
}