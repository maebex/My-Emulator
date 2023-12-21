
#include <stdio.h>
#include "Unity/src/unity.h"




int main()
{
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 1, "BLAAAAAAA");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, 0, "BLUBB");

  printf("BLAAAA\n");
  return 0;
}

void setUp(void) 
{
  ;
}

void tearDown(void) 
{
    // clean stuff up here
  ;
}


