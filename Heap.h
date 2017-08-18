#ifndef heap
#define heap

#include <map>
#include <fstream>
#include <iostream>

class Heap
{
	private:
		std::map<int, int> memory;
	public:
		void store(int value, int address);
		int retrieve(int address);
		void load();
		void save();
};

#endif
