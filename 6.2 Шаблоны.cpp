#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

// Шаблонный класс списка
template <typename T>
class List
{
private:
	struct list_ob
	{
		T _value;
		list_ob* _prev = NULL;
		list_ob* _next = NULL;
	};
	int _size;
	list_ob* _head;
public:
	// Конструктор1 списка 
	List()
	{
		_size = 0;
		_head = NULL;
	}
	// Конструктор2 списка (элемент в параметре сразу заносится в список)
	List(T x)
	{
		_size = 1;
		_head = new(list_ob);
		_head->_value = x;
		_head->_prev = NULL;
		_head->_next = NULL;
	}

	~List() {}

	// Добавить элемент в список
	void add_to_list(T x)
	{
		if (_size == 0)
		{
			_size = 1;
			_head = new(list_ob);
			_head->_value = x;
			_head->_prev = NULL;
			_head->_next = NULL;
			return;
		}
		_size++;
		list_ob* cur = new(list_ob);
		if (_head->_next == NULL)
		{
			if (x < _head->_value)
			{
				cur->_prev = NULL;
				cur->_next = _head;
				_head->_prev = cur;
				_head = cur;
				_head->_value = x;
			}
			else
			{
				_head->_next = cur;
				cur->_prev = _head;
				cur->_next = NULL;
				cur->_value = x;
			}
			return;
		}
		list_ob* cur_addr = cur;
		cur = _head;
		while (cur->_next != NULL)
		{
			if (x < cur->_value)
			{
				if (cur == _head)
				{
					cur = cur_addr;
					cur->_prev = NULL;
					cur->_next = _head;
					cur->_value = x;
					_head->_prev = cur;
					_head = cur;
					return;
				}
				list_ob* left, * right;
				left = cur->_prev;
				right = cur;
				cur = left;
				cur->_next = cur_addr;
				cur = cur_addr;
				cur->_prev = left;
				cur->_next = right;
				cur->_value = x;
				cur = right;
				cur->_prev = cur_addr;
				return;
			}
			cur = cur->_next;
		}
		if (cur->_next == NULL)
		{
			if (x >= cur->_value)
			{
				list_ob* left;
				left = cur;
				cur->_next = cur_addr;
				cur = cur_addr;
				cur->_prev = left;
				cur->_next = NULL;
				cur->_value = x;
				return;
			}
			else
			{
				list_ob* left, * last;
				left = cur->_prev;
				last = cur;
				cur = left;
				cur->_next = cur_addr;
				cur = cur_addr;
				cur->_prev = left;
				cur->_next = last;
				cur->_value = x;
				cur = last;
				cur->_prev = cur_addr;
				cur->_next = NULL;
				return;
			}
		}
	}

	// Перегрузка оператора += для добавления элемента списка
	// Элемент для добавления передается в параметре
	void operator+=(T x)
	{
		this->add_to_list(x);
	}

	void read_from_file(char filename[])
	{
		ifstream fin(filename);
		if (!fin) { cout << "Ошибка! Невозможно открыть файл.\n"; }
		T el;
		while (!fin.eof())
		{
			fin >> el;
			this->add_to_list(el);
		}
		fin.close();
	}

	// Вывод головы списка
	T peek()
	{
		return _head->_value;
	}
	// Вывод списка
	void print_list()
	{
		if (_size == 0)
		{
			cout << "Список пуст!\n";
			return;
		}
		list_ob* head;
		head = _head;
		while (_head != NULL)
		{
			cout << peek() << endl;
			_head = _head->_next;
		}
		_head = head;
	}
	// Поиск элемента в списке
	// Элемент для поиска передается в параметре 
	int find_element(T x)
	{
		if (_size == 0)
		{
			cout << "Список пуст. Искать нечего\n";
			return 0;
		}
		list_ob* head;
		head = _head;
		while (_head != NULL)
		{
			if (_head->_value == x)
			{
				cout << "Элемент \"" << x << "\" найден\n";
				_head = head;
				return 1;
			}
			_head = _head->_next;
		}
		cout << "Элемента \"" << x << "\" в списке нет\n";
		_head = head;
		return 0;
	}
	// Перегрузка оператора -= для удаления элемента списка
	// Элемент для удаления передается в параметре 
	void operator-=(T x)
	{
		if (_size == 0)
		{
			cout << "Список пуст. Удалять нечего.\n";
			return;
		}
		list_ob* cur, * rem;
		cur = _head;
		while (cur != NULL)
		{
			if (cur->_value == x)
			{
				if (cur == _head)
				{
					if (_size > 1)
					{
						rem = _head;
						_head = cur->_next;
						cur = cur->_next;
						cur->_prev = rem;
						delete rem;
						_size--;
						cout << "Элемент \"" << x << "\" удален\n";
						return;
					}
					else
					{
						delete _head;
						_head = NULL;
						_size--;
						cout << "Элемент \"" << x << "\" удален\n";
						return;
					}
				}
				else
				{
					list_ob* left;
					left = cur->_prev;
					rem = cur;
					if (cur->_next != NULL)
					{
						cur = left;
						cur->_next = rem->_next;
						cur = rem->_next;
						cur->_prev = left;
					}
					else
					{
						left->_next = NULL;
					}
					delete rem;
					_size--;
					cout << "Элемент \"" << x << "\" удален\n";
					return;
				}
			}
			cur = cur->_next;
		}
		cout << "Элемента \"" << x << "\" в списке нет\n";
	}
	// Удаление списка целиком
	void delete_list()
	{
		list_ob* cur = _head;
		while (_head != NULL)
		{
			cur = _head;
			_head = _head->_next;
			delete cur;
			_size--;
		}
	}
	//Функция возвращает размер списка (количество элементов)
	int stack_size()
	{
		return _size;
	}

 friend ostream& operator <<(ostream& os, List<T>& l)
{
	if (l._size == 0)
	{
		return os << "Список пуст!\n";
	}
	list_ob* head;
	head = l._head;
	while (l._head != NULL)
	{
		os << l.peek() << endl;
		l._head = l._head->_next;
	}
	l._head = head;
	return os;
}
}; // Конец класса списка

// Создание манипулятора
ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50) << setfill('=');
	return stream;
}

// Шаблонная функция для чтения данных из файла и записи в STL-список
template <typename T>
void read_from_file(char filename[], list<T>& listSTL)
{
	ifstream fin(filename);
	if (!fin) { cout << "Ошибка! Невозможно открыть файл.\n"; }
	T el;
	while (!fin.eof())
	{
		fin >> el;
		listSTL.push_back(el);
	}
	fin.close();
}

// Шаблонная функция для вывода элементов STL-списка
template <typename T>
void printListSTL(const list<T>& listSTL)
{
	for (auto i = listSTL.cbegin(); i != listSTL.cend(); ++i) 
	{
		// auto - ключевое слово, позволяющее определить тип i автоматически при инициализации
		// i - константный итератор
		cout << *i << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	char data[] = "list_data.txt";

	// Работа с шаблонным списком (тип string)
	List<string> a;
	a.read_from_file(data); // чтение из файла
	cout << setup << "" << endl;
	cout << "Вывод списка (тип string)\n";
	cout << setup << "" << endl;
	cout << a << endl;
	cout << setup << "" << endl;
	cout << "Поиск элемента списка (тип string)" << endl;
	cout << setup << "" << endl;
	a.find_element("aaa");
	a.find_element("hhh");
	a.find_element("eee");
	a.find_element("dfs");
	a.find_element("aaa8");
	cout << endl << setup << "" << endl;
	cout << "Удаление элементов списка (тип string)" << endl;
	cout << setup << "" << endl;
	a -= ("ddd");
	a -= ("ddd");
	a -= ("aaa");
	a -= ("aaa");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	cout << endl << setup << "" << endl;
	cout << "Вывод списка после удаления элементов (тип string)\n";
	cout << setup << "" << endl;
	cout << a << endl;
	a.delete_list();
	cout << setup << "" << endl;
	cout << "Вывод списка после удаления целиком (тип string)\n";
	cout << setup << "" << endl;
	cout << a << endl;

	// Работа с шаблонным списком (тип int)
	List<int> i(2);
	i += (888);
	i += (7);
	i += (42);
	i += (8);
	i += (-111);
	i += (11);
	cout << setup << "" << endl;
	cout << "Вывод списка (тип int)\n";
	cout << setup << "" << endl;
	i.print_list();
	cout << endl << setup << "" << endl;
	cout << "Поиск элемента списка (тип int)" << endl;
	cout << setup << "" << endl;
	i.find_element(8);
	i.find_element(888);
	i.find_element(7);
	i.find_element(0);
	i.find_element(100);
	cout << endl << setup << "" << endl;
	cout << "Удаление элементов списка (тип int)" << endl;
	cout << setup << "" << endl;
	i -= (7);
	i -= (2);
	i -= (11);
	i -= (-111);
	i -= (1);
	cout << endl << setup << "" << endl;
	cout << "Вывод списка после удаления элементов (тип int)\n";
	cout << setup << "" << endl;
	cout << i << endl;
	cout << setup << "" << endl;
	cout << "Вывод списка после удаления целиком (тип int)\n";
	cout << setup << "" << endl;
	i.delete_list();
	i.print_list();

	// Работа с STL списком
	list<string> listSTL;
	cout << endl << setup << "" << endl;
	cout << "Вывод STL-списка\n";
	cout << setup << "" << endl;
	read_from_file(data, listSTL);
	listSTL.sort();
	printListSTL(listSTL);
	cout << endl << setup << "" << endl;
	cout << "Вывод STL-списка после удаления элементов\n";
	cout << setup << "" << endl;
	listSTL.remove("ddd");
	listSTL.remove("aaa");
	listSTL.remove("hhh");
	printListSTL(listSTL);
	cout << endl << setup << "" << endl;
	cout << "Вывод STL-списка после удаления целиком\n";
	cout << setup << "" << endl;
	listSTL.clear();
	printListSTL(listSTL);
	if (!listSTL.size())
	{
		cout << "STL-список пуст!" << endl;
	}

	
	return 0;
}