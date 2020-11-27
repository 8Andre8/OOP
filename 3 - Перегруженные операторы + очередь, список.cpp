#include<iostream>
#include<string>

using namespace std;

class List;
// Класс очереди
class Queue              
{
private:
	struct queue_ob      // Структура для хранения элементов очереди
	{
		string _value;   // Поле для хранения значения элемента очереди
		queue_ob *_addr; // Поле для хранения следующего элемента
	};
	queue_ob *_head;     // Указатель, хранящий адресс головы очереди
	queue_ob *_tail;     // Указатель хранящий адрес хвоста
	int _size;           // Текущий размер очереди

public:
	Queue()
	{
		_size = 0;
		_head = NULL;
		_tail = NULL;
	}

	Queue(string x)// Конструктор класса
	//В параметру передается голова очереди
	{
		_head = new(queue_ob); // Выделяем память под элемент
		_tail = _head;         // При создании очереди хвост и голова являются одним и тем же элементом
		_head->_value = x;     // Записываем значение
		_head->_addr = NULL;   // Адрес ноль, так как следующего элемента пока нет
		_size = 1;             // После выделения памяти и заполнения полей структуры очередь стала иметь размер 1
	}

	~Queue(){}

	int stack_size() // Функция возвращает размер очереди(кол-во элеменетов)
	{
		return _size;
	}
	// Перегрузка оператора += для удаления элемента списка
	// Элемент для добавления передается в параметре
	void operator+=(string value)
	{
		if (value.length() > 12) 
		{
			cout << "Введенная строка " << value <<" слишком велика (> 12)\n";
			return;
		}
		if (_size == 0) {
			_head = new(queue_ob); // Выделяем память под элемент
			_tail = _head;         // При создании очереди хвост и голова являются одним и тем же элементом
			_head->_value = value; // Записываем значение
			_head->_addr = 0;      // Адрес ноль, так как следующего элемента пока нет
			_size++;
			return;
		}
		_size++;                       // Кол-во элементов очереди увеличивается
		queue_ob* cur = new(queue_ob); // Выделяем память под новый хвост очереди
		cur->_addr = 0;                // Записываем в поле адреса нового хвоста ноль, так как за ничего нету
		cur->_value = value;           // Заполняем поле значения нового хвоста
		_tail->_addr = cur;            // Записываем в поле адреса старого хвоста адрес нового хвоста
		_tail = cur;                   //Записываем в указатель хвоста адрес действительного хвоста
	}

	string pop() // Удаляет элемент (выталкивает) и возвращает его
	{
		if (_size == 0)
		{
			return "Очередь пуста - удалять нечего!\n";
		}
		string value;
		queue_ob *cur = _head; // Записываем адрес головы
		value = _head->_value; // Записываем значение головы
		_head = _head->_addr;  // Изменяем адрес головы
		delete cur;            // Удаляем старую голову
		_size--;               // Уменьшаем размер
		return value;
	}
	// Перегрузка оператора -- для удаления головы очереди
	Queue operator--(int)
	{
		this->pop();
		return *this;
	}
	// Удаление очереди целиком
	void delete_all()
	{
		while (_size != 0) {
			this->pop();
		}
	}
	// Чтение головы очереди
	string peek()
	{
		if (_size == 0) // Если очередь пуста(_size == 0), то ничего не выгружает
		{
			return "Очередь пуста!\n";
		}
		return _head->_value; // Выгружаем значение головы
	}
	// Вывод очередь с удалением ее элементов
	void print_queue_and_delete()
	{
		while (_size != 0)
		{
			cout << peek() << endl;
			this->pop();
		}
	}
	// Объявление дружественной функции
	friend void compare_size(Queue q, List l);
}; // Конец класса очереди

//=================================================================================

// Класс списка
class List
{
private:
	struct list_ob
	{
		string _value;
		list_ob *_prev;
		list_ob *_next;
	};
	int _size;
	list_ob *_head;
public:
	// Конструктор1 списка 
	List()
	{
		_size = 0;
		_head = NULL;
	}
	// Конструктор2 списка (элемент в параметре сразу заносится в список)
	List(string x)
	{
		_size = 1;
		_head = new(list_ob);
		_head->_value = x;
		_head->_prev = NULL;
		_head->_next = NULL;
	}

	~List() {}

	// Перегрузка оператора += для удаления элемента списка
	// Элемент для добавления передается в параметре
	void operator+=(string x)
	{
		if (x.length() > 12)
		{
			cout << "\n Введенная строка " << x << " слишком велика (> 12)\n";
			return;
		}
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
		list_ob *cur = new(list_ob);
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
		list_ob *cur_addr = cur;
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
				list_ob *left, *right;
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
				list_ob *left;
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
				list_ob *left, *last;
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
	// Вывод головы списка
	string peek() 
	{
		if (_size == 0) 
		{
			return "Список пуст!\n";
		}
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
	void find_element(string x)
	{
		if (_size == 0)
		{
			cout << "Список пуст. Искать нечего\n";
			return;
		}
		list_ob* head;
		head = _head;
		while (_head != NULL)
		{
			if (_head->_value == x)
			{
				cout << "Элемент \"" << x << "\" найден\n";
				_head = head;
				return;
			}
			_head = _head->_next;
		}
		cout << "Элемента \"" << x << "\" в списке нет\n";
		_head = head;
	}
	// Перегрузка оператора -= для удаления элемента списка
	// Элемент для удаления передается в параметре 
	void operator-=(string x) 
	{
		if (_size == 0)
		{
			cout << "Список пуст. Удалять нечего.\n";
			return;
		}
		list_ob *cur, *rem;
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
					list_ob *left;
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
	// Объявление дружественной функции
	friend void compare_size(Queue q, List l);
}; // Конец класса списка

// Дружественная функция сравнения размеров очереди и списка
void compare_size(Queue q, List l) 
{
	if (q._size == l._size)
	{
		cout << "Размеры очереди и списка совпадают: " << q._size << endl;
	}
	else
	{
		cout << "Размеры очереди и стека не совпадают:" << endl;
		cout << "Очередь: " << q._size << " Список: " << l._size << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	// Работа с очередью
	Queue a;
	a += ("aaa"); 
	a += ("bbb"); 
	a += ("ccc"); 
	a += ("ddd");
	a += ("eee");
	a += ("fff");
	a += ("ggg");
	a += ("hhh");
	a += ("iii");
	cout << "Голова очереди: " << a.peek() << endl;
	a--;
	a--;
	cout <<  "===== Вывод очереди после удаления элементов =====\n";
	a.print_queue_and_delete();
	cout << "===== Вывод очереди после удаления целиком =====\n";
	cout << a.peek();
	// Работа со списком
	List b;
	b += ("aaa");
	b += ("hhh");
	b += ("ddd");
	b += ("ccc");
	b += ("hhh");
	b += ("bbb");
	b += ("fff");
	b += ("ddd");
	b += ("eee");
	b += ("ggg");
	b += ("hhh");
	b += ("aaa");
	cout << endl << "===== Вывод списка =====\n";
	b.print_list();
	cout << endl << "===== Поиск элемента списка: =====" << endl;
	b.find_element("aaa");
	b.find_element("hhh");
	b.find_element("eee");
	b.find_element("dfs");
	b.find_element("aaa8");
	cout << endl << "===== Удаление элемента списка: =====" << endl;
	b-=("ddd");
	b-=("aaa");
	b-=("hhh");
	b-=("hhh");
	b-=("hhh");
	b-=("hhh");
	cout << endl << "===== Вывод списка после удаления элементов =====\n";
	b.print_list();
	b.delete_list();
	cout << endl << "===== Вывод списка после удаления целиком =====\n";
	b.print_list();
	// Использование дружественной функции
	cout << endl << "===== Сравнение размеров =====\n";
	compare_size(a, b);
	Queue q("***");
	q += ("@");
	List l("***");
	compare_size(q, l);
	return 0;
}