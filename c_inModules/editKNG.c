#include "editKNG.h"

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
                if(subjFrac->grades_length > 0){
                    do{
                        printf("Choose the grade:\n");
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
        case grade:;
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
        case subjFrac:;
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
        case subjet:;
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
        case BoxKMG:;
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
