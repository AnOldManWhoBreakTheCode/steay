#include <iostream>

class Mystring {
private:
	char* string_content;		//���ڿ��� �������� �Ҵ��� �� ����� ������ ����
	int string_length;			// string�� ���̸� ��Ÿ���� ������ ����

public:
	Mystring(char ch) {
		string_content = new char[1];
		string_content[0] = ch;
		string_length = 1;
	}

	Mystring(const char* ch) {
		string_length = strlen(ch);
		string_content = new char[string_length];

		for (int i = 0; i != string_length ; i++)
			string_content[i] = ch[i];

	}

	Mystring(const Mystring& str) {
		string_length = str.string_length;
		string_content = new char[string_length];

		for (int i = 0; i != string_length; i++)
			string_content[i] = str.string_content[i];
	}

	~Mystring() {
		delete[] string_content;
	}

	int length() const { return string_length;}		//���ڿ��� ���̸� ���ϴ� �Լ�

	void print() {
		for (int i = 0; i != string_length; i++) {
			std::cout << string_content[i];
		}
		std::cout << std::endl;

	}

	void assign(const char* ch) {

		delete[] string_content;

		string_length = strlen(ch);
		string_content = new char[string_length];

		for (int i = 0; i != string_length; i++)
			string_content[i] = ch[i];
	}

	void insert(int pos, const char* ch) {
		for (int i = pos; i < pos + strlen(ch); i++)
			string_content[i] = ch[i - pos];
	}

	void earase(int pos, int num) {
		char* str = new char[string_length];
		for (int i = 0; i != string_length; i++)
			str[i] = string_content[i];

		delete[] string_content;

		string_length = string_length - num;

		string_content = new char[string_length];

		for (int i = 0; i != pos; i++)
			string_content[i] = str[i];				//wtf

		for (int i = pos; i != string_length; i++)
			string_content[i] = str[i + num];

		delete[] str;
			
	}

	bool find(const char* ch) {

		for (int i = 0; i != string_length; i++) {
			if (string_content[i] == ch[0] && i < (string_length - strlen(ch))) {
				for (int j = 0; j != strlen(ch); j++) {
					if (string_content[i + j] != ch[j]) break;
					if (j == (strlen(ch) - 1)) {
						std::cout << "ã���ô� ���ڿ��� ��ġ�� " << i << "��° ���� �����Դϴ�." << std::endl;
						return true;
					}
				}
			}
		}
		std::cout << "ã���ô� ���ڿ��� �����ϴ�." << std::endl;
		return false;
	}

	void compare(const char* ch) {		//ũ�� �� �Լ�
		signed int num = string_length - strlen(ch);

		if(num == 0) std::cout << "���ڿ��� ũ�Ⱑ �����ϴ�." << std::endl;
			
		else if(num > 0) std::cout << "���ڿ��� ũ�Ⱑ " << num <<  " ��ŭ Ů�ϴ�." << std::endl;
		
		else std::cout << "���ڿ��� ũ�Ⱑ " << abs(num) << " ��ŭ �۽��ϴ�." << std::endl;
	}
	

};

int main() {

	Mystring str("i keep walking steadilly and definitely");

	str.print();

	str.find("defin");

	str.compare("it's time for rest i am going to have lunch and use the washing machine");


	

	
	
	return 0;
}