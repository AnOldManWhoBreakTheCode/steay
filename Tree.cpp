#include <cstdio>
#include <cstdlib>

class BynaryNode {
protected:
	int data;
	BynaryNode* left;
	BynaryNode* right;

public:
	BynaryNode(int data_ = 0, BynaryNode* left_ = NULL, BynaryNode* right_ = NULL)
		:data(data_), left(left_), right(right_) {}

	//BynaryNode(int data_) : data(data_) {}

	void setData(int data_) { data = data_; }

	void setLeft(BynaryNode* left_) { left = left_; }

	void setRight(BynaryNode* right_) { right = right_; }

	int getData() { return data; }

	BynaryNode* getLeft() { return left; }

	BynaryNode* getRight() { return right; }

	bool isLeaf() { return left == NULL && right == NULL; }

};


class BynaryTree {
protected:
	BynaryNode* root;

public:
	BynaryTree(BynaryNode* root_) : root(root_) {}

	BynaryTree() : root(NULL) {}

	void setRoot(BynaryNode* root_) { root = root_; }

	BynaryNode* getRoot() { return root; }

	bool isEmpty() { return root == NULL; }

	int getCount() { return isEmpty() ? 0 : getCount(root); }		//override

	int getCount(BynaryNode* node) {

		if (node == NULL) return 0;		//base case , The smallest problem

		else return 1 + getCount(node->getLeft()) + getCount(node->getRight()); // recursion but, not tail recursion
	}

	int getHeight() { return isEmpty() ? 0 : getHeight(root); }

	int getHeight(BynaryNode* node) {

		if (node == NULL) return 0;

		else {
			int left_height = 1 + getHeight(node->getLeft());

			int right_height = 1 + getHeight(node->getRight());		//메모리를 너무 많이 잡아먹지 않을까?

			if (left_height >= right_height) return left_height;
			else return right_height;
		}
	}

	int getLeafCount() { return getLeafCount(root); }

	int getLeafCount(BynaryNode* node) {
		if (node == NULL) return 0;

		else if (node->isLeaf()) return 1;

		else {
			return getLeafCount(node->getLeft())
				+ getLeafCount(node->getRight());
		}
	}
	void inorder() { return inorder(root); }

	void inorder(BynaryNode* node) {
		if (node != NULL) {
			inorder(node->getLeft());
			printf("%d ", node->getData());
			inorder(node->getRight());
		}
	}

	void preorder() { return preorder(root); }

	void preorder(BynaryNode* node) {
		if (node != NULL) {
			printf("%d ", node->getData());
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}

	void postorder() { return postorder(root); }

	void postorder(BynaryNode* node) {
		if (node != NULL) {
			postorder(node->getLeft());
			postorder(node->getRight());
			printf("%d ", node->getData());
		}
	}

	bool isBalanced() {
		int left_height = getHeight(root->getLeft());
		int right_height = getHeight(root->getRight());

		return abs(left_height - right_height) <= 1;
	}

	int pathCount(int data) {
		if (root == NULL)
			return 0;

		else
			return pathCount(root, 0, data);
	}

	int pathCount(BynaryNode* node, int curv, int data) {

		curv += node->getData();

		//printf("%d\n", curv);

		if (curv > data) return 0;

		else if (curv == data) return 1;

		else {
			if (node->getLeft() == NULL && node->getRight() == NULL) return 0;

			else if (node->getLeft() != NULL && node->getRight() != NULL) {
				return
					pathCount(node->getLeft(), curv, data)
					+ pathCount(node->getRight(), curv, data);
			}

			else if (node->getLeft() == NULL) {
				return
					pathCount(node->getRight(), curv, data);
			}

			else if (node->getRight() == NULL) {
				return
					pathCount(node->getLeft(), curv, data);
			}

		}

	}

};

class BinScrTree : public  BynaryTree {
public:

	BynaryNode* search(BynaryNode* node, int key) {
		while (node != NULL) {
			if (key == node->getData()) return node;

			else if (key < node->getData()) node = node->getLeft();

			else node = node->getRight();
		}

		return NULL;
	}

	BynaryNode* search(int key) { return search(root, key); }

	void insert(BynaryNode* r, BynaryNode* n) {
		if (n->getData() == r->getData())
			return;


		else if (n->getData() < r->getData()) {
			if (r->getLeft() == NULL)
				r->setLeft(n);

			else
				insert(r->getLeft(), n);
		}

		else {
			if (r->getRight() == NULL)
				r->setRight(n);

			else
				insert(r->getRight(), n);
		}
	}

	void insert(BynaryNode* n) {
		if (n == NULL) return;

		if (isEmpty()) root = n;

		else insert(root, n);
	}

	void remove(BynaryNode* parent, BynaryNode* node) {
		//case 1
		if (node->isLeaf()) {
			if (parent == NULL)
				root = NULL;

			else {
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}
		//case 2
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			BynaryNode* child = (node->getLeft() != NULL)
				? node->getLeft() : node->getRight();

			if (node == root) root = child;

			else {
				if (parent->getLeft() == node) parent->setLeft(child);

				else parent->setRight(child);
			}
		}

		//case3
		else {
			BynaryNode* succp = node;	// node
			BynaryNode* succ = node->getRight();

			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();	// 오른쪽 서브트리중에 가장 작은값
			}

			if (succp->getLeft() == succ)			//일반적인 경우
				succp->setLeft(succ->getRight());	//교체될 노드의 왼쪽 자식 노드는 NULL이니 오른쪽 자식 노드를 setleft

			else
				succp->setRight(succ->getRight());	//오른쪽 자식 노드가 곧바로 교체할 노들일 시 setRight

			node->setData(succ->getData());	//입력된 노드를 삭제하는 방식이 아니라 값을 바꾸는 식으로 작동.

			node = succ;		//node에 넣을 값을 뽑아낸 자식 노드를 삭제함
		}

		delete node;
	}

	void remove(int key) {
		if (isEmpty()) return;	//void 형 일때 사용하는 return 값

		BynaryNode* parent = NULL;
		BynaryNode* node = root;

		while (node != NULL && node->getData() != key) {
			parent = node; //node가 가리키는 Bynarynode 주소가 바뀔 예정이므로 부모노드에 값을 저장

			node = (key < node->getData())
				? node->getLeft() : node->getRight();
		}

		if (node == NULL) {
			printf("Error : key is not in the tree\n");
			return;
		}

		else remove(parent, node);
	}
};


int main() {
	
	BinScrTree tree;
	int iter;
	int data;
	char ch;
	int dtnum;

	fscanf(stdin, "%d %d", &iter, &dtnum);

	getc(stdin);	// 개행문자 제거용

	for (int i = 0; i < iter; i++) {
		fscanf(stdin, "%c %d", &ch, &data);
		
		getc(stdin);		//개행문자 제거용

		if (ch == 'D') tree.remove(data);

		else tree.insert(new BynaryNode (data));

	}
	

	printf("%d", tree.pathCount(dtnum));

	
	return 0;
}