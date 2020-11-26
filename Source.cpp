#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// ����� ������
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
	// �����������1 ������ 
	List()
	{
		_size = 0;
		_head = NULL;
	}
	// �����������2 ������ (������� � ��������� ����� ��������� � ������)
	List(string x)
	{
		_size = 1;
		_head = new(list_ob);
		_head->_value = x;
		_head->_prev = NULL;
		_head->_next = NULL;
	}

	~List() {}

	// �������� ������� � ������
	void add_to_list(string x)
	{
		if (x.length() > 12)
		{
			cout << "\n ��������� ������ " << x << " ������� ������ (> 12)\n";
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

	// ���������� ��������� += ��� �������� �������� ������
	// ������� ��� ���������� ���������� � ���������
	void operator+=(string x)
	{
		this->add_to_list(x);
	}

	void read_from_file(char filename[])
	{
		ifstream fin(filename);
		if (!fin) { cout << "������! ���������� ������� ����.\n"; }
		string el;
		while (!fin.eof())
		{
			fin >> el;
			this->add_to_list(el);
		}
		fin.close();
	}

	// ����� ������ ������
	string peek()
	{
		if (_size == 0)
		{
			return "������ ����!\n";
		}
		return _head->_value;
	}
	// ����� ������
	void print_list()
	{
		if (_size == 0)
		{
			cout << "������ ����!\n";
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
	// ����� �������� � ������
	// ������� ��� ������ ���������� � ��������� 
	int find_element(string x)
	{
		if (_size == 0)
		{
			cout << "������ ����. ������ ������\n";
			return 0;
		}
		list_ob* head;
		head = _head;
		while (_head != NULL)
		{
			if (_head->_value == x)
			{
				cout << "������� \"" << x << "\" ������\n";
				_head = head;
				return 1;
			}
			_head = _head->_next;
		}
		cout << "�������� \"" << x << "\" � ������ ���\n";
		_head = head;
		return 0;
	}
	// ���������� ��������� -= ��� �������� �������� ������
	// ������� ��� �������� ���������� � ��������� 
	void operator-=(string x)
	{
		if (_size == 0)
		{
			cout << "������ ����. ������� ������.\n";
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
						cout << "������� \"" << x << "\" ������\n";
						return;
					}
					else
					{
						delete _head;
						_head = NULL;
						_size--;
						cout << "������� \"" << x << "\" ������\n";
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
					cout << "������� \"" << x << "\" ������\n";
					return;
				}
			}
			cur = cur->_next;
		}
		cout << "�������� \"" << x << "\" � ������ ���\n";
	}
	// �������� ������ �������
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
	//������� ���������� ������ ������ (���������� ���������)
	int stack_size()
	{
		return _size;
	}

	friend ostream& operator<<(ostream& os, List& q);
}; // ����� ������ ������

// ���������� ��������� << ��� ������ ������
ostream& operator<<(ostream& os, List& l)
{
	if (l._size == 0)
	{
		return os << "������ ����!\n";
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

// �������� ������������
ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50) << setfill('=');
	return stream;
}

// ������ ������ �� ����� � ������ � �������� ����
void readTxtWriteBin(char file[], char bin[])
{
	ifstream fin(file, ios::in);
	if (!fin) { cout << "������! ���������� ������� ����: " << file << endl; }
	ofstream biout;
	biout.open(bin, ios::binary | ios::out);
	if (!biout) { cout << "������! ���������� ������� ����: " << bin << endl; }
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
	fin.close(); // ������� ���� ������
	biout.close(); // ������� �������� ����
}

// ������ ��������� ����� � ����� ������ � ��������� ����
void readBinWriteTxt(char bin[], char file[])
{
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // ������� ������ ��� ������ � �������� ������
	if (!in) { cout << "������! ���������� ������� ����: " << bin << endl; }
	ofstream fout(file, ios::out);
	if (!fout) { cout << "������! ���������� ������� ����: " << file << endl; }
	fout << setup << "" << endl;
	fout << "===== ����� ����������� ��������� ����� =====\n";
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
	in.close(); // ������� �������� ���� ������
	fout.close(); // ������� �������� ����
}

// ������ ��������� ����� � ����� ������ � ��������� ����
void readBinAppendTxt(char bin[], char file[])
{
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // ������� ������ ��� ������ � �������� ������
	if (!in) { cout << "������! ���������� ������� ����: " << bin << endl; }
	ofstream fout(file, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << file << endl; }
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
	in.close(); // ������� �������� ���� ������
	fout.close(); // ������� �������� ����
}

// ����������� ��������� �����
void modBin(char bin[])
{
	char c;
	char C = 'H';
	long pos = -1;
	fstream f(bin, ios::binary | ios::in | ios:: out); // ������� ������ ��� ������ � ������ � �������� ������
	if (!f) { cout << "������! ���������� ������� ����: " << bin << endl; }
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

// �������� ������ �� ��������� �����
void delBin(char bin[])
{
	char c;
	char del = 'H';
	char C = ' ';
	int i = 0;
	long pos = -1;
	fstream f(bin, ios::binary | ios::in | ios::out); // ������� ������ ��� ������ � ������ � �������� ������
	if (!f) { cout << "������! ���������� ������� ����: " << bin << endl; }
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

// ����� ������������ �� ���� ������
void procBin(char bin[], char file[])
{
	string max = "";
	string str = "";
	char c;
	int i = 0;
	ifstream in(bin, ios::binary | ios::in); // ������� ������ ��� ������ � �������� ������
	if (!in) { cout << "������! ���������� ������� ����: " << bin << endl; }
	ofstream fout(file, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << file << endl; }
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
	fout << "������������ �� ���� ������: " << max;
	in.close(); // ������� �������� ���� ������
	fout.close(); // ������� �������� ����
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char data[] = "list_data.txt";
	List a;
	a.read_from_file(data); // ������ �� �����
	cout << setup << "" << endl;
	cout << "����� ������\n";
	cout << setup << "" << endl;
	cout << a << endl;
	cout << setup << "" << endl;
	cout << "===== ����� �������� ������: =====" << endl;
	cout << setup << "" << endl;
	a.find_element("aaa");
	a.find_element("hhh");
	a.find_element("eee");
	a.find_element("dfs");
	a.find_element("aaa8");
	cout << endl << setup << "" << endl;
	cout << "===== �������� �������� ������: =====" << endl;
	cout << setup << "" << endl;
	a -= ("ddd");
	a -= ("aaa");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	a -= ("hhh");
	cout << endl << setup << "" << endl;
	cout << "===== ����� ������ ����� �������� ��������� =====\n";
	cout << setup << "" << endl;
	cout << a << endl;
	a.delete_list();
	cout << setup << "" << endl;
	cout << "===== ����� ������ ����� �������� ������� =====\n";
	cout << setup << "" << endl;
	cout << a << endl;

	// ������ � �������� ������
	char bin[] = "binary.bin";
	char res[] = "results.txt";
	ofstream fout(res, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << res << endl; }
	readTxtWriteBin(data, bin);
	fout << setup << "" << endl;
	fout << "===== ����� ����������� ��������� ����� =====\n";
	fout << setup << "";
	fout.close();
	readBinWriteTxt(bin, res);
    fout.open(res, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << res << endl; }
	fout << setup << "" << endl;
	fout << "===== ����� ����� ����������� =====\n";
	fout << setup << "";
	fout.close();
	modBin(bin);
	readBinAppendTxt(bin, res);
	fout.open(res, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << res << endl; }
	fout << setup << "" << endl;
	fout << "===== ����� ����� �������� =====\n";
	fout << setup << "";
	fout.close();
	delBin(bin);
	readBinAppendTxt(bin, res);
	fout.open(res, ios::app);
	if (!fout) { cout << "������! ���������� ������� ����: " << res << endl; }
	fout << setup << "" << endl;
	fout << "==== �������������� ��������� ��������� ����� ====\n";
	fout << setup << "" << endl;
	fout.close();
	procBin(bin, res);
	return 0;
}