#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pyramid.h"
#include "base.h"

struct Base
{
   RightPyramid** arr;
   int ObjNum;
};

void InputStdin(Base* base)
{
   int answer = 0;
   
   do
   {
      base->ObjNum++;
      base->arr = (RightPyramid**)realloc(base->arr, base->ObjNum * sizeof(RightPyramid*));
      if (!base->arr)
      {
         printf("Memory is NULL");
         exit(1);
      }

      RightPyramid* Pyramid = Constructor();
      base->arr[base->ObjNum - 1] = Pyramid;
      printf("input again? [1/0]\n");
      scanf_s("%d", &answer);
   } while (answer == 'Y');
}

void InputFile(FILE* f, Base* base)
{
   char str[128] = { "0" };
   fseek(f, 0L, SEEK_END);
   int end = ftell(f);
   fseek(f, 0L, SEEK_SET);
   int pointer = ftell(f);
   while (pointer != end)
   {
      base->ObjNum++;
      base->arr = (RightPyramid**)realloc(base->arr, base->ObjNum * sizeof(RightPyramid*));
      if (!base->arr)
      {
         printf("Memory is NULL");
         exit(1);
      }
      RightPyramid* Pyramid = FileConstructor(f);
      base->arr[base->ObjNum - 1] = Pyramid;
      pointer = ftell(f);
   }
}

void BasePrintStdout(Base* base)
{
   for (int i = 0; i < base->ObjNum; i++)
   {
      printf("Pyramid #%d:\n", i + 1);
      PyramidPrint(base->arr[i]);
      printf("\n");
   }
}

void BasePrintFile(Base* base)
{
   FILE* output = fopen("output.txt", "w");
   for (int i = 0; i < base->ObjNum; i++)
   {
      fprintf(output, "Pyramid #%d:\n", i + 1);
      PyramidPrintFile(output, base->arr[i]);
      fprintf(output, "\n");
   }
   fclose(output);
}

Base* BaseConstructor()
{
   Base* base = (Base*)malloc(sizeof(Base));
   if (!base)
   {
      printf("Memory is NULL");
      exit(1);
   }

   base->ObjNum = 0;
   base->arr = (RightPyramid**)malloc(sizeof(RightPyramid*));
   if (!base->arr)
   {
      printf("Memory is NULL");
      exit(1);
   }

   int answer = 0;
   printf("Do you wanna input Pyramids now? [1/0]\n");
   scanf_s("%d", &answer);

      if (answer == 1)
      {
         char filename[32] = { "0" };
         printf("If you willing to input from a file, then write filename. If not, input N.\n");
         scanf_s("%s", filename, 32);
         if (filename[0] == 'N')
         {
            InputStdin(base);
         }
         else
         {
            FILE* f = fopen(filename, "r");
            InputFile(f,base);
            fclose(f);
         }

      }

   return base;
}

void qsortRecursive(RightPyramid** arr, int KeyNumber, int size)
{
   int i = 0;
   int j = size - 1;
   double mid = 0.0f;
   int midAng = 0;
   RightPyramid* tmp = NULL;
   switch (KeyNumber)
   {
   case 1:
      mid = GetHeight(arr[j / 2]);

      do
      {
         while (GetHeight(arr[i]) < mid)
            i++;
         while (GetHeight(arr[j]) > mid)
            j--;

         if (i <= j)
         {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
         }
      } while (i <= j);

      if (j > 0)
         qsortRecursive(arr, KeyNumber, j+1);
      if (i < size)
         qsortRecursive(&arr[i], KeyNumber, size - i);
      break;
   case 2:
      mid = GetSideRib(arr[j / 2]);

      do
      {
         while (GetSideRib(arr[i]) < mid)
            i++;
         while (GetSideRib(arr[j]) > mid)
            j--;

         if (i <= j)
         {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
         }
      } while (i <= j);

      if (j > 0)
         qsortRecursive(arr, KeyNumber, j+1);
      if (i < size)
         qsortRecursive(&arr[i], KeyNumber, size - i);

      break;
   case 3:
      mid = GetBaseRib(arr[j / 2]);

      do
      {
         while (GetBaseRib(arr[i]) < mid)
            i++;
         while (GetBaseRib(arr[j]) > mid)
            j--;

         if (i <= j)
         {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
         }
      } while (i <= j);

      if (j > 0)
         qsortRecursive(arr, KeyNumber, j+1);
      if (i < size)
         qsortRecursive(&arr[i], KeyNumber, size - i);

      break;
   case 4:
      mid = GetBaseRadius(arr[j / 2]);

      do
      {
         while (GetBaseRadius(arr[i]) < mid)
            i++;
         while (GetBaseRadius(arr[j]) > mid)
            j--;

         if (i <= j)
         {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
         }
      } while (i <= j);

      if (j > 0)
         qsortRecursive(arr, KeyNumber, j+1);
      if (i < size)
         qsortRecursive(&arr[i], KeyNumber, size - i);

      break;
      break;
   case 5:
      midAng = GetNumAngles(arr[j / 2]);

      do
      {
         while (GetNumAngles(arr[i]) < midAng)
            i++;
         while (GetNumAngles(arr[j]) > midAng)
            j--;

         if (i <= j)
         {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
         }
      } while (i <= j);

      if (j > 0)
         qsortRecursive(arr, KeyNumber, j+1);
      if (i < size)
         qsortRecursive(&arr[i], KeyNumber, size - i);

      break;
   }
}

void QuickSortMain(Base* base)
{
   int answer = 0;
   printf("Basing on which parameter do you wanna sort Pyramids?\n1)Height \n2)Side Rib \n3)Base Rib \n4)Base Radius \n5)Number of angles\n");
   scanf_s("%d\n", &answer);
   qsortRecursive(base->arr, answer, base->ObjNum);
}

int BinarySearchStdout(RightPyramid** arr, int KeyNumber, int size, double value, int point)
{

   int i = size / 2;

   double mid = 0.0f;
   if (size == 0)
   {
      printf("There is no such element!\n");
      return -1;
   }

      switch (KeyNumber)
      {
      case 1:
         mid = GetHeight(arr[i]);

         if (value < mid)
         {

            BinarySearchStdout(arr, KeyNumber, i, value, point-1);
         }
         else if (value > mid)
         {
            BinarySearchStdout(&arr[i+1], KeyNumber, size-i-1, value, point+1);
         }
         else
         {
            return point;
         }
         break;

      case 2:
         mid = GetSideRib(arr[i]);

         if (value < mid)
         {
            BinarySearchStdout(arr, KeyNumber, i, value, point - 1);
         }
         else if (value > mid)
         {
            BinarySearchStdout(&arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
         }
         else
         {
            return point;
         }
         break;

      case 3:
         mid = GetBaseRib(arr[i]);

         if (value < mid)
         {
            BinarySearchStdout(arr, KeyNumber, i, value, point - 1);
         }
         else if (value > mid)
         {
            BinarySearchStdout(&arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
         }
         else
         {
            return point;
         }
         break;

      case 4:
         mid = GetBaseRadius(arr[i]);

         if (value < mid)
         {
            BinarySearchStdout(arr, KeyNumber, i, value, point - 1);
         }
         else if (value > mid)
         {
            BinarySearchStdout(&arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
         }
         else
         {
            return point;
         }
         break;
      case 5:
         mid = GetNumAngles(arr[i]);

         if (value < mid)
         {
            BinarySearchStdout(arr, KeyNumber, i, value, point - 1);
         }
         else if (value > mid)
         {
            BinarySearchStdout(&arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
         }
         else
         {
            return point;
         }
         break;

      }
      return -1;/////////
}

int BinarySearchFile(FILE* output, RightPyramid** arr, int KeyNumber, int size, double value, int point)
{
   int i = size / 2;
   double mid = 0.0f;
   if (size == 0)
   {
      fprintf(output,"There is no such element!\n");
      return -1;
   }

   switch (KeyNumber)
   {
   case 1:
      mid = GetHeight(arr[i]);

      if (value < mid)
      {

         BinarySearchFile(output, arr, KeyNumber, i, value, point-1);
      }
      else if (value > mid)
      {
         BinarySearchFile(output, &arr[i + 1], KeyNumber, size - i - 1, value, point+1);
      }
      else
      {
         return point;
      }
      break;

   case 2:
      mid = GetSideRib(arr[i]);

      if (value < mid)
      {

         BinarySearchFile(output, arr, KeyNumber, i, value, point - 1);
      }
      else if (value > mid)
      {
         BinarySearchFile(output, &arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
      }
      else
      {
         return point;
      }
      break;

   case 3:
      mid = GetBaseRib(arr[i]);

      if (value < mid)
      {

         BinarySearchFile(output, arr, KeyNumber, i, value, point - 1);
      }
      else if (value > mid)
      {
         BinarySearchFile(output, &arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
      }
      else
      {
         return point;
      }
      break;

   case 4:
      mid = GetBaseRadius(arr[i]);

      if (value < mid)
      {

         BinarySearchFile(output, arr, KeyNumber, i, value, point - 1);
      }
      else if (value > mid)
      {
         BinarySearchFile(output, &arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
      }
      else
      {
         return point;
      }
      break;
   case 5:
      mid = GetNumAngles(arr[i]);

      if (value < mid)
      {

         BinarySearchFile(output, arr, KeyNumber, i, value, point - 1);
      }
      else if (value > mid)
      {
         BinarySearchFile(output, &arr[i + 1], KeyNumber, size - i - 1, value, point + 1);
      }
      else
      {
         return point;
      }
      break;

   }

   return -1;////////
}

void BinarySearchMain(Base* base)
{
   int answer = 0;
   double value = 0;
   printf("Basing on which parameter do you wanna find Pyramid?\n1)Height \n2)Side Rib \n3)Base Rib \n4)Base Radius \n5)Number of angles\n");
   scanf_s("%d", &answer);
   qsortRecursive(base->arr, answer, base->ObjNum);
   printf("What's the value of the chosen parameter?\n");
   scanf_s("%lf", &value);

   printf("If you wanna output the result in file, then type 1, else type 0.\n");
   int InputOrFile = 0;
   scanf_s("%d", &InputOrFile);
   if (InputOrFile)
   {
      FILE* output = fopen("output.txt", "w");
      int pointer = BinarySearchFile(output, base->arr, answer, base->ObjNum, value, (base->ObjNum / 2));
      if (pointer != -1)
      {
         fprintf(output, "The element was found:\n");
         PyramidPrintFile(output, base->arr[pointer]);
         fprintf(output, "\n");
         fclose(output);
      }
   }
   else
   {
      int pointer = BinarySearchStdout(base->arr, answer, base->ObjNum, value, (base->ObjNum/2) );
      if (pointer != -1)
      {
         printf("The element was found:\n");
         PyramidPrint(base->arr[pointer]);
         printf("\n");
      }

   }
   
}

int* SearchMultipleKeys(Base* base)
{
   int* PointersArray = (int*)malloc(base->ObjNum * sizeof(int));
   if (!PointersArray)
   {
      printf("Memory is NULL");
      exit(1);
   }

   RightPyramid** KeyArray = (RightPyramid**)malloc(base->ObjNum*sizeof(RightPyramid*));
   if (!KeyArray)
   {
      printf("Memory is NULL");
      exit(1);
   }

   int answer = 0;
   double value = 0;
   int size = base->ObjNum;
   int k = 0;

   for (size_t i = 0; i < size; i++)
   {
      KeyArray[i] = base->arr[i];
      PointersArray[i] = i;
   }

   do
   {
      k = 0;
      printf("Basing on which parameter do you wanna find Pyramid? If you want to stop, press 0.\n1)Height \n2)Side Rib \n3)Base Rib \n4)Base Radius \n5)Number of angles\n");
      scanf_s("%d", &answer);
      if (!answer)
      {
         break;
      }
      qsortRecursive(base->arr, answer, size);
      qsortRecursive(KeyArray, answer, size);
      
      printf("What's the value of the chosen parameter?\n");
      scanf_s("%lf", &value);
      for (int i = 0; i < size; i++)
      {
         switch (answer)
         {
         case 1:
             if(value == GetHeight(KeyArray[i]))
             {
                KeyArray[k] = KeyArray[i];
                PointersArray[k] = PointersArray[i];
                k++;
             }
             break;
         case 2:
            if (GetSideRib(KeyArray[i]) == value)
            {
               KeyArray[k] = KeyArray[i];
               PointersArray[k] = PointersArray[i];
               k++;
            }
            break;
         case 3:
            if (GetBaseRib(KeyArray[i]) == value)
            {
               KeyArray[k] = KeyArray[i];
               PointersArray[k] = PointersArray[i];
               k++;
            }
            break;
         case 4:
            if (GetBaseRadius(KeyArray[i]) == value)
            {
               KeyArray[k] = KeyArray[i];
               PointersArray[k] = PointersArray[i];
               k++;
            }
            break;
         case 5:
            if (GetNumAngles(KeyArray[i]) == value)
            {
               KeyArray[k] = KeyArray[i];
               PointersArray[k] = PointersArray[i];
               k++;
            }
            break;
         }

      }
      for (size_t i = k; i < size; i++)
      {
         PointersArray[i] = -1;
      }
      size = k;

   } while (answer != 0);

   if (PointersArray[0] == -1)
   {
      printf("There is no element with this parameters.\n");
      return;
   }
   free(KeyArray);
   return PointersArray;
}

void SearchMultipleKeysMain(Base* base)
{
   int* PointersArray = (int*)malloc(base->ObjNum * sizeof(int));
   if (!PointersArray)
   {
      printf("Memory is NULL");
      exit(1);
   }

   PointersArray = SearchMultipleKeys(base);
   printf("If you wanna output the result in file, then type 1, else type 0.\n");
   int InputOrFile = 0;
   scanf_s("%d", &InputOrFile);
   if (InputOrFile)
   {
      FILE* output = fopen("output.txt", "w");
      for (int i = 0; PointersArray[i] != -1; i++)
      {
         int index = PointersArray[i];
         PyramidPrintFile(output, base->arr[index]);
         fprintf(output, "\n");
      }
      fclose(output);

   }
   else
   {
      for (int i = 0; PointersArray[i] != -1; i++)
      {
         int index = PointersArray[i];
         PyramidPrint(base->arr[index]);
         printf("\n");
      }
   }
   free(PointersArray);
   return;
}

void DeleteMultipleKeys(Base* base)
{
   int answer = 0;
   double value = 0;
   printf("Starting a deleting by multiple keys...\n");

   int* PointerArray = SearchMultipleKeys(base);
   size_t i = 0;
   for (; PointerArray[i] != -1; i++)
   {
      swap(&base->arr[PointerArray[i]], &base->arr[base->ObjNum - 1 - i]);
   }
   for (size_t j = 0; j < i ; j++)
   {
      DeleteLast(base);
   }
   printf("The object was successfully deleted.\n");

}

void DeleteLast(Base* base)
{
   MemDestructor(base->arr[base->ObjNum - 1]);
   base->ObjNum--;
   base->arr = (RightPyramid**)realloc(base->arr, base->ObjNum * sizeof(RightPyramid*));
}

void swap(RightPyramid** p1, RightPyramid** p2) 
{
   RightPyramid* temp = *p1;
   *p1 = *p2;
   *p2 = temp;
}

void DeleteKey(Base* base)
{
   int answer = 0;
   double value = 0;
   printf("Basing on which parameter do you wanna delete Pyramid?\n1)Height \n2)Side Rib \n3)Base Rib \n4)Base Radius \n5)Number of angles\n");
   scanf_s("%d", &answer);
   qsortRecursive(base->arr, answer, base->ObjNum);
   printf("What's the value of the chosen parameter?\n");
   scanf_s("%lf", &value);
   
   int pointer = BinarySearchStdout(base->arr, answer, base->ObjNum, value, (base->ObjNum/2));
   swap(&base->arr[pointer], &base->arr[base->ObjNum - 1]);
   DeleteLast(base);
   printf("The object was successfully deleted.\n");
}

