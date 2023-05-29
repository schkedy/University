#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "Algorithms.h"

int main()
{
	setlocale(LC_ALL, "rus");
	char s[80], p[80], ch;
	Stack Sign, Prior;
	int i, j, t, Tab[256];
	for (i = 0; i < 256; i++) Tab[i] = 0;
	puts("Введите формулу:");
	gets_s(s);
	for (i = j = 0; s[i]; i++)
	{
		if (S_small(s[i]) || S_large(s[i]))
		{
			Tab[s[i]]++;
			p[j++] = s[i];
			p[j++] = ' ';
		}
		else if (S_number(s[i]))
		{
			p[j++] = s[i];
			i++;
			while (S_number(s[i]))
			{
				p[j++] = s[i++];
			}
			p[j++] = ' ';
			i--;
		}
		else if (Sign.Empty() || s[i] == '(')
		{
			Sign.Push(s[i]);
			Prior.Push(Prioritet(s[i]));
		}
		else if (s[i] == ')')
		{
			while (!Sign.Empty() && Sign.Top() != '(')
			{
				p[j++] = Sign.Pop();
				p[j++] = ' ';
				t = Prior.Pop();
			}
			if (Sign.Empty())
			{
				cout << endl << "Ошибка: потеряна '('";
				exit(-1);
			}
			ch = Sign.Pop();
			t = Prior.Pop();
		}
		else if (Prior.Top() < Prioritet(s[i]))
		{
			Sign.Push(s[i]);
			Prior.Push(Prioritet(s[i]));
		}
		else
		{
			while (!Sign.Empty() && Prior.Top() >= Prioritet(s[i]))
			{
				p[j++] = Sign.Pop();
				p[j++] = ' ';
				t = Prior.Pop();
			}
			Sign.Push(s[i]);
			Prior.Push(Prioritet(s[i]));
		}
	}
	while (!Sign.Empty())
	{
		if (Sign.Top() == '(')
		{
			cout << endl << "Ошибка: потеряна ')'";
			exit(-1);
		}
		p[j++] = Sign.Pop();
		p[j++] = ' ';
		t = Prior.Pop();
	}
	p[j] = '\0';
	cout << endl << "ПОЛИЗ: " << p << endl << endl;

	for (i = 0; i < 256; i++)
	{
		if (Tab[i])
		{
			cout << "Введите значение " << char(i) << ": ";
			cin >> Tab[i];
		}
	}
	float x, y, z, k;
	FStack Calc;
	for (i = 0; p[i];)
	{
		while (p[i] && (S_number(p[i]) || S_small(p[i]) || S_large(p[i]) || p[i] == ' '))
		{
			if (S_number(p[i]))
			{
				k = p[i++] - '0';
				while (S_number(p[i]))
				{
					k = k * 10 + (p[i++] - '0');
				}
				Calc.Push(k);
			}
			else if (S_small(p[i]) || S_large(p[i])) Calc.Push(Tab[p[i++]]);
			else if (p[i] == ' ') i++;
		}
		if (p[i])
		{
			if (Calc.Empty())
			{
				cout << "Ошибка: потерян операнд" << endl;
				exit(-1);
			}
			y = Calc.Pop();
			if (Calc.Empty())
			{
				cout << "Ошибка: потерян операнд" << endl;
				exit(-1);
			}
			x = Calc.Pop();
			switch (p[i++])
			{
			case '+': z = x + y; break;
			case '-': z = x - y; break;
			case '*': z = x * y; break;
			case '/': z = x / y; break;
			}
			Calc.Push(z);
		}
	}
	z = Calc.Pop();
	if (!Calc.Empty())
	{
		cout << endl << "Ошибка: потеряна операция" << endl;
		exit(-1);
	}
	cout << endl << "Значение ПОЛИЗ: " << z << endl;
	return 0;
}
