#ifndef __FSCANKNG_H_
#define __FSCANKNG_H_

#include "knowMyGrade.h"

//READ FILES AND COVERTS THEM TO STRUCTS

Box fscanMainBox();
Box* fscanBox(char* directory, char* filename);
Subjet* fscanSubjet(char* directory, char* filename);
SubjFrac* fscanSubjFrac(char* directory, char* filename);
Grade* fscanGrade(char* directory, char* filename);
void deleteDataDir();

#endif