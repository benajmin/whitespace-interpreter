#ifndef stackWrapper
#define stackWrapper

#include <stack>

class StackWrapper
{
	private:
		std::stack<int> stack;
	public:
		void push(int a);
		int pop();
		void duplicate();
		void swap();
};

#endif
