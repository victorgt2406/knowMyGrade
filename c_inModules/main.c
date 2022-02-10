/*
    Objectives:
    -Make a program which reading some .txt, calculates your grade in the schooll, college, university, ...
    -You save your subjets in boxes and you can save this boxes to another boxes. Each box can calculate
    the mean.

    -Make a .html where saves all of this data and used to know your worst subjet or your best subjet.
*/

#include "knowMyGrade.h"
//all files
#include "editKNG.h"
#include "fprintKNG.h"
#include "fscanKNG.h"
#include "newKNG.h"
#include "printKNG.h"
#include "tostringKNG.h"

char mainFileName[20]="Data.txt";
char mainDirName[20]="Data";

void main(){
    Box box = fscanMainBox();
    //If there are not files
    if(box.type == nothing){
        box = atomaticNewBox();
    }
    printcBox(box,1,0);
    editBox(&box);
    //Delete data in directory:
    deleteDataDir();
    //Create directory:
    makeDirectory(box.name);
    //Save main box.
    fprintMainBox(box);
}