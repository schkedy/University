#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <iomanip>
using namespace std;
struct Usel{
    int data; // данные
    Usel *next; //ссылка на следующий узел
};
Usel* push(Usel *head, int dataNew){
    Usel *p = new Usel; //Создаем новый узел
    p->data=dataNew; // Пишем в него данные
    p->next = head; // В next  пишем ссылку предыдущей верхушки
    head = p; // Меняем верхушку
    return head; // Возвращаем верхушку
}
Usel* pop(Usel *head, int *dataGet){
    *dataGet = head->data; // Сохраняем данные из бывшей верхушки
    Usel *p = head;  // делаем указатель чтобы изменить верхушку
    head=head->next; // меняем верхушку
    delete p;        // удаляем бывшую верхушку
    return head;
}
int top (Usel *head){
    return head->data;
}
bool empty (Usel *head){
    if (head == NULL) return true;
    return false;
}
void clear (Usel *head){
    int k;
    while (head) head=pop(head, NULL); // Не нужно сохранять данные
}
void output (Usel *head){
    Usel *p;
    for(p=head; p!=0; p=p->next) // Начинаем с вершины и идем пока не дойдем до конца
        cout<<p->data<<' ';
}
int main(){
Usel *head = NULL;
int k,i;
    head = push(head,5);
    output(head);
}