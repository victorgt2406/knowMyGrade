/*  
 *NEW BOX, SUBJET, SUBJET FRACTION, GRADES
 */
    #include "newKNG.h"
    
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
            cleanBuffer();
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
