#include "Heap.h"

void Heap::store(int value, int address){
	memory[address] = value;
}

int Heap::retrieve(int address){
	return memory[address];
}
