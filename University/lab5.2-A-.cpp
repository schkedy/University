#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#define UI unsigned int
/*
 * сортировка пузырьком и шейкером
создать динамический массив из n случайных чисел. Сортировать его указанными методами.
 Сравнить время выполнения сортировок.
 Для проверки правильности сортировок при первом запуске программы задать n≤30,
 при этом программа должна вывести на экран исходный, отсортированные массивы и время сортировок.
 Затем задать n≥5000 и программа должна вывести на экран только время сортировок (массивы не выводить).
 */


int main() {
    int size = 5;
    int *array,*array1,*array2;
    puts("Введите размер");
    scanf("%d",&size);
    array = new int[size];array1 = new int[size];array2 = new int[size];
    randomArray(array,size,0,100,array1,array2);
    if (size <30)
        printArray(array,size);
//
    if (sortBubble(array,size))
        printArray(array,size);
//
    if(sortShaker(array1,size))
        printArray(array1,size);

    if(sortInsertBinary(array2,size))
        printArray(array2,size);

    delete array,array1,array2;
    return 0;
}