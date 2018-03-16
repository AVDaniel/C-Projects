#pragma once
#include "Linked List.h"

ListElement * createElement(int value, int priority);

void removeHighestPriority(List * list);

void push(List * list, int value, int priority);

int getHighestPriority(List * list);