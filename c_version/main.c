/*
    Objectives:
    -Make a program which reading some .txt, calculates your grade in the schooll, college, university, ...
*/
#include <stdio.h>
#include <stdlib.h>

/*Structs*/
    /*For comodity*/

    /*Know My Grade*/
        /*Grades*/
        typedef struct Grade
        {
            char* name;
            float grade;
        }Grade;
        
        /*Fracctions of a subjet*/
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
            SubjFrac* subjFrac;     //Obligatory    Fracctions of a subjet
            int subFrac_length;     //Obligatory    Number of Subjets Fractions
            int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
        }Subjet;

        /*Union with my Know My Grade Structs*/
        typedef struct Arrays_KMG
        {
            union{
                Grade* grade;
                SubjFrac* subjFrac;
                Subjet* subjet;
            };
            int array_length;         
        }Arrays_KMG;

        /*Enum with my types*/
        typedef enum Enum_KMG{
                grade,
                subjFrac,
                subjet,
        }Enum_KMG;
        

/*FUNCTIONS DECLARATIONS*/
    /*Basics*/
    char* scanString();
    void cleanBuffer();
    char* strTabs(int n);

    /*Know My Grade*/
        //NEW
        Subjet newSubjet();
        SubjFrac newSubjFrac(int* usedValue);
        Grade newGrade();
        //PRINT
        void printcSubjet(Subjet print, int all, int tab);
        void printcSubjFrac(SubjFrac print, int all, int tab);
        void printcGrade(Grade print, int tab);
        //EDIT
        int editSubjet(Subjet* subjet);
        int editSubjFrac(SubjFrac* frac);
            //MENU
            int editSubjFracMenu();
            int editSubjetMenu();
        //DELETE
        Arrays_KMG deleteElement(Arrays_KMG orig, Enum_KMG e, int arrayPos);

    
void main(){
    Subjet sub = newSubjet();
    printcSubjet(sub,1,0);
    editSubjet(&sub);
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

            Grade newGrade(){
                Grade new;
                new.grade=0;
                printf("Grade name:\n");
                new.name=scanString();

                do{
                    printf("Your grade:\n");
                    scanf("%f",&new.grade);
                    cleanBuffer();
                }while(new.grade<0);

                return new;
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
                    printf("%s\tNumber of grades: %d\n",t,print.grades_length);
                    for(int i=0; i<print.grades_length; i++){
                        printcGrade(print.grades[i],tab+2);
                    }
                }
            }
    
            void printcGrade(Grade print, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%sScore of %.2f in %s\n",t,print.grade,print.name);
            }
        /*Edit*/
            int editSubjet(Subjet* subjet){
                /*
                printf("Edit subjet:"
                    "\t1.Edit name\n"
                    "\t2.Edit number of subjets fracctions\n"
                    "\t3.Edit subjets fracctions\n"
                    "\t-1.Delete\n");
                */
                printf("%s -> ",subjet->name);
                int menu = editSubjetMenu();
                int delete=0;
                switch (menu)
                {
                    case -1:
                        delete=1;
                        break;
                    case /*edit name*/1:
                        printf("Edit name:\n");
                        free(subjet->name);
                        subjet->name=NULL;
                        subjet->name=scanString();
                        break;

                    case /*Edit number of subjets fracctions*/2:;
                        int length=subjet->subFrac_length;
                        do{
                            printf("Fractions of subjets:\n");
                            scanf("%d",&subjet->subFrac_length);
                            cleanBuffer();
                        }while(subjet->subFrac_length<=0 || subjet->subFrac_length>=length);
                        break;

                    case /*Edit subjets fracctions*/3:;
                        int fraccion;
                        do{
                            printf("Choose the fraction of the subject:\n");
                            for(int i=0; i<subjet->subFrac_length; i++){
                                printf("%i: ",i+1);
                                printcSubjFrac(subjet->subjFrac[i],0,0);
                            }
                            scanf("%d",&fraccion);
                            cleanBuffer();
                        }while(fraccion <= 0 || fraccion > (subjet->subFrac_length));
                        fraccion--;
                        /*edit Subject fraction selected:*/
                        if(editSubjFrac(&(subjet->subjFrac[fraccion]))==1){
                            printf("%s has been deleted\n",subjet->subjFrac[fraccion].name);
                            /*In case of delete*/
                                /*Copy from the pointer of subjFrac*/
                                Arrays_KMG orig;    
                                orig.subjFrac=subjet->subjFrac;
                                orig.array_length=subjet->subFrac_length;
                                /*Copy the new pointer to subjFrac*/
                                Arrays_KMG res = deleteElement(orig, subjFrac, fraccion);
                                subjet->subjFrac = res.subjFrac;
                                subjet->subFrac_length = res.array_length;
                        }
                        break;
                    default:
                        printf("Error in editSubjet();\n");
                        break;
                    }
                return delete;
            }
    
            int editSubjFrac(SubjFrac* frac){
                /*
                printf("Edit subjet fraccion:\n"
                    "\t1.Edit name"
                    "\t2.Edit value"
                    "\t3.Edit grades"
                    "\t-1.Delete");
                */
                printf("%s -> ",frac->name);
                int menu = editSubjFracMenu();
                int delete=0;
                switch (menu)
                {
                    case /*delete*/ -1:
                        delete=1;
                        break;
                    case /*edit name*/ 1:
                        printf("Edit name:\n");
                        free(frac->name);
                        frac->name=NULL;
                        frac->name=scanString();
                        break;
                    
                    case /*edit value*/ 2:;
                        int lastValue=frac->value;
                        do{
                            printf("Edit value:\n");
                            scanf("%d",&frac->value);
                        }while(frac->value <= 0 || frac->value>=lastValue);
                        break;

                    case /*edit grades*/ 3:
                        break;

                    default:
                        printf("Error in editSubjFrac();\n");
                        break;
                    }
                return delete;
            }
            /*Edit menu*/
                int editSubjetMenu(){
                    /*
                    typedef struct Subjet
                    {
                        char* name;             //Obligatory
                        SubjFrac* subjFrac;     //Obligatory    Fracctions of a subjet
                        int subFrac_length;     //Obligatory    Number of Subjets Fractions
                        int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
                    }Subjet;
                    */
                    int menu=-2;
                    do{
                        printf("Edit subjet:\n"
                            "\t1.Edit name\n"
                            "\t2.Edit number of subjets fracctions\n"
                            "\t3.Edit subjets fracctions\n"
                            "\t-1.Delete\n");
                        scanf("%d",&menu);
                        cleanBuffer();                    
                    }while((menu < -1 && menu > 2) || menu == 0);
                    return menu;
                }

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
                            "\t1.Edit name\n"
                            "\t2.Edit value\n"
                            "\t3.Edit grades\n"
                            "\t-1.Delete\n");

                        scanf("%d",&menu);
                        cleanBuffer();
                    }while((menu < -1 && menu > 3) || menu == 0);
                    return menu;
                }
        
        /*Delete element in array*/
            Arrays_KMG deleteElement(Arrays_KMG orig, Enum_KMG e, int arrayPos){
                Arrays_KMG array;
                array.array_length = orig.array_length-1;
                switch (e)
                {
                case grade:
                    array./*Change*/grade = (/*Change*/Grade*)malloc(sizeof(/*Change*/Grade)*(array.array_length));
                    int j=0; //j-array counter
                    for(int i=0; i<orig.array_length; i++){
                        //i-orig counter
                        if(i!=arrayPos){
                            array./*Change*/grade[j]=orig./*Change*/grade[i];
                            j++;
                        }
                    }
                    free(orig./*Change*/grade);
                    orig./*Change*/grade=NULL;
                    break;
                case subjFrac:
                    array./*Change*/subjFrac = (/*Change*/SubjFrac*)malloc(sizeof(/*Change*/SubjFrac)*(array.array_length));
                    j=0; //j-array counter
                    for(int i=0; i<orig.array_length; i++){
                        //i-orig counter
                        if(i!=arrayPos){
                            array./*Change*/subjFrac[j]=orig./*Change*/subjFrac[i];
                            j++;
                        }
                    }
                    free(orig./*Change*/subjFrac);
                    orig./*Change*/subjFrac=NULL;
                    break;
                case subjet:
                    array./*Change*/subjet = (/*Change*/Subjet*)malloc(sizeof(/*Change*/Subjet)*(array.array_length));
                    j=0; //j-array counter
                    for(int i=0; i<orig.array_length; i++){
                        //i-orig counter
                        if(i!=arrayPos){
                            array./*Change*/subjet[j]=orig./*Change*/subjet[i];
                            j++;
                        }
                    }
                    free(orig./*Change*/subjet);
                    orig./*Change*/subjet=NULL;
                    break; 
                default:
                    printf("Error in deleteElement();\n");
                    break;
                }

                return array;
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
