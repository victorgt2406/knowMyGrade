/*
    Objectives:
    -Make a program which reading some .txt, calculates your grade in the schooll, college, university, ...
*/
#include <stdio.h>
#include <stdlib.h>

/*Structs*/
    /*For comodity*/
        typedef struct String
        {
            char* toString;
            int length;
        }String;
    /*Know My Grade*/
        /*Fracctions of a subjet*/
        typedef struct SubjFrac
        {
            char* name;         //Obligatory
            int value;          //Obligatory    Values from 1% to 100%
            int* grades;        //Obligatory
            int grades_length;  //Obligatory

            float mean;         //Not Obligatory
        }SubjFrac;

        /*Subjet*/
        typedef struct Subjet
        {
            char* name;             //Obligatory
            SubjFrac* subjFrac;     //Obligatory    Fracctions of a subjet
            int subFrac_length;     //Obligatory    Number of Subjets Fractions
            int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
        }Subjet;

/*FUNCTIONS DECLARATIONS*/
    /*Basics*/
    char* scanString();
    void cleanBuffer();
    char* strTabs(int n);

    /*Know My Grade*/
        //NEW
        Subjet newSubjet();
        SubjFrac newSubjFrac(int* usedValue);
        void newGrade(SubjFrac* subjFrac);
        //PRINT
        void printcSubjet(Subjet print, int all, int tab);
        void printcSubjFrac(SubjFrac print, int all, int tab);

    
void main(){
    Subjet sub = newSubjet();
    printcSubjet(sub,1,0);
}

/*FUNCTIONS*/
    /*Know My Grade*/
        /*NEW*/
            /*Creates a new subjet*/
            Subjet newSubjet(){
                Subjet new;

                /*GetInputs*/
                    //Name
                    printf("Subjet name:\n");
                    new.name=scanString();

                    //Fractions
                    do{
                        printf("Fractions of subjets:\n");
                        scanf("%d",&new.subFrac_length);
                        cleanBuffer();
                    }while(new.subFrac_length<=0);

                    //Create new Fractions
                    new.subjFrac=(SubjFrac*)malloc(sizeof(SubjFrac)*new.subFrac_length);
                    new.usedValue=0;
                    for(int i=0; i<new.subFrac_length; i++){
                        new.subjFrac[i]=newSubjFrac(&new.usedValue);
                    }
                return new;
            }

            /*Creates a new subjet Fracction*/
            SubjFrac newSubjFrac(int* usedValue){
                SubjFrac new;

                /*GetInputs*/
                    //Name
                    printf("Fraction subjet name:\n");
                    new.name=scanString();

                    //Value
                    new.value=0;
                    do{
                        printf("Fraction subjet value:\n");
                        scanf("%d",&new.value);
                        cleanBuffer();
                    }while(new.value<=1 || new.value >(100-(*usedValue)));
                    
                    //Update used Value
                    (*usedValue)+=new.value;

                    //Grades length
                    new.grades_length = 0;
                    new.grades=NULL;

                return new;
            }

            void newGrade(SubjFrac* subjFrac){
                int grade=0;
                do{
                    printf("Your grade:\n");
                    scanf("%d",&grade);
                    cleanBuffer();
                }while(grade<0);
                subjFrac->grades=(SubjFrac*)realloc(subjFrac->grades,sizeof(SubjFrac)*((subjFrac->grades_length)+1));
                subjFrac->grades[subjFrac->grades_length]=grade;
                subjFrac->grades_length++;
            }

        /*Print in console*/
            /*Print Subjet*/
            void printcSubjet(Subjet print, int all, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%s%s\n",t,print.name);
                //Fractions
                printf("%s\tNumber of fractions: %d\n",t,print.subFrac_length);
                for(int i=0; i<print.subFrac_length; i++){
                    printcSubjFrac(print.subjFrac[i],all,(tab+1));
                }
                //Used Value:
                printf("%sUsed value: %d\n",t,print.usedValue);
            }

            void printcSubjFrac(SubjFrac print, int all, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%s%s\n",t,print.name);
                printf("%s\tValue: %d%%\n",t,print.value);
                if(all==1){
                    printf("%s\tNumber of grades:%d\n%s\t",t,print.grades_length,t);
                    for(int i=0; i<print.grades_length; i++){
                        printf("%d",print.grades[i]);
                        if(i!=print.grades_length-1){
                            printf(",");
                        }
                        else{
                            printf(";");
                        }
                    }
                    printf("\n");
                }
            }
    
        /*Edit*/
            int editSubjet(Subjet subjet,int option){
                int delete=0;
                switch (option)
                {
                case 0:
                    delete=1;
                    break;
                case 1://name
                    printf("Edit name:\n");
                    free(subjet.name);
                    subjet.name=NULL;
                    subjet.name=scanString();
                    break;

                case 2://Fractions length
                    int length=subjet.subFrac_length;
                    do{
                        printf("Fractions of subjets:\n");
                        scanf("%d",&subjet.subFrac_length);
                        cleanBuffer();
                    }while(subjet.subFrac_length<=0 || subjet.subFrac_length>=length);
                    break;

                case 3://Fractions 
                    for(int i=0; i<subjet.subFrac_length; i++){
                        printcSubjFrac(subjet.subjFrac[i],0,0);
                    }
                    int fraccion;
                    do{
                        printf("Choose the fraction of the subject:\n");
                        scanf("%d",&fraccion);
                        cleanBuffer();
                    }while(fraccion<=0 || fraccion>=subjet.subFrac_length);

                default:
                    break;
                }
                return delete;
            }
    
            int editSubjFrac(SubjFrac frac){
                /*
                printf("Edit subjet fraccion:\n"
                    "\t1.Edit name"
                    "\t2.Edit value"
                    "\t3.Edit grades"
                    "\t-1.Delete");
                */
                int menu = editSubjFracMenu();
                switch (menu)
                {
                case /*edit name*/1:
                    printf("Edit name:\n");
                    free(frac.name);
                    frac.name=NULL;
                    frac.name=scanString();
                    break;

                default:
                    break;
                }
            }
            /*Edit menu*/
            int editSubjFracMenu(){
                /*
                typedef struct SubjFrac
                {
                    char* name;         //Obligatory
                    int value;          //Obligatory    Values from 1% to 100%
                    int* grades;        //Obligatory
                    int grades_length;  //Obligatory

                    float mean;         //Not Obligatory
                }SubjFrac;
                */
                int menu=-2;
                do{
                    printf("Edit subjet fraccion:\n"
                        "\t1.Edit name"
                        "\t2.Edit value"
                        "\t3.Edit grades"
                        "\t-1.Delete");

                    scanf("%d",&menu);
                    cleanBuffer();
                }while(menu<-1 && menu>3);
                return menu;
            }
    /***************/
    /*Basics*/
        void cleanBuffer(){
            while(getchar()!='\n'){
                ;
            }
        }

        char* scanString(){
            char letra='a';
            int i=0;
            char* str=(char*)malloc(sizeof(char));
            while(letra!='\n'){
                letra=getchar();
                if(letra!='\n'){
                    str[i]=letra;
                    i++;
                    str=(char*)realloc(str,sizeof(char)*i);
                }
            }
            str[i]='\0';
            return str;
        }

        char* strTabs(int n){
            char* str=(char*)malloc(sizeof(char)*(n+1));
            for(int i=0; i<n; i++){
                str[i]='\t';
            }
            str[n]='\0';
            return str;
        }
    /***************/
