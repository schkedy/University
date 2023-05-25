#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define UI unsigned int
struct Complex {float re, im;};

int main(){
char *s,*p;

s = "sobakaobakas"; // a = 2 k =1 * = 2
p = "ka";
s = new char [1];
p = new char [1];
    puts("Введите текст");
    fgets(s,100,stdin);
    puts("Введите подстроку для поиска");
    fgets(p,100,stdin);
    printf("%d",searchBM(s,p));
}