#include "cpu.h"

static void SetStateUsr_vd(void);
static void SetStateSvc_vd(void);
static void CpsrSetN_vd(uint32_t Value);
static uint32_t CpsrGetN_ui32(void);
static void CpsrSetZ_vd(uint32_t Value);
static uint32_t CpsrGetZ_ui32(void);
static void CpsrSetC_vd(uint32_t Value);
static uint32_t CpsrGetC_ui32(void);
static void CpsrSetQ_vd(uint32_t Value);
static uint32_t CpsrGetQ_ui32(void);
static void CpsrSetIT_vd(uint32_t Lower, uint32_t Higher);
static uint32_t CpsrGetIT_ui32(void);
static void CpsrSetJ_vd(uint32_t Value);
static uint32_t CpsrGetJ_ui32(void);
static void CpsrSetGE_vd(uint32_t Value);
static uint32_t CpsrGet_ui32(void);
static void CpsrSetE_vd(uint32_t Value);
static uint32_t CpsrGetE_ui32(void);
static void CpsrSetA_vd(uint32_t Value);
static uint32_t CpsrGetA_ui32(void);
static void CpsrSetI_vd(uint32_t Value);
static uint32_t CpsrGetI_ui32(void);
static void CpsrSetF_vd(uint32_t Value);
static uint32_t CpsrGetF_ui32(void);
static void CpsrSetT_vd(uint32_t Value);
static uint32_t CpsrGetT_ui32(void);
static void CpsrSetM_vd(uint32_t Value);
static uint32_t CpsrGetM_ui32(void);


// CPU
Cpu_Processor_st CPU;

// BANKED REGISTERS
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

// Other registers
Cpu_Register_ui32 CPSR;
Cpu_Register_ui32 APSR;

#include <stdio.h>
Cpu_Error_enm Cpu_Reset_ui32(void)
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Processor always starts in SVC mode
  Error_ui32 = Cpu_SetMode_ui32(Cpu_Mode_SVC_en);
  if(Cpu_Error_Success==Error_ui32)
  {
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
  return Error_ui32;
}

Cpu_Error_enm Cpu_SetMode_ui32(const Cpu_Mode_enm f_Mode)
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

Cpu_Mode_enm Cpu_GetMode_ui32(void)
{
  return CpsrGetM_ui32(); // TODO user GetMs
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
  CpsrSetM_vd(Cpu_Mode_USR_en);
}

// static void SetStateFiq_vd(void)
// {

// }

// static void SetStateIrq_vd(void)
// {

// }

static void SetStateSvc_vd(void)
{
  CPU.Privilege = Cpu_PL_PL1;
  CPU.Registers.R8_pui32 = &R8;
  CPU.Registers.R9_pui32 = &R9;
  CPU.Registers.R10_pui32 = &R10;
  CPU.Registers.R11_pui32 = &R11;
  CPU.Registers.R12_pui32 = &R12;
  CPU.Registers.SP_pui32 = &SP_svc;
  CPU.Registers.LR_pui32 = &LR_svc;
  CPU.Registers.PC_pui32 = &PC;
  CPU.Registers.PSR_pui32 = &SPSR_svc;
  CpsrSetM_vd(Cpu_Mode_SVC_en);
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

void Cpu_ShowProcessorInfo(void)
{
  printf("\n");
  printf("--------------------CPU Info:--------------------\n");
  printf("Add. of CPU instance:\t0x%p\n", Cpu_GetCpu_pst());
  printf("State:\t\t\t%d\n", Cpu_GetMode_ui32());
  printf("Privilege Level:\t%d\n", Cpu_GetPrivilege_ui32());
  printf("Register:\n");
  printf("R0:\t%d\tR6:\t%d\n", *(CPU.Registers.R0_pui32), *(CPU.Registers.R6_pui32));
  printf("R1:\t%d\tR7:\t%d\n", *(CPU.Registers.R1_pui32), *(CPU.Registers.R7_pui32));
  printf("R2:\t%d\tR8:\t%d\n", *(CPU.Registers.R2_pui32), *(CPU.Registers.R8_pui32));
  printf("R3:\t%d\tR9:\t%d\n", *(CPU.Registers.R3_pui32), *(CPU.Registers.R9_pui32));
  printf("R4:\t%d\tR10:\t%d\n", *(CPU.Registers.R4_pui32), *(CPU.Registers.R10_pui32));
  printf("R5:\t%d\tR11:\t%d\n", *(CPU.Registers.R5_pui32), *(CPU.Registers.R11_pui32));
  printf("SP:\t%d\n", *(CPU.Registers.SP_pui32));
  printf("LR:\t%d\n", *(CPU.Registers.LR_pui32));
  printf("PC:\t%d\n", *(CPU.Registers.PC_pui32));
  printf("PSR:\t%d\n", *(CPU.Registers.PSR_pui32));
  printf("-------------------------------------------------\n");
}

// CPSR Acccess Functions
static void CpsrSetN_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= Value<<CPSR_N;
}
static uint32_t CpsrGetN_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_N));
}

static void CpsrSetZ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_Z);
}
static uint32_t CpsrGetZ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_Z));
}

static void CpsrSetC_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_V);
}
static uint32_t CpsrGetC_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_C));
}

static void CpsrSetQ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_Q);
}
static uint32_t CpsrGetQ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_Q));
}

static void CpsrSetIT_vd(uint32_t Lower, uint32_t Higher)
{
  *(CPU.Registers.PSR_pui32) |= (Lower<<CPSR_ITL);
  *(CPU.Registers.PSR_pui32) |= (Higher<<CPSR_ITH);
}
static uint32_t CpsrGetIT_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&((0x11U<<CPSR_ITH)||(0x111111U<<CPSR_ITL)));
}

static void CpsrSetJ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_J);
}
static uint32_t CpsrGetJ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_J));
}

static void CpsrSetGE_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_GE);
}
static uint32_t CpsrGet_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1111U<<CPSR_GE));
}

static void CpsrSetE_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_E);
}
static uint32_t CpsrGetE_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_E));
}

static void CpsrSetA_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_A);
}
static uint32_t CpsrGetA_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_A));
}

static void CpsrSetI_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_I);
}
static uint32_t CpsrGetI_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_I));
}

static void CpsrSetF_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_F);
}
static uint32_t CpsrGetF_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_F));
}

static void CpsrSetT_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_T);
}
static uint32_t CpsrGetT_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x1U<<CPSR_T));
}

static void CpsrSetM_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_M);
}
static uint32_t CpsrGetM_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&&(0x111111U<<CPSR_M));
}

