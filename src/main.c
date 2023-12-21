#include <stdio.h>
#include <stdint.h>

#include "emulator/emulator.h"

#define MSTACK_SIZE (0x10000U)

int main(int argc, char *argv[])
{
  Emulator_Error_enm Error_ui32;
  printf("\nThis is My Emulator\n");
  printf("Provided elffile: %s\n", argv[argc-1]);

  Error_ui32 = Emulator_Init_ui32(MSTACK_SIZE);
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
    Emulator_CpuSetMode_ui32(Cpu_Mode_USR_en);
    Cpu_ShowProcessorInfo_vd();
    Memory_ShowStackInfo_vd(&MainStack_st);
  }

	printf("\n\nExiting.\n\n");

  return 0;
}


