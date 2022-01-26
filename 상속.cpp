#include <iostream>
#include <string>

class Employee {
protected:
	std::string name = NULL;
	int age;

	std::string position = NULL;
	int rank;

public:
	Employee(std::string name_, int age_, std::string position_, int rank_) : 
		name(name_), age(age_), position(position_), rank(rank_){}

	//복사 생성자

	Employee(Employee& empyee) {
		name = empyee.name;
		age = empyee.age;
		position = empyee.position;
		rank = empyee.rank;
	}

	Employee(){}

	void print_info() {
		std::cout << name << " (" << position << " , " << age << ") ==> "
			<< calculate_pay() << "만원" << std::endl;
	}

	int calculate_pay() { return 200 + rank * 50;}
};

class Manager : public Employee {

	int year_of_service;

public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service)
		: year_of_service(year_of_service), Employee(name, age, position, rank) {}

	Manager(const Manager& m)	//변형 시키지 않고 읽기만 할 때는 const
		: Employee(m.name, m.age, m.position, m.rank), year_of_service(m.year_of_service) {}

	Manager() : Employee() {} //default 생성자

	int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }

	void print_info() {
		std::cout << name << " (" << position << " , " << age << ", "
			<< year_of_service << "년차) ==> " << calculate_pay() << "만원"
			<< std::endl;
	}


};

class EmployeeList {
	int current_employee = 0;
	int current_manager = 0;

	int alloc_employee = 0;
	int alloc_manager = 0;

	Employee** employee_list = NULL;
	Manager** manager_list = NULL;

public:
	EmployeeList(int alloc_employee_) : alloc_employee(alloc_employee_), alloc_manager(alloc_employee_) {
		employee_list = new Employee * [alloc_employee];
		manager_list = new Manager * [alloc_manager];

		current_employee = 0;
		current_manager = 0;
	}

	void add_employee(Employee* employee) {
		if (!employee) return;	//employee가 NULL이면 반환

		if (current_employee == alloc_employee) {
			/*할당된 메모리가 다 찼으면*/

			Employee** temp_employee_list = employee_list;	//잠시 동적 list를 저장 할 변수
			//delete[] employee_list;

			alloc_employee *= 2;
			employee_list = new Employee * [alloc_employee];	//원래 크기의 2배를 새롭게 할당

			for (int i = 0; i < current_employee; i++)
				employee_list[i] = temp_employee_list[i];	//새롭게 할당한 메모리에 데이터 값을 복사

			delete[] temp_employee_list;

			employee_list[current_employee] = employee;	//입력 값으로 받은 employee를 리스트에 추가
			current_employee++;
		}

		else {
			employee_list[current_employee] = employee;
			current_employee++;
			/*새롭게 동적 할당을 할 필요가 없이 그냥 리스트에 데이터를 추가만 해주면 됨*/
		}
	}

	void add_manager(Manager* manager) {
		if (!manager) return;	//employee가 NULL이면 반환

		if (current_manager == alloc_manager) {
			/*할당된 메모리가 다 찼으면*/

			Manager** temp_manager_list = manager_list;	//잠시 동적 list를 저장 할 변수
			//delete[] employee_list;

			alloc_manager *= 2;
			manager_list = new Manager * [alloc_manager];	//원래 크기의 2배를 새롭게 할당

			for (int i = 0; i < current_manager; i++)
				employee_list[i] = temp_manager_list[i];	//새롭게 할당한 메모리에 데이터 값을 복사

			delete[] temp_manager_list;

			manager_list[current_manager] = manager;	//입력 값으로 받은 employee를 리스트에 추가
			current_manager++;
		}

		else {
			manager_list[current_manager] = manager;
			current_manager++;
			/*새롭게 동적 할당을 할 필요가 없이 그냥 리스트에 데이터를 추가만 해주면 됨*/
		}
	}

	int current_employee_num() { return current_employee + current_manager; }

	void print_employee_info() {
		int total_pay = 0;
		for (int i = 0; i < current_employee; i++) {
			employee_list[i]->print_info();
			total_pay += employee_list[i]->calculate_pay();
		}
		for (int i = 0; i < current_manager; i++) {
			manager_list[i]->print_info();
			total_pay += manager_list[i]->calculate_pay();
		}
		std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; i++)
			delete employee_list[i];

		for (int i = 0; i < current_manager; i++)
			delete manager_list[i];

		delete[] employee_list;	//소멸자.. employee* 와 employee**를 둘 다 할당 해제
		delete[] manager_list;
	}


};




int main() {

	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
	emp_list.add_manager(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.add_manager(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.add_manager(new Manager("박명수", 43, "차장", 5, 13));
	emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
	emp_list.add_employee(new Employee("길", 36, "인턴", -2));
	emp_list.print_employee_info();
	return 0;
}