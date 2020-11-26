#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Класс списка
class List
{
private:
	struct list_ob
	{
		string _value;
		list_ob* _prev;
		list_ob* _next;
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
	List(string x)
	{
		_size = 1;
		_head = new(list_ob);
		_head->_value = x;
		_head->_prev = NULL;
		_head->_next = NULL;
	}

	~List() {}

	// Добавить элемент в список
	void add_to_list(string x)
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

	// Перегрузка оператора += для удаления элемента списка
	// Элемент для добавления передается в параметре
	void operator+=(string x)
	{
		this->add_to_list(x);
	}

	void read_from_file(char filename[])
	{
		ifstream fin(filename);
		if (!fin) { cout << "Ошибка! Невозможно открыть файл.\n"; }
		string el;
		while (!fin.eof())
		{
			fin >> el;
			this->add_to_list(el);
		}
		fin.close();
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
	int find_element(string x)
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
	void operator-=(string x)
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

	friend ostream& operator<<(ostream& os, List& q);
}; // Конец класса списка

// Перегрузка оператора << для вывода списка
ostream& operator<<(ostream& os, List& l)
{
	if (l._size == 0)
	{
		return os << "Список пуст!\n";
	}
	List::list_ob* head;
	head = l._head;
	while (l._head != NULL)
	{
		os << l.peek() << endl;
		l._head = l._head->_next;
	}
	l._head = head;
	return os;
}

// Создание манипулятора
ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50) << setfill('=');
	return stream;
}

// Чтение данных из файла и запись в бинарный файл
void readTxtWriteBin(char file[], char bin[])
{
	ifstream fin(file, ios::in);
	if (!fin) { cout << "Ошибка! Невозможно открыть файл: " << file << endl; }
	ofstream biout;
	biout.open(bin, ios::binary | ios::out);
	if (!biout) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	char el;
	while (!fin.eof())
	{
		fin >> el;
		if (fin.eof())
		{
			break;
		}
		biout.write((char*)&el, sizeof el);
	}
	fin.close(); // Закрыли файл данных
	biout.close(); // Закрыли бинарный файл
}

// Чтение бинарного файла и вывод данных в текстовый файл
void readBinWriteTxt(char bin[], char file[])
{
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // Открыли только для чтения в бинарном режиме
	if (!in) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	ofstream fout(file, ios::out);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << file << endl; }
	fout << setup << "" << endl;
	fout << "===== Вывод содержимого бинарного файла =====\n";
	fout << setup << "";
	while (!in.eof())
	{
		if (i % 3 == 0)
		{
			fout << endl;
		}
		in.read((char*)&c, sizeof(c));
		if (in.eof())
		{
			break;
		}
		fout << c;
		i++;
	}
	in.close(); // Закрыли бинарный файл данных
	fout.close(); // Закрыли выходной файл
}

// Чтение бинарного файла и вывод данных в текстовый файл
void readBinAppendTxt(char bin[], char file[])
{
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // Открыли только для чтения в бинарном режиме
	if (!in) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	ofstream fout(file, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << file << endl; }
	while (!in.eof())
	{
		if (i % 3 == 0)
		{
			fout << endl;
		}
		in.read((char*)&c, sizeof(c));
		if (in.eof())
		{
			break;
		}
		fout << c;
		i++;
	}
	in.close(); // Закрыли бинарный файл данных
	fout.close(); // Закрыли выходной файл
}

// Модификация бинарного файла
void modBin(char bin[])
{
	char c;
	char C = 'H';
	long pos = -1;
	fstream f(bin, ios::binary | ios::in | ios:: out); // Открыли только для чтения и записи в бинарном режиме
	if (!f) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	while (!f.eof())
	{
		pos = f.tellp();
		f.read((char*)&c, sizeof(c));
		if (f.eof())
		{
			return;
		}
		if (c == 'h')
		{
			f.seekp(pos);
			f.write((char*)&C, sizeof(C));
			f.seekp(pos);
		}
	}
	f.close();
}

// Удаление строки из бинарного файла
void delBin(char bin[])
{
	char c;
	char del = 'H';
	char C = ' ';
	int i = 0;
	long pos = -1;
	fstream f(bin, ios::binary | ios::in | ios::out); // Открыли только для чтения и записи в бинарном режиме
	if (!f) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	while (!f.eof())
	{
		pos = f.tellp();
		f.read((char*)&c, sizeof(c));
		if (f.eof())
		{
			return;
		}
		if ((c == del) && (i % 3 == 0))
		{
			while (!f.eof())
			{
				for (int i = 0; i < 3; i++) {
					f.seekp(pos + 3 + i);
					f.read((char*)&c, sizeof(c));
					f.seekp(pos + i);
					f.write((char*)&c, sizeof(c));
				}
				f.seekp(pos + 3);
				pos = f.tellp();
				f.seekp(pos + 3);
				f.read((char*)&c, sizeof(c));
				if (f.eof())
				{
					f.close();
					f.open(bin, ios::binary | ios::in | ios::out);
					for (int i = 0; i < 3; i++) {
						f.seekp(pos+i);
						f.write((char*)&C, sizeof(C));
					}
					return;
				}
				f.seekp(pos);
			}
		}
		i++;
	}
	f.close();
}

// Поиск максимальной по коду строки
void procBin(char bin[], char file[])
{
	string max = "";
	string str = "";
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // Открыли только для чтения в бинарном режиме
	if (!in) { cout << "Ошибка! Невозможно открыть файл: " << bin << endl; }
	ofstream fout(file, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << file << endl; }
	while (!in.eof())
	{
		if (i % 3 == 0)
		{
			if (str > max) 
			{
				max = str;
			}
			str = "";
		}
		in.read((char*)&c, sizeof(c));
		if (in.eof())
		{
			break;
		}
		str += c;
		i++;
	}
	fout << "Максимальная по коду строка: " << max;
	in.close(); // Закрыли бинарный файл данных
	fout.close(); // Закрыли выходной файл
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char data[] = "list_data.txt";
	List a;
	a.read_from_file(data); // чтение из файла
	cout << setup << "" << endl;
	cout << "Вывод списка\n";
	cout << setup << "" << endl;
	cout << a << endl;
	cout << setup << "" << endl;
	cout << "===== Поиск элемента списка: =====" << endl;
	cout << setup << "" << endl;
	a.find_element("aaa");
	a.find_element("hhh");
	a.find_element("eee");
	a.find_element("dfs");
	a.find_element("aaa8");
	cout << endl << setup << "" << endl;
	cout << "===== Удаление элемента списка: =====" << endl;
	cout << setup << "" << endl;
	a -= ("ddd");
	a -= ("aaa");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	cout << endl << setup << "" << endl;
	cout << "===== Вывод списка после удаления элементов =====\n";
	cout << setup << "" << endl;
	cout << a << endl;
	a.delete_list();
	cout << setup << "" << endl;
	cout << "===== Вывод списка после удаления целиком =====\n";
	cout << setup << "" << endl;
	cout << a << endl;

	// Работа с бинарным файлом
	char bin[] = "binary.bin";
	char res[] = "results.txt";
	ofstream fout(res, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << res << endl; }
	readTxtWriteBin(data, bin);
	fout << setup << "" << endl;
	fout << "===== Вывод содержимого бинарного файла =====\n";
	fout << setup << "";
	fout.close();
	readBinWriteTxt(bin, res);
    fout.open(res, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << res << endl; }
	fout << setup << "" << endl;
	fout << "===== Вывод после модификации =====\n";
	fout << setup << "";
	fout.close();
	modBin(bin);
	readBinAppendTxt(bin, res);
	fout.open(res, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << res << endl; }
	fout << setup << "" << endl;
	fout << "===== Вывод после удаления =====\n";
	fout << setup << "";
	fout.close();
	delBin(bin);
	readBinAppendTxt(bin, res);
	fout.open(res, ios::app);
	if (!fout) { cout << "Ошибка! Невозможно открыть файл: " << res << endl; }
	fout << setup << "" << endl;
	fout << "==== Арифметическая обработка бинарного файла ====\n";
	fout << setup << "" << endl;
	fout.close();
	procBin(bin, res);
	return 0;
}