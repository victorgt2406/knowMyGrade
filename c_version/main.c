/*
    Objectives:
    -Make a program which reading some .txt, calculates your grade in the schooll, college, university, ...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*to make directories*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*Structs*/
    /*For comodity*/

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
            int subjFrac_length;     //Obligatory    Number of Subjets Fractions
            int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
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
            
            
        }Box;
        

        /*Atruct with my Know My Grade Structs*/
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
        

/*FUNCTIONS DECLARATIONS*/
    /*Basics*/
    char* scanString();     //Read a string from console.
    void cleanBuffer();     //Cleans the buffer from scanf();
    char* strTabs(int n);   //Creates a string with n tabulators
    int makeDirectory(char* nameOfDirectory);   //Creates a new directory if it doesn't exist.

    /*Know My Grade*/

        //NEW

        Box atomaticNewBox();
        Box newBox();
        Subjet newSubjet();
        SubjFrac newSubjFrac(int* usedValue);
        Grade newGrade();

        //PRINT

        void printcBox(Box print, int all, int tab);
        void printcSubjet(Subjet print, int all, int tab);
        void printcSubjFrac(SubjFrac print, int all, int tab);
        void printcGrade(Grade print, int tab);

        //EDIT

        int editBox(Box* box);
        int editSubjet(Subjet* subjet);
        int editSubjFrac(SubjFrac* frac);
        int editGrade(Grade* grade);

            //MENU

            int editBoxMenu();
            int editSubjetMenu();
            int editSubjFracMenu();
            int editGradeMenu();

            //EXTRA

            void updateSubjFracValues(Subjet* subjet);

        //DELETE

        Arrays_KMG deleteElement(Arrays_KMG orig, Enum_KMG e, int arrayPos);

        //FILES

            //MAIN

            void fprintInsideBox(Box box, char* directory);
            void fprintInsideSubjet(Subjet subjet, char* directory);
            void fprintInsideSubjFrac(SubjFrac subjFrac, char* directory);

            //FPRINTS

            void fprintBox(char* filename, Box* box, int length);
            void fprintSubjet(char* filename, Subjet* subjet, int length);
            void fprintSubjFrac(char* filename, SubjFrac* subjFrac, int length);
            void fprintGrade(char* filename, Grade* grades, int length);

            //EXTRA
            
            void deleteDataDir();
                
        //TOSTRINGS

        char* boxToString(Box box);
        char* subjetToString(Subjet subjet);
        char* subjFracToString(SubjFrac subjFrac);
        char* gradeToString(Grade grade);

    
void main(){
    Box box = atomaticNewBox();
    printcBox(box,1,0);
    editBox(&box);
    printcBox(box,1,0);
    deleteDataDir();
    int dir = makeDirectory(box.name);
    printf("%d\n",dir);
    fprintInsideBox(box,box.name);
}

/*FUNCTIONS*/
    
    /*Know My Grade*/
        
        /*NEW*/

            /*Create an automatic new box. Just used the first time executed*/
            Box atomaticNewBox(){
                Box new;
                //Name
                //new.name=(char*) malloc(sizeof(char)*strlen("Data"));
                new.name="Data";
                printf("%s\n",new.name);
                //Type
                new.type=tSubjet;
                //New subjet
                new.length=1;
                new.subjet=(Subjet*)malloc(sizeof(Subjet));
                new.subjet[0]=newSubjet();

                return new;
            }
            /*Create a new box by user*/
            Box newBox(){
                Box new;
                printf("New box\n");
                //Input
                printf("Box name:\n");
                new.name=scanString();
                new.type=nothing;
                do{
                    int choice=0;
                    printf("Box save\n"
                        "\t1.Subjetes\n"
                        "\t2.Boxes\n");
                    scanf("%d",&choice);
                    //Subjet
                    if(choice==1){
                        new.type=tSubjet;
                    }
                    //box
                    else if(choice==2){
                        new.type=tBox;
                    }
                    else{
                        new.type=nothing;
                    }
                }while(new.type==nothing);
                
                new.length=0;
                return new;
            }
            /*Create a new subjet by user*/
            Subjet newSubjet(){
                printf("New subjet:\n");
                Subjet new;

                /*GetInputs*/
                    //Name
                    printf("Subjet name:\n");
                    new.name=scanString();

                    //Fractions
                    do{
                        printf("Fractions of subjets:\n");
                        scanf("%d",&new.subjFrac_length);
                        cleanBuffer();
                    }while(new.subjFrac_length<=0);

                    //Create new Fractions
                    new.subjFrac=(SubjFrac*)malloc(sizeof(SubjFrac)*new.subjFrac_length);
                    new.usedValue=0;
                    for(int i=0; i<new.subjFrac_length; i++){
                        new.subjFrac[i]=newSubjFrac(&new.usedValue);
                    }
                return new;
            }
            /*Create a new subjet fraction by user*/
            SubjFrac newSubjFrac(int* usedValue){
                printf("New subjet fraction:\n");
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
            /*Create a new Grade by user*/
            Grade newGrade(){
                printf("New grade:\n");
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

            /*Print Box in console*/
            void printcBox(Box print, int all, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%s%s\n",t,print.name);
                free(t);
                t=NULL;
                t=strTabs(tab+1);
                if(print.type == tSubjet){
                    printf("%sSubjets(%d)\n",t,print.length);
                    for(int i=0; i<print.length; i++){
                        printcSubjet(print.subjet[i],all,(tab+2));
                    }
                }
                else{
                    printf("%sBoxes(%d)\n",t,print.length);
                    for(int i=0; i<print.length; i++){
                        printcBox(print.box[i],all,(tab+2));
                    }
                }
                free(t);
            }
            /*Print Subjet in console*/
            void printcSubjet(Subjet print, int all, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%s%s\n",t,print.name);
                //Fractions
                printf("%s\tFractions(%d):\n",t,print.subjFrac_length);
                for(int i=0; i<print.subjFrac_length; i++){
                    printcSubjFrac(print.subjFrac[i],all,(tab+2));
                }
                //Used Value:
                printf("%s\tUsed value: %d\n",t,print.usedValue);
                free(t);
            }
            /*Print Subjet Fraction in console*/
            void printcSubjFrac(SubjFrac print, int all, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%s%s\n",t,print.name);
                printf("%s\tValue: %d%%\n",t,print.value);
                if(all==1){
                    printf("%s\tGrades(%d):\n",t,print.grades_length);
                    for(int i=0; i<print.grades_length; i++){
                        printcGrade(print.grades[i],tab+2);
                    }
                }
                free(t);
            }
            /*Print Grade in console*/
            void printcGrade(Grade print, int tab){
                char* t=strTabs(tab);
                //modelo printf("%s",t);
                printf("%sScore of %.2f in %s\n",t,print.grade,print.name);
                free(t);
            }
        
        /*Edit*/

            /*Edit just a pointer of BOX, *NO ARRAYS**/
            int editBox(Box* box){
                /*
                printf("Edit Box:\n"
                    "\t1.Edit name\n"
                    "\t2.Edit subjets or boxes\n"
                    "\n\t3.New subjet or box\n"
                    "\n\t4.Move all this data to a new parent box\n"
                    "\n\t0.Exit\n"
                    "\t-1.Delete\n");
                */
                printf("%s -> ",box->name);
                int menu = editBoxMenu();
                int delete=0;
                switch (menu)
                {
                    case /*delete*/-1:
                        delete=1;
                        break;
                    case /*exit*/0:
                        printf("Exit from edit Subjet menu\n");
                        break;
                    case /*edit name*/1:
                        printf("Edit name:\n");
                        free(box->name);
                        box->name=NULL;
                        box->name=scanString();
                        break;
                    case /*edit Boxes or Subjets*/2:;
                        int pos;
                        do{
                            
                            if(box->type==tSubjet){
                                printf("Choose the Subjet:\n");
                                for(int i=0; i<box->length; i++){
                                    printf("%i: ",i+1);
                                    printcSubjet(box->subjet[i],0,0);
                                }
                            }
                            else{
                               printf("Choose the Box:\n");
                                for(int i=0; i<box->length; i++){
                                    printf("%i: ",i+1);
                                    printcBox(box->box[i],0,0);
                                } 
                            }
                            scanf("%d",&pos);
                            cleanBuffer();
                        }while(pos <= 0 || pos > (box->length));
                        pos--;
                        /*edit Subject fraction selected:*/
                        if(box->type==tSubjet){
                            if(editSubjet(&(box->subjet[pos]))==1){
                                printf("%s has been deleted\n",box->subjet[pos].name);
                                /*In case of delete*/
                                    /*Copy from the pointer of subjFrac*/
                                    Arrays_KMG orig;    
                                    orig.subjet=box->subjet;
                                    orig.array_length=box->length;
                                    /*Copy the new pointer to subjFrac*/
                                    Arrays_KMG res = deleteElement(orig, subjet, pos);
                                    box->subjet = res.subjet;
                                    box->length = res.array_length;
                            }
                        }
                        else{
                            if(editBox(&(box->box[pos]))==1){
                                printf("%s has been deleted\n",box->subjet[pos].name);
                                /*In case of delete*/
                                    /*Copy from the pointer of subjFrac*/
                                    Arrays_KMG orig;    
                                    orig.box=box->box;
                                    orig.array_length=box->length;
                                    /*Copy the new pointer to subjFrac*/
                                    Arrays_KMG res = deleteElement(orig, BoxKMG, pos);
                                    box->subjet = res.subjet;
                                    box->length = res.array_length;
                            }
                        }
                        break;
                    
                    case /*New box or Subjet*/3:
                        //+1 length of the array
                        box->length++;
                        if(box->type==tSubjet){
                            box->subjet=(Subjet*)realloc(box->subjet, sizeof(Subjet)*(box->length));
                            //getting the new element in the las position
                            box->subjet[(box->length-1)]=newSubjet();
                        }
                        else{
                            box->box=(Box*)realloc(box->box, sizeof(Box)*(box->length));
                            //getting the new element in the las position
                            box->box[(box->length-1)]=newBox();
                        }
                        break;

                    case /*Move data to a parent new box*/4:;
                        if(box->type==tBox){
                            //Input data of new box
                            Box newBox;
                            printf("Name for the parent new Box:\n");
                            newBox.name = scanString();
                            newBox.type = tBox;
                            newBox.box = box->box;
                            newBox.length = box->length;
                            //Update the box data
                            box->box=NULL;
                            box->length=1;
                            box->box=(Box*)malloc(sizeof(Box)*box->length);
                            box->box[0]=newBox;
                        }
                        else{
                            //Input data of new box
                            Box newBox;
                            printf("Name for the parent new Box:\n");
                            newBox.name = scanString();
                            newBox.type = tSubjet;
                            newBox.subjet = box->subjet;
                            newBox.length = box->length;
                            //Update the box data
                            box->subjet=NULL;
                            box->type=tBox;//parse to type box
                            box->box=NULL;
                            box->length=1;
                            box->box=(Box*)malloc(sizeof(Box)*box->length);
                            box->box[0]=newBox;
                        }
                        break;
                    
                    default:
                        printf("Error in editBox();\n");
                        break;
                    }
                    return delete;
                }            
            /*Edit just a pointer of SUBJET, *NO ARRAYS**/
            int editSubjet(Subjet* subjet){
                /*
                 printf("Edit subjet:\n"
                    "\t1.Edit name\n"
                    "\t2.Edit subjets fractions\n"
                    "\n\t3.New subjet fraction\n"
                    "\n\t0.Exit\n"
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
                    case 0:
                        printf("Exit from edit Subjet menu\n");
                        break;
                    case /*edit name*/1:
                        printf("Edit name:\n");
                        free(subjet->name);
                        subjet->name=NULL;
                        subjet->name=scanString();
                        break;

                    case /*Edit subjets fractions*/2:;
                        int pos;
                        do{
                            printf("Choose the fraction of the subject:\n");
                            for(int i=0; i<subjet->subjFrac_length; i++){
                                printf("%i: ",i+1);
                                printcSubjFrac(subjet->subjFrac[i],0,0);
                            }
                            scanf("%d",&pos);
                            cleanBuffer();
                        }while(pos <= 0 || pos > (subjet->subjFrac_length));
                        pos--;
                        /*edit Subject fraction selected:*/
                        if(editSubjFrac(&(subjet->subjFrac[pos]))==1){
                            printf("%s has been deleted\n",subjet->subjFrac[pos].name);
                            /*In case of delete*/
                                /*Copy from the pointer of subjFrac*/
                                Arrays_KMG orig;    
                                orig.subjFrac=subjet->subjFrac;
                                orig.array_length=subjet->subjFrac_length;
                                /*Copy the new pointer to subjFrac*/
                                Arrays_KMG res = deleteElement(orig, subjFrac, pos);
                                subjet->subjFrac = res.subjFrac;
                                subjet->subjFrac_length = res.array_length;
                        }
                        break;

                    case /*New subjet fraction*/3:;
                        //Updating subjet fractions values
                        if(subjet->usedValue >= 100){
                            updateSubjFracValues(subjet);
                        }
                        //+1 length of the array
                        subjet->subjFrac_length++;
                        subjet->subjFrac=(SubjFrac*)realloc(subjet->subjFrac, sizeof(SubjFrac)*(subjet->subjFrac_length));
                        //getting the new element in the las position
                        subjet->subjFrac[(subjet->subjFrac_length-1)]=newSubjFrac(&(subjet->usedValue));

                        break;
                    default:
                        printf("Error in editSubjet();\n");
                        break;
                    }
                return delete;
            }
            /*Edit just a pointer of a FRACTION_OF_A_SUBJET, *NO ARRAYS**/
            int editSubjFrac(SubjFrac* subjFrac){
                /*
                printf("Edit subjet fraccion:\n"
                    "\t1.Edit name\n"
                    "\t2.Edit value\n"
                    "\t3.Edit grades\n"
                    "\n\t4.New grade\n"
                    "\n\t0.Exit\n"
                    "\t-1.Delete\n");
                */
                printf("%s -> ",subjFrac->name);
                int menu = editSubjFracMenu();
                int delete=0;
                switch (menu)
                {
                    case /*delete*/ -1:
                        delete=1;
                        break;
                    case 0:
                        printf("Exit from edit Subjet Fraction menu\n");
                        break;
                    case /*edit name*/ 1:
                        printf("Edit name:\n");
                        free(subjFrac->name);
                        subjFrac->name=NULL;
                        subjFrac->name=scanString();
                        break;
                    
                    case /*edit value*/ 2:;
                        int lastValue=subjFrac->value;
                        do{
                            printf("Edit value:\n");
                            scanf("%d",&subjFrac->value);
                        }while(subjFrac->value <= 0 || subjFrac->value>=lastValue);
                        break;

                    case /*edit grades*/ 3:;
                        int pos=0;
                        do{
                            printf("Choose the fraction of the subject:\n");
                            for(int i=0; i<subjFrac->grades_length; i++){
                                printf("\t%i: ",i+1);
                                printcGrade(subjFrac->grades[i],0);
                            }
                            scanf("%d",&pos);
                            cleanBuffer();
                        }while(pos <= 0 || pos > (subjFrac->grades_length));
                        if(editGrade(subjFrac->grades)==1){
                            /*Delete*/
                            printf("%s has been deleted\n",subjFrac->grades[pos].name);
                            /*In case of delete*/
                                /*Copy from the pointer of grades*/
                                Arrays_KMG orig;    
                                orig.grade=subjFrac->grades;
                                orig.array_length=subjFrac->grades_length;
                                /*Copy the new pointer to grades*/
                                Arrays_KMG res = deleteElement(orig, grade, pos);
                                subjFrac->grades = res.grade;
                                subjFrac->grades_length = res.array_length;

                        }

                    case /*new grade*/4:;
                        //+1 length of the array
                        subjFrac->grades_length++;  
                        subjFrac->grades=(Grade*)realloc(subjFrac->grades, sizeof(Grade)*(subjFrac->grades_length));
                        //getting the new element in the las position
                        subjFrac->grades[(subjFrac->grades_length-1)]=newGrade();
                        break;

                    default:
                        printf("Error in editSubjFrac();\n");
                        break;
                    }
                return delete;
            }
            /*Edit just a pointer of a GRADE, *NO ARRAYS**/
            int editGrade(Grade* grade){
                int delete=0;
                /*
                printf("Edit Grade:\n"
                    "\t1.Edit name\n"
                    "\t2.Edit grade\n\n"
                    "\t0.Exit\n"
                    "\t-1.Delete\n"
                    );
                */
                int menu = editGradeMenu();
                switch (menu)
                {
                    case /*Delete*/-1:
                        delete=1;
                        break;
                    case /*exit*/0:
                        break;
                    case /*Edit name*/1:
                        printf("Edit name (actual = %s):\n",grade->name);
                        free(grade->name);
                        grade->name=NULL;
                        grade->name=scanString();
                        break;
                    case /*Edit grade*/2:;
                        do{
                            printf("Edit grade (actual = %f):\n",grade->grade);
                            scanf("%f",&grade->grade);
                            cleanBuffer();
                        }while(grade->grade<0);
                        break;
                    
                    default:
                        printf("Error in editGrade();\n");
                        break;
                    }
            }
            
            /*Edit menu*/

                /*Prints in console the edit BOX menu*/
                int editBoxMenu(){
                    #define MAX_boxMenu 4
                    /*
                    typedef struct Box
                    {
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
                    }Box;
                    */
                    int menu=-2;
                    do{
                        printf("Edit Box:\n"
                            "\t1.Edit name\n"
                            "\t2.Edit subjets or boxes\n"
                            "\n\t3.New subjet or box\n"
                            "\n\t4.Move all this data to a new parent box\n"
                            "\n\t0.Exit\n"
                            "\t-1.Delete\n");
                        scanf("%d",&menu);
                        cleanBuffer();                    
                    }while((menu < -1 && menu > MAX_boxMenu));
                    return menu;
                }
                /*Prints in console the edit SUBJET menu*/
                int editSubjetMenu(){
                    #define MAX_editSubjetMenu 3
                    /*
                    typedef struct Subjet
                    {
                        char* name;             //Obligatory
                        SubjFrac* subjFrac;     //Obligatory    fractions of a subjet
                        int subFrac_length;     //Obligatory    Number of Subjets Fractions
                        int usedValue;          //Obligatory    To know the value that has being used in the Subjets Fractions
                    }Subjet;
                    */
                    int menu=-2;
                    do{
                        printf("Edit subjet:\n"
                            "\t1.Edit name\n"
                            "\t2.Edit subjets fractions\n"
                            "\n\t3.New subjet fraction\n"
                            "\n\t0.Exit\n"
                            "\t-1.Delete\n");
                        scanf("%d",&menu);
                        cleanBuffer();                    
                    }while((menu < -1 && menu > MAX_editSubjetMenu));
                    return menu;
                }
                /*Prints in console the edit a FRACTION_OF_A_BOX menu*/
                int editSubjFracMenu(){
                    #define MAX_editSubjFracMenu 5
                    /*
                    typedef struct SubjFrac
                    {
                        char* name;         //Obligatory
                        int value;          //Obligatory    Values from 1% to 100%
                        Grades* grades;     //Obligatory
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
                            "\n\t4.New grade\n"
                            "\n\t0.Exit\n"
                            "\t-1.Delete\n");

                        scanf("%d",&menu);
                        cleanBuffer();
                    }while((menu < -1 && menu > 3));
                    return menu;
                }
                /*Prints in console the edit GRADE menu*/
                int editGradeMenu(){
                    int menu=0;
                    do{
                        printf("Edit Grade:\n"
                            "\t1.Edit name\n"
                            "\t2.Edit grade\n"
                            "\n\t0.Exit\n"
                            "\t-1.Delete\n");
                        scanf("%d",&menu);
                        cleanBuffer();
                    }while( menu < -1 && menu > 2);

                    return menu;
                }
            
            /*Extra*/

                /*Ask the user to update the used value inside a Subjet*/
                void updateSubjFracValues(Subjet* subjet){
                    while(subjet->usedValue>=100){
                        subjet->usedValue=0;
                        for(int i=0; i<(subjet->subjFrac_length); i++){
                            int yes=0;
                            printf("%s has a value of %d%%,\n"
                            "do you want to change it?\n"
                            "Press 1 if yes.\n",subjet->subjFrac[i].name,subjet->subjFrac[i].value);
                            scanf("%d",&yes);
                            cleanBuffer();
                            if(yes==1){
                                do{
                                    printf("Type the new value:\n");
                                    scanf("%d",&subjet->subjFrac[i].value);
                                    cleanBuffer();
                                }while(subjet->subjFrac[i].value <= 0);
                            }
                            subjet->usedValue+=subjet->subjFrac[i].value;
                        }
                        if(subjet->usedValue>=100){
                            printf("The total value is over 100%%, %d%%.\n  It has to be under 100%%\n",subjet->usedValue);
                        }
                    }
                }
        
        /*Delete element in an array*/
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
                case BoxKMG:
                    array./*Change*/box = (/*Change*/Box*)malloc(sizeof(/*Change*/Box)*(array.array_length));
                    j=0; //j-array counter
                    for(int i=0; i<orig.array_length; i++){
                        //i-orig counter
                        if(i!=arrayPos){
                            array./*Change*/box[j]=orig./*Change*/box[i];
                            j++;
                        }
                    }
                    free(orig./*Change*/box);
                    orig./*Change*/box=NULL;
                    break; 
                default:
                    printf("Error in deleteElement();\n");
                    break;
                }

                return array;
            }
    
        /*Files*/
            /*Call to print*/

                /*Print in a file all data inside a Box and creates its directories*/
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
                /*Print in a file all data inside a Subjet with its directories of subjet fraction*/
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
                /*Print in a file all grades data in .txt with the name of the Subjet Fraction*/
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

            /*print in Files*/

                /*Prints the data of an array of boxes inside a Box*/
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
                        fprintf(f,"%s",boxToString(box[i]));
                    }
                    fclose(f);
                }
                /*Prints the data of an array of subjets inside a Box*/
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
                    char* text=NULL;
                    for(int i=0; i<length; i++){
                        text=subjetToString(subjet[i]);
                        fprintf(f,"%s",text);
                        free(text);
                        text=NULL;
                    }
                    fclose(f);
                }
                /*Prints the data of an array of a subjet fractions inside a Subjet*/
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
                        fprintf(f,"%s",subjFracToString(subjFrac[i]));
                    }
                    fclose(f);
                }
                /*Prints the data of an array of grades inside a Subjet_Fraction(SubjFrac)*/
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
                        fprintf(f,"%s",gradeToString(grades[i]));
                    }
                    fclose(f);
                }
            
            /*EXTRA*/

                /*delete main directory*/
                void deleteDataDir(){
                    system("rm -d -r Data");
                }
        /*ToStrings*/

            #define BUFFER_SPRINTF 200
            /*to string of a Box*/
            char* boxToString(Box box){
                char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
                sprintf(res,"%s-%d-%d\n",box.name,box.length,box.type);
                return res;
            }
            /*to string of a Subjet*/
            char* subjetToString(Subjet subjet){
                char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
                sprintf(res,"%s-%d-%d\n",subjet.name,subjet.subjFrac_length,subjet.usedValue);
                return res;          
            }
            /*to string of a SubjFrac*/
            char* subjFracToString(SubjFrac subjFrac){
                char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
                sprintf(res,"%s-%d-%d-%.3f\n",subjFrac.name,subjFrac.grades_length,subjFrac.value,subjFrac.mean);
                return res;
            }
            /*to string of a Grade*/
            char* gradeToString(Grade grade){
                    char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
                    sprintf(res,"%s-%.3f\n",grade.name,grade.grade);
                    return res;
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
    
        int makeDirectory(char* nameOfDirectory){
            struct stat st = {0};
            int exist=0;
            if (stat(nameOfDirectory, &st) == -1) {
                mkdir(nameOfDirectory, 0700);
                exist=1;
            }
            return exist;
        }

    /***************/
