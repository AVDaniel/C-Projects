// Huffman Coding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define MAX_SIZE 100
#define FILENAME "C:\\Users\\Daniel\\Documents\\Visual Studio 2017\\Projects\\Exercises\\Huffman Coding\\file.txt"
#define OUTPUT_DIR "C:\\Users\\Daniel\\Documents\\Visual Studio 2017\\Projects\\Exercises\\Huffman Coding\\decoded.txt"

struct Node {
	Node* next;
	Node* right;
	Node* left;
	char key;
	int value;
	char* code;
	unsigned char byte;
};
typedef Node Node;

typedef struct List {
	Node* first;
	Node* last;
} List;

typedef struct {
	Node* root;
} BinaryTree;


int isEmpty(List* list) {
	return list->first == NULL;
}

Node* getNext(Node* node) {
	return node->next;
}

Node* getFirst(List* list) {
	return list->first;
}

void listInit(List* list) {
	list->first = NULL;
	list->last = NULL;
}

void pushFront(List* list, Node* Node) {
	if (isEmpty(list)) {
		list->first = Node;
		list->last = Node;
		list->last->next = NULL;
		list->first->next = NULL;
	}
	else {
		Node->next = list->first;
		list->first = Node;
	}
}

void pushBack(List* list, Node* Node) {
	if (isEmpty(list)) {
		list->first = Node;
		list->last = Node;
	}
	else {
		list->last->next = Node;
		list->last = Node;
	}
	Node->next = NULL;
}

void pushElement(List* list, Node* node) {
	int value = node->value;
	if (isEmpty(list)) {
		pushBack(list, node);
		return;
	}
	if (value > list->first->value) {
		node->next = list->first;
		list->first = node;
	}
	else {
		Node* i = list->first;
		while ((i->next != NULL) && (i->next->value >= value)) {
			i = i->next;
		}
		if (i->next == NULL) {
			list->last = node;
		}
		node->next = i->next;
		i->next = node;
	}
}

void printListKeys(List* list) {
	for (Node* i = list->first; i != NULL; i = i->next) {
		char temp = i->key;
		printf("%c ,", temp);
	}
	printf("\n");
}

void printListBytes(List* list) {
	for (Node* i = list->first; i != NULL; i = i->next) {
		unsigned char temp = i->byte;
		printf("%u, ", temp);
	}
	printf("\n");
}

int size(List* list) {
	int i = 0;
	for (Node* j = list->first; j != NULL; j = j->next) {
		i++;
	}
	return i;
}

Node* getElement(List* list, int index) {
	if (index >= size(list)) {
		return NULL;
	}
	Node* listElement = (Node*)malloc(sizeof(Node));
	listElement = list->first;
	for (int i = 0; i < index; i++) {
		listElement = listElement->next;
	}
	return listElement;
}

void initTree(BinaryTree& tree) {
	tree.root = NULL;
}

Node* createElement(char key, int value) {
	Node* treeElement = (Node*)malloc(sizeof(Node));
	treeElement->key = key;
	treeElement->value = value;
	treeElement->right = NULL;
	treeElement->left = NULL;

	return treeElement;
}

int isTreeEmpty(BinaryTree& tree) {
	return tree.root == NULL;
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
	Node* Node = createElement(key, value);
	addElement(tree, Node);
}

void printTree(Node* root) {
	if (root->right != NULL) {
		printTree(root->right);
	}
	printf("%c: %d\n", root->key, root->value);
	if (root->left != NULL) {
		printTree(root->left);
	}
}

Node* getElement(BinaryTree& tree, char key) {
	Node* i = tree.root;
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
	Node* Node = getElement(tree, key);
	Node->value = newValue;
}

int getValue(BinaryTree& tree, char key) {
	Node* Node = getElement(tree, key);
	return Node->value;
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

int isKeyInList(List* list, char key) {
	if (isEmpty(list)) {
		return 0;
	}
	for (int i = 0; i < size(list); i++) {
		if ((getElement(list, i) != NULL) && (getElement(list, i)->key == key)) {
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
		}
		else if ((i->key > key) && (i->left != NULL)) {
			i = i->left;
			Node* zero = createElement(0, '0');
		}
	}
}

char* getCode(char arr[], int n) {
	int codeSize = n + 1;
	char* code = (char*)malloc((codeSize) * sizeof(char));
	for (int i = 0; i < n; i++) {
		*(code+i) = arr[i];
	}
	*(code + codeSize-1) = '\0';
	return code;
}

void buildCodeTree(Node* root, BinaryTree* output, char arr[], int top) {
	if (root->left != NULL) {
		arr[top] = '0';
		buildCodeTree(root->left, output, arr, top + 1);
	}

	if (root->right != NULL) {

		arr[top] = '1';
		buildCodeTree(root->right, output, arr, top + 1);
	}

	if ((root->left == NULL) && (root->right == NULL)) {
		Node* element = createElement(root->key, 0);
		element->code = getCode(arr, top);
		printf("%c: %s\n", root->key, element->code);
		addElement(*output, element);
	}
}

void push(List* list, char key, int value) {
	Node* element = createElement(key, value);
	if (isEmpty(list)) {
		pushBack(list, element);
		return;
	}
	if (value > list->first->value) {
		element->next = list->first;
		list->first = element;
	}
	else {
		Node* i = list->first;
		while ((i->next != NULL) && (i->next->value > value)) {
			i = i->next;
		}
		if (i->next == NULL) {
			list->last = element;
		}
		element->next = i->next;
		i->next = element;
	}
}

int read10Chars(FILE* file, char buffer[11]) {
	for (int i = 0; i < 9; i++) {
		int c = getc(file);
		if (c == EOF) {
			buffer[i] = '\0';
			return 0;
		}
		buffer[i] = (char) c;
	}
	buffer[10] = '\0';
	return 1;
}

List* createList() {
	List* list = (List*)malloc(sizeof(List));
	listInit(list);
	return list;
}

List* countInstances(const char filename[]) {
	FILE* file = fopen(filename, "r+");
	List* list = createList();
	int isEOF = 0;
	while (!isEOF) {
		char string[11] = "";
		isEOF = !read10Chars(file, string);
		for (int i = 0; i <= strlen(string); i++) {
			char c = string[i];
			if (isKeyInList(list, c)) {
				getElement(list, c)->value++;
			}
			else {
				push(list, c, 1);
			}
		}
	}
	List* sortedList = createList();
	for (int i = 0; i < size(list); i++) {
		Node* node = getElement(list, i);
		push(sortedList,  node->key, node->value);
	}
	fclose(file);
	free(list);
	return sortedList;
}

void removeFirst(List* list) {
	if (isEmpty(list)) {
		return;
	}
	Node* first = list->first;
	list->first = list->first->next;
	free(first);
}

Node* popFirst(List* list) {
	Node* element = (Node*)malloc(sizeof(Node));
	*element = {
	list->first->next,
	list->first->right,
	list->first->left,
	list->first->key,
	list->first->value,
	list->first->code,
	list->first->byte
	};
	removeFirst(list);
	return element;
}

Node* removeLowestPriority(List* list) {
	if (size(list) == 1) {
		Node* node = createElement(list->first->key, list->first->value);
		node->right = list->first->right;
		node->left = list->first->left;
		free(list->first);
		list->first = NULL;
		return node;
	}
	Node* i = list->first;
	while (i->next != list->last) {
		i = i->next;
	}
	Node* node = createElement(i->next->key, i->next->value);
	node->right = i->next->right;
	node->left = i->next->left;
	free(i->next);
	i->next = NULL;
	list->last = i;
	return node;
}

void generateHuffman(List* priorityQueue) {
	while (size(priorityQueue) > 1) {
		Node* a = removeLowestPriority(priorityQueue);
		Node* b = removeLowestPriority(priorityQueue);
		int prioritySum = a->value + b->value;
		Node* sumElem = createElement(-1, prioritySum);
		sumElem->left = a;
		sumElem->right = b;
		pushElement(priorityQueue, sumElem);
	}
}

char* createSringCode(char string[], List* huffman, BinaryTree* codeTree) {
	char* code = (char*)malloc(MAX_SIZE * sizeof(char));
	int codeIndex = 0;
	for (int i = 0; i <= strlen(string); i++) {
		Node* element = getElement(*codeTree, string[i]);
		for (int i = 0; i < strlen(element->code); i++) {
			*(code + codeIndex) = element->code[i];
			codeIndex++;
		}
	}
	*(code + codeIndex) = '\0';
	return code;
}

char* decodeString(char code[], List* huffman) {
	char* string = (char*)malloc(MAX_SIZE * sizeof(char));
	Node* j = huffman->first;
	int stringIndex = 0;

	for (int i = 0; i < strlen(code); i++) {
		if (code[i] == '0') {
			j = j->left;
		}
		if (code[i] == '1') {
			j = j->right;
		}
		if ((j->right == NULL) && (j->left == NULL)) {
			if (j->key == '\0') {
				*(string + stringIndex) = 0;
				return string;
			}
			*(string + stringIndex) = j->key;
			j = huffman->first;
			stringIndex++;
		}
	}
}

unsigned char putCodeInByte(List* string) {
	unsigned char result = 0;
	unsigned char arr[] = {128, 64, 32, 16, 8, 4, 2, 1};
	for (int i = 7; i >= 0; i--) {
		Node* character = getElement(string, i);
		if ((character != NULL) && (getElement(string, i)->key == '1')) {
			result = result | arr[i];
		}
	}
	return result;
}

char* byteAsString(unsigned char byte) {
	char* result = (char*) malloc(9 * sizeof(char));
	unsigned char arr[] = {128, 64, 32, 16, 8, 4, 2, 1};
	for (int i = 7; i >= 0; i--) {
		if ((arr[i] & byte) == 0) {
			result[i] = '0';
		}
		else {
			result[i] = '1';
		}
	}
	*(result + 8) = '\0';
	return result;
}	

List* createSringCodeLoop(char createSringCodedString[]) {
	List* queue = createList();
	List* bytes = createList();
	for (int i = 0; i < strlen(createSringCodedString); i++) {
		Node* character = createElement(createSringCodedString[i], 0);
		pushBack(queue, character);
	}
	while (!isEmpty(queue)) {
		unsigned char byte = putCodeInByte(queue);
		Node* byteNode = (Node*)malloc(sizeof(Node));
		byteNode->byte = byte;
		pushBack(bytes, byteNode);
		for (int i = 0; i < 8; i++) {
			removeFirst(queue);
		}
 	}
	return bytes;
}

char* decodeLoop(List* bytes, List* huffman) {
	char* result = (char*)malloc(MAX_SIZE);
	*result = '\0';
	while (!isEmpty(bytes)) {
		unsigned char byte = popFirst(bytes)->byte;
		char* code = byteAsString(byte);
		strcat_s(result, MAX_SIZE, code);
	}
	return decodeString(result, huffman);
}

void encode(char* string, List * huffman, BinaryTree * codeTree, FILE* outputFile) {
		char* code = createSringCode(string, huffman, codeTree);
		printf("code: %s\n", code);
		List* bytes = createSringCodeLoop(code);
		while (!isEmpty(bytes)) {
			fputc(popFirst(bytes)->byte, outputFile);
		}
}

void decode(FILE* outputFile, List* huffman) {
	char* decodedString = decodeLoop(bytes, huffman);
}

int main() {
	List* huffman = countInstances(FILENAME);
	BinaryTree* codeTree = (BinaryTree*)malloc(sizeof(BinaryTree));
	initTree(*codeTree);
	generateHuffman(huffman);
	char arr[MAX_SIZE];
	buildCodeTree(huffman->first, codeTree, arr, 0);
	int isEOF = 0;
	FILE* inputFile = fopen(FILENAME, "r+");
	FILE* outputFile = fopen(OUTPUT_DIR, "w");
	while (!isEOF) {
		char string[11] = "";
		isEOF = !read10Chars(inputFile, string);
		encode(string, huffman, codeTree, outputFile);
	}
	return 0;
}

