#include "Command.h"
#include <iostream>

Command::Command(CommandType cmdType){
	type = cmdType;
}

int Command::getParameter(){
	return parameter;
}

void Command::setParameter(std::string input){
	int sign;
	int result = 0;

	if (input[0]==' '){
		sign = 1;
	}else if(input[0]=='\t'){
		sign = -1;
	}

	int len = input.length();

	for (int i = 1; i <= len; i++){
		if (input[i] == '\t'){
			result = result | (1 << (len - i - 1));
		}
	}

	parameter = result;
}

CommandType Command::getType(){
	return type;
}
