#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Command.h"
#include "Trie.h"
#include "StackWrapper.h"
#include "Heap.h"

void loadSyntax(Trie &trie, bool hasParamater[]);
std::vector<Command> loadProgram(std::string inputFile, Trie syntaxTrie,
	bool hasParamater[], std::map<int, int> &labelPositions);
int execute(std::vector<Command> program, StackWrapper stack,
	std::map<int, int> labelPositions, Heap memory, int pos);

int main(){
	Trie syntaxTrie;
	bool hasParamater[30];
	std::map<int, int> labelPositions;
	StackWrapper stack;
	Heap memory;

	loadSyntax(syntaxTrie, hasParamater);

	std::vector<Command> program = loadProgram("count.whitespace", syntaxTrie,
		hasParamater, labelPositions);

	execute(program, stack, labelPositions, memory, -1);

	return 0;
}

void loadSyntax(Trie &syntaxTrie, bool hasParamater[]){
	std::ifstream fin ("Syntax.dat");
	std::map<std::string, CommandType> commandMap = Command::getCommandMap();
	std::string syntax;
	std::string commandType;

	if (!fin.good()){
		std::cerr << "Error: Missing syntax file" << std::endl;
		return;
	}

	//ignore leadin <
	fin.ignore();

	//loop until eof
	while (std::getline(fin, syntax, '>')){
		fin >> commandType;

		//ensure command hasn't been loaded yet
		if (commandMap.find(commandType) != commandMap.end()){
			//TODO std::cout << syntax << ':' << commandType << '|';
			syntaxTrie.insert(syntax, commandMap[commandType]);
			fin >> hasParamater[commandMap[commandType]];
		}else{
			std::cerr << "Error: Unrecognized command in syntax definitions" << std::endl;
		}

		//ignore < and newline
		fin.ignore(2);
	}
}

std::vector<Command> loadProgram(std::string inputFile, Trie syntaxTrie,
	bool hasParameter[], std::map<int, int> &labelPositions){

	std::ifstream fin (inputFile);
	std::vector<Command> program;
	Command * cmd;
	std::string parameter;

	if (!fin.good()){
		std::cerr << "Error: Missing program file" << std::endl;
		return program;
	}

	do{
		cmd = new Command(syntaxTrie.lookup(fin));

		//Set Parameter
		if (cmd->getType() != nullCmd && hasParameter[cmd->getType()]){
			std::getline(fin, parameter);
			cmd->setParameter(parameter);
		}

		//Record label positions
		if (cmd->getType() == Mark){
			if (labelPositions.find(cmd->getParameter()) == labelPositions.end()){
				labelPositions[cmd->getParameter()] = program.size();
			}else{
				std::cerr << "Error: Non-unique labels" << std::endl;
			}
		}

		program.push_back(*cmd);
	}while (cmd->getType() != nullCmd);

	//remove null command
	program.pop_back();

	return program;
}

int execute(std::vector<Command> program, StackWrapper stack,
	std::map<int, int> labelPositions, Heap memory, int pos){

	int i = (pos == -1)? 0: pos;

	while (i < program.size()){
		switch(program[i].getType()){
			case Push:
				stack.push(program[i].getParameter());
				break;
			case Duplicate:
				stack.duplicate();
				break;
			case Swap:
				stack.swap();
				break;
			case Pop:
				stack.pop();
				break;
			case Add:
				stack.add();
				break;
			case Subtract:
				stack.subtract();
				break;
			case Multiply:
				stack.multiply();
				break;
			case Divide:
				stack.divide();
				break;
			case Mod:
				stack.mod();
				break;
			case Store:
				memory.store(stack.pop(), stack.pop());
				break;
			case Retrieve:
				stack.push(memory.retrieve(stack.pop()));
				break;
			case Mark:
				break;
			case Call:
				if (execute(program, stack, labelPositions, memory,
					labelPositions[program[i].getParameter()]) == 1){

					return 1;
				}
				break;
			case Jump:
				i = labelPositions[program[i].getParameter()];
				break;
			case JumpZero:
				if (stack.pop() == 0) i = labelPositions[program[i].getParameter()];
				break;
			case JumpNegative:
				if(stack.pop() < 0) i = labelPositions[program[i].getParameter()];
				break;
			case EndSub:
				if (pos != -1) return 0;
				break;
			case End:
				return 1;
			case OutChar:
				std::cout << (char) stack.pop();
				break;
			case OutInt:
				std::cout << (int) stack.pop();
				break;
			case InChar:
			case InInt:
				stack.push(std::cin.get());
				break;
			default:
				std::cerr << "Error: Unrecognized command loaded" << std::endl;
				return -1;
		}
		i++;
	}

	std::cerr << "Error: Control reached end of program" << std::endl;
	return -1;
}
