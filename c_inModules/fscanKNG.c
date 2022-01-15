#include "fscanKNG.h"

/*Read*/
    /*Parse all files in a box*/    
    Box fscanMainBox(){
        Box main;
        FILE* f;
        f = fopen(mainFileName, "r");
        if (f == NULL)
        {
            printf("%s is not created\n",mainFileName);
            main.type=nothing;
        }
        else{
            RowColumnStr file = fileToStr(f,'-');
            char* name = (char*)malloc(sizeof(char)*strlen(file.str[0][0]));
            strcpy(name, file.str[0][0]);
            main.name = name;
            main.length = atoi(file.str[0][1]);
            main.type = atoi(file.str[0][2]);
            freeRowColStr(file);
            if(main.type==tBox){
                int size=strlen(main.name)+strlen("/")+strlen(main.name)+strlen(".txt");
                char* filename=NULL;
                filename=(char*)malloc(sizeof(char)*(size+1));
                strcpy(filename,main.name);                          
                strcat(filename,"/");
                strcat(filename,main.name);
                strcat(filename,".txt");
                main.box = fscanBox(main.name,filename);
                free(filename);
            }
            else{
                int size=strlen(main.name)+strlen("/")+strlen(main.name)+strlen(".txt");
                char* filename=NULL;
                filename=(char*)malloc(sizeof(char)*(size+1));
                strcpy(filename,main.name);                          
                strcat(filename,"/");
                strcat(filename,main.name);
                strcat(filename,".txt");
                main.subjet = fscanSubjet(main.name,filename);
                free(filename);
            }
            printf("All data required read\n");
        }
        return main;
    }
    /*Read Box file*/
    Box* fscanBox(char* directory, char* filename){
        /*
        sprintf(res,"%s-%d-%d\n",box.name,box.length,box.type);
        */
        FILE* f;
        Box* box=NULL;
        f=fopen(filename,"r");
        if(f!=NULL){
            RowColumnStr file = fileToStr(f,'-');
            box=(Box*)malloc(sizeof(Box)*file.row);
            for(int i=0; i<file.row; i++){
                for(int j=0; j<file.col[i]; j++){
                    if(j==0){
                        char* name = (char*)malloc(sizeof(char)*strlen(file.str[i][j]));
                        strcpy(name, file.str[i][j]);
                        box[i].name = name;
                    }
                    if(j==1){
                        box[i].length = atoi(file.str[i][j]);
                    }
                    if(j==2){
                        box[i].type = atoi(file.str[i][j]);

                        if(box[i].type == tBox){
                            /*NEW DIRECTORY*/
                            int size=strlen(directory)+strlen("/")+strlen(box[i].name);
                            char* newDirectory=NULL;
                            newDirectory=(char*)malloc(sizeof(char)*(size+1));
                            strcpy(newDirectory,directory); 
                            strcat(newDirectory,"/");
                            strcat(newDirectory,box[i].name);

                            /*NEW FILE NAME*/
                            size=strlen(newDirectory)+strlen("/")+strlen(box[i].name)+strlen(".txt");
                            char* newFilename=NULL;
                            newFilename=(char*)malloc(sizeof(char)*(size+1));
                            strcpy(newFilename,newDirectory);                          
                            strcat(newFilename,"/");
                            strcat(newFilename,box[i].name);
                            strcat(newFilename,".txt");
                            box[i].box = fscanBox(newDirectory, newFilename);

                            /*Frees*/
                            free(newDirectory);
                            free(newFilename);
                        }
                        else if(box[i].type == tSubjet){
                            /*NEW DIRECTORY*/
                            int size=strlen(directory)+strlen("/")+strlen(box[i].name);
                            char* newDirectory=NULL;
                            newDirectory=(char*)malloc(sizeof(char)*(size+1));
                            strcpy(newDirectory,directory); 
                            strcat(newDirectory,"/");
                            strcat(newDirectory,box[i].name);

                            /*NEW FILE NAME*/
                            size=strlen(newDirectory)+strlen("/")+strlen(box[i].name)+strlen(".txt");
                            char* newFilename=NULL;
                            newFilename=(char*)malloc(sizeof(char)*(size+1));
                            strcpy(newFilename,newDirectory);                          
                            strcat(newFilename,"/");
                            strcat(newFilename,box[i].name);
                            strcat(newFilename,".txt");
                            box[i].subjet = fscanSubjet(newDirectory, newFilename);

                            /*Frees*/
                            free(newDirectory);
                            free(newFilename);
                        }
                    }
                    

                }
            }
            freeRowColStr(file);
        }
        return box;
    }
    /*Read Subjet file*/
    Subjet* fscanSubjet(char* directory, char* filename){
        /*
            sprintf(res,"%s-%d-%d\n",subjet.name,subjet.subjFrac_length,subjet.usedValue);
        */
        FILE* f;
        Subjet* subjet=NULL;
        f=fopen(filename,"r");
        if(f!=NULL){
            RowColumnStr file = fileToStr(f,'-');
            subjet=(Subjet*)malloc(sizeof(Subjet)*file.row);
            for(int i=0; i<file.row; i++){
                for(int j=0; j<file.col[i]; j++){
                    if(j==0){
                        char* name = (char*)malloc(sizeof(char)*strlen(file.str[i][j]));
                        strcpy(name, file.str[i][j]);
                        subjet[i].name = name;
                    }
                    if(j==1){
                        subjet[i].subjFrac_length = atoi(file.str[i][j]);
                    }
                    if(j==2){
                        subjet[i].usedValue = atoi(file.str[i][j]);

                        /*NEW DIRECTORY*/
                        int size=strlen(directory)+strlen("/")+strlen(subjet[i].name);
                        char* newDirectory=NULL;
                        newDirectory=(char*)malloc(sizeof(char)*(size+1));
                        strcpy(newDirectory,directory); 
                        strcat(newDirectory,"/");
                        strcat(newDirectory,subjet[i].name);

                        /*NEW FILE NAME*/
                        size=strlen(newDirectory)+strlen("/")+strlen(subjet[i].name)+strlen(".txt");
                        char* newFilename=NULL;
                        newFilename=(char*)malloc(sizeof(char)*(size+1));
                        strcpy(newFilename,newDirectory);                          
                        strcat(newFilename,"/");
                        strcat(newFilename,subjet[i].name);
                        strcat(newFilename,".txt");
                        subjet[i].subjFrac = fscanSubjFrac(newDirectory, newFilename);

                        /*Frees*/
                        free(newDirectory);
                        free(newFilename);
                    }
                }
            }
            freeRowColStr(file);
        }
        return subjet;
    }
    /*Read Subjet Fraction file*/
    SubjFrac* fscanSubjFrac(char* directory, char* filename){
        /*
        sprintf(res,"%s-%d-%d-%.3f\n",subjFrac.name,subjFrac.grades_length,subjFrac.value,subjFrac.mean);
        */
        
        FILE* f;
        SubjFrac* subjFrac=NULL;
        f=fopen(filename,"r");
        if(f!=NULL){
            RowColumnStr file = fileToStr(f,'-');
            subjFrac=(SubjFrac*)malloc(sizeof(SubjFrac)*file.row);
            for(int i=0; i<file.row; i++){
                for(int j=0; j<file.col[i]; j++){
                    if(j==0){
                        char* name = (char*)malloc(sizeof(char)*strlen(file.str[i][j]));
                        strcpy(name, file.str[i][j]);
                        subjFrac[i].name = name;
                    }
                    if(j==1){
                        subjFrac[i].grades_length = atoi(file.str[i][j]);
                    }
                    if(j==2){
                        subjFrac[i].value = atoi(file.str[i][j]);

                        /*NEW DIRECTORY*/
                        int size=strlen(directory)+strlen("/")+strlen(subjFrac[i].name);
                        char* newDirectory=NULL;
                        newDirectory=(char*)malloc(sizeof(char)*(size+1));
                        strcpy(newDirectory,directory); 
                        strcat(newDirectory,"/");
                        strcat(newDirectory,subjFrac[i].name);

                        /*NEW FILE NAME*/
                        size=strlen(newDirectory)+strlen("/")+strlen(subjFrac[i].name)+strlen(".txt");
                        char* newFilename=NULL;
                        newFilename=(char*)malloc(sizeof(char)*(size+1));
                        strcpy(newFilename,newDirectory);                          
                        strcat(newFilename,"/");
                        strcat(newFilename,subjFrac[i].name);
                        strcat(newFilename,".txt");
                        subjFrac[i].grades = fscanGrade(newDirectory, newFilename);

                        /*Frees*/
                        free(newDirectory);
                        free(newFilename);
                    }
                    if(j==3){
                        subjFrac[i].mean=(float)atof(file.str[i][j]);
                    }
                }
            }
            freeRowColStr(file);
        }
        return subjFrac;
    }
    /*Read Grade file*/
    Grade* fscanGrade(char* directory, char* filename){
    /*
    sprintf(res,"%s-%.3f\n",grade.name,grade.grade);
    */
    FILE* f;
    Grade* grade=NULL;
    f=fopen(filename,"r");
    if(f!=NULL){
        RowColumnStr file = fileToStr(f,'-');
        grade=(Grade*)malloc(sizeof(Grade)*file.row);
        for(int i=0; i<file.row; i++){
            for(int j=0; j<file.col[i]; j++){
                if(j==0){
                    char* name = (char*)malloc(sizeof(char)*strlen(file.str[i][j]));
                    strcpy(name, file.str[i][j]);
                    grade[i].name = name;
                }
                if(j==1){
                    grade[i].grade = (float)atof(file.str[i][j]);
                }
            }
        }
        freeRowColStr(file);
    }

    return grade;
}

/*EXTRA*/

    /*delete main directory*/
    void deleteDataDir(){
        system("rm -d -r Data");
    }