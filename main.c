#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pyramid.h"
#include "base.h"


int main()
{
   Base* base = BaseConstructor();
   BasePrintStdout(base);
   DeleteMultipleKeys(base);
   BasePrintStdout(base);

   return 0;
}