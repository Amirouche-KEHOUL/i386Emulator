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

  // hndle divition by 0

  // Non Maskable Interrupt via NMI PIN
  if (pin_read(&pins, pin_NMI) == ON)
  {
  }

  // Maskable Interrupts via INTR PIN
  if (eflag_reg_st.interrupt_enable_x == ACCEPT_EXTERNAL_INTERRUPT_VIA_INTR_PIN)
  {
  }
}