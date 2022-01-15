#ifndef __KNOWMYGRADE_H_
#define __KNOWMYGRADE_H_
/*Know My Grade*/
    /*Grades*/
    typedef struct Grade
    {
        char* name;
        float grade;
    }Grade;
    
    /*Fractions of a subjet*/
    typedef struct SubjFrac
    {
        char* name;         //Obligatory
        int value;          //Obligatory    Values from 1% to 100%
        Grade* grades;      //Obligatory
        int grades_length;  //Obligatory

        float mean;         //Not Obligatory
    }SubjFrac;

    /*Subjet*/
    typedef struct Subjet
    {
        char* name;             //Obligatory
        SubjFrac* subjFrac;     //Obligatory    Fractions of a subjet
        int subjFrac_length;    //Obligatory    Number of Subjets Fractions
        int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
    
        float mean;         //Not Obligatory
    }Subjet;

    /*Box*/
    typedef struct Box
    {
        /*It works like a directoy*/
        char* name;
        int length; //Number of subjets or boxes

        enum type{
            nothing,
            tSubjet,
            tBox,
        }type;

        union{      //Box can only contains subjets or other boxes
            Subjet* subjet;
            struct Box* box;
        };
        
        float mean;         //Not Obligatory
    }Box;

    /*struct with my Know My Grade Structs*/
    typedef struct Arrays_KMG
    {
        union{
            Grade* grade;
            SubjFrac* subjFrac;
            Subjet* subjet;
            Box* box;
        };
        int array_length;         
    }Arrays_KMG;

    /*Enum with my types*/
    typedef enum Enum_KMG{
        grade,
        subjFrac,
        subjet,
        BoxKMG,
    }Enum_KMG;

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    //My libs
    #include "libs/basics.h"
    #include "libs/filemanager.h"

    char mainFileName[20];
    char mainDirName[20];

#endif