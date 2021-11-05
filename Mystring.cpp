#include <iostream>

class Mystring {
private:
	char* string_content;		//문자열을 동적으로 할당할 때 사용할 포인터 변수
	int string_length;			// string의 길이를 나타내는 정수현 변수

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

	int length() const { return string_length;}		//문자열의 길이를 구하는 함수

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
						std::cout << "찾으시는 문자열의 위치는 " << i << "번째 부터 시작입니다." << std::endl;
						return true;
					}
				}
			}
		}
		std::cout << "찾으시는 문자열이 없습니다." << std::endl;
		return false;
	}

	void compare(const char* ch) {		//크기 비교 함수
		signed int num = string_length - strlen(ch);

		if(num == 0) std::cout << "문자열의 크기가 같습니다." << std::endl;
			
		else if(num > 0) std::cout << "문자열의 크기가 " << num <<  " 만큼 큽니다." << std::endl;
		
		else std::cout << "문자열의 크기가 " << abs(num) << " 만큼 작습니다." << std::endl;
	}
	

};

int main() {

	Mystring str("i keep walking steadilly and definitely");

	str.print();

	str.find("defin");

	str.compare("it's time for rest i am going to have lunch and use the washing machine");


	

	
	
	return 0;
}