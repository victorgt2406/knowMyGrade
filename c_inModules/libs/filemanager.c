#include "filemanager.h"

/*Save data from files in a three pointer.
    *-Pointer 1: Row (Strings)
    *-Pointer 2: Column (String)
    *-Pointer 3: Word (Caracter)*/
RowColumnStr fileToStr(FILE* f, char delimiter){
    rewind(f);
    RowColumnStr res;
    char*** str;
    res.col=(int*)malloc(sizeof(int));
    res.len=(int**)malloc(sizeof(int*));
    res.len[0]=(int*)malloc(sizeof(int));

    int row=0, col=0, len=0;
    
    str=(char***)malloc(sizeof(char**)*(row+1));
    str[0]=(char**)malloc(sizeof(char*)*(col+1));
    str[0][0]=(char*)malloc(sizeof(char)*(len+1));

    char aux='a';
    
    while(aux!=EOF){
        
        aux = getc(f);
        if(aux=='\n' || aux == EOF){//New row -> Strings
            /*Save counters*/
            res.col[row]=col+1;     //Save number of columns per row
            res.len[row][col]=len;  //Save number of characters per column
            /*Restart caracters*/
            if(aux=='\n'){
                len=0;
                col=0;
                row++;
                /*Memory necesary to work*/
                str=(char***)realloc(str,sizeof(char**)*(row+1));   //add a row
                str[row]=(char**)malloc(sizeof(char*)*(col+1));     //Inizialize column
                str[row][col]=(char*)malloc(sizeof(char*)*(len+2)); //Inizialize str
                /*Memory of counters*/
                res.col=(int*)realloc(res.col,sizeof(int)*(row+1));
                res.len=(int**)realloc(res.len,sizeof(int*)*(row+1));//add row in len counter
                res.len[row]=(int*)malloc(sizeof(int)*(col+1));     //Inizialize len row column in new row
            }
        }
        else if(aux==delimiter){//New column ->  String
            //printf("%s\n",str[row][col]);
            /*Save counters*/
            res.len[row][col]=len;//Save number of characters per column
            /*Restart caracters*/
            len=0;
            col++;
            /*Memory necesary to work*/
            str[row]=(char**)realloc(str[row],sizeof(char*)*(col+1));       //add column
            str[row][col]=(char*)malloc(sizeof(char*)*(len+2));             //Inizialize str
            /*Memory of counters*/
            res.len[row]=(int*)realloc(res.len[row],sizeof(int)*(col+1));   //add colum to len counter
        }
        else if(aux != EOF){//New caracter -> char
            str[row][col][len]=aux;
            str[row][col][len+1]='\0';
            
            len++;
            /*Memory necesary to work*/
            str[row][col]=(char*)realloc(str[row][col],sizeof(char)*(len+2));
        }
    }

    //Saving data to res
    res.row=row+1;  //Coping the number of rows
    res.str=str;    //Coping the triple pointer.
    //Close file
    fclose(f);

    return res;
}
/*Print rowColumStr*/
void printcRowColStr(RowColumnStr str){
    printf("Rows: %d\n",str.row);
    for(int i=0; i<str.row; i++){
        printf("Column: %d in row: %d\n",str.col[i],i);
        for(int j=0; j<str.col[i]; j++){
            printf("%s ",str.str[i][j]);
        }
        printf("\n");
    }
}
/*Free everything of RowColumnStr*/
void freeRowColStr(RowColumnStr data){
    for(int i=0; i<data.row; i++){
        for(int j=0; j<data.col[i]; j++){
            free(data.str[i][j]);
        }
        free(data.str[i]);
        free(data.len[i]);                       
    }
    free(data.len);
    free(data.col);
}
/*Make directory*/
int makeDirectory(char* nameOfDirectory){
    struct stat st = {0};
    int exist=0;
    if (stat(nameOfDirectory, &st) == -1) {
        mkdir(nameOfDirectory, 0700);
        exist=1;
    }
    return exist;
}
