#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;
/////////////////////////////////////////////////////////////////////
// Алгоритм "решета Сундарама". Вибирає усі прості числа
// до заданого (випадково згенерованого).
int sundaram(int n)
{
	int* a = new int[n], i, j, k;
	memset(a, 0, sizeof(int) * n);
	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
			a[k] = 1;
	}
	// Вибирає зі списку простих чисел найближчим до заданого.
	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}
/////////////////////////////////////////////////////////////////////
// Алгоритм Евкліда. Алгоритм для знаходження найбільшого
// загального дільника двох цілих чисел. Використовується для перевірки
// чисел на взаємопростоту.
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
/////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Please wait... Key generation procces." << endl << endl;
	// Генерація двох чисел та вибір двох простих чисел.
	srand((unsigned)time(NULL));
	int p = rand() % 100;
	int q = rand() % 100;
	int p_simple = sundaram(p);
	int q_simple = sundaram(q);
	// Знаходимо число n.
	unsigned int n = p_simple * q_simple;
	// Генерація числа d та перевірка його на взаємопростоту
	// з числом ((p_simple-1)*(q_simple-1)).
	int d, d_simple = 0;
	while (d_simple != 1)
	{
		d = rand() % 100;
		d_simple = gcd(d, ((p_simple - 1) * (q_simple - 1)));
	}
	// Визначення числа e, для якого є дійсним
	// відношення (e*d)%((p_simple-1)*(q_simple-1))=1.
	unsigned int e = 0, e_simple = 0;
	while (e_simple != 1)
	{
		e += 1;
		e_simple = (e * d) % ((p_simple - 1) * (q_simple - 1));
	}
	// Згенеровані ключі.
	cout << '{' << setw(12) << e << ',' << setw(12) << n << '}' << " - Open key"
		<< endl;
	cout << '{' << setw(12) << d << ',' << setw(12) << n << '}' << " - Secret key"
		<< endl << endl;
	// Введення даних, що шифруються.
	const int MAX = 20;
	char* Text = new char[MAX];
	cout << "Please enter the Text. Use <Enter> button when done." << endl;
	cin.get(Text, MAX);
	// Масив для зберігання шифротексту.
	unsigned int* CryptoText = new unsigned int[MAX];
	unsigned int* Tdecrypt = new unsigned int[MAX];
	// Отримання з введених даних десяткового коду ASCII та
	// подальше його перетворення за формулою ci = (mj^e)%n.
	int b = 301;
	int c;
	cout << endl << setw(5) << "Text" << setw(6) << "ASCII"
		<< setw(20) << "CryptoText/Block#" << setw(14)
		<< "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl
		<< "------------------------------------------------------------" << endl;
	for (int j = 0; j < MAX; j++)
	{
		c = 1;
		unsigned int i = 0;
		int ASCIIcode = (static_cast<int>(Text[j])) + b;
		while (i < e)
		{
			c = c * ASCIIcode;
			c = c % n;
			i++;
		}
		CryptoText[j] = c;
		b += 1;
	}
	// Розшифрування отриманого коду за формулою mi = (ci^d)%n
	// та переведення його в десятковий код ASCII.
	b = 301;
	int m;
	for (int j = 0; j < MAX; j++)
	{
		m = 1;
		unsigned int i = 0;
		while (i < d)
		{
			m = m * CryptoText[j];
			m = m % n;
			i++;
		}
		m = m - b;
		Tdecrypt[j] = m;
		b += 1;
	}
	for (int j = 0; j < MAX; j++)
	{
		cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) <<
			setw(20) << CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) <<
			static_cast<char>(Tdecrypt[j]) << endl;
	}
	delete[] Text;
	delete[] CryptoText;
	delete[] Tdecrypt;
	return 0;
}
