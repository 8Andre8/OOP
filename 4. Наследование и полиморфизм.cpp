#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class Machine 
{
protected:
    string _brand = "Nan";
public:
    // Чистая виртуальная функция
    virtual void print_info() = 0;
    Machine(string brand) 
    {
        string type = typeid(*this).name();
        _brand = brand;
    }
};

class Truck : public Machine
{
    string _type = "Nan";
protected:
    int _cylinders_number = -1;
    long int _tonnage = -1;
public:
    Truck(const string brand, int cylinders_number, long int tonnage) : Machine(brand)
    {
        _type = "Грузовик";
        _cylinders_number = cylinders_number;
        _tonnage = tonnage;
    }
    // Переобъявление виртуальной функции
    void print_info()
    {
        string s = typeid(*this).name();
        cout << s << endl;
        cout << "Класс: " << _type << endl;
        cout << "Марка: " << _brand << endl;
        cout << "Количество цилиндров: " << _cylinders_number << endl;
        cout << "Грузоподъемность (тонны): " << _tonnage << endl;
    }
    // Рассчитать количество рейсов, необходимых для перевозки груза
    void calc_runs_number()
    {
        int total_cargo = 105;
        cout << "Количество рейсов, необходимых для перевозки " << total_cargo <<" тонн груза: " << ceil((double)total_cargo / _tonnage) << endl;
    }
};

class Car : public Machine
{
    string _type = "Nan";
protected:
    string _model = "Nan";
    int _speed = -1;
public:
    Car(const string brand, const string model, int speed) : Machine(brand)
    {
        _model = model;
        _speed = speed;
        _type = "Легковая";
    }
    // Переобъявление виртуальной функции
    void print_info()
    {
        cout << typeid(*this).name() << endl;
        cout << "Класс: " << _type << endl;
        cout << "Марка: " << _brand << endl;
        cout << "Модель: " << _model << endl;
        cout << "Максимальная скорость: " << _speed << " км/ч" << endl;
    }
    
    void calc_travel_time()
    {
        const int distance = 710;
        double average_speed = _speed / 2;
        cout << "Время в пути (из Петербурга в Москву): " << round(distance / average_speed) << " ч" << endl;
    }
};

class Bus : public Machine
{
    string _type = "Nan";
protected:
    int _passengers_number = -1;
public:
    Bus(const string brand, int passengers_number) : Machine(brand)
    {
        _passengers_number = passengers_number;
        _type = "Автобус";
    }
    // Переобъявление виртуальной функции
    void print_info()
    {
        cout << typeid(*this).name() << endl;
        cout << "Класс: " << _type << endl;
        cout << "Марка: " << _brand << endl;
        cout << "Количество пассажиров: " << _passengers_number << endl;
    }
    // Рассчитать общий вес автобуса
    void calc_weight()
    {
        const int human_weight = 65;
        cout << "Общий перевозимый вес: " << human_weight * _passengers_number << " кг" << endl;
    }
};

class School_bus : public Bus
{
    string _type = "Nan";
protected:
    string _color = "Nan";
public:
    School_bus(const string brand, int number, const string color) : Bus(brand, number)
    {
        _color = color;
        _type = "Школьный автобус";
    }
    // Переобъявление виртуальной функции
    void print_info()
    {
        cout << typeid(*this).name() << endl;
        cout << "Класс: " << _type << endl;
        cout << "Число пассажиров: " << _passengers_number << endl;
        cout << "Марка: " << _brand << endl;
        cout << "Цвет: " << _color << endl;
    }
};

class Cost
{
protected:
    int _cost = -1;
public:
    Cost(int cost)
    {
        _cost = cost;
    }
};

class Car_with_cost : public Car, public Cost
{
public:
    Car_with_cost(const string brand, const string model, int speed, int cost) : Car(brand, model, speed), Cost(cost)
    {
        _model = model;
        _speed = speed;
    }
    // Переобъявление виртуальной функции
    void print_info()
    {
        cout << typeid(*this).name() << endl;
        cout << "Марка: " << _brand << endl;
        cout << "Модель: " << _model << endl;
        cout << "Максимальная скорость: " << _speed << " км/ч" << endl;
        cout << "Стоимость: " << _cost << " руб." << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Bus b("Volvo", 20);
    b.print_info();
    b.calc_weight();
    Car c("BMW", "x8", 200);
    cout << endl;
    c.print_info();
    c.calc_travel_time();
    Truck t("КАМАЗ", 32, 10);
    cout << endl;
    t.print_info();
    t.calc_runs_number();
    School_bus b1("LIAZ", 25, "Yellow");
    cout << endl;
    b1.print_info();
    Car_with_cost c1("Лада", "Веста", 180, 600000);
    cout << endl;
    c1.print_info();
    c1.calc_travel_time();
    return 0;
}

