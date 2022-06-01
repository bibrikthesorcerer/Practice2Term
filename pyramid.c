#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pyramid.h"

struct RightPyramid
{
   double Height;// высота
   double SideRib;//боковое ребро
   double BaseRib;// ребро основания
   double BaseRadius;//радиус вписанной окр
   int NumOfAngles;// кол-во углов
};

RightPyramid* FileConstructor(FILE* f)
{
   RightPyramid* obj = (RightPyramid*)malloc(sizeof(RightPyramid));
   if (!obj)
   {
      return NULL;
   }

   fscanf_s(f,"%lf", &obj->Height);
   fscanf_s(f, "%lf", &obj->SideRib);
   fscanf_s(f, "%lf", &obj->BaseRib);
   fscanf_s(f, "%lf", &obj->BaseRadius);
   fscanf_s(f, "%d", &obj->NumOfAngles);

   return obj;
}

RightPyramid* Constructor()
{
	RightPyramid* obj = (RightPyramid*)malloc(sizeof(RightPyramid));
   if (!obj)
   {
      return NULL;
   }
   //Input
   printf("Enter values of the Pyramid in centimeters\n");  
   //Height
   printf("Height of the Pyramid: ");
   scanf_s("%lf",&obj->Height);
   //SideRib
   printf("Side rib of the Pyramid: ");
   scanf_s("%lf", &obj->SideRib);
   //BaseRib
   printf("Base rib of the Pyramid: ");
   scanf_s("%lf", &obj->BaseRib);
   //BaseRadius
   printf("Base radius of the Pyramid: ");
   scanf_s("%lf", &obj->BaseRadius);
   //NumberOfAngles
   printf("The number of corners of the base of the Pyramid: ");
   scanf_s("%d", &obj->NumOfAngles);
   //
	return obj;
}

void PyramidPrint(RightPyramid* Object)
{
   printf("Height - %lf\n", Object->Height);
   printf("SideRib - %lf\n", Object->SideRib);
   printf("BaseRib - %lf\n", Object->BaseRib);
   printf("BaseRadius - %lf\n", Object->BaseRadius);
   printf("NumberOfAngles - %d\n", Object->NumOfAngles);
}

void PyramidPrintFile(FILE*f, RightPyramid* Object)
{
   fprintf(f, "Height - %lf\n", Object->Height);
   fprintf(f, "SideRib - %lf\n", Object->SideRib);
   fprintf(f, "BaseRib - %lf\n", Object->BaseRib);
   fprintf(f, "BaseRadius - %lf\n", Object->BaseRadius);
   fprintf(f, "NumberOfAngles - %d\n", Object->NumOfAngles);
}

void MemDestructor(RightPyramid* Object)
{
   free(Object);
}

double AreaOfBase(RightPyramid* Object)
{
   return 0.5 * Object->BaseRib * Object->NumOfAngles * Object->BaseRadius;
}

double PyramidVolume(RightPyramid* Object)
{
   return (AreaOfBase(Object) * Object->Height) / 3;
}

double Apothem(RightPyramid* Object)
{
   return sqrtf(pow(Object->SideRib, 2) - pow((Object->BaseRib / 2.0), 2));
}

double AreaOfSideSurface(RightPyramid* Object)
{
   return 0.5 * Object->BaseRib * Object->NumOfAngles * Apothem(Object);
}

double AreaOfFullSurface(RightPyramid* Object)
{
   return AreaOfSideSurface(Object) + AreaOfBase(Object);
}

double GetHeight(RightPyramid* Object)
{
   return Object->Height;
}

double GetSideRib(RightPyramid* Object)
{
   return Object->SideRib;
}

double GetBaseRib(RightPyramid* Object)
{
   return Object->BaseRib;
}

double GetBaseRadius(RightPyramid* Object)
{
   return Object->BaseRadius;
}

int GetNumAngles(RightPyramid* Object)
{
   return Object->NumOfAngles;
}