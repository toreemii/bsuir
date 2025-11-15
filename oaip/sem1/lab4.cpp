#include <iostream>
//#include <algorithm> 
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	int n;
	cout << "Введите n: "; 
	cin >> n;
	int* m1 = new int[n];
	int* m2 = new int[n];

	cout << "Введите массив 1: " << endl;
	for (int i = 0; i < n; i++) 
	{
		cin >> m1[i];
	}
	cout << "Введите массив 2: " << endl;
	for (int i = 0; i < n; i++) 
	{
		cin >> m2[i];
	}

	//сортировка 
	//sort(m1, m1 + n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (m1[j] > m1[j + 1])
			{
				swap(m1[j], m1[j + 1]);
			}
		}
	}
	int k1 = 0;
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		for (int j = 0; j < n; j++)
		{
			if (m1[i] == m2[j])
			{
				k++;
				k1++;
			}
		}
		if (k == 0)
		{
			cout << "Наименьшее среди чисел первого массива, которое не входит во второй массив: " << m1[i];
			exit(0);
		}
	}

	if (k1 == n)
	{
		cout << "Наименьшего среди чисел первого массива, которое не входит во второй массив не существует!";
	}
	delete[] m1;
	delete[] m2;
}


