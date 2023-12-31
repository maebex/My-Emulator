#ifndef D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B
#define D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B

#include "memory/memory.h"
#include "cpu/cpu.h"

typedef enum{
  Emulator_Error_Success = 0U,         // Success
  Emulator_Error_Generic = 1U,         // Generic error
}Emulator_Error_enm;

Emulator_Error_enm Emulator_Init_ui32(uint32_t MStackSizeInWords);
void Emulator_Shutdown_vd(void);
// Emulator_Error_enm Emulator_LoadElf_ui32(const FILE * const File);
Emulator_Error_enm Emulator_CpuReset_ui32(void);
Emulator_Error_enm Emulator_CpuSetMode_ui32(Cpu_Mode_enm f_Mode);
Cpu_Mode_enm Emulator_CpuGetMode_ui32(void);
uint32_t Emulator_CpuGetPrivilege_ui32(void);
Cpu_Processor_st* Emulator_CpuGetProcessor_ui32(void);
void Emulator_CpuShowProcessorInfo_vd(void);
void Emulator_MemoryShowStackInfo_vd(const Memory_Stack_st * const Stack);


#endif /* D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B */
