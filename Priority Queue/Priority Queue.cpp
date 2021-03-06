
// Priority Queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct Node {
	Node* next;
	Node* right;
	Node* left;
	int value;
	int priority;
};
typedef Node Node;

typedef struct List {
	Node* first;
	Node* last;
} List;

int isEmpty(List& list) {
	return list.first == NULL;
}

void listInit(List& list) {
	list.first = NULL;
	list.last = NULL;
}

Node* getElement(List& list, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node = list.first;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}
	return node;
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
		while ((i->next != NULL) && (i->next->value > value)) {
			i = i->next;
		}
		if (i->next == NULL) {
			list->last = node;
		}
		node->next = i->next;
		i->next = node;
	}
}

void printList(List& list) {
	for (Node* i = list.first; i != NULL; i = i->next) {
		int temp = i->value;
		printf("%d\n", temp);
	}
	printf("\n");
}


Node* createElement(int value, int priority) {
	Node* element = (Node*)malloc(sizeof(Node));
	element->value = value;
	element->priority = priority;
	element->next = NULL;
	return element;
}

void removeHighestPriority(List* list) {
	Node* element = list->first;
	list->first = list->first->next;
	free(element);
}

void push(List* list, int value, int priority) {
	Node* element = createElement(value, priority);
	pushElement(list, element);
}

int getHighestPriority(List* list) {
	return list->first->value;
}
int isEmpty(List* list) {
	return list->first == NULL;
}

Node* getNext(Node* Node) {
	return Node->next;
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

void printListValues(List* list) {
	for (Node* i = list->first; i != NULL; i = i->next) {
		int temp = i->value;
		printf("%d", temp);
	}
	printf("\n");
}

Node* getElement(List* list, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	node = list->first;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}
	return node;
}

int size(List* list) {
	int i = 0;
	for (Node* j = list->first; j != NULL; j = j->next) {
		i++;
	}
	return i;
}

int main() {
	List* list = (List*) malloc(sizeof(List));
	listInit(*list);
	push(list, 2, 2);
	push(list, 1, 1);
	push(list, 3, 3);
	printList(*list);

    return 0;
}

