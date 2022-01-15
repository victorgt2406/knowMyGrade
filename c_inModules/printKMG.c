
#include "printKNG.h"
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
