#ifndef __BASICS_H_
#define __BASICS_H_

/*Basics*/
char* scanString();     //Read a string from console.
void cleanBuffer();     //Cleans the buffer from scanf();
char* strTabs(int n);   //Creates a string with n tabulators
int makeDirectory(char* nameOfDirectory);   //Creates a new directory if it doesn't exist.

#endif