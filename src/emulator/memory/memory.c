#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

#include "memory.h"

/* @bbrief Our stack */
Memory_Stack_st MainStack_st;


/* @brief This function is used to initialize the stack structurew 
   @details Stack->Size_ui32 must be set beforehand and is used for memory allocation. */
Memory_Error_enm Memory_StackInit_ui32(Memory_Stack_st *Stack)
{
  // TODO: Process Stack missing
  uint32_t Error_ui32 = Memory_Error_Success;

  // Check if Stack is already initialized
  if(NULL!=Stack->Base_pui32)
  {
    Error_ui32 = Memory_Error_NoRealloc;
  }
  else
  {
    // Reserve memory
    Stack->Base_pui32 = mmap(NULL, 
                        Stack->Size_ui32, 
                        PROT_READ||PROT_WRITE, 
                        MAP_PRIVATE||MAP_GROWSDOWN||MAP_ANONYMOUS,
                        0U,
                        0U);
    if (NULL!=Stack->Base_pui32)
    {
      // set top pointer
      Stack->Top_pui32 = Stack->Base_pui32;
    }
    else
    {
      Error_ui32 = Memory_Error_Alloc;
    }
  }
  return Error_ui32;
}

/* @brief Pop 4 byte word from the stack */
uint32_t Memory_StackPopWord_ui32(Memory_Stack_st *Stack)
{
  return (*(Stack->Top_pui32++));
}

/* @brief Push 4 byte word onto stack */
void Memory_StackPushWord_vd(Memory_Stack_st *Stack, uint32_t value)
{
  Stack->Top_pui32--;
  *(Stack->Top_pui32) = value;
}

/* @brief Stack if stack is full */
uint32_t Memory_StackIsFull(const Memory_Stack_st * const Stack)
{
  return ((Stack->Base_pui32-Stack->Top_pui32)>=Stack->Size_ui32);
}

/* @brief Check if stack is empty */
uint32_t Memory_StackIsEmpty(const Memory_Stack_st * const Stack)
{
  return (Stack->Base_pui32<=Stack->Top_pui32);
}

/* @brief Push a word to the stack but detect overflow */
Memory_Error_enm Memory_StackPushWordSafe_ui32(Memory_Stack_st *Stack, uint32_t value)
{
  Memory_Error_enm Error_ui32 = Memory_Error_Success;
  // Check if stack is full
  if(0U!=Memory_StackIsFull(Stack))
  {
    Error_ui32 = Memory_Error_StackOverflow;
  }
  else
  {
    Memory_StackPushWord_vd(Stack, value);
  }
  return Error_ui32;
}


void Memory_ShowStackInfo_vd(const Memory_Stack_st * const Stack)
{
  printf("\n");
  printf("-------------------Stack Info:-------------------\n");
  printf("Stack size:\t\t0x%x\n", Stack->Size_ui32);
  printf("Stack Base:\t\t%p\n", (void*)Stack->Base_pui32);
  printf("Stack Top:\t\t%p\n", (void*)Stack->Top_pui32);
  printf("-------------------------------------------------\n");
}

