#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;
struct Stud {
    char fam[20];
    char name[20];
    int group;
    unsigned short mark[3];
};
bool parseFileToStud(FILE *f,Stud kurs[],int n){
    int i = 0;
    while((fscanf(f,"%s %s %d %hu %hu %hu",&(kurs[i].fam),&(kurs[i].name),&(kurs[i].group),
                 &(kurs[i].mark[0]),&(kurs[i].mark[1]),&(kurs[i].mark[2]))!= EOF)&&(i<n)){
        if ((kurs[i].mark[2] >   5)||((kurs[i].mark[2] < 2))){
            puts("--->Проверьте данные<---");
            return 0;
        }
        printf("%s %s %d %hu %hu %hu\n",(kurs[i].fam),(kurs[i].name),(kurs[i].group),
               (kurs[i].mark[0]),(kurs[i].mark[1]),(kurs[i].mark[2]));
        i++;
    }
    printf("Всего %d студентов\n",i);
    if (n<i)
        printf("Вы не посчитали %d студентов\n",i-n);
    if (n>i)
        printf(" %d студентов нет в списке\n",n-i);
    return 1;
}
void outputStud(Stud stud){
    cout << stud.fam<<" "<<stud.name<<" "<<stud.group<<" ";
    for (int i =0;i<3;i++){
        cout << stud.mark[i]<<" ";
    }
    cout << endl;
}
int main() {
    FILE *f;
    char file[20] = "University/data.txt";
    f = fopen(file,"r");
    checkFile(f);
    int n,count = 0;
    cout << "Введите размер потока" << endl;
    cin >> n;
    Stud *kurs = new Stud[n];

    if (parseFileToStud(f,kurs,n)) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 3; j++)
                if (kurs[i].mark[j] == 2) {
                    count++;
                    if(count == 1)
                        puts("Отчислены:");
                    outputStud(kurs[i]);
                    j = 3;
                }
    }
    if (count == 0)
        puts("Все из перечисленных успешно сдали");

    delete kurs;
    fcloseall();
    }