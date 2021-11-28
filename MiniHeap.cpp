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

	bool isFull() { return size == MAX_ELEMENT - 1; } //구현의 편의를 위해 node[0] 은 사용하지 않기 때문에 최고 사이즈에 - 1를 해준다.

	HeapNode& getParent(int i) { return node[i / 2]; }	//부모 노드

	HeapNode& getLeft(int i) { return node[i * 2]; }	//왼쪽 자식 노드

	HeapNode& getRight(int i) { return node[i * 2 + 1]; }	// 오른쪽 자식 노드

	/*참조자 반환 != 포인터 반환	*/

	void insert(int key_) {// 삽입연산
		if (isFull()) return;	//예외조건 꼭꼭 확인
		int i = ++size;		//새로운 노드가 삽일 될 위치는 size++

		while (i != 1 && key_ < getParent(i).getKey()) { 

			node[i] = getParent(i);
			i /= 2;		//정수형 변수이기에 홀수는 알아서 떨어저 나간다.
		}

		/*node가 root이거나 부모노드보다 크기전까지는 계속해서 부모노드를 아래로 끌고 내려온다*/

		node[i].setKey(key_);	//node 본인이 있어야 할 자리를 찾았으므로 입력받은 키값을 대입

	}

	HeapNode remove() {
		if (isEmpty()) return NULL;		//예외조건

		HeapNode item = node[1];	//꺼낼 노드 = root node
		HeapNode last = node[size--]; //마지막 노드/ 꺼낸 다음에 size를 하나 줄임

		int parent = 1;
		int child = 2;

		while (child <= size) {

			if (child < size && getLeft(parent).getKey() > getRight(parent).getKey())
				child++;
			/*오른쪽 노드가 왼쪽 노드보다 작은 값을 가지고 있으면 끌어올릴 노드를 오른쪽 노드로 할수 있게 child++ 를 한다.
			그래서 조건 중에 하나가 child < size 이다	*/

			if (last.getKey() <= node[child].getKey())
				break;
			// 마지막 노드가 자식노드들 중에 작은 값을 가진 노드 보다 작으면 그곳이 정착해야 할 장소

			//아니면 한 단계 이동
			node[parent] = node[child];
			//값을 복사 했을 뿐이지만, node[child]에 들어 있는 값은 슥삭 해버려도 상관 없어진 상태임
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
			//	level *= 2;		//트리의 레벨이 바뀔 때 마다 개행문자를 추가하는 알고리즘. 나름 신박하다.
			//}					//기억해 두자.

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