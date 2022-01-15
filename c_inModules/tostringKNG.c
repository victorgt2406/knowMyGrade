/*ToStrings*/
#include "tostringKNG.h"

#define BUFFER_SPRINTF 200

/*to string of a Box*/
char* boxToString(Box box){
    char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
    sprintf(res,"%s-%d-%d",box.name,box.length,box.type);
    return res;
}
/*to string of a Subjet*/
char* subjetToString(Subjet subjet){
    char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
    sprintf(res,"%s-%d-%d",subjet.name,subjet.subjFrac_length,subjet.usedValue);
    return res;          
}
/*to string of a SubjFrac*/
char* subjFracToString(SubjFrac subjFrac){
    char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
    sprintf(res,"%s-%d-%d-%.3f",subjFrac.name,subjFrac.grades_length,subjFrac.value,subjFrac.mean);
    return res;
}
/*to string of a Grade*/
char* gradeToString(Grade grade){
    char* res=(char*)malloc(sizeof(char)*BUFFER_SPRINTF);
    sprintf(res,"%s-%.3f",grade.name,grade.grade);
    return res;
}