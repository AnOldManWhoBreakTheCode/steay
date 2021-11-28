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
		printf("%d ", key);
	}
};

class MiniHeap {
private:
	HeapNode node[MAX_ELEMENT];
	int size;

public:
	MiniHeap() : size(0) {}

	bool isEmpty() { return size == 0; }

	bool isFull() { return size == MAX_ELEMENT - 1; } //������ ���Ǹ� ���� node[0] �� ������� �ʱ� ������ �ְ� ����� - 1�� ���ش�.

	HeapNode& getParent(int i) { return node[i / 2]; }	//�θ� ���

	HeapNode& getLeft(int i) { return node[i * 2]; }	//���� �ڽ� ���

	HeapNode& getRight(int i) { return node[i * 2 + 1]; }	// ������ �ڽ� ���

	/*������ ��ȯ != ������ ��ȯ	*/

	void insert(int key_) {// ���Կ���
		if (isFull()) return;	//�������� ���� Ȯ��
		int i = ++size;		//���ο� ��尡 ���� �� ��ġ�� size++

		while (i != 1 && key_ < getParent(i).getKey()) { 

			node[i] = getParent(i);
			i /= 2;		//������ �����̱⿡ Ȧ���� �˾Ƽ� ������ ������.
		}

		/*node�� root�̰ų� �θ��庸�� ũ���������� ����ؼ� �θ��带 �Ʒ��� ���� �����´�*/

		node[i].setKey(key_);	//node ������ �־�� �� �ڸ��� ã�����Ƿ� �Է¹��� Ű���� ����

	}

	HeapNode remove() {
		if (isEmpty()) return NULL;		//��������

		HeapNode item = node[1];	//���� ��� = root node
		HeapNode last = node[size--]; //������ ���/ ���� ������ size�� �ϳ� ����

		int parent = 1;
		int child = 2;

		while (child <= size) {

			if (child < size && getLeft(parent).getKey() > getRight(parent).getKey())
				child++;
			/*������ ��尡 ���� ��庸�� ���� ���� ������ ������ ����ø� ��带 ������ ���� �Ҽ� �ְ� child++ �� �Ѵ�.
			�׷��� ���� �߿� �ϳ��� child < size �̴�	*/

			if (last.getKey() <= node[child].getKey())
				break;
			// ������ ��尡 �ڽĳ��� �߿� ���� ���� ���� ��� ���� ������ �װ��� �����ؾ� �� ���

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

		for (int i = 1; i <= size; i++) {

			//if (i == level) {
			//	printf("\n");
			//	level *= 2;		//Ʈ���� ������ �ٲ� �� ���� ���๮�ڸ� �߰��ϴ� �˰���. ���� �Ź��ϴ�.
			//}					//����� ����.

			node[i].display();
		}

		//printf("\n-----------------------------------------");
	}
};

int main() {

	int num, outnum;
	int data[100];
	MiniHeap heap;



	fscanf(stdin, "%d %d", &num, &outnum);

	getc(stdin);

	for (int i = 1; i <= num; i++)
		fscanf(stdin, "%d", &data[i]); getc(stdin);


	for (int i = 1; i <= num; i++)
		heap.insert(data[i]);

	heap.display();

	printf("\n");

	for (int i = 1; i <= outnum; i++)
		heap.remove();

	heap.display();


	return 0;
}