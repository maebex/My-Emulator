#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "memory/memory.h"

/* @bbrief Our stack */
Memory_Stack_st MainStack_st;
//Memory_Stack_st ProcessStack_st; // TODO

/* @brief This function is used to initialize the stack structurew 
   @details Stack->SizeInWords_ui32 must be set beforehand and is used for memory allocation. */
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
    uint32_t *tmp = mmap(NULL, 
                    Stack->SizeInWords_ui32*4U, 
                    PROT_READ|PROT_WRITE, 
                    MAP_PRIVATE|MAP_ANONYMOUS,
                    0U,
                    0U);
    if (MAP_FAILED!=tmp)
    {
      Stack->Base_pui32 = tmp+Stack->SizeInWords_ui32*4U;
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

/* @brief Free memory of stack and clear structure */
void Memory_StackDestroy_vd(Memory_Stack_st *Stack)
{
  if(NULL!=Stack)
  {
    if(Stack->Base_pui32)
    {
      munmap(Stack->Base_pui32-(Stack->SizeInWords_ui32*4U), Stack->SizeInWords_ui32*4U);
    }
    Stack->Base_pui32 = NULL;
    Stack->Top_pui32 = NULL;
    Stack->SizeInWords_ui32 = 0U;
  }
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
  return ((Stack->Base_pui32-Stack->Top_pui32)>=Stack->SizeInWords_ui32);
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
  printf("Stack size in words:\t0x%x\n", Stack->SizeInWords_ui32);
  printf("Stack Base:\t\t%p\n", (void*)Stack->Base_pui32);
  printf("Stack Top:\t\t%p\n", (void*)Stack->Top_pui32);
  printf("-------------------------------------------------\n");
}

