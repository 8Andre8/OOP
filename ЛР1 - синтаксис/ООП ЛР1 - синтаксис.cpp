#include <iostream>
#include <fstream>
using namespace std;

void arithmetic_expression();
void logical_expression();
void range();
void array_work();
void print_array(double** array, int n, int m);
void print_array_to_file(double** array, int n, int m, char filename[]);
void read_array_from_file(double** array, int n, int m, char filename[]);
double* count_products_of_negatives(double** array, int n, int m);
void find_minimal_in_row(double** array, int n, int m);
double* create_array(int n);

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
	int n, m;
	cout << "Введите количество строк n (не больше 4)\n";
	cin >> n;
	cout << "Введите количество строк m (не больше 5)\n";
	cin >> m;
	double** array = new double* [n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new double[m];
	}
	char filename[] = "array.txt";
	read_array_from_file(array, n, m, filename);
	cout << "\nИсходный массив:\n";
	print_array(array, n, m);
	//
	char filename_out[] = "array_out_original.txt";
	print_array_to_file(array, n, m, filename_out);
	//
	double* array_of_products = count_products_of_negatives(array, n, m);
	for (int j = 0; j < m; j++)
	{
		//cout << array_of_products[j] << ' ';
		printf("%8.3f ", array_of_products[j]);
	}
	find_minimal_in_row(array, n, m);
	for (int i = 0; i < n; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	delete[] array_of_products;
}
	
void print_array(double** array, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			//cout << array[i][j] << ' ';
			printf("%8.3f ", array[i][j]);
		}
		cout << endl;
	}
}

void print_array_to_file(double** array, int n, int m, char filename[])
{
	ofstream output_file(filename);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			output_file << array[i][j] << ' ';
		}
		output_file << endl;
	}
	output_file.close();
}

void read_array_from_file(double** array, int n, int m, char filename[])
{
	ifstream input_file(filename);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			input_file >> array[i][j];
		}
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
		//cout << min << ' ' << i << ' ' << min_j << '\n';
		printf("%8.3f %8d %8d", min, i, min_j);
		cout << endl;
		min = 1e6;
		min_j = 0;
	}
	cout << endl;
}

double* create_array(int n)
{
	double* array = new double[n];
	return array;
}
