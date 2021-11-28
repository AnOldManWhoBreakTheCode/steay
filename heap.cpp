#include <cstdio>
#include <cstdlib>

#define MAX_ELEMENT 200

class HeapNode {
private:
	int key;

public:
	HeapNode(int key_ = 0) : key(key_) {}

	void setKey(int key_) { key = key_; }

	int getKey() { return key; }

	void display() {
		printf("%4d", key);
	}
};

class MaxHeap {
private:
	HeapNode node[MAX_ELEMENT];
	int size;

public:
	MaxHeap() : size(0) {}

	bool isEmpty() { return size == 0; }

	bool isFull() { return size == MAX_ELEMENT - 1; } //������ ���Ǹ� ���� node[0] �� ������� �ʱ� ������ �ְ� ����� - 1�� ���ش�.

	HeapNode& getParent(int i) { return node[i / 2]; }	//�θ� ���

	HeapNode& getLeft(int i) { return node[i * 2]; }	//���� �ڽ� ���

	HeapNode& getRight(int i) { return node[i * 2 + 1]; }	// ������ �ڽ� ���

	/*������ ��ȯ != ������ ��ȯ	*/

	void insert(int key_) {// ���Կ���
		if (isFull()) return;	//�������� ���� Ȯ��
		int i = ++size;		//���ο� ��尡 ���� �� ��ġ�� size++

		while (i != 1 && key_ > getParent(i).getKey()) {
			
			node[i] = getParent(i);
			i /= 2;		//������ �����̱⿡ Ȧ���� �˾Ƽ� ������ ������.
		}

		/*node�� root�̰ų� �θ��庸�� �۱��������� ����ؼ� �θ��带 �Ʒ��� ���� �����´�*/

		node[i].setKey(key_);	//node ������ �־�� �� �ڸ��� ã�����Ƿ� �Է¹��� Ű���� ����

	}

	HeapNode remove() {
		if (isEmpty()) return NULL;		//��������

		HeapNode item = node[1];	//���� ��� = root node
		HeapNode last = node[size--]; //������ ���/ ���� ������ size�� �ϳ� ����

		int parent = 1;
		int child = 2;

		while (child <= size) {

			if (child < size && getLeft(parent).getKey() < getRight(parent).getKey())
				child++;	
			/*������ ��尡 ���� ��庸�� ū ���� ������ ������ ����ø� ��带 ������ ���� �Ҽ� �ְ� child++ �� �Ѵ�.
			�׷��� ���� �߿� �ϳ��� child < size �̴�	*/

			if (last.getKey() >= node[child].getKey())
				break;
			// ������ ��尡 �ڽĳ��� �߿� ū ���� ���� ��� ���� ũ�� �װ��� �����ؾ� �� ���

			//�ƴϸ� �� �ܰ� �̵�
			node[parent] = node[child];
			//���� ���� ���� ��������, node[child]�� ��� �ִ� ���� ���� �ع����� ��� ������ ������
			parent = child;
			child *= 2;		
		}

		node[parent] = last;
		return item;
	}


	void display() {

		for (int i = 1, level = 1; i <= size; i++) {

			if (i == level) {
				printf("\n");
				level *= 2;		//Ʈ���� ������ �ٲ� �� ���� ���๮�ڸ� �߰��ϴ� �˰���. ���� �Ź��ϴ�.
			}					//����� ����.

			node[i].display();
		}

		printf("\n-----------------------------------------");
	}
};

/*�� �������� ������ ���������� �ƴ� �� ������, ���� ū ���� ���� ��µȴٴ� ������ �츮�� ���ϴ� �ڷᱸ����
Ư���� �����Ѵ�.	*/

void heapSort(int *a, int n) {
	MaxHeap h;

	for (int i = 0; i < n; i++)
		h.insert(a[i]);

	for (int i = n - 1; i >= 0; i--)
		a[i] = h.remove().getKey();
}


int main() {

	MaxHeap heap;
	int data[10];

	for (int i = 0; i < 10; i++)
		data[i] = rand() % 100;

	printf("\n������");

	for (int i = 0; i < 10; i++)
		printf("%3d", data[i]);

	heapSort(data, 10);

	printf("\n������");

	for (int i = 0; i < 10; i++)
		printf("%3d", data[i]);

	printf("\n");
	

	return 0;
}