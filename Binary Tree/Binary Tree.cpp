// Binary Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct TreeElement {
	TreeElement* right;
	TreeElement* left;
	char key;
	int value;
};
typedef TreeElement TreeElement;

typedef struct {
	TreeElement* root;
} BinaryTree;

void initTree(BinaryTree& tree) {
	tree.root = NULL;
}

int isTreeEmpty(BinaryTree& tree) {
	return tree.root == NULL;
}

TreeElement* createElement(char key, int value) {
	TreeElement* treeElement = (TreeElement*)malloc(sizeof(TreeElement));
	treeElement->key = key;
	treeElement->value = value;
	treeElement->right = NULL;
	treeElement->left = NULL;

	return treeElement;
}

void addElement(BinaryTree& tree, TreeElement* element) {
	if (isTreeEmpty(tree)) {
		tree.root = element;
		tree.root->right = NULL;
		tree.root->left = NULL;
	}
	else {
		TreeElement* i = tree.root;
		while (true) {
			if (element->key >= i->key) {
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
		}
	}
}

void add(BinaryTree& tree, char key, int value) {
	TreeElement* TreeElement = createElement(key, value);
	addElement(tree, TreeElement);
}

void printTree(BinaryTree& tree, TreeElement* root) {
	if (root->right != NULL) {
		printTree(tree, root->right);
	}
	printf("%d\n", root->value);
	if (root->left != NULL) {
		printTree(tree, root->left);
	}
}

TreeElement* getElement(BinaryTree& tree, char key) {
	TreeElement* i = tree.root;
	while (i->key != key) {
		if ((i->key < key) && (i->right != NULL)) {
			i = i->right;
		}
		else if ((i->key > key) && (i->left != NULL)) {
			i = i->left;
		}
		else {
			return NULL;
		}
	}
	return i;
}

int isKeyInTree(BinaryTree& tree, char key) {
	if (!isTreeEmpty(tree)) {
		return getElement(tree, key) != NULL;
	}
	else {
		return 0;
	}
}

void setValue(BinaryTree& tree, char key, int newValue) {
	TreeElement* TreeElement = getElement(tree, key);
	TreeElement->value = newValue;
}

int getValue(BinaryTree& tree, char key) {
	TreeElement* TreeElement = getElement(tree, key);
	return TreeElement->value;
}

int main() {
	BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	initTree(*tree);
	TreeElement* elm0 = createElement('4', 13);
	TreeElement* elm1 = createElement('4', 13);
	TreeElement* elm2 = createElement('5', 8);
	TreeElement* elm3 = createElement('2', 581);
	TreeElement* elm4 = createElement('8', 31);
	TreeElement* elm5 = createElement('7', 12);
	TreeElement* elm6 = createElement('3', 5);
	add(*tree, '3', 53);
	add(*tree, '4', 235);
	add(*tree, '5', 84);
	add(*tree, '6', 574);
	add(*tree, '7', 23);
	add(*tree, '8', 52);
	add(*tree, '9', 8);
	add(*tree, '1', 9);
	printTree(*tree, tree->root);
	printf("\n");
	setValue(*tree, '5', 99);
	printTree(*tree, tree->root);
	return 0;
}