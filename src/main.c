#include <stdio.h>
#include <stdint.h>

#include "emulator/emulator.h"

uint32_t main(uint32_t argc, char *argv[])
{
  printf("\nThis is My Emulator\n");

	Emulator_Error_enm Error_ui32 = Emulator_CpuReset_ui32();
	if(Emulator_Error_Success != Error_ui32)
	{
		printf("ERROR during Reset.\n");
	}

	Cpu_ShowProcessorInfo();

	printf("\n\nExiting.\n\n");

  return 0;
}
