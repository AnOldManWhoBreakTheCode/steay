#ifndef UTILS_H
#define UTILS_H
//UTILS_H를 선언하지 않았으면 선언한다.
//중복 선언 되는 것을 막기 위해 사용되는 구문임

#include <string>
#include <iostream>

using namespace std;

namespace MyExcel{

	class Vector {
		std::string* data;
		int capacity;
		int length;

	public:
		Vector(int n = 1);
		/*Default argument 는 본체에만 쓰던가 클래스 내부 함수 선언에만 쓰던가 둘 중 하나만 해야함*/

		void push_back(std::string s);

		std::string operator[] (int i);

		void remove(int x);

		int size();

		~Vector();
	};

	Vector::Vector(int n) : data(new std::string[n]), capacity(n), length(0) {}

	void Vector::push_back(std::string s) {
		if (capacity <= length) {
			std::string* temp = new std::string[capacity * 2];

			for (int i = 0; i < length; i++)
				temp[i] = data[i];

			delete[] data;
			data = new std::string[capacity * 2];
			data = temp;

			capacity *= 2;
		}

		data[length] = s;
		length++;
	}

	std::string Vector::operator[](int i) { return data[i]; }

	void Vector::remove(int x) {
		for (int i = x + 1; i < length; i++)
			data[i - 1] = data[i];

		length--;
	}

	int Vector::size() { return length; }

	Vector::~Vector() {
		if (data)
			delete[] data;
	}

	class Stack {
		struct Node {
			Node* prev;
			std::string s; //data를 저장 할 공간

			Node(Node* prev, std::string s) : prev(prev), s(s) {}
		};

		Node* current;
		Node start;

	public:
		Stack();

		void push(std::string s);

		std::string pop();

		std::string peek();

		bool is_empty();

		~Stack();

	};

	Stack::Stack() : start(NULL, "") { current = &start; }

	void Stack::push(std::string s) {
		Node* n = new Node(current, s);
		current = n;
	}

	std::string Stack::pop() {
		if (current == &start)
			return "";

		std::string s = current->s;
		Node* prev = current;
		current = current->prev;

		delete prev;
		return s;
	}

	std::string Stack::peek() { return current->s; }

	bool Stack::is_empty() { return current == &start; }

	Stack::~Stack() {
		while (current != &start) {	// Stack이 비어있는 지 확인하는 기능도 하면서, 탈출 조건도 포함함
			Node* temp = current;
			current = current->prev;
			delete temp;
		}
	}

	class NumStack {
		struct Node {
			Node* prev;
			double s; //data를 저장 할 공간

			Node(Node* prev, double s) : prev(prev), s(s) {}
		};

		Node* current;
		Node start;

	public:
		NumStack();

		void push(double s);

		double pop();

		double peek();

		bool is_empty();

		~NumStack();

	};

	NumStack::NumStack() : start(NULL, 0) { current = &start; }

	void NumStack::push(double s) {
		Node* n = new Node(current, s);
		current = n;
	}

	double NumStack::pop() {
		if (current == &start)
			return 0;

		double s = current -> s;
		Node* prev = current;
		current = current->prev;

		delete prev;
		return s;
	}

	double NumStack::peek() { return current->s; }

	bool NumStack::is_empty() { return current == &start; }

	NumStack::~NumStack() {
		while (current != &start) {	// Stack이 비어있는 지 확인하는 기능도 하면서, 탈출 조건도 포함함
			Node* temp = current;
			current = current->prev;
			delete temp;
		}
	}

	class Table;
	//없으면 에러가 뜸
	//아직 본문을 정의하지는 않았지만, 우선 선언 해 줌으로서 Cell class에서 사용 할 수 있게 해줌
	//즉, compiler 에게 Table class 가 있다는 걸 인지 시켜줌

	class Cell {

	protected:
		int x, y;
		Table* table;
		

		std::string data;

	public:
		virtual string stringify();
		virtual int to_numeric();

		Cell(string data, int x, int y, Table* table) :
			data(data), x(x), y(y), table(table) {}
	};

	//Cell::Cell(string data, int x, int y, Table* table)
	//	: data(data), x(x), y(y), table(table) {}		왜 안되는거지?????????????????

	string Cell::stringify() { return data; }
	int Cell::to_numeric() { return 0; }


	class Table {
	protected:
		int max_row_size, max_col_size;

		Cell*** data_table;

	public:
		Table(int max_row_size, int max_col_size);

		~Table();

		void reg_cell(Cell* c, int row, int col);

		int to_numeric(const string& s);

		int to_numeric(int row, int col);

		string stringify(const string& s);
		string stringify(int row, int col);

		virtual string print_table() = 0;
		/*순수 가상합수	내용은 없고, frame 만을 제공함. */
	};

	Table::Table(int max_row_size, int max_col_size)
		: max_row_size(max_row_size), max_col_size(max_col_size) {

		data_table = new Cell * *[max_row_size];
		for (int i = 0; i < max_row_size; i++) {
			data_table[i] = new Cell * [max_col_size];
			for (int j = 0; j < max_col_size; j++)
				data_table[i][j] = NULL;
		}
	}

	Table::~Table() {
		for (int i = 0; i < max_row_size; i++) {
			for (int j = 0; j < max_col_size; j++)
				if (data_table[i][j]) delete data_table[i][j];
		}
		for (int i = 0; i < max_row_size; i++)
			delete[] data_table[i];

		delete[] data_table;
	}

	void Table::reg_cell(Cell* c, int row, int col) {
		if (!((row < max_row_size) && (col < max_col_size))) return;

		if (data_table[row][col])
			delete data_table[row][col];

		data_table[row][col] = c;
	}

	int Table::to_numeric(const string& s) {
		int col = s[0] - 'A';
		int row = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col])
				return data_table[row][col]->to_numeric();
		}

		return 0;
	}

	int Table::to_numeric(int row, int col) {
		if (row < max_row_size && col < max_col_size && data_table[row][col]) {
			return data_table[row][col]->to_numeric();
		}

		return 0;
	}

	string Table::stringify(const string& s) {
		//Cell 이름으로 받는다.

		int col = s[0] - 'A';
		int row = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col])
				return data_table[row][col]->stringify();
		}

		return 0;

	}

	string Table::stringify(int row, int col) {
		if (row < max_row_size && col < max_col_size && data_table[row][col]) {
			return data_table[row][col]->stringify();
		}

		return "";
	}

	std::ostream& operator<<(std::ostream& o, Table& table) {
		o << table.print_table();
		return o;
	}	//요렇게 하면 table을 출력할 수 있게 됨 operator....

	class TxtTable : public Table {
		string repeat_char(int n, char c);

		string col_num_to_str(int n);

	public:

		TxtTable(int row, int col);

		string print_table();
	};

	TxtTable::TxtTable(int row, int col) : Table(row, col) {}

	string TxtTable::print_table() {
		string total_table;

		int* col_max_wide = new int[max_col_size];

		for (int i = 0; i < max_col_size; i++) {
			unsigned int max_wide = 2;	//basic colum wide
			for (int j = 0; j < max_row_size; j++) {
				if (data_table[j][i] && data_table[j][i]->stringify().length() > max_wide)
					max_wide = data_table[j][i]->stringify().length();
			}

			col_max_wide[i] = max_wide;
		}
		/*각 열 (colum) 에 대해서 셀의 최대 넚이를 구해서 그 값을 열의 최대 넓이를 저장하는 배열에 저장한다. */


		total_table += "    ";
		int total_wide = 4;
		for (int i = 0; i < max_col_size; i++) {
			if (col_max_wide[i]) {
				int max_len = max(2, col_max_wide[i]);
				total_table += " | " + col_num_to_str(i);
				total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');

				total_wide += (max_len + 3);
			}
		}

		total_table += "\n";

		

		for (int i = 0; i < max_row_size; i++) {
			total_table += repeat_char(total_wide, '-');
			total_table += "\n" + to_string(i + 1);
			total_table += repeat_char(4 - to_string(i + 1).length(), ' ');

			bool new_line = true;
			int* new_line_position = new int[max_col_size];
			int prev_position = 0;

			for (int k = 0; k < max_col_size; k++)
				new_line_position[k] = 0;

			
			while (new_line) {
				new_line = false;

				//조건문에서 -1은 참을 뜻한다...
				//??????? 
				for (int j = 0; j < max_col_size; j++) {
					if (col_max_wide[j]) {
						int max_len = max(2, col_max_wide[j]);

						string s = "";
						string sub_str = "";

						if (data_table[i][j]) {
							s = data_table[i][j]->stringify();

							prev_position = new_line_position[j];
							new_line_position[j] = s.find('\n', prev_position);

							if (new_line_position[j] != -1)
								new_line = true;
							
							if (new_line_position[j] == -1) new_line_position[j] = s.length();

							sub_str = s.substr(prev_position , new_line_position[j] - prev_position - 1);

							if (prev_position == s.length() + 1)	sub_str = "";
						}

						total_table += " | " + sub_str;
						total_table += repeat_char(max_len - sub_str.length(), ' ');
					}

					
				}
				total_table += '\n';
			}

			//total_table += "\n";
		}

		return total_table;
	}

	string TxtTable::repeat_char(int n, char c) {
		string s = "";
		for (int i = 0; i < n; i++) s.push_back(c);

		return s;
	}

	string TxtTable::col_num_to_str(int n) {
		string s = "";
		if (n < 26) {
			s.push_back('A' + n);
		}
		else {
			char first = 'A' + n / 26 - 1;
			char second = 'A' + n % 26;

			s.push_back(first);
			s.push_back(second);
		}

		return s;

	}
}
#endif