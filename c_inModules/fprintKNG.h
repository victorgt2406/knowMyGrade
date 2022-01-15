#ifndef __FPRINTKNG_H_
#define __FPRINTKNG_H_

#include "tostringKNG.h"

/*Write in files data of the diferents structs*/

//MAIN

void fprintMainBox(Box main);
void fprintInsideBox(Box box, char* directory);
void fprintInsideSubjet(Subjet subjet, char* directory);
void fprintInsideSubjFrac(SubjFrac subjFrac, char* directory);

//FPRINTS

void fprintBox(char* filename, Box* box, int length);
void fprintSubjet(char* filename, Subjet* subjet, int length);
void fprintSubjFrac(char* filename, SubjFrac* subjFrac, int length);
void fprintGrade(char* filename, Grade* grades, int length);

#endif