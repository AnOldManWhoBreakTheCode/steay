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
			void* next;	//���� �����͸� �����ϴ� ����ü�� �ƴ϶� �߰� �ٸ� ��Ȱ�� �ϴ� ����ü
		};
		Address* top;



	public:
		Int operator[](const int index);

		Array(int dim_, int* array_size) : dim(dim_) {
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = array_size[i];
			/*dim -> �� ������ �� �Է�, size �迭 -> �� ������ �Ҵ�Ǿ�� �ϴ� �迭�� ũ��(������ ��) ��
			�����ϰ� �ִ� �迭 ex) size[4][3][2] �̸� �迭�� ���Ҵ� (4, 3, 2) �� �ɰ��� */

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
			if (!dst || !src) return;	//Address ������ �� �Ѱ��� NULL�̸�, return

			if (dst->level == dim - 1) {
				for (int i = 0; i < size[dst->level]; i++)
					static_cast <int*> (dst->next)[i] = static_cast <int*> (src->next)[i];
				return;
			}

			for (int i = 0; i < size[dst->level]; i++) {
				copy_address(static_cast <Address*> (dst->next) + i, static_cast <Address*> (src->next) + i);
			}

			//void* next�� �����߱� ������ ��� �� �� �� casting�� ����� �Ѵ�....
		}

		~Array() {
			delete_address(top);
			delete[] size;

			//�Ҹ���.. �Ҵ�Ǿ��ִ� ��� �迭�� �������ش�.
		}

		void initialize_address(Address* current) {
			if (!current) return;
			if (current->level = dim - 1) {
				current->next = new int[size[current->level]];
				return;	//base case ����, �����͸� �����ϴ� ������ ������ ���� �Ҵ�
			}
			current->next = new  Address[size[current->level]];	//������ ������ �ƴ� ��, �߰� �ٸ� �� ��
			for (int i = 0; i != size[current->level]; i++) {
				(static_cast<Address*> (current->next) + i)->level = current->level + 1;

				initialize_address(static_cast <Address*> (current->next) + i);
				/*1. ���� ������ �ش��ϴ� �迭�� ũ��(���� ������ �ڽ� ������ ����)��ŭ�� �޸𸮸� �Ҵ��� �ְ�
				2. ���� ������ ���ҵ���(���Ҵ� Address����ü�� �� ����) level ������ ���� ���� �� + 1�� �ؼ� �Է��� �ش�.
				3. ����������, ��� �ڽ� ������ Address����ü���� ��� �Լ��� ȣ�����ش� // ���� �켱 Ž���� �ɰ��̴�. */
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