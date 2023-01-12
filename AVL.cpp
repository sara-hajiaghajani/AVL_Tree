#include<iostream>
#include<string>

using namespace std;

class treeNode {
	friend class tree;
private:
	treeNode *left;
	treeNode *right;
	treeNode *parent;
	double value;
public:
	treeNode(double m_value = 0.0) {
		left = right = parent = NULL;
		value = m_value;

	}
};
class tree {


private:
	treeNode *root;


public:

	tree() {}

	int size() {
		treeNode *u = root, *prev = NULL, *next;
		int n = 0;
		while (u != NULL) {
			if (prev == u->parent) {
				n++;
				if (u->left != NULL) {
					next = u->left;
				}
				else if (u->right != NULL) {
					next = u->right;
				}
				else {
					next = u->parent;
				}

			}
			else if (prev == u->left) {
				if (u->right != NULL) {
					next = u->right;
				}
				else {
					next = u->parent;
				}
			}
			else {
				next = u->parent;
			}
			prev = u;
			u = next;
		}
		return n;
	}


	int max(int a, int b)
	{
		return (a >= b) ? a : b;
	}

	int height(treeNode *u) {
		if (u == NULL) {
			return -1;
		}
		else {
			return 1 + max(height(u->left), height(u->right));
		}
	}

	int isBalanced(treeNode *u)
	{
		int left_height;
		int right_height;
		//treeNode *u = root;

		/*if (root == NULL)
		return 1;
			*/

		left_height = height(u->left);
		right_height = height(u->right);

		if ((left_height - right_height) > 1)
		{
			return 1;
		}
		else if ((left_height - right_height) < -1)
		{
			return -1;
		}

		else {

			return 0;
		}
	}

	double find(double num) {
		treeNode *w = root;
		treeNode *z = NULL;
		while (w != NULL) {
			if (num < w->value) {
				z = w;
				w = w->left;
			}
			else if (num > w->value) {
				w = w->right;
			}
			else
			{

				return w->value;
			}

		}
		return z == NULL ? NULL : z->value;


	}

	treeNode* remove_find(double x) {
		treeNode *z = NULL;
		treeNode *w = root;
		while (w != NULL) {
			if (x < w->value) {
				w = w->left;
			}
			else if (x > w->value) {
				w = w->right;
			}
			else {
				return w;
			}
		}

		return z;
	}

	treeNode* findLast(double x) {
		treeNode *w = root;
		treeNode *prev = NULL;
		while (w != NULL) {
			prev = w;
			if (x < w->value) {
				w = w->left;
			}
			else if (x > w->value) {
				w = w->right;
			}
			else {
				return w;
			}

		}
		return prev;
	}
	bool addChild(treeNode *p, treeNode *u) {
		int m = size();
		if (p == NULL) {
			root = u;
		}
		else {
			if (u->value < p->value) {
				p->left = u;
			}
			else if (u->value > p->value) {
				p->right = u;
			}
			else {
				cout << "already in there" << endl;
				return false;
			}
			u->parent = p;
		}
		m++;
		cout << "added" << endl;
		return true;
	}

	bool add(double x) {
		treeNode *p = findLast(x);
		treeNode *u = new treeNode;
		u->value = x;
		bool a = addChild(p, u);

		if (a)
		{
			while (isBalanced(u) == 0) {
				if (u == root) {
					break;
				}
				u = u->parent;

			}
			if (isBalanced(u) == 1 || isBalanced(u) == -1) {
				cout << "balancing " << u->value;
				if (u->value == (int)u->value) {
					cout << ".0";
				}
				cout << endl;
				addBalancing(u, x);
				//cout << root->value << endl;
			}
		}
		return a;
	}


	void splice(treeNode *u) {
		int m = size();
		treeNode *s, *p;
		if (u->left != NULL) {
			s = u->left;
		}
		else {
			s = u->right;
		}
		if (u == root) {
			root = s;
			p = NULL;
		}
		else {
			p = u->parent;
			if (p->left == u) {
				p->left = s;
			}
			else {
				p->right = s;
			}
		}
		if (s != NULL) {
			s->parent = p;
		}

		m--;
	}
	void remove(double x) {
		treeNode *u = remove_find(x);
		

		if (u == NULL) {
			cout << "does not exist" << endl;
		}
		else {
			treeNode *z = new treeNode;

			if (u != root){
				z = u->parent;
			}

			if (u->left == NULL || u->right == NULL) {
				splice(u);
				delete u;
				cout << "removed" << endl;
			}
			else {
				treeNode *w = u->right;
				while (w->left = NULL) {
					w = w->left;
					u->value = w->value;
					splice(w);
					delete w;
					cout << "removed" << endl;
				}
			}

			if (z != root) {
				if (z->parent != NULL) {
					while (isBalanced(z) == 0) {
						if (z == root) {
							break;
						}
						z = z->parent;
					}
				}
			}
			if (isBalanced(z) == 1 || isBalanced(z) == -1) {
				cout << "balancing " << z->value;
				if (z->value == (int)z->value) {
					cout << ".0";
				}
				cout << endl;
				removeBalancing();
			}

		}

	}


	void leftBalance(treeNode *k2) {
		treeNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;


	}
	void rotateLeft(treeNode *u) {
		treeNode *w = u->right;
		w->parent = u->parent;
		if (w->parent != NULL) {
			if (w->parent->left == u) {
				w->parent->left = w;
			}
			else {
				w->parent->right = w;
			}
		}
		u->right = w->left;
		if (u->right != NULL) {
			u->right->parent = u;
		}
		u->parent = w;
		w->left = u;
		if (u == root) {
			root = w;
			root->parent = NULL;
		}
	}
	void rotateRight(treeNode *u) {
		treeNode *w = u->left;
		w->parent = u->parent;
		if (w->parent != NULL) {
			if (w->parent->left == u) {
				w->parent->left = w;
			}
			else {
				w->parent->right = w;
			}
		}
		u->left = w->right;
		if (u->left != NULL) {
			u->left->parent = u;

		}
		u->parent = w;
		w->right = u;
		if (u == root) {
			root = w;
			root->parent = NULL;
		}
	}
	void addBalancing(treeNode *u, double x) {
		if (isBalanced(u) == 1 && x < u->left->value) {
			rotateRight(u);
			return;
		}
		if (isBalanced(u) == -1 && x > u->right->value) {
			rotateLeft(u);
			return;
		}
		if (isBalanced(u) == 1 && x > u->left->value) {
			rotateLeft(u->left);
			rotateRight(u);
			return;

		}
		if (isBalanced(u) == -1 && x < u->right->value) {
			rotateRight(u->right);
			rotateLeft(u);
			return;

		}
	}
	void removeBalancing() {
		if (isBalanced(root) == 1 && isBalanced(root->left) >= 0) {
			rotateRight(root);
			return;

		}
		if (isBalanced(root) == 1 && isBalanced(root->left) == -1) {
			rotateLeft(root->left);
			rotateRight(root);
			return;
		}
		if (isBalanced(root) == -1 && isBalanced(root->right) <= 0) {
			rotateLeft(root);
			return;
		}
		if (isBalanced(root) == -1 && isBalanced(root->right) == 1) {
			rotateRight(root->right);
			rotateLeft(root);
			return;
		}
	}
};


int main() {

	tree a;
	/*a.add(2.0);
	a.add(2.1);
	a.add(2.2);
	a.find(3.0);
	a.remove(1.0);
	a.remove(2.0);*/

	/*a.add(1.0);
	a.add(2.0);
	a.add(3.0);
	a.add(4.0);
	a.add(5.0);
	a.add(6.0);
	a.add(7.0);
	a.remove(7.0);
	a.remove(6.0);
	a.remove(5.0);
	a.remove(4.0);*/

	string input,test,function="",num1="";
	double mynumber=0.0;
	int n;
	cin >> n;
	string *Number = new string[n];
	cin.ignore();
	for (int i = 0; i < n; i++) {
		getline(cin, input);
		Number[i] = input;
		input = "";
	}
	
	for (int i = 0; i < n; i++) {

		int z = 0;
		test = Number[i];
		function = "";
		num1 = "";
		mynumber = 0.0;

		for (int j = 0; j < test.length(); j++) {
			if (test[j] != ' ') {
				function += test[j];
			}
			if (test[j] == ' ') {
				z = j + 1;
				break;
			}
		}


		if (function == "add") {
			for (z; z < test.length(); z++) {
				if (test[z] != ' ') {
					num1 += test[z];
				}
			}
			mynumber = stod(num1);
			a.add(mynumber);
		}
		if (function == "remove") {
			for (z; z < test.length(); z++) {
				if (test[z] != ' ') {
					num1 += test[z];
				}
			}
			mynumber = stod(num1);
			a.remove(mynumber);
		}
		if (function == "find") {
			for (z; z < test.length(); z++) {
				if (test[z] != ' ') {
					num1 += test[z];
				}
			}
			mynumber = stod(num1);
			double b = a.find(mynumber);
			if (b == 0) {
				cout << "not found" << endl;
			}
			else {
				cout << b;
				if (b == (int)b){
					cout << ".0" << endl;
			}
		}
	}
	}


	/*int n;
	double x;
	cin >> n;
	string input;

	for (int i = 0; i < n; i++) {
		cin >> input;
		cin >> x;

		if (input == "add") {
			//cin >> x;
			a.add(x);
		}
		else if (input == "remove") {
			//cin >> x;
			a.remove(x);
		}
		else if (input == "find") {
			//cin >> x;
			double b = a.find(x);
			if (b == 0) {
				cout << "not found" << endl;
			}
			else {
				cout << b;
				if (b == (int)b)
					cout << ".0" << endl;
			}
		}
	}*/

	system("pause");
	return 0;
}