#include "../../../../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/number.h"
#include "../../../../submodules/udemy-dsa-cpp/data-structures/stack/number.h"

#ifndef MOD_HANOI_ALGORITHM
#define MOD_HANOI_ALGORITHM

// NumberDoublyPtr Definition
using NumberDoublyPtr = NumberDoublyLinkedList<int> *;

// NumberStackPtr Definition
using NumberStackPtr = NumberStackLinkedList<int> *;

// --- Function Prototypes
void modHanoi(int nNodes, int stackLen, int *maxLen, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void moveAtoB(int stackLen, int *maxLen, int sleepFor, int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void printStacks(NumberDoublyPtr *stacks, int stackLen, int maxLen, int sleepFor, int listIndexToCheck = -1, int nodeIndexToCheck = -1);

#endif