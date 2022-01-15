/*Basics*/
#include <stdio.h>
#include <stdlib.h>

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