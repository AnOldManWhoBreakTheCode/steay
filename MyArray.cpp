#include <iostream>

namespace MyArray {

	class Array;
	class Int;

	class Array {

		friend class Int;

		const int dim;
		int* size;

		struct Address {
			int level;
			void* next;	//실제 데이터를 저장하는 구조체가 아니라 중간 다리 역활을 하는 구조체
		};
		Address* top;



	public:
		Int operator[](const int index);

		Array(int dim_, int* array_size) : dim(dim_) {
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = array_size[i];
			/*dim -> 몇 차원인 지 입력, size 배열 -> 각 레벨에 할당되어야 하는 배열의 크기(원소의 수) 를
			저장하고 있는 배열 ex) size[4][3][2] 이면 배열의 원소는 (4, 3, 2) 가 될것임 */

			top = new Address;
			top->level = 0;

			initialize_address(top);

		}

		Array(const Array& arr) : dim(arr.dim) {
			size = new int[arr.dim];
			for (int i = 0; i < arr.dim; i++) size[i] = arr.size[i];

			top = new Address;
			top->level = 0;

			initialize_address(top);

			copy_address(top, arr.top);
		}

		void copy_address(Address* dst, const Address* src) {
			if (!dst || !src) return;	//Address 포인터 중 한개라도 NULL이면, return

			if (dst->level == dim - 1) {
				for (int i = 0; i < size[dst->level]; i++)
					static_cast <int*> (dst->next)[i] = static_cast <int*> (src->next)[i];
				return;
			}

			for (int i = 0; i < size[dst->level]; i++) {
				copy_address(static_cast <Address*> (dst->next) + i, static_cast <Address*> (src->next) + i);
			}

			//void* next로 정의했기 때문에 사용 할 때 꼭 casting을 해줘야 한다....
		}

		~Array() {
			delete_address(top);
			delete[] size;

			//소멸자.. 할당되어있는 모든 배열을 해제해준다.
		}

		void initialize_address(Address* current) {
			if (!current) return;
			if (current->level = dim - 1) {
				current->next = new int[size[current->level]];
				return;	//base case 실제, 데이터를 저장하는 마지막 레벨에 대해 할당
			}
			current->next = new  Address[size[current->level]];	//마지막 레벨이 아닐 때, 중간 다리 일 때
			for (int i = 0; i != size[current->level]; i++) {
				(static_cast<Address*> (current->next) + i)->level = current->level + 1;

				initialize_address(static_cast <Address*> (current->next) + i);
				/*1. 다음 레벨에 해당하는 배열의 크기(현재 레벨의 자식 노드들의 개수)만큼의 메모리를 할당해 주고
				2. 다음 레벨의 원소들의(원소는 Address구조체가 될 것임) level 변수에 현재 레벨 값 + 1을 해서 입력해 준다.
				3. 마지막으로, 모든 자식 노드들의 Address구조체에게 재귀 함수를 호출해준다 // 깊이 우선 탐색이 될것이다. */
			}
		}

		void delete_address(Address* current) {
			if (!current) return;
			for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
				delete_address(static_cast<Address*> (current->next) + i);
			}

			if (current->level == dim - 1) {
				delete[] static_cast<int*> (current->next);
			}

			delete[] static_cast<Address*> (current->next);
		}
	};

	class Int {
		void* data;

		int level;
		Array* array;

	public:
		Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL) :
			level(_level), data(_data), array(_array) {

			if (_level < 1 || index >= array->size[level - 1]) {
				data = NULL;
				return;
			}

			if (level == array->dim) {
				data = static_cast<void*>((
					static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
			}
			else {
				data = static_cast<void*>
					(static_cast<Array::Address*> (static_cast<Array::Address*>(data)->next) + index);
			}
		}

		Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

		Int& operator=(const int& a) {
			if (data) *static_cast<int*>(data) = a;
			return *this;
		}

		operator int() {
			if (data) return *static_cast<int*> (data);
			return 0;
		}

		Int operator[](const int index) {
			if (!data) return 0;
			return Int(index, level + 1, data, array);
		}

	};

	Int Array::operator[](const int index) {
		return Int(index, 1, static_cast<void*>(top), this);
	}

}

int main() {
	int size[] = { 2, 3, 4 };
	MyArray::Array arr(3, size);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
					<< std::endl;
			}
		}
	}
}