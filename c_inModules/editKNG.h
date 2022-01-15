#ifndef __EDITKNG_H_
#define __EDITKNG_H_

#include "knowMyGrade.h"
#include "printKNG.h"
#include "newKNG.h"

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

#endif