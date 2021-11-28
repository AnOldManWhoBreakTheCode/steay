#include <cstdio>

bool CheckPriorityQueue(int data[],int num ,int parent) {
	
	if (parent > num) return true;
	/*base case1 */

	int child = parent * 2;
	//child 변수 생성	자식 노드 중 왼쪽 노드를 가르킴

	int child_data = (data[child] >= data[child + 1]) ? data[child] : data[child + 1];
	//자식 노드들 중에 더 큰 값을 골라 부모노드의 값과 비교하면 더 이상의 비교는 필요치 않음 parent >= child 1 >= child 2

	if (data[parent] < child_data) return false;	//자식 노드가 부모 노드보다 커지면 false

	return (data[parent] >= child_data) && CheckPriorityQueue(data, num, child) && CheckPriorityQueue(data, num, child + 1);
	/*현재 parent 노드가 자식 노드들 보다 크고, 서브 트리 노드들도 그것을 만족하면 True 이므로
	&& 연산을 통해 조건을 중첩시켰다.	*/
}

bool CheckPriorityQueue(int data[], int num) {return CheckPriorityQueue (data, num, 1); }
//쉽게 사용 할 수 있도록 인터페이스 제공


int main() {

	int num;
	int data[100] = {};


	fscanf(stdin, "%d", &num);

	getc(stdin);

	for (int i = 1; i <= num; i++)
		fscanf(stdin, "%d", &data[i]); getc(stdin);

	if (CheckPriorityQueue(data, num))
		printf("YES");

	else
		printf("NO");

	//printf("\n\n");

	//for (int i = 0; i < num; i++)
	//	printf("%d ", data[i]);

	return 0;
}