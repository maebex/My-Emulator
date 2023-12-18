#include <stdint.h>
#include "emulator.h"
#include "cpu/cpu.h"

Emulator_Error_enm Emulator_CpuReset_ui32(void)
{
  Emulator_Error_enm Error_ui32 = Emulator_Error_Success;
  Cpu_Error_enm InternalError_ui32 = Cpu_Reset_ui32();
  if(0U!=InternalError_ui32){
    Error_ui32 = Emulator_Error_Generic;
  }
  return Error_ui32;
}

Emulator_Error_enm Emulator_CpuSetState_ui32(const Cpu_Mode_enm f_Mode)
{
  Emulator_Error_enm Error_ui32 = Emulator_Error_Success;
  Cpu_Error_enm InternalError_ui32 = Cpu_SetState_ui32(f_Mode);
  if(0U!=InternalError_ui32){
    Error_ui32 = Emulator_Error_Generic;
  }
  return Error_ui32;
}

Cpu_Mode_enm Emulator_CpuGetState_ui32(void)
{
  return Cpu_GetState_ui32();
}

Cpu_Privilege_enm Emulator_CpuGetPrivilege_ui32(void)
{
  return Cpu_GetPrivilege_ui32();
}

Cpu_Processor_st* Emulator_CpuGetProcessor_ui32(void)
{
  return Cpu_GetCpu_pst();
}

