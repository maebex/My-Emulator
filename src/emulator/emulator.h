#ifndef D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B
#define D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B

#include "cpu/cpu.h"

typedef enum{
  Emulator_Error_Success = 0U,         // Success
  Emulator_Error_Generic = 1U,         // 
}Emulator_Error_enm;


Emulator_Error_enm Emulator_CpuReset_ui32(void);
Emulator_Error_enm Emulator_CpuSetState_ui32(const Cpu_Mode_enm f_Mode);
Cpu_Mode_enm Emulator_CpuGetState_ui32(void);
Cpu_Privilege_enm Emulator_CpuGetPrivilege_ui32(void);
Cpu_Processor_st* Emulator_CpuGetProcessor_ui32(void);


#endif /* D75E98DB_4E6C_4ABD_BFC9_33552D8FFB4B */
