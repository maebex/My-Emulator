#ifndef A3754B19_DEA4_4C31_9620_A5FEACA40530
#define A3754B19_DEA4_4C31_9620_A5FEACA40530

#include <stdint.h>

#define PIPELINE_LENGTH (3U)


typedef enum{
  Instructions_Error_Success = 0U,              // success
  Instructions_Error_Generic = 1U,              // Generic error
  Instructions_Error_UnknownOpcode = 2U,        // Unknown opcode detected during decoding stages
}Instructions_Error_enm;



typedef enum{
  Instructions_Opcode_AddRegisterT1 = 0x0U,    // Unknown
  // Instructions_Opcode_AddRegisterT1 = 0x1800U, // Add register, update condition flags
  Instructions_Opcode_AddRegisterT2 = 0x4400U, // Add register, do not update condition flags
}Instructions_Opcode_enm;

typedef struct{
  uint32_t Instruction_ui32;    // Instruction in binary
  uint32_t Stage_pf;            // Index of entry in ProcFunctionArray_ppf that pointer to next processing stage
}Instructions_Instruction_st;

/* @brief Function pointer to a processing function of the 3-stage pipeline (either fetch, decode or execute)
   @details Pointer to function receiving Instructions_Instruction_st as argument and return uint32_t.  */
typedef uint32_t (*ProcFunction_pf)(Instructions_Instruction_st);


// If bits [15:11] of the halfword being decoded take any of the following values, the halfword is the first
// halfword of a 32-bit instruction:
// • 0b11101 = 0x1D
// • 0b11110 = 0x1E
// • 0b11111 = 0x1f
#define Instructions_32BitCode_1  (0x1DU<<27U)
#define Instructions_32BitCode_2  (0x1EU<<27U)
#define Instructions_32BitCode_3  (0x1FU<<27U)

/* @brief Return true if Instruction_ui32 is a 32 bit instruction */
uint32_t Instructions_InstructionIs32Bit_ui32(uint32_t Instruction_ui32)
{
  return ((Instructions_32BitCode_1==(Instruction_ui32&(Instructions_32BitCode_1)))||
          (Instructions_32BitCode_2==(Instruction_ui32&(Instructions_32BitCode_2)))||
          (Instructions_32BitCode_3==(Instruction_ui32&(Instructions_32BitCode_3))));
}






#endif /* A3754B19_DEA4_4C31_9620_A5FEACA40530 */
