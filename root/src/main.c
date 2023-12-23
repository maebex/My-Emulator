#include <stdio.h>
#include <stdint.h>

#include "emulator/emulator.h"

#define MSTACK_SIZEINWORDS (0x1000U)

int main(int argc, char *argv[])
{
  Emulator_Error_enm Error_ui32;
  printf("\nThis is My Emulator\n");
  printf("Provided elffile: %s\n", argv[argc-1]);

  Error_ui32 = Emulator_Init_ui32(MSTACK_SIZEINWORDS);
	if(Emulator_Error_Success != Error_ui32)
	{
		printf("ERROR during Init.\n");
	}
  else
  {
    Error_ui32 = Emulator_CpuReset_ui32();
    if(Emulator_Error_Success != Error_ui32)
    {
      printf("ERROR during Reset.\n");
    }
    Emulator_CpuShowProcessorInfo_vd();
    Error_ui32 = Emulator_CpuSetMode_ui32(Cpu_Mode_USR_en);
    {
      printf("ERROR during CPU moded set.");
    }
    Emulator_CpuShowProcessorInfo_vd();
    Error_ui32 = Emulator_CpuSetMode_ui32(Cpu_Mode_SVC_en);
    Emulator_CpuShowProcessorInfo_vd();

    Emulator_MemoryShowStackInfo_vd(&(Memory_EntireMemory_st.MainStack_st));
  }

  Emulator_Shutdown_vd();
	printf("\n\nExiting.\n\n");

  return 0;
}


