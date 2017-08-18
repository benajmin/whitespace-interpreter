#include "Heap.h"

void Heap::store(int value, int address){
	memory[address] = value;
}

int Heap::retrieve(int address){
	return memory[address];
}

void Heap::load(){
	std::ifstream fin ("Heap.dat");
	
	int value, address;
	
	if (!fin.good()){
		std::cerr << "Error: Missing memory file" << std::endl;
		return;
	}
	
	while (fin >> address >> value){
		memory[address] = value;
	}
}

void Heap::save(){
	std::ofstream fout ("Heap.dat");
	
	if (!fout.good()){
		std::cerr << "Error: Missing memory file" << std::endl;
		return;
	}
	
	fout.flush();
	
	for (std::map<int, int>::iterator it = memory.begin(); it != memory.end(); ++it) {
    	fout << it->first << ' ' << it->second << std::endl;
	}
}
