#include <bits/stdc++.h>
using namespace std;
struct TreapNod  { //node declaration
	int data;
	int priority;
	TreapNod* l, *r;
	TreapNod(int d) { //constructor
		this->data = d;
		this->priority = rand() % 100;
		this->l= this->r = nullptr;
	}
};
void rotLeft(TreapNod* &root) { //left rotation
	TreapNod* R = root->r;
	TreapNod* X = root->r->l;
	R->l = root;
	root->r= X;
	root = R;
}
void rotRight(TreapNod* &root) { //right rotation
	TreapNod* L = root->l;
	TreapNod* Y = root->l->r;
	L->r = root;
	root->l= Y;
	root = L;
}
void insertNod(TreapNod* &root, int d) { //insertion
	if (root == nullptr) {
		root = new TreapNod(d);
		return;
	}
	if (d < root->data) {
		insertNod(root->l, d);
		if (root->l != nullptr && root->l->priority > root->priority)
			rotRight(root);
	} else {
		insertNod(root->r, d);
		if (root->r!= nullptr && root->r->priority > root->priority)
			rotLeft(root);
	}
}
bool searchNod(TreapNod* root, int key) {
	if (root == nullptr)
		return false;
	if (root->data == key)
		return true;
	if (key < root->data)
		return searchNod(root->l, key);
	return searchNod(root->r, key);
}
void deleteNod(TreapNod* &root, int key) {
	//node to be deleted which is a leaf node
	if (root == nullptr)
		return;
	if (key < root->data)
		deleteNod(root->l, key);
	else if (key > root->data)
		deleteNod(root->r, key);
	//node to be deleted which has two children
	else {
		if (root->l ==nullptr && root->r == nullptr) {
			delete root;
			root = nullptr;
		}
		else if (root->l && root->r) {
			if (root->l->priority < root->r->priority) {
				rotLeft(root);
				deleteNod(root->l, key);
			} else {
				rotRight(root);
				deleteNod(root->r, key);
			}
		}
		//node to be deleted has only one child
		else {
			TreapNod* child = (root->l)? root->l: root->r;
			TreapNod* curr = root;
			root = child;
			delete curr;
		}
	}
}
void displayTreap(TreapNod *root, int space = 0, int height =10) { //display treap
	if (root == nullptr)
		return;
	space += height;
	displayTreap(root->l, space);
	cout << endl;
	for (int i = height; i < space; i++)
		cout << ' ';
	cout << root->data << "(" << root->priority << ")\n";
	cout << endl;
	displayTreap(root->r, space);
}
int main() {
	int num=1024;
	for(int i=10; i<31; ++i){
		TreapNod* root = nullptr;
		srand(time(nullptr));
		int n;
		int *array = new int[num];
		clock_t tinsert;
		tinsert = clock();
		for(int j=0; j<num ; ++j){
			array[j] = rand();
		insertNod(root, array[j]);
		}
		tinsert = clock() - tinsert;
		clock_t tsearch;
		tsearch = clock();
		for(int j=0; j<100000; ++j){
			n=rand();
			int x=searchNod(root, n);
		}
		tsearch = clock() - tsearch;
		delete []array;
		cout<<"treap,"<<i<<","<<(double)tinsert/CLOCKS_PER_SEC<<","<<(double)tsearch/CLOCKS_PER_SEC<<endl;
		num *= 2;
	}
	return 0;
}

