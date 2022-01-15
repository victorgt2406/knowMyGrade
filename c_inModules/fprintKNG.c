/*FPRINTKNG*/

#include "fprintKNG.h"


/*Call to write*/

    void fprintMainBox(Box main){
        /*Paste the main box to an "array" with poniters to use the func that prints
            *the data of arrays of boxes.
            */
        Box* box = (Box*)malloc(sizeof(Box));
        box[0]=main;
        //Print the data of the main box in the project directory
        fprintBox(mainFileName,box,1);
        //Then print the data inside of the main box
        fprintInsideBox(main, main.name);
        //free
        free(box);
    }
    /*Write in a file all data inside a Box and creates its directories*/
    void fprintInsideBox(Box box, char* directory){
        //Make .txt with the content of the box
        int size=strlen(directory)+strlen("/")+strlen(box.name)+strlen(".txt");
        char* newFile=NULL;
        newFile=(char*)malloc(sizeof(char)*(size+1));
        strcpy(newFile,directory);                          
        strcat(newFile,"/");
        strcat(newFile,box.name);
        strcat(newFile,".txt");                   
        //See type
        if(box.type==tBox){
            fprintBox(newFile,box.box, box.length);
            for(int i=0; i<box.length; i++){
                //Copy new directory:
                char* newDirectory=NULL;
                size=strlen(directory)+strlen("/")+strlen(box.box[i].name);
                newDirectory=(char*)malloc(sizeof(char)*(size+1));
                strcpy(newDirectory,directory);
                strcat(newDirectory,"/");
                strcat(newDirectory,box.box[i].name);
                //Make new directory
                makeDirectory(newDirectory);
                //Look next box
                fprintInsideBox(box.box[i], newDirectory);
                free(newDirectory);
            }
        }
        else if(box.type==tSubjet){
            fprintSubjet(newFile,box.subjet, box.length);
            for(int i=0; i<box.length; i++){
                //Copy new directory:
                char* newDirectory=NULL;
                size=strlen(directory)+strlen("/")+strlen(box.subjet[i].name);
                newDirectory=(char*)malloc(sizeof(char)*(size+1));
                strcpy(newDirectory,directory);
                strcat(newDirectory,"/");
                strcat(newDirectory,box.subjet[i].name);
                //Make new directory
                makeDirectory(newDirectory);
                //Look next box
                fprintInsideSubjet(box.subjet[i], newDirectory);
                //free
                free(newDirectory);
                newDirectory=NULL;
            }
        }
        free(newFile);
    }
    /*Write in a file all data inside a Subjet with its directories of subjet fraction*/
    void fprintInsideSubjet(Subjet subjet, char* directory){
        //Make .txt with the content of the Subjet
        int size=strlen(directory)+strlen("/")+strlen(subjet.name)+strlen(".txt");
        char* newFile=NULL;
        newFile=(char*)malloc(sizeof(char)*(size+1));
        strcpy(newFile,directory);                          
        strcat(newFile,"/");
        strcat(newFile,subjet.name);
        strcat(newFile,".txt");
        
        fprintSubjFrac(newFile,subjet.subjFrac, subjet.subjFrac_length);    //Create file
        //loop for subjet.subjFrac array pointer
        for(int i=0; i<subjet.subjFrac_length; i++){
            //Copy new directory:
            char* newDirectory=NULL;
            size=strlen(directory)+strlen("/")+strlen(subjet.subjFrac[i].name);
            newDirectory=(char*)malloc(sizeof(char)*(size+1));
            strcpy(newDirectory,directory);
            strcat(newDirectory,"/");
            strcat(newDirectory,subjet.subjFrac[i].name);
            //Make new directory
            makeDirectory(newDirectory);
            //Go to Subjt Frac
            fprintInsideSubjFrac(subjet.subjFrac[i],newDirectory);
            //free
            free(newDirectory);
            newDirectory=NULL;
        }
        free(newFile);
    }
    /*Write in a file all grades data in .txt with the name of the Subjet Fraction*/
    void fprintInsideSubjFrac(SubjFrac subjFrac, char* directory){
        //Make .txt with the content of the box
        int size=strlen(directory)+strlen("/")+strlen(subjFrac.name)+strlen(".txt");
        char* newFile=NULL;
        newFile=(char*)malloc(sizeof(char)*(size+1));
        strcpy(newFile,directory);                          
        strcat(newFile,"/");
        strcat(newFile,subjFrac.name);
        strcat(newFile,".txt");

        fprintGrade(newFile,subjFrac.grades, subjFrac.grades_length);
        free(newFile);
    }

/*Writes in Files*/

    /*Writes the data of an array of boxes inside a Box*/
    void fprintBox(char* filename, Box* box, int length){
        FILE* f;
        f = fopen(filename, "r");
        if (f == NULL)
        {
            printf("%s file is created\n",filename);
        }
        else{
            printf("%s file is updated\n",filename);
            fclose(f);
        }
        
        f = fopen(filename, "w");
        for(int i=0; i<length; i++){
            char* toString = NULL;
            toString = boxToString(box[i]);
            fprintf(f,"%s",toString);
            if(!(i>=length-1)){
                fprintf(f,"\n");
            }
            free(toString);
        }
        fclose(f);
    }
    /*Writes the data of an array of subjets inside a Box*/
    void fprintSubjet(char* filename, Subjet* subjet, int length){
        FILE* f;
        f = fopen(filename, "r");
        if (f == NULL)
        {
            printf("%s file is created\n",filename);
        }
        else{
            printf("%s file is updated\n",filename);
            fclose(f);
        }
        
        f = fopen(filename, "w");
        for(int i=0; i<length; i++){
            char* toString = NULL;
            toString = subjetToString(subjet[i]);
            fprintf(f,"%s",toString);
            if(!(i>=length-1)){
                fprintf(f,"\n");
            }
            free(toString);
        }
        fclose(f);
    }
    /*Writes the data of an array of a subjet fractions inside a Subjet*/
    void fprintSubjFrac(char* filename, SubjFrac* subjFrac, int length){
        FILE* f;
        f = fopen(filename, "r");
        if (f == NULL)
        {
            printf("%s file is created\n",filename);
        }
        else{
            printf("%s file is updated\n",filename);
            fclose(f);
        }
        f = fopen(filename, "w");
        for(int i=0; i<length; i++){
            char* toString = NULL;
            toString = subjFracToString(subjFrac[i]);
            fprintf(f,"%s",toString);
            if(!(i>=length-1)){
                fprintf(f,"\n");
            }
            free(toString);
        }
        fclose(f);
    }
    /*Writes the data of an array of grades inside a Subjet_Fraction(SubjFrac)*/
    void fprintGrade(char* filename, Grade* grades, int length){
        FILE* f;
        f = fopen(filename, "r");
        if (f == NULL)
        {
            printf("%s file is created\n",filename);
        }
        else{
            printf("%s file is updated\n",filename);
            fclose(f);
        }
        f = fopen(filename, "w");
        for(int i=0; i<length; i++){
            char* toString = NULL;
            toString = gradeToString(grades[i]);
            fprintf(f,"%s",toString);
            if(!(i>=length-1)){
                fprintf(f,"\n");
            }
            free(toString);
        }
        fclose(f);
    }
