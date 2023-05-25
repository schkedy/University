
#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#define UI unsigned int
int main(){
    FILE *f,*g;
    int number;
    char fName[100] = "University/filer.txt";
    char gName[100] = "University/gile.txt";
    f = fopen(fName,"w");
    checkFile(f);
    writeRandFileMin(f,10,20);
    fclose(f);
    fRead(fName);


    f = fopen(fName,"r");
    checkFile(f);
    g = fopen(gName,"w");
    checkFile(g);

    while ( fscanf(f,"%d",&number)!=EOF){
        if(number%2 == 0)
            fprintf(g,"%d ",number);

    }

    fcloseall();
    fRead(gName);
    return  0;
}