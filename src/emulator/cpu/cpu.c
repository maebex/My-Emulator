#include "cpu.h"

static void SetStateUsr_vd(void);
static void SetStateSvc_vd(void);

// CPU
Cpu_Processor_st CPU;

// User registers
Cpu_Register_ui32 R0;
Cpu_Register_ui32 R1;
Cpu_Register_ui32 R2;
Cpu_Register_ui32 R3;
Cpu_Register_ui32 R4;
Cpu_Register_ui32 R5;
Cpu_Register_ui32 R6;
Cpu_Register_ui32 R7;
Cpu_Register_ui32 R8;
Cpu_Register_ui32 R9;
Cpu_Register_ui32 R10;
Cpu_Register_ui32 R11;
Cpu_Register_ui32 R12;
Cpu_Register_ui32 SP;
Cpu_Register_ui32 LR;
Cpu_Register_ui32 PC;
Cpu_Register_ui32 CPSR;

// FIQ Registers
Cpu_Register_ui32 R8_fiq;
Cpu_Register_ui32 R9_fiq;
Cpu_Register_ui32 R10_fiq;
Cpu_Register_ui32 R11_fiq;
Cpu_Register_ui32 R12_fiq;
Cpu_Register_ui32 SP_fiq;
Cpu_Register_ui32 LR_fiq;
Cpu_Register_ui32 SPSR_fiq;

// IRQ Registers
Cpu_Register_ui32 SP_irq;
Cpu_Register_ui32 LR_irq;
Cpu_Register_ui32 SPSR_irq;

// Abort Registers
Cpu_Register_ui32 SP_abt;
Cpu_Register_ui32 LR_abt;
Cpu_Register_ui32 SPSR_abt;

// Supervisor Registers
Cpu_Register_ui32 SP_svc;
Cpu_Register_ui32 LR_svc;
Cpu_Register_ui32 SPSR_svc;

// Undefined Registers
Cpu_Register_ui32 SP_und;
Cpu_Register_ui32 LR_und;
Cpu_Register_ui32 SPSR_und;


Cpu_Error_enm Cpu_Reset_ui32(void)
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Processor always starts in SVC mode
  Error_ui32 = Cpu_SetState_ui32(Cpu_Mode_SVC_en);
  if(Cpu_Error_Success!=Error_ui32)
  {
    return Error_ui32;
  }
  // Set GP Registers - they always stay the same
  CPU.Registers.R0_pui32 = &R0;
  CPU.Registers.R1_pui32 = &R1;
  CPU.Registers.R2_pui32 = &R2;
  CPU.Registers.R3_pui32 = &R3;
  CPU.Registers.R4_pui32 = &R4;
  CPU.Registers.R5_pui32 = &R5;
  CPU.Registers.R6_pui32 = &R6;
  CPU.Registers.R7_pui32 = &R7;
}

Cpu_Error_enm Cpu_SetState_ui32(const Cpu_Mode_enm f_Mode)
{
  uint32_t Error_ui32 = Cpu_Error_Success;
  switch (f_Mode){
    case Cpu_Mode_USR_en:
      SetStateUsr_vd();
      break;
    case Cpu_Mode_FIQ_en:
      // SetStateFiq_vd();
      break;
    case Cpu_Mode_IRQ_en:
      // SetStateIrq_vd();
      break;
    case Cpu_Mode_SVC_en:
      SetStateSvc_vd();
      break;
    case Cpu_Mode_ABT_en:
      // SetStateAbt_vd();
      break;
    case Cpu_Mode_UND_en:
      // SetStateUnd_vd();
      break;
    case Cpu_Mode_SYS_en:
      // SetStateSys_vd();
      break;
    default:
      Error_ui32 = Cpu_Error_UnknownMode;
      break;
  }
  return Error_ui32;
}

Cpu_Mode_enm Cpu_GetState_ui32(void)
{
  return CPU.Mode;
} 

Cpu_Privilege_enm Cpu_GetPrivilege_ui32(void)
{
  return CPU.Privilege;
}

Cpu_Processor_st* Cpu_GetCpu_pst(void)
{
  return &CPU;
}

static void SetStateUsr_vd(void)
{
  CPU.Mode = Cpu_Mode_USR_en;
  CPU.Privilege = Cpu_PL_PL0;
  CPU.Registers.R8_pui32 = &R8;
  CPU.Registers.R9_pui32 = &R9;
  CPU.Registers.R10_pui32 = &R10;
  CPU.Registers.R11_pui32 = &R11;
  CPU.Registers.R12_pui32 = &R12;
  CPU.Registers.SP_pui32 = &SP;
  CPU.Registers.LR_pui32 = &LR;
  CPU.Registers.PC_pui32 = &PC;
  CPU.Registers.PSR_pui32 = &CPSR;
}

// static void SetStateFiq_vd(void)
// {

// }

// static void SetStateIrq_vd(void)
// {

// }

static void SetStateSvc_vd(void)
{
  CPU.Mode = Cpu_Mode_SVC_en;
  CPU.Privilege = Cpu_PL_PL1;
  CPU.Registers.R8_pui32 = &R8;
  CPU.Registers.R9_pui32 = &R9;
  CPU.Registers.R10_pui32 = &R10;
  CPU.Registers.R11_pui32 = &R11;
  CPU.Registers.R12_pui32 = &R12;
  CPU.Registers.SP_pui32 = &SP_svc;
  CPU.Registers.LR_pui32 = &LR_svc;
}

// static void SetStateAbt_vd(void)
// {

// }

// static void SetStateUnd_vd(void)
// {

// }

// static void SetStateSys_vd(void)
// {

// }

