// 2. Основы работы с классами.cpp 

#include <iostream>
using namespace std;

class Series1
{
private:
    double x = 5.;
    double eps = 1e-6;
    double f = 0;
    double f_n = 1e+6;
    int n = 0;
public:
    void print()
    {
        while (fabs(f_n) > eps)
        {
            f_n = pow(-1, n) * 1 / ((2 * (double)n + 1) * pow(x, 2 * n + 1));
            f += f_n;
            n++;
        }
        cout << "Класс 1:\n";
        cout << "arctg(1/x) = " << f << "\n";
        cout << "Проверка: arctg(1/x) = " << atan(1 / x) << "\n\n";
    }

};

class Series2
{
private:
    double x;
    double eps;
    double f;
    double f_n;
    int n;
public:
    // Конструктор
    Series2()
    {
        x = 5;
        eps = 1e-6;
        f = 0;
        f_n = 1e+6;
        n = 0;
    }
    // Деструктор
    ~Series2()
    {
        cout << "Тут сработал деструктор Series2 \n";
    }

    void print()
    {
        while (fabs(f_n) > eps)
        {
            f_n = pow(-1, n) * 1 / ((2 * (double)n + 1) * pow(x, 2 * n + 1));
            f += f_n;
            n++;
        }
        cout << "Класс 2:\n";
        cout << "arctg(1/x) = " << f << "\n";
        cout << "Проверка: arctg(1/x) = " << atan(1 / x) << "\n\n";
    }
};

class Series3
{
private:
    double _x;
    double _eps;
    double _f;
    double _f_n;
    int _n;
public:
    void print();
    // Конструктор
    Series3(double x, double eps)
    {
        _x = x;
        _eps = eps;
        _f = 0;
        _f_n = 1e+6;
        _n = 0;
    }
    // Деструктор
    ~Series3()
    {
        cout << "Тут сработал деструктор Series3 \n";
    }
};
// Явное использование встроенной функции
inline void Series3 :: print()
{
    if (_x == 0)
    {
        cout << "Деление на 0!\n\n";
        return;
    }
    if (fabs(_x) < 1)
    {
        cout << "Ряд расходится!\n\n";
        return;
    }
    while (fabs(_f_n) > _eps)
    {
        _f_n = pow(-1, _n) * 1 / ((2 * (double)_n + 1) * pow(_x, 2 * _n + 1));
        _f += _f_n;
        _n++;
    }
    cout << "Класс 3:\n";
    cout << "arctg(1/x) = " << _f << "\n";
    cout << "Проверка: arctg(1/x) = " << atan(1 / _x) << "\n\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Series1 n1;
    n1.print();
    Series2 n2;
    n2.print();
    double x;
    double eps;
    cout << "Введите x ( область сходимости ряда (-inf, -1] U [1, + inf) )\n";
    cin >> x;
    cout << "Введите необходимую точность\n";
    cin >> eps;
    Series3 n3 {x, eps};
    n3.print();
    return 0;
}

