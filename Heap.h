#ifndef heap
#define heap

#include <map>

class Heap
{
	private:
		std::map<int, int> memory;
	public:
		void store(int value, int address);
		int retrieve(int address);
};

#endif
