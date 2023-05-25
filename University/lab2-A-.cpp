/*
Поменять местами столбец с номером k и столбец с максимальным весом (k
вводится с клавиатуры).
*/
#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#define UI unsigned int


int main(){
    UI *bm;
    int m,n,numberWeightest,k;
    puts("Введите количество вектор строк  и столбцов");
    scanf("%d%d", &m, &n);
    getchar();

    bm = new UI[m];
    puts("Введите булевы строки");
    inputBM(bm,m,n);


    puts("Введите номер столбца для изменения");
    scanf("%d",&k);
    k = n - k -1;
    getchar();

    numberWeightest = indexMaxWeightColumnBM(bm,m,n);

    changeColumn(bm,m,k,numberWeightest);
    outputBM(bm,m,n);

    delete bm;
    return 0;
}