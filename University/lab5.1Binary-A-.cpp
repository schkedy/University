#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#define UI unsigned int
int main(){
    int size,*array;

    puts("Введите размер");
    scanf("%d",&size);

    array = new int[size];
    randomSortArray(array,size,0,100);
    printArray(array,size);
    int a = 0;
    puts("Введите число для поиска");
    scanf("%d",&a);
    int c = searchBinary(array,size,a);
    printf("%d ",c);
}
