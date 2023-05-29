#include "mylib.h"
#include <cstdio>
#include <iostream>

#define UI unsigned int

#include <time.h>
#include <unistd.h>
#include <string.h>

//Сдвигает маску на k компоненту если и возвращает побитовый и
bool definebit(UI value, int k) { //Сдвигает маску на k компоненту и возвращает побитовый и
    UI mask = 1;
    mask = mask << k; // mask <<=k
    if ((value & mask) == 0)
        return 0;
    else
        return 1;
}
//УСТАНАВЛИВАЕТ K КОМПОНЕТУ БУЛЕВА ВЕКТОРА (СТАВИТ 1)
UI setUp1(UI x, int k) {
    UI mask = 1;
    mask <<= k;
    x |= mask;
    return x;
}
//СБРАСЫВАЕТ K КОМПОНЕНТУ БУЛЕВА ВЕКТОРА (СТАВИТ 0)
UI setUp0(UI x, int k) {
    UI mask = 1;
    mask <<= k; // 000001000
    mask = ~mask; // 111110111
    x &= mask; // 111001111 & 111110111 = 111000111
    return x;
}
//СТАВИТ НА ВЫБОР
UI setUp(UI x, int k, bool one_null) {
    if (one_null == 1)
        x = setUp1(x, k);
    else
        x = setUp0(x, k);
    return x;
}
//ИНВЕРТИРУЕТ К КОМПОНЕНТУ БУЛЕВА ВЕКТОРА
UI invert(UI x, int k) {
    UI mask = 1;
    mask <<= k;
    x ^= mask;
    return x;
}

//НАХОДИТ ВЕС (КОЛИЧЕСТВО ЕДИНИЦ БУЛЕВА ВЕКТОРА)
int weight(UI x, int n) {
    int w, i;
    UI mask = 1;
    for (w = 0, i = 0; i < n; i++, mask <<= 1)// СДВИГАЕТ ЕДИНИЦУ НА КАЖДУЮ К ПОЗИЦИЮ И ПОБИТОВО И
        if (x & mask) {
            w++;
        }
    return w;
}
//ВВОД БУЛЕВОГО ВЕКТОРА ПО ЧАРУ
UI input2BV(char s[], int n) {
    UI x = 0;
    int i;
    for (i = 0; i < n; i++) {
        x <<= 1;
        if (s[i] == '1')
            x++;  // CHAR[10100000]: 00000000 ->00000001 -> 00000010-> 000000101 ->...-> 10100000
    }
    return x;
}

//ВЫВОД БУЛЕВОГО ВЕКТОРА
void outputBV(UI x, int n) {
    UI mask = 1;
    int i;
    mask <<= n - 1;
    for (i = 0; i < n; i++, mask >>= 1)
        if (x & mask) putchar('1');
        else putchar('0');
}

//ВВОД БУЛЕВОЙ МАТРИЦЫ
void inputBM(UI *bm, int m, int n) {
    int i;
    char s[33];
    for (i = 0; i < m; i++) {
        fgets(s, 33, stdin); //считывает строку n-1 символа из входного потока stdin и пишет ее char[]
        *(bm + i) = input2BV(s, n);
    }
}

//ВЫВОД БУЛЕВОЙ МАТРИЦЫ
void outputBM(UI *bm, int m, int n) {
    int i;
    for (i = 0; i < m; i++) {
        outputBV(*(bm + i), n);
        puts(" ");
    }
}

//ВЕС БУЛЕВОГО СТОЛБЦА
int weightColumn(UI *bm, int m, int n, int k) {
    int w, i;
    UI mask = 1 << k;               //ставит единицу в k позицию
    for (w = 0, i = 0; i < m; i++)  //проходит по строкам
        if (*(bm + i) & mask) w++;
    return w;
}

int countDifferentPos(UI a, UI b, int n) {
    UI c = a ^ b;
    return weight(c, n);
}

int countDifferentPosAndPos(UI a, UI b, int n) {
    UI c = a ^ b;
    return weight(c, n);
}

void changeColumn(UI *bm, int m, int columnA, int columnB) {
    bool changeA, changeB;
    if (columnB != columnA)
        for (int i = 0; i < m; i++) {
            changeB = definebit(*(bm + i), columnA); //присваевам в changeB бит в столбце А
            changeA = definebit(*(bm + i), columnB);//присваевам в changeB бит в столбце Б
            if (changeB != changeA) {
                *(bm + i) = setUp(*(bm + i), columnA, changeA);
                *(bm + i) = setUp(*(bm + i), columnB, changeB);
            }
        }
}

int indexMaxWeightColumnBM(UI *bm, int m, int n) {
    int maxWeight = 0, index, weight;
    for (int i = 0; i <= n; i++) {
        weight = weightColumn(bm, m, n, i);
        if (weight > maxWeight) {
            index = i;
            maxWeight = weight;
        }
    }
    return index;
}

//ВОЗВРАЩАЕТ РАНДОМНОЕ ЦЕЛОЕ ЧИСЛО
int getRandomNumber(int minBorder, int maxBorder) {
    srand(time(0));
    int number = minBorder + rand() % (maxBorder - minBorder - 1);
    return number;
}

int getRandomNumber(int minBorder) {

    int number = minBorder + rand() % (INT32_MAX - minBorder - 1);
    return number;
}

void checkFile(FILE *f) {
    if (f == NULL) {
        perror("error opening file");
        exit(132);
    }
}

void writeRandFileMin(FILE *f, int min, int size) {
    int number;
    for (int i = min; i < min + size; i++) {
        number = getRandomNumber(i, 100);
        fprintf(f, "%d ", number);
    }
}

void writeRandFileMinMax(FILE *f, int min, int max, int size) {
    int number;
    for (int i = 0; i < size; i++) {
        number = getRandomNumber(min, 100);
        fprintf(f, "%d ", number);
    }
}

void fRead(char name[]) {
    int a;
    FILE *f;
    f = fopen(name, "r");
    while (fscanf(f, "%d", &a) != EOF)
        printf("%d ", a);
    fclose(f);
    printf("\n");
}

void fRead(char name[], char text[]) {
    int a;
    FILE *f;
    f = fopen(name, "r");
    while (fscanf(f, "%d", &a) != EOF)
        printf("%d ", a);
    fclose(f);
    puts(text);
    printf("\n");
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void printTime() {
    clock_t start = clock();
    sleep(0);
    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    printf("the time :%f seconds \n", seconds);
}

bool sortBubble(int *array, int size) {
    clock_t start = clock();
    int middle, lastChange;
    lastChange = size - 1;
    for (int k = size - 1; (k > 0); k--) {
        //lastChange = 0;
        for (int i = 0; i < k; i++)
            if (array[i] > array[i + 1]) {
                middle = array[i + 1];        //
                array[i + 1] = array[i];      // Меняет пару элементов между собой
                array[i] = middle;          //
                //lastChange = i+1;
            }
        //k = lastChange;
        //printArray(array, size);
    }
    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    puts("Bubble ->");
    printf("the time :%f seconds \n", seconds);
    if (size >= 30)
        return 0;
    else return 1;


}

bool sortShaker(int *array, int size) {
    clock_t start = clock();
    int middle;
    int lastChange;
    int firstchange = 0;
    for (int k = size - 1, b = 0; (k > 0) & (b < size - 1); k--, b++) {
        //lastChange = 0;
        firstchange = 0;
        for (int i = b; i < k; i++)     //i = b
            if (array[i] > array[i + 1]) {
                middle = array[i + 1];        //
                array[i + 1] = array[i];      // Меняет пару элементов между собой
                array[i] = middle;          //
                //lastChange = i+1;
            }
        //k = lastChange;
        //printArray(array, size);
        for (int i = --k; i > b; i--) //i > 0
            if (array[i] < array[i - 1]) {
                middle = array[i - 1];
                array[i - 1] = array[i];
                array[i] = middle;
                //firstchange = i;
            }
        //b = firstchange;
        //printArray(array, size);
    }
    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    puts("Shaker ->");
    printf("the time :%f seconds \n", seconds);
    if (size >= 30)
        return 0;
    else return 1;

}

void randomArray(int *array, int size, int minBorder, int maxBorder, int *array1) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        *(array + i) = minBorder + rand() % (maxBorder - minBorder - 1);
        *(array1 + i) = *(array + i);
    }
}

void randomArray(int *array, int size, int minBorder, int maxBorder, int *array1, int *array2) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        *(array + i) = minBorder + rand() % (maxBorder - minBorder - 1);
        *(array1 + i) = *(array + i);
        *(array2 + i) = *(array + i);
    }
}

void randomSortArray(int *array, int size, int minBorder, int maxBorder) {
    int step = (maxBorder - minBorder) / size;
    maxBorder = minBorder + step;
    for (int i = 0; i < size; i++) {
        maxBorder = minBorder + step;
        array[i] = getRandomNumber(minBorder, maxBorder);
        minBorder = maxBorder;
    }
}

int searchBinary(int *array, int size, int a) {
    int L = 0, R = size - 1;
    while (L < R) {
        int move = (L + R) / 2;
        if (a == array[move])
            return move;
        if ( a > array[move]) {
            L = move + 1;
        }
        if (a < array[move])
            R = move - 1;
    }
    puts("Элемент не найден");
    return -1;
}

int getStrSize(char *s) {
    int count = 0, i = 0;
    while (true) {
        if (s[i++] == 0)
            return count;
        else count++;
    }
}

void printPart(char *s, int start, int end) {
    int i = start;
    while (i < end) {
        printf("%c", s[i++]);
    }
    printf("\n");
}

int searchBM(char *s, char *p) {
    int TAB[256], sizeS, sizeP, count = 0, cc = 0;
    sizeS = strlen(s) - 1;
    sizeP = strlen(p) - 1;
    for (int i = 0; i < 256; i++) //
        TAB[i] = sizeP;
    for (int i = 0; i < sizeP - 1; i++)
        TAB[p[i]] = sizeP - 1 - i;   // Присваивает ASCII таблице степень удаленности от конца подстроки

    for (int i = sizeP - 1; i < sizeS; i += count) {
        cc = 0;
        for (int j = sizeP - 1, l = i; j >= 0; j--, l--) {
            printf("%c %c\n", s[l], p[j]);
            getchar();
            if (s[l] != p[j]) {
                count = TAB[s[i]];
                j = 0;
            } else if (j == 0) return l;
        }
        //printPart(s,i-sizeP+1,i+1);
    }
    return -1;
}

int searchBinaryIntegrate(int *array, int size, int a) {
    int L = 0, R = size, move;
    while (L <= R) {
        move = (L + R) / 2;
        if (a == array[move])
            return move;
        if (a > array[move]) {
            L = move + 1;
        }
        if (a < array[move])
            R = move - 1;
    }
    return R + 1;
}

bool sortInsertBinary(int *array, int size) {
    clock_t start = clock();
    int middle, move;
    for (int i = 1; i < size; i++)
        if (array[i] < array[i - 1]) {
            move = searchBinaryIntegrate(array, i, array[i]);//Возвращает индекс вставки числа
            int backStep = i;
            while (move != backStep) {
                middle = array[backStep - 1];
                array[backStep - 1] = array[backStep];
                array[backStep--] = middle;
            }
        }
    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    puts("InsertBinary ->");
    printf("the time :%f seconds \n", seconds);
    if (size >= 30)
        return 0;
    else return 1;
}

bool digit(char ch) {
    if ('0' <= ch && ch <= '9') return true;
    return false;
}
bool letter(char ch) {
    if ('a' <= ch && ch <= 'z') return true;
    return false;
}

int prioritet(char s) {
    switch (s) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
    }
    return -1;
}
