#include <iostream>
#include <string>
#include <cstring>

size_t GetStringSize(const char* s){return strlen(s);}

size_t GetStringSize(const std::string& str){return str.size();}
//char 배열 형식과 string 형식을 모두 허용 하기 위해 두 개의 함수를 오버로딩 해준다

template <typename str, typename... strs>
size_t GetStringSize(str s, strs... ss){
    return GetStringSize(s) + GetStringSize(ss...);
}
//가변길이 템플릿을 사용해 입력된 문자열들의 데이터 크기를 구하는 함수

void AppendToString(std::string* concat_str){return;}//베이스 케이스

template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& str, Strings... strs){
    concat_str->append(str);
    AppendToString(concat_str, strs...);
}
//충분한 크기의 메모리가 할당된 string에 실질적으로 문자열을 합해주는 함수,

template <typename str>
std::string catstr(const str& s){
    return std::string(s);
}

template <typename str, typename... strs>
std::string catstr(const str& s, strs... ss){
    size_t total_size = GetStringSize(s, ss...);
    
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;

    AppendToString(&concat_str, ss...);

    return concat_str; 
}
//입력된 문자열들을 합해주는 함수. 실제 문자열을 합해주는 건 AppendToString 함수가 하지만, 이 함수는 동적메모리 할당과
//ApeendToString 함수에 인자를 전달 해 주는 기능을 한다.

int main(){

    std::cout<< catstr("오늘은", std::string("너무도"), "피곤하구나....", std::string("빨리 자야겠어"))<<std::endl;

    return 0;
}
