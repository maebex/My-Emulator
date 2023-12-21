
#include <stdio.h>
#include "Unity/src/unity.h"
#include "memory/memory.h"


void UTST_memory_tc1__Memory_StackInit_vd(void)
{ 
  Memory_Error_enm Error = Memory_Error_Success;
  Memory_Stack_st TestStack = {0};
  // Test if we cal init a stack
  TestStack.SizeInWords_ui32 = 0xFFU;
  Error = Memory_StackInit_ui32(&TestStack);
  TEST_ASSERT_EQUAL(Memory_Error_Success, Error);
  // Test if it raises an error if stack is already initialized
  Error = Memory_StackInit_ui32(&TestStack);
  TEST_ASSERT_EQUAL(Memory_Error_NoRealloc, Error);
  // Test if an error is raised if mmap fails
  // TODO
  
  Memory_StackDestroy_vd(&TestStack);
}

void UTST_memory_tc2__Memory_StackDestroy_vd(void)
{ 
  Memory_Error_enm Error = Memory_Error_Success;
  Memory_Stack_st TestStack = {0};
  // Test if we can call Memory_StackDestroy_vd with NULL pointer
  Memory_StackDestroy_vd(NULL);
  // Test if we can call Memory_StackDestroy_vd if Base pointer is NULL
  Memory_StackDestroy_vd(&TestStack);
  // Test regular operation
  TestStack.SizeInWords_ui32 = 0xFFU;
  Error = Memory_StackInit_ui32(&TestStack);
  TEST_ASSERT_EQUAL(Memory_Error_Success, Error);
}

void UTST_memory_tc3__Memory_PushAndPop_vd(void)
{ 
  #define LEN_SEQUENCE (5U)
  Memory_Error_enm Error = Memory_Error_Success;
  Memory_Stack_st TestStack = {0};
  TestStack.SizeInWords_ui32 = 0x5U;
  Error = Memory_StackInit_ui32(&TestStack);
  TEST_ASSERT_EQUAL(Memory_Error_Success, Error);
  uint32_t TestSequence[LEN_SEQUENCE] = {0xAFFE, 0xDEAD, 0xBEEF, 0xFAFE, 0xEFFA};
  uint32_t PoppedSequence[LEN_SEQUENCE] = {0U};
  // Push sequence onto stack
  for(uint32_t i=0; i<LEN_SEQUENCE; i++)
  {
    Memory_StackPushWord_vd(&TestStack, TestSequence[i]);
  }
  // Check if stack is now full
  uint32_t IsFull = Memory_StackIsFull(&TestStack);
  TEST_ASSERT_EQUAL(1U, IsFull);

  // Check if an error is raised if we keep pushing
  Error = Memory_StackPushWordSafe_ui32(&TestStack, 0xABU);
  TEST_ASSERT_EQUAL(Memory_Error_StackOverflow, Error);

  // Pop sequence back
  for(uint32_t i=0; i<LEN_SEQUENCE; i++)
  {
    PoppedSequence[LEN_SEQUENCE-1-i] = Memory_StackPopWord_ui32(&TestStack);
  }

  // Assert if sequences are equal
  TEST_ASSERT_EQUAL_UINT32_ARRAY(TestSequence, PoppedSequence, LEN_SEQUENCE);

  // Check if stack is empty
  uint32_t IsEmpty = Memory_StackIsEmpty(&TestStack);
  TEST_ASSERT_EQUAL(1U, IsEmpty);

  Memory_StackDestroy_vd(&TestStack);

  #undef LEN_SEQUENCE
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(UTST_memory_tc1__Memory_StackInit_vd);
  RUN_TEST(UTST_memory_tc2__Memory_StackDestroy_vd);
  RUN_TEST(UTST_memory_tc3__Memory_PushAndPop_vd);

  return UNITY_END();
}

void setUp(void) 
{
  ;
}

void tearDown(void) 
{
  ;
}

