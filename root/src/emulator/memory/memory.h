#ifndef AA18CE25_D279_4356_BCF8_E5344F4EE6E1
#define AA18CE25_D279_4356_BCF8_E5344F4EE6E1

#include <stdint.h>

typedef enum{
  Memory_Error_Success = 0U,          // Success
  Memory_Error_Alloc = 1U,            // Error on memory allocation using mmap, malloc or similar
  Memory_Error_NoRealloc = 2U,        // re-allocation of dynamically memory is forbidden
  Memory_Error_StackOverflow = 3U,    // Stack overflow detected
  Memory_Error_MemoryInit = 4U,       // An error occured during initialiazing the memory
}Memory_Error_enm;

typedef struct{
  uint32_t SizeInWords_ui32;  // Size in Bytes
  uint32_t *Base_pui32;       // Pointer to base of stack, i.e. highest address
  uint32_t *Top_pui32;        // Pointer to last element stack, i.e. lowest address in use
} Memory_Stack_st;

#define CODE_SIZE_IN_BYTES   (0x1000U)
#define DATA_SIZE_IN_BYTES   (0x100U)
#define BSS_SIZE_IN_BYTES    (0x100U)

typedef struct{
  Memory_Stack_st MainStack_st;
  char Code_pch[CODE_SIZE_IN_BYTES];
  char Data_pch[DATA_SIZE_IN_BYTES];
  char Bss_pch[BSS_SIZE_IN_BYTES];
}Memory_Memory_st;


extern Memory_Memory_st Memory_EntireMemory_st;

Memory_Error_enm Memory_StackInit_ui32(Memory_Stack_st *Stack);
void Memory_StackDestroy_vd(Memory_Stack_st *Stack);
uint32_t Memory_StackPopWord_ui32(Memory_Stack_st *Stack);
void Memory_StackPushWord_vd(Memory_Stack_st *Stack, uint32_t value);
uint32_t Memory_StackIsFull(const Memory_Stack_st * const Stack);
uint32_t Memory_StackIsEmpty(const Memory_Stack_st * const Stack);
Memory_Error_enm Memory_StackPushWordSafe_ui32(Memory_Stack_st *Stack, uint32_t value);
void Memory_ShowStackInfo_vd(const Memory_Stack_st * const Stack);




#endif /* AA18CE25_D279_4356_BCF8_E5344F4EE6E1 */
