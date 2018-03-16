// Huffman Coding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Binary Tree.cpp"
#include "Priority Queue.cpp"
#include "Linked List.cpp"

struct Node {
	Node* next;
	Node* right;
	Node* left;
	char key;
	int value;
};
typedef Node Node;

void initTree(BinaryTree& tree) {
	tree.root = NULL;
}

int isTreeEmpty(BinaryTree& tree) {
	return tree.root == NULL;
}

Node* createTreeElem(char key, int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->value = value;
	node->right = NULL;
	node->left = NULL;

	return node;
}

void addElement(BinaryTree& tree, Node* element) {
	if (isTreeEmpty(tree)) {
		tree.root = element;
		tree.root->right = NULL;
		tree.root->left = NULL;
	}
	else {
		Node* i = tree.root;
		while (true) {
			if (element->key > i->key) {
				if (i->right == NULL) {
					i->right = element;
					break;
				}
				i = i->right;
			}
			if (element->key < i->key) {
				if (i->left == NULL) {
					i->left = element;
					break;
				}
				i = i->left;
			}
			else {
				return;
			}
		}
	}
}

void add(BinaryTree& tree, char key, int value) {
	Node* Node = createTreeElem(key, value);
	addElement(tree, Node);
}

void printTree(BinaryTree& tree, Node* root) {
	if (root->right != NULL) {
		printTree(tree, root->right);
	}
	printf("%d\n", root->key);
	if (root->left != NULL) {
		printTree(tree, root->left);
	}
}

Node* getElement(List* list, char key) {
	for (int i = 0; i < size(list); i++) {
		Node* element = getElement(list, i);
		if (element->key == key) {
			return element;
		}
	}
	Node* element = NULL;
	return element;
}

int isValInList(List* list, int value) {
	if (isEmpty(*list)) {
		return 0;
	}
	for (int i = 0; i < size(list); i++) {
		if ((getElement(*list, i) != NULL) && (getElement(*list, i)->value == value)) {
			return 1;
		}
	}
	return 0;
}

void traverseToChar(List* tree, List* output, char key) {
	Node* i = tree->first;
	while (i->key != key) {
		if ((i->key < key) && (i->right != NULL)) {
			i = i->right;
			Node* one = createElement(0, '1');
			addBack(output, one);
		}
		else if ((i->key > key) && (i->left != NULL)) {
			i = i->left;
			Node* zero = createElement(0, '0');
			addBack(output, zero);
		}
	}
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", arr[i]);
	}
	printf("\n");
}

void addCode(BinaryTree* tree, int code[], int n, Node* node) {

	for (int i = 0; i < n; i++) {
		add(*tree, node->key, code[i]);
	}
	printf("\n");
}

void encode(Node* root, int arr[], int top) {

	if (root->left != NULL) {
		arr[top] = 0;
		encode(root->left, arr, top + 1);
	}

	if (root->right != NULL) {

		arr[top] = 1;
		encode(root->right, arr, top + 1);
	}

	if ((root->left == NULL) && (root->right == NULL)) {
		printf("%c: ", root->key);
		printArray(arr, top);

	}
}


List* countInstances(char string[]) {
	List* list = (List*)malloc(sizeof(List));
	listInit(*list);
	for (int i = 0; i < strlen(string); i++) {
		if (isValInList(list, string[i])) {
			getElement(list, string[i])->value++;
		}
		else {
			push(list, string[i], 1);
		}
	}
	List* sortedList = (List*)malloc(sizeof(List));
	listInit(*sortedList);
	for (int i = 0; i < size(list); i++) {
		Node* Node = getElement(*list, i);
		push(sortedList, Node->key, Node->value);
	}
	return sortedList;
}

void buildTree(List* priorityQueue) {
	while (size(priorityQueue) > 1) {
		Node* a = removeLowestPriority(priorityQueue);
		Node* b = removeLowestPriority(priorityQueue);
		int prioritySum = a->value + b->value;
		Node* sumElem = createElement(prioritySum, 0);
		sumElem->left = a;
		sumElem->right = b;
		pushElement(priorityQueue, sumElem);
	}
}


int main() {
	char string[] = "yes";
	List* list = countInstances(string);
	BinaryTree* huffman = (BinaryTree*)malloc(sizeof(BinaryTree));
	buildTree(list);
	int arr[100];
	encode(list->first, arr, 0);
}

