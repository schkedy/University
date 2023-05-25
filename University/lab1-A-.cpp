/*

Подсчитать все несовпадающие разряды двух булевых векторов.

*/
#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#define UI unsigned int
int main() {
    UI a,b;
    int sizeA,sizeB;
    char *chA,*chB;
    chB = new char[33],chA = new char[33];
    puts("Введите размер первого и второго булева вектора");
    scanf("%d %d",&sizeA,&sizeB);
    puts("Введите первый вектор");
    scanf("%s", chA);
    puts("Введите второй вектор");
    scanf("%s", chB);

    a = input2BV(chA,sizeA);
    b = input2BV(chB,sizeB);

    int maxSize = sizeA > sizeB?sizeA:sizeB;
    int count  = countDifferentPos(a,b,maxSize);
    printf("%d",count);
    return  0;
}

