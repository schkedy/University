#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#define UI unsigned int


void diverse(FILE *f,FILE **g,char fName[], char **gName){
    int x1,x2,n=0;
    f = fopen(fName,"r");checkFile(f);
    fscanf(f,"%d",&x1);
    *g = fopen(*(gName),"w");checkFile(*g);
    *(g+1) = fopen(*(gName+1),"w");checkFile(*(g+1));
    while(!feof(f)){
        fprintf(*(g + n), "%d ", x1);
        fscanf(f, "%d", &x2);
        while (!feof(f) & (x1 <= x2)){
            x1 = x2;
            fprintf(*(g + n), "%d ", x1);
            fscanf(f, "%d", &x2);
        }
        x1 = x2;
        n = !n;
    }
    fcloseall();
}
void merger(FILE *f,FILE **g,char fName[],char **gName){
    int *x,*y,n;
    x = new int[2];y = new int[2];
    f = fopen(fName,"w");
    *g = fopen(*gName,"r");
    *(g+1) = fopen(*(gName+1),"r");
    checkFile(*g);
    checkFile(*(g+1));
    fscanf(*g,"%d",&x[0]);  //читаеет первый элемент из первойго файла
    fscanf(*(g+1),"%d",&x[1]);//читаеет первый элемент из второго файла
    while(!feof(*g)&!feof(*(g+1))   ){
        n = x[0]<x[1]?0:1;                          // проверят младшенство элментов
        fprintf(f,"%d ",x[n]);       //  младший элемент вставляет в первый файл
        fscanf(*(g+n),"%d",&y[n]);    //читает второй элемент из "младшего отрезка"
        if (!feof(*(g+n))&(x[n]<=y[n]))     // если младший отрезок не закончился и файл в тоже
            x[n] = y[n];                           //  сдвигаем читаемый элемент
        else{
            fprintf(f,"%d ",x[!n]);       // коли младший отрезок пишем элемент из старшего отрезка (n-1)
            fscanf(*(g+!n),"%d",&y[!n]);
            while(!feof(*(g+!n))&(x[!n]<=y[!n])){
                x[!n] = y[!n];
                fprintf(f,"%d ",x[!n]);
                fscanf(*(g+!n),"%d",&y[!n]);
            }
            x[0] = y[0];x[1]=y[1];
        }

    }
    while(!feof(*g)){                   // Дозаписываем элементы
        fprintf(f,"%d ",x[0]);
        fscanf(*g,"%d",&y[0]);
        x[0] = y[0];
    }
    while(!feof(*(g+1))){           //Тоже дозаписываем
        fprintf(f,"%d ",x[1]);
        fscanf(*(g+1),"%d",&y[1]);
        x[1] = y[1];
    }
    delete x;delete y;
fcloseall();
}
void sort(FILE *f, FILE **g,char fName[],char **gName){
    f = fopen(fName,"a");
    checkFile(f);
    fprintf(f,"\n");
    fclose(f);
    diverse(f,g,fName,gName);
    int a;
    fRead(*(gName), " G1");fRead(*(gName+1)," G2");
    while(!feof(*(g+1))){
        fclose(*(g+1));
        merger(f,g,fName,gName);
        fRead(fName, " F");
        diverse(f,g,fName,gName);
        fRead(*(gName)," G1");fRead(*(gName+1)," G2");
        *(g+1) = fopen(*(gName+1),"r");
        fscanf(*(g+1),"%d",&a);
    }
}

int main(){
    FILE *f,**g;
    char fName[] = "University/file.txt";
    char **gName;
    gName = new char *[2];
    *gName = "University/gile1.txt";
    *(gName+1) ="University/gile2.txt";
    g = new FILE *[2];
    sort(f,g,fName,gName);
    delete g;
    delete gName;
    return 0;
}
