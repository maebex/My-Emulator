#include <stdint.h>
#include "emulator.h"

/* @brief Initialize emulator, i.e. implements startup code
   @details Reserve memory for stack, data and bss, copy data from elf to  */
Emulator_Error_enm Emulator_Init_ui32(const uint32_t MStackSize)
{
  static uint32_t EmulatorInitCalled_ui32; // flag to ensure we only init once
  Emulator_Error_enm Error_ui32 = Emulator_Error_Success;
  Memory_Error_enm InternalError_ui32 = Memory_Error_Success;
  if(0U==EmulatorInitCalled_ui32)
  {
    EmulatorInitCalled_ui32 = 1U;
    // Init stack
    MainStack_st.Size_ui32 = MStackSize;
    InternalError_ui32 = Memory_StackInit_ui32(&MainStack_st);
    if(Memory_Error_Success!=InternalError_ui32)
    {
      Error_ui32 = Emulator_Error_Generic;
    }
  }
  else
  {
    Error_ui32 = Emulator_Error_Generic;
  }
  return Error_ui32;
}

// Emulator_Error_enm Emulator_LoadElf_ui32(const FILE * const File)
// {
//   Emulator_Error_enm Error_ui32;

//   // TODO

//   return Error_ui32;
// }


/* @brief Set CPU bvack to reset state*/
Emulator_Error_enm Emulator_CpuReset_ui32(void)
{
  Emulator_Error_enm Error_ui32 = Emulator_Error_Success;
  Cpu_Error_enm InternalError_ui32 = Cpu_Reset_ui32();
  if(Cpu_Error_Success!=InternalError_ui32){
    Error_ui32 = Emulator_Error_Generic;
  }
  return Error_ui32;
}

/* @brief Invoke state transition */
Emulator_Error_enm Emulator_CpuSetMode_ui32(const Cpu_Mode_enm f_Mode)
{
  Emulator_Error_enm Error_ui32 = Emulator_Error_Success;
  Cpu_Error_enm InternalError_ui32 = Cpu_SetMode_ui32(f_Mode);
  if(Cpu_Error_Success!=InternalError_ui32){
    Error_ui32 = Emulator_Error_Generic;
  }
  return Error_ui32;
}

/* @brief Get CPU Mode*/
Cpu_Mode_enm Emulator_CpuGetMode_ui32(void)
{
  return Cpu_GetMode_ui32();
}

/* @brief */
uint32_t Emulator_CpuGetPrivilege_ui32(void)
{
  return Cpu_GetPrivilege_ui32();
}

/* @brief */
Cpu_Processor_st* Emulator_CpuGetProcessor_ui32(void)
{
  return Cpu_GetCpu_pst();
}

