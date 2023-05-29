#include <iostream>
#include "/home/len/CLionProjects/mylib/mylib.cpp"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;
struct LUsel {
    int data; // данные
    LUsel *next; //ссылка на следующий узел
};

struct List {
    LUsel *head;

    List() {
        head = new LUsel; // Конструктор
        head->next = 0;
    };

    ~List() {
        clear();
        //delete head;
    }; // Деструктор
    void addAfter(int k, LUsel *element);

    void addToTail(int k);

    void addToHead(int k);

    void delAfter(LUsel *element);

    void delHead();

    void delTail();

    bool empty();

    void clear();

    void form(int n);

    LUsel *findKey(int k);

    LUsel *findPos(int pos);

    void printList();

    void addAfterKey(int key, int data);

    void dellAfterKey(int key);
};

void List::addAfter(int k, LUsel *element) {
    LUsel *q = new LUsel;
    q->data = k;
    q->next = element->next;
    element->next = q;
}

void List::addToTail(int k) {
    LUsel *p = head;
    while (p->next) p = p->next; //пока next не null
    addAfter(k, p);
}

void List::addToHead(int k) {
    addAfter(k, head);
}

void List::delAfter(LUsel *element) {
    if (element->next == NULL) puts("узел последний");
    else {
        LUsel *q = element->next;
        element->next = q->next;
        delete q;
    }
}

void List::delHead() {
    delAfter(head);
}

void List::delTail() {
    if (empty()) puts("список пустой");
    else {
        LUsel *p = head;
        while (p->next->next != 0) p = p->next;
        delAfter(p);
    }
}

void List::form(int n) {//формирование списка из n элементов элементы добавляются в хвост
    int x, i;
    cout << "Вводи " << n << " элементов списка";
    for (i = 1; i <= n; i++) {
        cin >> x;
        addToTail(x);
    }
}

LUsel* List::findKey(int k) { //поиск в списке по ключу.
    if (head->next->data == k) return head->next;
    else {
        LUsel *p = head->next;
        while (p->next && p->next->data != k)
            p = p->next;
        if (p->next == 0) return NULL;
        else return p->next;
    }
}

LUsel *List::findPos(int pos) {//поиск в списке позиции pos, возвращает адрес элемента если элементов <pos – выводит NULL и сообщение
    LUsel *p = head->next;
    int i = 1;
    while ((p->next != NULL) && (i < pos)) {
        i++;
        p = p->next;
    }
    if (i != pos) {
        cout << "список меньше " << pos << " элементов";
        return NULL;
    } else  return p;
}
bool List::empty() {
    if(!head->next) return true;
    return false;
}
void List::printList(){
    if(empty()) puts("Список пуст");
    else {
        LUsel *p = head->next;
        int i = 1;
        while(p) {
            cout << i++ << "-->" << p->data << endl;
            p = p->next;
        }
    }
}
void List::clear(){
    while(head->next) delAfter(head);
    delete head;
}
void List::addAfterKey(int key,int data) {
    LUsel *p = findKey(key);
    if (!p) puts("Такого ключа нет");
    else {
        addAfter(data,p);
    }
}
void List::dellAfterKey(int key) {
    LUsel *p = findKey(key);
    if (!p) puts("Такого ключа нет");
    else {
        delAfter(p);
    }
}
int main(){
    List list;
    list.form(4);
    list.printList();
    //list.dellAfterKey(3);
    //list.addAfterKey(3,100);
    cout << endl;
    list.printList();
}