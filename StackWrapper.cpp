#include "StackWrapper.h"

void StackWrapper::push(int a){
	stack.push(a);
}

int StackWrapper::pop(){
	int a = stack.top();
	stack.pop();
	return a;
}

void StackWrapper::duplicate(){
	push(stack.top());
}

void StackWrapper::swap(){
	int a = pop();
	int b = pop();

	push(a);
	push(b);
}

void StackWrapper::add(){
	int b = pop();
	int a = pop();
	push(a+b);
}

void StackWrapper::subtract(){
	int b = pop();
	int a = pop();
	push(a-b);
}

void StackWrapper::multiply(){
	int b = pop();
	int a = pop();
	push(a*b);
}

void StackWrapper::divide(){
	int b = pop();
	int a = pop();
	push(a/b);
}

void StackWrapper::mod(){
	int b = pop();
	int a = pop();
	push(a%b);
}
