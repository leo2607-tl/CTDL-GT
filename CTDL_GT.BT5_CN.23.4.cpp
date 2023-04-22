
#include <iostream>
#include <string>
using namespace std;
//Câu 1: Stack + bài tập check_bracket
struct node {
	char data;
	node* pNext;
	node* pPre;
};

struct Stack {
	node* top;
};

void Init(Stack& stack) {
	stack.top = NULL;
}

node* createNode(char bra) {
	node* newNode = new node;
	if (newNode == NULL)
		cout << "Error";
	newNode->data = bra;
	newNode->pNext = NULL;
	newNode->pPre = NULL;
	return newNode;
}

void push(Stack& stack, char bra) {
	node* newNode = createNode(bra);
	if (stack.top == NULL)
		stack.top = newNode;
	else {
		newNode->pNext = stack.top;
		stack.top->pPre = newNode; 
		stack.top = newNode;
	}
}

char pop(Stack& stack) { 
	if (stack.top == NULL)
		return '\0';
	node* p = stack.top;
	char p_data = p->data;
	stack.top = p->pNext;
	if (stack.top != NULL) {
		stack.top->pPre = NULL; 
	}
	delete p;
	return p_data;
}

void printSt(Stack stack) {
	node* temp = stack.top;
	while (temp != NULL) {
		cout << temp->data << " ;";
		temp = temp->pNext;
	}
}

bool checkSame(node* op, node* lst) {
	if (op->data == '{' && lst->data == '}') {
		return true;
	}
	else if (op->data == '[' && lst->data == ']') {
		return true;
	}
	else if (op->data == '(' && lst->data == ')') {
		return true;
	}
	else
		return false;
}

bool check_bracket(string bra) {
	Stack st{};
	for (int i = 0; i < bra.length(); i++) {
		if (bra[i] == '(' || bra[i] == '[' || bra[i] == '{') {
			push(st, bra[i]);
		}
		else if (bra[i] == ')' || bra[i] == ']' || bra[i] == '}') {
			char top = pop(st);
			if (top == '\0' || !checkSame(createNode(top), createNode(bra[i]))) {
				return false;
			}
		}
	}
	if (st.top == NULL) {
		return true;
	}
	return false;
}

//Câu 2: B_Tree + Bài tập kiểm tra LNR 
typedef struct node_tree {
	int value;
	node_tree* pRig;
	node_tree* pLef;
} tode;

typedef struct tagtree {
	tode* root;
} tree;

void tinit(tree& tree_) {
	tree_.root = NULL;
}

tode* createTode(int value) {
	tode* newTode = new tode;
	if (newTode == NULL)
		cout << "Error";
	newTode->value = value;
	newTode->pLef = NULL;
	newTode->pRig = NULL;
	return newTode;
}

void insertTode(tree& tree_, int value) {
	if (tree_.root == NULL) {
		tree_.root = createTode(value);
		return;
	}
	tode* tmp = tree_.root;
	tode* parent = NULL;
	while (tmp != NULL) {
		parent = tmp;
		if (value < tmp->value)
			tmp = tmp->pLef;
		else
			tmp = tmp->pRig;
	}
	if (value < parent->value)
		parent->pLef = createTode(value);
	else
		parent->pRig = createTode(value);
}


void showTree(node_tree* node) {
	if (node == NULL)
		return;
	showTree(node->pLef);
	cout << node->value << " ";
	showTree(node->pRig);
}

void deleteTree(tode*& node) {
	if (node == NULL)
		return;
	deleteTree(node->pLef);
	deleteTree(node->pRig);
	delete node;
	node = NULL;
}

void LNR(tode* root) {
	if (root != NULL) {
		LNR(root->pLef);
		cout << root->value << " ";
		LNR(root->pRig);
	}
}

void NLR(tode* root) {
	if (root != NULL) {
		cout << root->value << " ";
		NLR(root->pLef);
		NLR(root->pRig);
	}
}

void LRN(tode* root) {
	if (root != NULL) {
		LRN(root->pLef);
		LRN(root->pRig);
		cout << root->value << " ";
	}
}

/*
	từ thứ tự duyệt cho sẵn, ta nhận thấy NLR có root bằng 5 và Rig cuối luôn bằng 7
	đồng thời lef đầu bằng 9 và node trước nó là 1.
	Tiếp theo, ta có lef thứ 2 từ root đếm xuống là 3, theo NLR thì L tiếp theo là 1, 
	thỏa mãn node và có lef là 9, suy ra rig của 1 phải là 11 theo LNR.
	LNR có dãy 5, 6, 4, 7 và có dấu hiệu LN-NL là 6-4 và 4-6 => 4 là node còn 6 là lef của 4.
	Do 2, 10, 8 đứng trước root 5 nên bây giờ nó chỉ có thể là lef và rig của 3. 
	Theo NLR, sau khi có dãy 5, 3, 1, 9, 11 thì chắc chắn 2 phải là rig của 3 
	và theo thứ tự 2-10-8 (NLR) và 10-2-8(LNR) thì ta suy ra được 10 là lef của 2 và 8 là rig của 2.
	Từ đó ta suy ra được cây nhị phân: 
	                            5
	                        /       \
	                      3           4
                        /  \        /   \
                      1      2     6     7
                     /  \   / \ 
                   9    11 10  8  
	  =>Do đó, thứ tự duyệt LRN sẽ là: 9 11 1 10 8 2 3 6 7 4 5 
*/

int main() {
	string br;
	cout << "Nhap dau: ";
	cin >> br;
	cout << check_bracket(br);

	tree tree_; tinit(tree_);
	insertTode(tree_, 7);
	insertTode(tree_, 2);
	insertTode(tree_, 4);
	insertTode(tree_, 11);
	insertTode(tree_, 10);
	insertTode(tree_, 9);
	insertTode(tree_, 1);
	insertTode(tree_, 3);
	insertTode(tree_, 5);
	insertTode(tree_, 8);
	showTree(tree_.root);
	cout << "\nLNR: ";
	LNR(tree_.root);
	cout << "\nNLR: ";
	NLR(tree_.root);
	cout << "\nLRN: ";
	LRN(tree_.root);
}
