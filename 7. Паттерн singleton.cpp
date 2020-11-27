#include <string>
#include <iostream>
using namespace std;
class Singleton
{
//Конструктор скрыт, чтобы предотвратить создание объекта.
private:
    Singleton(const string value) : value_(value)
    {
    }
    static Singleton* singleton_;
    string value_;
public:
    //Одиночки не должны быть клонируемыми.
    Singleton(Singleton& other) = delete; // копирующий конструктор
    void operator=(const Singleton&) = delete;
    // Это статический метод, управляющий доступом к экземпляру одиночки
    static Singleton* getInstance(const string& value);
    // Изменить значение объекта
    void change_value(string x)
    {
        value_ = x;
    }
    // Получить значение объекта
    string value() const {
        return value_;
    }
};

// Определение статического переменной-члена класса
Singleton* Singleton::singleton_ = nullptr;;

// Определение статического метода
Singleton* Singleton::getInstance(const std::string& value)
{
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Результат:\n";
    //Singleton t("sds"); конструктор недоступен
    Singleton* t1 = Singleton::getInstance("Test1");
    Singleton* t2 = Singleton::getInstance("Test222222");
    cout << "t1 = " << t1->value() << endl;
    cout << "t2 = " << t2->value() << endl;
    t2->change_value("***");
    cout << "После изменения на \"***\"" << endl;
    cout << "t1 = " << t1->value() << endl;
    cout << "t2 = " << t2->value() << endl;
    Singleton* t3 = Singleton::getInstance("Test3333333333333");
    cout << "t3 = " << t3->value() << endl;
    cout << "Адрес t1 = " << t1 << endl;
    cout << "Адрес t2 = " << t2 << endl;
    cout << "Адрес t3 = " << t3 << endl;
    return 0;
}