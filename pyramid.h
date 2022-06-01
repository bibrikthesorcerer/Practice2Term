#pragma once

struct RightPyramid;

typedef struct RightPyramid RightPyramid;

struct RightPyramid* Constructor();

RightPyramid* FileConstructor(FILE* f);

void MemDestructor(RightPyramid* Object);

void PyramidPrint(RightPyramid* Object);

void PyramidPrintFile(FILE* f, RightPyramid* Object);

/*
calculates the area of pyramid's base
*/
double AreaOfBase(RightPyramid* Object);//1
/*
calculates the pyramid's volume
*/
double PyramidVolume(RightPyramid* Object);//2
/*
calculates the pyramid's apothem
*/
double Apothem(RightPyramid* Object);//3
/*
calculates the area of pyramid's side surface
*/
double AreaOfSideSurface(RightPyramid* Object);//4
/*
calculates the area of pyramid's full surface
*/
double AreaOfFullSurface(RightPyramid* Object);//5

double GetHeight(RightPyramid* Object);

double GetSideRib(RightPyramid* Object);

double GetBaseRib(RightPyramid* Object);

double GetBaseRadius(RightPyramid* Object);

int GetNumAngles(RightPyramid* Object);
