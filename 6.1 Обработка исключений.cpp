#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void arithmetic_expression(); // Вычисление арифметического выражения
void logical_expression();    // Вычисление логического выражения
void range();                 // Вычсиление значения функции с помощью ряда
void array_work();            // Работа с массивом
void print_array(double** array, int n, int m); // Печать массива в консоль
void print_array_to_file(double** array, int n, int m, char filename[]); // Печать массива в файл
void read_array_from_file(double** array, int n, int m, char filename[]); // Чтение массива из файла
double* count_products_of_negatives(double** array, int n, int m); // Подсчет произведений 
// отрицательных элементов по каждому столбцу массива
void find_minimal_in_row(double** array, int n, int m); // Нахождение минимального элемента в строке
double** create_bivariate_array(int n, int m); // Создание двумерного динамического массива
double* create_array(int n); // Создание одномерного динамического массива
void delete_bivariate_array(double** bivariate_array, int n); // Удаление двумерного динамического массива
void delete_array(double* array); // Удаление одномерного динамического массива


int main()
{
	char choice;
	int work = 1;
	setlocale(LC_ALL, "Russian");
	while (work)
	{
		cout << "Что будем делать?\n"
			<< "1 - Вычисление арифметического выражения\n"
			<< "2 - Вычисление логического выражения\n"
			<< "3 - Вычисление значения функции с помощью ряда\n"
			<< "4 - Работа с массивом\n"
			<< "Любой другой символ - выход\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case '1':
			arithmetic_expression();
			break;
		case '2':
			logical_expression();
			break;
		case '3':
			range();
			break;
		case '4':
			array_work();
			break;
		default:
			work = 0;
			break;
		}
	}
}

void arithmetic_expression()
{
	double x, y, z;
	cout << "Арифметическое выражение:\n";
	cout << "R = X * Y * (X - Z) / ((Y - X) * (1 + (Z - Y))) + fabs(exp(X * Y) - sqrt(Z / Y)): \n";
	cout << "Введите X\n";
	cin >> x;
	cout << "Введите Y\n";
	cin >> y;
	cout << "Введите Z\n";
	cin >> z;
	cout << "R = " << x * y * (x - z) / ((y - x) * (1 + (z - y))) + fabs(exp(x * y) - sqrt(z / y)) << "\n\n";
}

void logical_expression()
{
	int a, b, c;
	cout << "Логическое выражение:\n";
	cout << "(A && B && C) || (!A && !B && !C)\n";
	cout << "Введите A\n";
	cin >> a;
	cout << "Введите B\n";
	cin >> b;
	cout << "Введите C\n";
	cin >> c;
	a = a != 0;
	b = b != 0;
	c = c != 0;
	cout << ((a && b && c) || (!a && !b && !c) ? "Результат: True\n\n" : "Результат: False\n\n");
}

void range()
{
	double x;
	double eps = 1e-6;
	double f = 0;
	double f_n = 1e+6;
	cout << "arctg(1/x) = 1 / x - 1/3x^3 + 1/5x^5 - 1/7x^7 + ... \n";
	cout << "Область сходимости ряда (-inf, -1] U [1, + inf)\n";
	cout << "Введите x\n";
	cin >> x;
	if (x == 0)
	{
		cout << "Деление на 0!\n\n";
		return;
	}
	if (fabs(x) < 1)
	{
		cout << "Ряд расходится!\n\n";
		return;
	}
	for (int n = 0; fabs(f_n) > eps; n++)
	{
		f_n = pow(-1, n) * 1 / ((2 * (double)n + 1) * pow(x, 2 * n + 1));
		f += f_n;
	}
	cout << "arctg(1/x) = " << f << "\n";
	cout << "Проверка: arctg(1/x) = " << atan(1 / x) << "\n\n";
}

void array_work()
{
	int n = 0, m = 0;
	int DO = 1;
	double** array = NULL;
	// Исходный файл
	char filename[] = "array.txt";
	while (DO)
	{
		try
		{
			cout << "Введите количество строк n (не больше 4)\n";
			cin >> n;
			cout << "Введите количество строк m (не больше 5)\n";
			cin >> m;
			// Создание двумерного динамического массива
			array = create_bivariate_array(n, m);
			// Чтение массива из файла
			read_array_from_file(array, n, m, filename);
		}
		catch (int i)
		{
			cout << "Вызвано исключение: неожиданный конец файла\n\n";
			continue;
		}
		DO = 0;
	}
	cout << "\nИсходный массив:\n";
	// Печать массива в консоль
	print_array(array, n, m);
	// Файл для вывода 
	char filename_out[] = "array_out_original.txt";
	// Печать массива в файл
	print_array_to_file(array, n, m, filename_out);
	// Подсчет произведений отрицательных элементов по каждому столбцу массива
	double* array_of_products = count_products_of_negatives(array, n, m);
	for (int j = 0; j < m; j++)
	{
		printf("%8.3f ", array_of_products[j]);
	}
	// Нахождение минимального элемента в каждой строке массива
	find_minimal_in_row(array, n, m);
	// Освобождение выделенной памяти
	delete_bivariate_array(array, n);
	delete_array(array_of_products);
}

void print_array(double** array, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%8.3f ", array[i][j]);
		}
		cout << endl;
	}
}

void print_array_to_file(double** array, int n, int m, char filename[])
{
	FILE* output_file;
	errno_t err;
	if ((err = fopen_s(&output_file, filename, "w")) != 0)
	{
		cout << "Ошибка! Файл не был открыт.";
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				fprintf(output_file, "%8.3f ", array[i][j]);
			}
			fprintf(output_file, "\n");
		}
	}
	fclose(output_file);
}

void read_array_from_file(double** array, int n, int m, char filename[])
{
	ifstream input_file(filename);
	// Обработка исключений
	try {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				// Если встречен конец файла, то вызывается исключение
				if (input_file.eof())
				{
					throw - 1;
				}
				input_file >> array[i][j];
			}
		}
	}
	catch (int i)
	{
		throw - 1;
		input_file.close();
	}
	input_file.close();
}

double* count_products_of_negatives(double** array, int n, int m)
{
	double* array_of_products = create_array(m);
	int k = 0;
	double mul = 1;
	bool have_negative = false;
	cout << "\nМассив из произведений отрицательных элементов каждого столбца:\n";
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (array[i][j] < 0)
			{
				mul *= array[i][j];
				have_negative = true;
			}
		}
		if (!have_negative)
		{
			mul = 0;
		}
		array_of_products[k] = mul;
		mul = 1;
		have_negative = false;
		k++;
	}
	return array_of_products;
}

void find_minimal_in_row(double** array, int n, int m)
{
	double min = 1e6;
	int min_j = 0;
	cout << "\n\nМинимальные элементы по каждой строке и их индексы:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (array[i][j] < min)
			{
				min = array[i][j];
				min_j = j;
			}
		}
		printf("%8.3f %8d %8d", min, i, min_j);
		cout << endl;
		min = 1e6;
		min_j = 0;
	}
	cout << endl;
}

double** create_bivariate_array(int n, int m) {
	double** bivariate_array = new double* [n];
	for (int i = 0; i < n; i++)
	{
		bivariate_array[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			bivariate_array[i][j] = 0;
		}
	}
	return bivariate_array;
}

double* create_array(int n)
{
	double* array = new double[n];
	return array;
}

void delete_bivariate_array(double** bivariate_array, int n)
{
	for (int i = 0; i < n; i++) {
		delete[] bivariate_array[i];
	}
	delete[] bivariate_array;
}

void delete_array(double* array)
{
	delete[] array;
}