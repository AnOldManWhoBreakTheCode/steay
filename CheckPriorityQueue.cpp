#include <cstdio>

bool CheckPriorityQueue(int data[],int num ,int parent) {
	
	if (parent > num) return true;
	/*base case1 */

	int child = parent * 2;
	//child ���� ����	�ڽ� ��� �� ���� ��带 ����Ŵ

	int child_data = (data[child] >= data[child + 1]) ? data[child] : data[child + 1];
	//�ڽ� ���� �߿� �� ū ���� ��� �θ����� ���� ���ϸ� �� �̻��� �񱳴� �ʿ�ġ ���� parent >= child 1 >= child 2

	if (data[parent] < child_data) return false;	//�ڽ� ��尡 �θ� ��庸�� Ŀ���� false

	return (data[parent] >= child_data) && CheckPriorityQueue(data, num, child) && CheckPriorityQueue(data, num, child + 1);
	/*���� parent ��尡 �ڽ� ���� ���� ũ��, ���� Ʈ�� ���鵵 �װ��� �����ϸ� True �̹Ƿ�
	&& ������ ���� ������ ��ø���״�.	*/
}

bool CheckPriorityQueue(int data[], int num) {return CheckPriorityQueue (data, num, 1); }
//���� ��� �� �� �ֵ��� �������̽� ����


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