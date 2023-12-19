#include <stdio.h>
#include <stdint.h>

#include "emulator/emulator.h"

int main(int argc, char *argv[])
{
  printf("\nThis is My Emulator\n");

  printf("File: %s", argv[argc-1]);

	Emulator_Error_enm Error_ui32 = Emulator_CpuReset_ui32();
	if(Emulator_Error_Success != Error_ui32)
	{
		printf("ERROR during Reset.\n");
	}
  Emulator_CpuSetState_ui32(Cpu_Mode_USR_en);
	Cpu_ShowProcessorInfo();

	printf("\n\nExiting.\n\n");

  return 0;
}
