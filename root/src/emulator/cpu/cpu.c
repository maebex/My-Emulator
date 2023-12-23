#include <stdio.h>
#include "cpu/cpu.h"
#include "memory/memory.h"


static void SetStateUsr_vd(void);
static void SetStateSvc_vd(void);


// CPU instance
Cpu_Processor_st CPU = {0};

// BANKED REGISTERS
// User registers
Cpu_Register_ui32 R8;
Cpu_Register_ui32 R9;
Cpu_Register_ui32 R10;
Cpu_Register_ui32 R11;
Cpu_Register_ui32 R12;
Cpu_Register_ui32 LR;
Cpu_Register_ui32 PC;

// IRQ Registers
Cpu_Register_ui32 LR_irq;
Cpu_Register_ui32 SPSR_irq;

// Supervisor Registers
Cpu_Register_ui32 LR_svc;
Cpu_Register_ui32 SPSR_svc;

// Other registers
Cpu_Register_ui32 MSP; // Main stack pointer
Cpu_Register_ui32 PSP; // Process stack pointer // TODO: Add usage to configuration
Cpu_Register_ui32 CPSR;
Cpu_Register_ui32 APSR;
Cpu_Register_ui32 PRIMASK;
Cpu_Register_ui32 CONTROL;

/* @brief Perform a CPU reset 
   @details Set mode to SVC, <TODO: more?>*/
Cpu_Error_enm Cpu_Reset_ui32(void)
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Processor always starts in SVC mode
  Error_ui32 = Cpu_SetMode_ui32(Cpu_Mode_SVC_en);
  //Reset PC
  *(CPU.Registers.PC_pui32) = Memory_EntireMemory_st.Code_pch[0U];
  
  // Reset pipeline
  // TODOs

  return Error_ui32;
}

/* @brief Invoke CPU state transition */
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

/* @brief Return current CPU mode */
Cpu_Mode_enm Cpu_GetMode_ui32(void)
{
  return Cpu_CpsrGetM_ui32(); // TODO user GetMs
} 

/* @brief Get current CPU privilige level */
uint32_t Cpu_GetPrivilege_ui32(void)
{
  return (Cpu_ControlGetnPriv_ui32());
}

/* @brief Get pointer to CPU instance */
Cpu_Processor_st* Cpu_GetCpu_pst(void)
{
  return &CPU;
}

/* @brief Print some CPU information */
void Cpu_ShowProcessorInfo_vd(void)
{
  printf("\n");
  printf("--------------------CPU Info:--------------------\n");
  printf("Add. of CPU instance:\t%p\n", (void*)Cpu_GetCpu_pst());
  printf("Mode:\t\t\t%d\n", Cpu_GetMode_ui32());
  printf("Privilege Level:\t%d\n", Cpu_GetPrivilege_ui32());
  printf("Register:\n");
  printf("R0:\t%d\tR6:\t%d\n", CPU.Registers.R0_ui32, CPU.Registers.R6_ui32);
  printf("R1:\t%d\tR7:\t%d\n", CPU.Registers.R1_ui32, CPU.Registers.R7_ui32);
  printf("R2:\t%d\tR8:\t%d\n", CPU.Registers.R2_ui32, *(CPU.Registers.R8_pui32));
  printf("R3:\t%d\tR9:\t%d\n", CPU.Registers.R3_ui32, *(CPU.Registers.R9_pui32));
  printf("R4:\t%d\tR10:\t%d\n", CPU.Registers.R4_ui32, *(CPU.Registers.R10_pui32));
  printf("R5:\t%d\tR11:\t%d\n", CPU.Registers.R5_ui32, *(CPU.Registers.R11_pui32));
  printf("SP:\t%d\n", *(CPU.Registers.SP_pui32));
  printf("LR:\t%d\n", *(CPU.Registers.LR_pui32));
  printf("PC:\t%d\n", *(CPU.Registers.PC_pui32));
  printf("PSR:\t%d\n", *(CPU.Registers.PSR_pui32));
  printf("-------------------------------------------------\n");
}

// Register Access Functions
/* @brief Set SP */
void Cpu_SetSP(uint32_t value)
{
  *(CPU.Registers.SP_pui32) = value;
}

/* @brief Get SP */
uint32_t Cpu_GetSP(void)
{
  return *(CPU.Registers.SP_pui32);
}

/* @brief Set LR */
void Cpu_SetLR(uint32_t value)
{
  *(CPU.Registers.LR_pui32) = value;
}

/* @brief Get LR */
uint32_t Cpu_GetLR(void)
{
  return *(CPU.Registers.LR_pui32);
}

/* @brief Set PC */
void Cpu_SetPC(uint32_t value)
{
  *(CPU.Registers.PC_pui32) = value;
}

/* @brief Get PC */
uint32_t Cpu_GetPC(void)
{
  return *(CPU.Registers.PC_pui32);
}

/* @brief Increment PC by 4-byte word */
void Cpu_IncrementPC(void)
{
  *(CPU.Registers.PC_pui32) += 0x4U;
}


// CPSR Acccess Functions
void Cpu_CpsrSetN_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= Value<<CPSR_N;
}
uint32_t Cpu_CpsrGetN_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_N));
}

void Cpu_CpsrSetZ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_Z);
}
uint32_t Cpu_CpsrGetZ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_Z));
}

void Cpu_CpsrSetC_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_V);
}
uint32_t Cpu_CpsrGetC_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_C));
}

void Cpu_CpsrSetQ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_Q);
}
uint32_t Cpu_CpsrGetQ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_Q));
}

// Lower: IT[1:0]
// Higher: IT[7:2]
void Cpu_CpsrSetIT_vd(uint32_t Lower, uint32_t Higher)
{
  *(CPU.Registers.PSR_pui32) |= (Lower<<CPSR_ITL);
  *(CPU.Registers.PSR_pui32) |= (Higher<<CPSR_ITH);
}
uint32_t Cpu_CpsrGetIT_ui32(void)
{
  uint32_t tmp1, tmp2;
  tmp1 = (*(CPU.Registers.PSR_pui32)&((0x3FU<<CPSR_ITH)))>>CPSR_ITH;
  tmp2 = (*(CPU.Registers.PSR_pui32)&((0x3U<<CPSR_ITL)))>>CPSR_ITL;
  return (tmp1||tmp2);
}

void Cpu_CpsrSetJ_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_J);
}
uint32_t Cpu_CpsrGetJ_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_J));
}

void Cpu_CpsrSetGE_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_GE);
}
uint32_t Cpu_CpsrGet_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0xFU<<CPSR_GE));
}

void Cpu_CpsrSetE_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_E);
}
uint32_t Cpu_CpsrGetE_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_E));
}

void Cpu_CpsrSetA_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_A);
}
uint32_t Cpu_CpsrGetA_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_A));
}

void Cpu_CpsrSetI_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_I);
}
uint32_t Cpu_CpsrGetI_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_I));
}

void Cpu_CpsrSetF_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_F);
}
uint32_t Cpu_CpsrGetF_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_F));
}

void Cpu_CpsrSetT_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_T);
}
uint32_t Cpu_CpsrGetT_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1U<<CPSR_T));
}

void Cpu_CpsrSetM_vd(uint32_t Value)
{
  *(CPU.Registers.PSR_pui32) |= (Value<<CPSR_M);
}
uint32_t Cpu_CpsrGetM_ui32(void)
{
  return (*(CPU.Registers.PSR_pui32)&(0x1FU<<CPSR_M));
}

void Cpu_ControlSetnPriv_vd(uint32_t Value)
{
  *(CPU.Registers.CONTROL_pui32) |= (Value<<CONTROL_nPRIV);
}
uint32_t Cpu_ControlGetnPriv_ui32(void)
{
  return (*(CPU.Registers.CONTROL_pui32)&(0x1U<<CONTROL_nPRIV));
}

void Cpu_ControlSetSpsel_vd(uint32_t Value)
{
  *(CPU.Registers.CONTROL_pui32) |= (Value<<CONTROL_SPSEL);
}
uint32_t Cpu_ControlGetSpsel_ui32(void)
{
  return (*(CPU.Registers.CONTROL_pui32)&(0x1U<<CONTROL_SPSEL));
}

static void SetStateUsr_vd(void)
{
  CPU.Registers.R8_pui32 = &R8;
  CPU.Registers.R9_pui32 = &R9;
  CPU.Registers.R10_pui32 = &R10;
  CPU.Registers.R11_pui32 = &R11;
  CPU.Registers.R12_pui32 = &R12;
  CPU.Registers.SP_pui32 = &MSP;
  CPU.Registers.LR_pui32 = &LR;
  CPU.Registers.PC_pui32 = &PC;
  CPU.Registers.PSR_pui32 = &CPSR;
  Cpu_CpsrSetM_vd(Cpu_Mode_USR_en);
  Cpu_ControlSetnPriv_vd(CONTROL_nPRIV_Unprivileged);
  Cpu_ControlSetSpsel_vd(CONTROL_SPSEL_PSP);
}

static void SetStateSvc_vd(void)
{
  CPU.Registers.R8_pui32 = &R8;
  CPU.Registers.R9_pui32 = &R9;
  CPU.Registers.R10_pui32 = &R10;
  CPU.Registers.R11_pui32 = &R11;
  CPU.Registers.R12_pui32 = &R12;
  CPU.Registers.SP_pui32 = &MSP;
  CPU.Registers.LR_pui32 = &LR_svc;
  CPU.Registers.PC_pui32 = &PC;
  CPU.Registers.PSR_pui32 = &SPSR_svc;
  CPU.Registers.CONTROL_pui32 = &CONTROL;
  Cpu_CpsrSetM_vd(Cpu_Mode_SVC_en);
  Cpu_ControlSetnPriv_vd(CONTROL_nPRIV_Privileged);
  Cpu_ControlSetSpsel_vd(CONTROL_SPSEL_MSP);
}



// SYSTEM CLOCK
static uint32_t Cpu_SysClockCounter_ui32 = 0U;
uint32_t Cpu_SysClockStart_ui32(); // TODO
uint32_t Cpu_SysClockReset_ui32(); // TODO
uint32_t Cpu_SysClockIncrement_ui32(); // TODO



// PIPELINE
Cpu_Error_enm Cpu_PipelineInit(void)
{
  CPU.Pipeline_st.FetchIdx_ui8 = 0;
  CPU.Pipeline_st.DecodeIdx_ui8 = 1;
  CPU.Pipeline_st.ExecuteIdx_ui8 = 2;
}

Cpu_Error_enm Cpu_PipelineExecute_ui32(void) // TODO
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Check if pipeline container is populated 
  // TODO
  return Error_ui32;
}

Cpu_Error_enm Cpu_PipelineDecode_ui32(void) // TODO
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Check if pipeline container is populated 
  // TODO
  return Error_ui32;
}

Cpu_Error_enm Cpu_PipelineFetch_ui32(void) // TODO
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // Load raw instruction into Container
  CPU.Pipeline_st.PipelineData_pst[CPU.Pipeline_st.FetchIdx_ui8].RawInstruction_ui32 = *(CPU.Registers.PC_pui32);
  return Error_ui32;
}

Cpu_Error_enm Cpu_PipelineFlush_ui32(void) // TODO
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  // TODO
  return Error_ui32;
}


/* @brief Increment values of pipeline stage indices */
Cpu_Error_enm Cpu_PipelineUpdate_ui32(void)
{
  CPU.Pipeline_st.FetchIdx_ui8 = (CPU.Pipeline_st.FetchIdx_ui8+1U)%PIPELINE_LENGTH;
  CPU.Pipeline_st.DecodeIdx_ui8 = (CPU.Pipeline_st.DecodeIdx_ui8+1U)%PIPELINE_LENGTH;
  CPU.Pipeline_st.ExecuteIdx_ui8 = (CPU.Pipeline_st.ExecuteIdx_ui8+1U)%PIPELINE_LENGTH;
}


/* @brief This function invoces the pipeline to process for another stage, 
          i.e. we run fetch, decode and execute operation on the three currently worked on Instruction Containers           
*/
Cpu_Error_enm Cpu_PipelineProcessInstructions_ui32(void)
{
  Cpu_Error_enm Error_ui32 = Cpu_Error_Success;
  Cpu_Error_enm InternalError_ui32;

  // Execute
  InternalError_ui32 = Cpu_PipelineExecute_ui32(&(CPU.Pipeline_st.PipelineData_pst[CPU.Pipeline_st.ExecuteIdx_ui8]));
  if(Cpu_Error_Success!=InternalError_ui32)
  {
    ; // TODO
  }

  // Decode
  InternalError_ui32 = Cpu_PipelineDecode_ui32(&(CPU.Pipeline_st.PipelineData_pst[CPU.Pipeline_st.DecodeIdx_ui8]));
  if(Cpu_Error_Success!=InternalError_ui32)
  {
    ; // TODO
  }

  // Fetch
  InternalError_ui32 = Cpu_PipelineFetch_ui32(&(CPU.Pipeline_st.PipelineData_pst[CPU.Pipeline_st.FetchIdx_ui8]));
  if(Cpu_Error_Success!=InternalError_ui32)
  {
    ; // TODO
  }


  return Error_ui32;
}

