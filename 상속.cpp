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

	//���� ������

	Employee(Employee& empyee) {
		name = empyee.name;
		age = empyee.age;
		position = empyee.position;
		rank = empyee.rank;
	}

	Employee(){}

	void print_info() {
		std::cout << name << " (" << position << " , " << age << ") ==> "
			<< calculate_pay() << "����" << std::endl;
	}

	int calculate_pay() { return 200 + rank * 50;}
};

class Manager : public Employee {

	int year_of_service;

public:
	Manager(std::string name, int age, std::string position, int rank, int year_of_service)
		: year_of_service(year_of_service), Employee(name, age, position, rank) {}

	Manager(const Manager& m)	//���� ��Ű�� �ʰ� �б⸸ �� ���� const
		: Employee(m.name, m.age, m.position, m.rank), year_of_service(m.year_of_service) {}

	Manager() : Employee() {} //default ������

	int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }

	void print_info() {
		std::cout << name << " (" << position << " , " << age << ", "
			<< year_of_service << "����) ==> " << calculate_pay() << "����"
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
		if (!employee) return;	//employee�� NULL�̸� ��ȯ

		if (current_employee == alloc_employee) {
			/*�Ҵ�� �޸𸮰� �� á����*/

			Employee** temp_employee_list = employee_list;	//��� ���� list�� ���� �� ����
			//delete[] employee_list;

			alloc_employee *= 2;
			employee_list = new Employee * [alloc_employee];	//���� ũ���� 2�踦 ���Ӱ� �Ҵ�

			for (int i = 0; i < current_employee; i++)
				employee_list[i] = temp_employee_list[i];	//���Ӱ� �Ҵ��� �޸𸮿� ������ ���� ����

			delete[] temp_employee_list;

			employee_list[current_employee] = employee;	//�Է� ������ ���� employee�� ����Ʈ�� �߰�
			current_employee++;
		}

		else {
			employee_list[current_employee] = employee;
			current_employee++;
			/*���Ӱ� ���� �Ҵ��� �� �ʿ䰡 ���� �׳� ����Ʈ�� �����͸� �߰��� ���ָ� ��*/
		}
	}

	void add_manager(Manager* manager) {
		if (!manager) return;	//employee�� NULL�̸� ��ȯ

		if (current_manager == alloc_manager) {
			/*�Ҵ�� �޸𸮰� �� á����*/

			Manager** temp_manager_list = manager_list;	//��� ���� list�� ���� �� ����
			//delete[] employee_list;

			alloc_manager *= 2;
			manager_list = new Manager * [alloc_manager];	//���� ũ���� 2�踦 ���Ӱ� �Ҵ�

			for (int i = 0; i < current_manager; i++)
				employee_list[i] = temp_manager_list[i];	//���Ӱ� �Ҵ��� �޸𸮿� ������ ���� ����

			delete[] temp_manager_list;

			manager_list[current_manager] = manager;	//�Է� ������ ���� employee�� ����Ʈ�� �߰�
			current_manager++;
		}

		else {
			manager_list[current_manager] = manager;
			current_manager++;
			/*���Ӱ� ���� �Ҵ��� �� �ʿ䰡 ���� �׳� ����Ʈ�� �����͸� �߰��� ���ָ� ��*/
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
		std::cout << "�� ��� : " << total_pay << "���� " << std::endl;
	}

	~EmployeeList() {
		for (int i = 0; i < current_employee; i++)
			delete employee_list[i];

		for (int i = 0; i < current_manager; i++)
			delete manager_list[i];

		delete[] employee_list;	//�Ҹ���.. employee* �� employee**�� �� �� �Ҵ� ����
		delete[] manager_list;
	}


};




int main() {

	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
	emp_list.add_employee(new Employee("����", 34, "����", 1));
	emp_list.add_manager(new Manager("���缮", 41, "����", 7, 12));
	emp_list.add_manager(new Manager("������", 43, "����", 4, 15));
	emp_list.add_manager(new Manager("�ڸ��", 43, "����", 5, 13));
	emp_list.add_employee(new Employee("������", 36, "�븮", 2));
	emp_list.add_employee(new Employee("��", 36, "����", -2));
	emp_list.print_employee_info();
	return 0;
}