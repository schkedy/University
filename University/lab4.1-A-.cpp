#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#define UI unsigned int


void diverse(FILE *f,FILE **g){
    int x1,x2,n=0;
    f = fopen("University/file.txt","r");
    fscanf(f,"%d",&x1);
    *g = fopen("University/gile1.txt","w");
    *(g+1) = fopen("University/gile2.txt","w");
    while(!feof(f)){
        fprintf(*(g + n), "%d ", x1);
        fscanf(f, "%d", &x2);
        while (!feof(f) & (x1 <= x2)) {
            x1 = x2;
            fprintf(*(g + n), "%d ", x1);
            fscanf(f, "%d", &x2);
        }        x1 = x2;
        n = !n;
    }
    fcloseall();
}
void merger(FILE *f,FILE **g){
    int *x,*y,n;
    x = new int[2];y = new int[2];
    f = fopen("University/file.txt","w");
    *g = fopen("University/gile1.txt","r");
    *(g+1) = fopen("University/gile2.txt","r");
    fscanf(*g,"%d",&x[0]);
    fscanf(*(g+1),"%d",&x[1]);
    while(!feof(*g)&!feof(*(g+1))){
        n = x[0]<x[1]?0:1;
        fprintf(f,"%d ",x[n]);
        fscanf(*(g+n),"%d",&y[n]);
        if (!feof(*(g+n))&(x[n]<=y[n]))
            x[n] = y[n];
        else{
            fprintf(f,"%d ",x[!n]);
            fscanf(*(g+!n),"%d",&y[!n]);
            while(!feof(*(g+!n))&(x[!n]<=y[!n])){
                x[!n] = y[!n];
                fprintf(f,"%d ",x[!n]);
                fscanf(*(g+!n),"%d",&y[!n]);
            }
            x[0] = y[0];x[1]=y[1];
        }
    }
    while(!feof(*g)){
        fprintf(f,"%d ",x[0]);
        fscanf(*g,"%d",&y[0]);
        x[0] = y[0];
    }
    while(!feof(*(g+1))){
        fprintf(f,"%d ",x[1]);
        fscanf(*(g+1),"%d",&y[1]);
        x[1] = y[1];
    }
    fcloseall();
    delete[] x;
    delete[] y;
}
void sort(FILE *f, FILE **g){
    diverse(f,g);
    do{
        merger(f,g);
        diverse(f,g);
    }while(!feof(*(g+1)));
}
int main(){
    FILE *f,**g;
    g = new FILE *[2];

    f = fopen("University/file.txt","w");
    fprintf(f,"1 0 32 18 18 193 384 23 100 232 0 34 45 -23 123 391 99 44");
    fclose(f);

    sort(f,g);
    delete[] g;
    return 0;
}
