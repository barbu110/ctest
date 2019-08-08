/*
 * Copyright (c) 2019 by Victor Barbu and Alexandru - George Rusu. All Rights Reserved.
 */

#include "ctest/assertions.h"

int opi(int a, enum iops_enum b, int c)
{
  static const char array[] = {
#define $(x,op)   &&x - &&ADD,
    IOPS
#undef $
  };
  if (b >= IOPSENUM_COUNT) return a;
  goto *(&&ADD + array[b]);
#define $(x,op)   x: return a op c;
  IOPS
#undef $
}