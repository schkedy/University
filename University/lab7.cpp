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
    float data; // данные
    LUsel *next; //ссылка на следующий узел
};
struct LStack {
    LUsel *head;

    LStack() { head = 0; }; // Конструктор
    ~LStack() { clear(); }; // Деструктор
    void push(float k);

    float pop();

    float top();

    bool empty();

    void clear();

};

LUsel *push(LUsel *head, float dataNew) {
    LUsel *p = new LUsel; //Создаем новый узел
    p->data = dataNew; // Пишем в него данные
    p->next = head; // В next  пишем ссылку предыдущей верхушки
    head = p; // Меняем верхушку
    return head; // Возвращаем верхушку
}

LUsel *pop(LUsel *head, float *dataGet) {
    *dataGet = head->data; // Сохраняем данные из бывшей верхушки
    LUsel *p = head;  // делаем указатель чтобы изменить верхушку
    head = head->next; // меняем верхушку
    delete p;        // удаляем бывшую верхушку
    return head;
}

float top(LUsel *head) {
    return head->data;
}

bool empty(LUsel *head) {
    if (head == NULL) return true;
    return false;
}

void clear(LUsel *head) {
    float k;
    while (head) head = pop(head, NULL); // Не нужно сохранять данные
}

void output(LUsel *head) {
    LUsel *p;
    for (p = head; p != 0; p = p->next) // Начинаем с вершины и идем пока не дойдем до конца
        cout << p->data << ' ';
}

void LStack::clear() {
    float k;
    while (head) k = pop();
}

void LStack::push(float k) {
    LUsel *p = new LUsel;
    p->data = k;
    p->next = head;
    head = p;
}

float LStack::pop() {
    float k = head->data;
    LUsel *p = head;
    head = head->next;
    delete p;
    return k;
}

float LStack::top() {
    return head->data;
}

bool LStack::empty() {
    if (head == 0) return true;
    return false;
}
int main() {
    char s[80], p[80], ch;
    LStack Znak, Prior,Calc;
    int i, j, Tab[256];
    for (i = 0; i < 256; i++) Tab[i] = 0;
    puts("введите формулу:");

    cin.getline(s, 79);

    for (i = j = 0; s[i]; i++)
        if (digit(s[i])) { // если цифра, то ее в ПОЛИЗ
            p[j++] = s[i];
            while (digit(s[++i]))
                p[j++] = s[i];
            p[j++] = ' ';
            i--;
        } else if (letter(s[i])) { // Если буква ее в полиз
            Tab[s[i]]++;
            p[j++] = s[i];
            p[j++] = ' ';
        } else if (Znak.empty() || s[i] == '(') {
            Znak.push(s[i]); // операцию в стек операций
            Prior.push(prioritet(s[i]));
        } else if (s[i] == ')') {// если текущий символ ')'
            while (!Znak.empty() && Znak.top() != '(') {
                p[j++] = Znak.pop();
                p[j++] = ' ';
                Prior.pop();
            }
            if(Znak.empty()) {
                perror("Не нашли (");
                exit(1);
            }
            Znak.pop();
            Prior.pop();
        } else if (Prior.top() < prioritet(s[i])) { // приоритет операции в стеке < приоритета текущей
            Znak.push(s[i]); // помещаем операцию в стек операций
            Prior.push(prioritet(s[i]));
        } else {
            while (!Znak.empty() && Prior.top() >= prioritet(s[i])) {
                p[j++] = Znak.pop();
                p[j++] = ' ';
                Prior.pop();
            }
            Znak.push(s[i]); //после этого кладем в стек текущую операцию,
            Prior.push(prioritet(s[i]));
        }
    while (!Znak.empty()) {
        if (Znak.top() == '(') {
            perror("Отсутствует ')'");
            exit(1);
        }
        p[j++] = Znak.pop();
        p[j++] = ' ';
        Prior.pop();
    }
    p[j] = '\0';
    cout << " ПОЛИЗ: " << p << endl;

    for (i = 0; i < 256; i++) {
        if (Tab[i]) {
            cout << "Введите значение для " << char(i) << ": ";
            cin >> Tab[i];
        }
    }
    float x, y, z, k;

    for (i = 0; p[i];) {
        while (p[i] && (digit(p[i]) || letter(p[i]) || p[i] == ' ')) {
            if (digit(p[i])) {
                k = p[i++] - '0'; // даем реальное значаение цифре
                while (digit(p[i])) {
                    k = k * 10 + (p[i++] - '0'); //записываем разряды
                }
                Calc.push(k);
            } else if (letter(p[i])) Calc.push(Tab[p[i++]]); // если буква пушим в стек значение
            else if (p[i] == ' ') i++;
        }
        if (p[i]) {
            if (Calc.empty()) {
                cout << "Ошибка: потерян операнд" << endl;
                exit(-1);
            }
            y = Calc.pop();
            if (Calc.empty()) {
                cout << "Ошибка: потерян операнд" << endl;
                exit(-1);
            }
            x = Calc.pop();
            switch (p[i++]) {
                case '+':
                    z = x + y;
                    break;
                case '-':
                    z = x - y;
                    break;
                case '*':
                    z = x * y;
                    break;
                case '/':
                    z = x / y;
                    break;
            }
            Calc.push(z);
        }
    }
    z = Calc.pop();
    if (!Calc.empty()) {
        cout << endl << "Ошибка: потеряна операция" << endl;
        exit(-1);
    }
    cout << endl << "Значение ПОЛИЗ: " << z << endl;
    return 0;

}//Сформировать односвязный список с фиктивной головой вставить элемент после определенного ключа