// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Linked List.h"
#include <stdlib.h>

struct ListElement {
	ListElement* next;
	int value;
};
typedef ListElement ListElement;

typedef struct List {
	ListElement* first;
	ListElement* last;
} List;

int main()
{
	List* list = (List*) malloc(sizeof(List));
	ListElement* listElement = (ListElement*)malloc(sizeof(ListElement));
	listElement->value = 1;
	pushBack(list, listElement);
	printListValues(list);
	return 0;

}

