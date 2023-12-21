#ifndef C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02
#define C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02

#include <stdint.h>

/* TYPES */

typedef enum{
  Cpu_Error_Success = 0U,         // Success
  Cpu_Error_UnknownMode = 1U,     // Unknown state value passed to Cpu_SetState()
}Cpu_Error_enm;

typedef uint32_t Cpu_Register_ui32; 

typedef enum{
  Cpu_Mode_USR_en   = 0x10U,    // User
  Cpu_Mode_FIQ_en   = 0x11U,    // FIQ
  Cpu_Mode_IRQ_en   = 0x12U,    // IRQ
  Cpu_Mode_SVC_en   = 0x13U,    // Supervisor
  Cpu_Mode_ABT_en   = 0x17U,    // Abort
  Cpu_Mode_UND_en   = 0x1BU,    // Undefined
  Cpu_Mode_SYS_en   = 0x1FU     // System
} Cpu_Mode_enm;

typedef struct{
  // Regular, GP registers
  Cpu_Register_ui32 R0_ui32;
  Cpu_Register_ui32 R1_ui32;
  Cpu_Register_ui32 R2_ui32;
  Cpu_Register_ui32 R3_ui32;
  Cpu_Register_ui32 R4_ui32;
  Cpu_Register_ui32 R5_ui32;
  Cpu_Register_ui32 R6_ui32;
  Cpu_Register_ui32 R7_ui32;
  // Banked registers - pointing to global variables defined in cpu.c and changed on state transition
  Cpu_Register_ui32 *R8_pui32;
  Cpu_Register_ui32 *R9_pui32;
  Cpu_Register_ui32 *R10_pui32;
  Cpu_Register_ui32 *R11_pui32;
  Cpu_Register_ui32 *R12_pui32;
  Cpu_Register_ui32 *SP_pui32;
  Cpu_Register_ui32 *LR_pui32;
  Cpu_Register_ui32 *PC_pui32;
  Cpu_Register_ui32 *PSR_pui32;
  Cpu_Register_ui32 *PRIMASK_pui32;
  Cpu_Register_ui32 *CONTROL_pui32;
} Cpu_Registers_st;

typedef struct{
  Cpu_Registers_st Registers;
}Cpu_Processor_st;


/* GLOBAL VARIABLES */

// CPU
extern Cpu_Processor_st CPU;

// BANKED REGISTERS 
// User registers
extern Cpu_Register_ui32 R0;
extern Cpu_Register_ui32 R1;
extern Cpu_Register_ui32 R2;
extern Cpu_Register_ui32 R3;
extern Cpu_Register_ui32 R4;
extern Cpu_Register_ui32 R5;
extern Cpu_Register_ui32 R6;
extern Cpu_Register_ui32 R7;
extern Cpu_Register_ui32 R8;
extern Cpu_Register_ui32 R9;
extern Cpu_Register_ui32 R10;
extern Cpu_Register_ui32 R11;
extern Cpu_Register_ui32 R12;
extern Cpu_Register_ui32 LR;
extern Cpu_Register_ui32 PC;

// IRQ Registers
extern Cpu_Register_ui32 LR_irq;
extern Cpu_Register_ui32 SPSR_irq;

// Supervisor Registers
extern Cpu_Register_ui32 LR_svc;
extern Cpu_Register_ui32 SPSR_svc;

// Other registers
extern Cpu_Register_ui32 MSP; // Main stack pointer
extern Cpu_Register_ui32 PSP; // Process stack pointer
extern Cpu_Register_ui32 CPSR;
extern Cpu_Register_ui32 APSR;
extern Cpu_Register_ui32 PRIMASK;
extern Cpu_Register_ui32 CONTROL;



#define CPSR_N    (31U)       // Negative condition code flag 
#define CPSR_Z    (30U)       // Zero condition code flag 
#define CPSR_C    (29U)       // Carry condition code flag 
#define CPSR_V    (28U)       // Overflow condition code flag 
#define CPSR_Q    (27U)       // Cumulative saturation bit 
#define CPSR_ITL  (25U)       // Lower If-Then execution state bits for the Thumb IT (If-Then) instruction 
#define CPSR_J    (24U)       // Jazelle bit 
#define CPSR_GE   (16U)       // Greater than or Equal flags 
#define CPSR_ITH  (10U)       // Higher If-Then execution state bits for the Thumb IT (If-Then) instruction
#define CPSR_E    (9U)        // Endianness execution state bit: 0 - Little-endian, 1 - Big-endian 
#define CPSR_A    (8U)        // Asynchronous abort mask bit 
#define CPSR_I    (7U)        // IRQ mask bit 
#define CPSR_F    (6U)        // FIRQ mask bit 
#define CPSR_T    (5U)        // Thumb execution state bit 
#define CPSR_M    (0U)        // Mode field

#define CONTROL_nPRIV   (0U)  // If the Unprivileged/Privileged Extension is implemented, defines the execution privilege in Thread mode:
                              // 0: Thread mode has privileged access, 1: Thread mode has unprivileged access.
#define CONTROL_nPRIV_Privileged    (0U)
#define CONTROL_nPRIV_Unprivileged  (1U)
#define CONTROL_SPSEL   (1U)  // Defines the stack to be used:
                              // 0:  Use SP_main as the current stack 1: In Thread mode, use SP_process as the current stack. In Handler mode, this value is reserved.
#define CONTROL_SPSEL_MSP           (0U)
#define CONTROL_SPSEL_PSP           (1U)



extern Cpu_Register_ui32 APSR;


// Function Prototypes
Cpu_Error_enm Cpu_Reset_ui32(void);
Cpu_Error_enm Cpu_SetMode_ui32(const Cpu_Mode_enm f_Mode);
Cpu_Mode_enm Cpu_GetMode_ui32(void);
uint32_t Cpu_GetPrivilege_ui32(void);
Cpu_Processor_st* Cpu_GetCpu_pst(void);
void Cpu_ShowProcessorInfo_vd(void);
__attribute__((__used__)) uint32_t Cpu_GetSP(void);
__attribute__((__used__)) void Cpu_SetLR(uint32_t value);
__attribute__((__used__)) uint32_t Cpu_GetLR(void);
__attribute__((__used__)) void Cpu_SetPC(uint32_t value);
__attribute__((__used__)) uint32_t Cpu_GetPC(void);
__attribute__((__used__)) void Cpu_IncrementPC(void);
__attribute__((__used__)) void Cpu_CpsrSetN_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetN_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetZ_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetZ_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetC_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetC_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetQ_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetQ_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetIT_vd(uint32_t Lower, uint32_t Higher);
__attribute__((__used__)) uint32_t Cpu_CpsrGetIT_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetJ_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetJ_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetGE_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGet_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetE_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetE_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetA_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetA_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetI_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetI_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetF_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetF_ui32(void);
__attribute__((__used__)) void Cpu_CpsrSetT_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_CpsrGetT_ui32(void);
void Cpu_CpsrSetM_vd(uint32_t Value);
uint32_t Cpu_CpsrGetM_ui32(void);
__attribute__((__used__)) void Cpu_ControlSetnPriv_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_ControlGetnPriv_ui32(void);
__attribute__((__used__)) void Cpu_ControlSetSpsel_vd(uint32_t Value);
__attribute__((__used__)) uint32_t Cpu_ControlGetSpsel_ui32(void);



#endif /* C044F80B_9F0E_4EFB_A9BC_9D90FB5DFD02 */
