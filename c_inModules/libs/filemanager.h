#ifndef __FILEMANAGER_H_
#define __FILEMANAGER_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/*Rows Columns Strigs*/

typedef struct RowColumnStr
{
    char*** str;    /*String:
                        *-Pointer 1: Row (Strings)
                        *-Pointer 2: Column (String)
                        *-Pointer 3: Word (Character)*/
    int row;        //Number of rows
    int* col;       //Number of columns per row
    int** len;      //String len per row & column
}RowColumnStr;


//READ FILES

RowColumnStr fileToStr(FILE* f, char delimiter);    //Convert File in a 3 pointer char or 2 pointer String
void printcRowColStr(RowColumnStr str);             //Print the RowColumn String
void freeRowColStr();                               //Free the memory of RowColumn String
int makeDirectory(char* nameOfDirectory);           //Makes a directory with the route or name introduced as a String

#endif