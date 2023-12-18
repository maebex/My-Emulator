#ifndef C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02
#define C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02

#include <stdint.h>

/* TYPES */

typedef enum{
  Cpu_Error_Success = 0U,         // Success
  Cpu_Error_UnknownMode = 1U,     // Unknown state value passed to Cpu_SetState()
}Cpu_Error_enm;

typedef uint32_t Cpu_Register_ui32; 

typedef enum{
  Cpu_PL_PL0  = 0,
  Cpu_PL_PL1  = 1,
  Cpu_PL_PL2  = 2,
} Cpu_Privilege_enm;

typedef enum{
  Cpu_Mode_USR_en   = 0b10000,    // User
  Cpu_Mode_FIQ_en   = 0b10001,    // FIQ
  Cpu_Mode_IRQ_en   = 0b10010,    // IRQ
  Cpu_Mode_SVC_en   = 0b10011,    // Supervisor
  Cpu_Mode_ABT_en   = 0b10111,    // Abort
  Cpu_Mode_UND_en   = 0b11011,    // Undefined
  Cpu_Mode_SYS_en   = 0b11111     // System
} Cpu_Mode_enm;

typedef struct{
  Cpu_Register_ui32 *R0_pui32;
  Cpu_Register_ui32 *R1_pui32;
  Cpu_Register_ui32 *R2_pui32;
  Cpu_Register_ui32 *R3_pui32;
  Cpu_Register_ui32 *R4_pui32;
  Cpu_Register_ui32 *R5_pui32;
  Cpu_Register_ui32 *R6_pui32;
  Cpu_Register_ui32 *R7_pui32;
  Cpu_Register_ui32 *R8_pui32;
  Cpu_Register_ui32 *R9_pui32;
  Cpu_Register_ui32 *R10_pui32;
  Cpu_Register_ui32 *R11_pui32;
  Cpu_Register_ui32 *R12_pui32;
  Cpu_Register_ui32 *SP_pui32;
  Cpu_Register_ui32 *LR_pui32;
  Cpu_Register_ui32 *PC_pui32;
  Cpu_Register_ui32 *PSR_pui32;
} Cpu_Registers_st;

typedef struct{
  Cpu_Mode_enm Mode;
  Cpu_Privilege_enm Privilege;
  Cpu_Registers_st Registers;
}Cpu_Processor_st;


/* GLOBAL VARIABLES */

// CPU
extern Cpu_Processor_st CPU;

// BANKED REGISTERS 
// User registers
extern Cpu_Register_ui32 R0;
extern Cpu_Register_ui32 R1;
extern Cpu_Register_ui32 R2;
extern Cpu_Register_ui32 R3;
extern Cpu_Register_ui32 R4;
extern Cpu_Register_ui32 R5;
extern Cpu_Register_ui32 R6;
extern Cpu_Register_ui32 R7;
extern Cpu_Register_ui32 R8;
extern Cpu_Register_ui32 R9;
extern Cpu_Register_ui32 R10;
extern Cpu_Register_ui32 R11;
extern Cpu_Register_ui32 R12;
extern Cpu_Register_ui32 SP;
extern Cpu_Register_ui32 LR;
extern Cpu_Register_ui32 PC;
extern Cpu_Register_ui32 CPSR;

// FIQ Registers
extern Cpu_Register_ui32 R8_fiq;
extern Cpu_Register_ui32 R9_fiq;
extern Cpu_Register_ui32 R10_fiq;
extern Cpu_Register_ui32 R11_fiq;
extern Cpu_Register_ui32 R12_fiq;
extern Cpu_Register_ui32 SP_fiq;
extern Cpu_Register_ui32 LR_fiq;
extern Cpu_Register_ui32 SPSR_fiq;

// IRQ Registers
extern Cpu_Register_ui32 SP_irq;
extern Cpu_Register_ui32 LR_irq;
extern Cpu_Register_ui32 SPSR_irq;

// Abort Registers
extern Cpu_Register_ui32 SP_abt;
extern Cpu_Register_ui32 LR_abt;
extern Cpu_Register_ui32 SPSR_abt;

// Supervisor Registers
extern Cpu_Register_ui32 SP_svc;
extern Cpu_Register_ui32 LR_svc;
extern Cpu_Register_ui32 SPSR_svc;

// Undefined Registers
extern Cpu_Register_ui32 SP_und;
extern Cpu_Register_ui32 LR_und;
extern Cpu_Register_ui32 SPSR_und;


Cpu_Error_enm Cpu_Reset_ui32(void);
Cpu_Error_enm Cpu_SetState_ui32(const Cpu_Mode_enm f_Mode);
Cpu_Mode_enm Cpu_GetState_ui32(void);
Cpu_Privilege_enm Cpu_GetPrivilege_ui32(void);
Cpu_Processor_st* Cpu_GetCpu_pst(void);




#endif /* C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02 */
