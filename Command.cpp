#include "Command.h"
#include <iostream>

Command::Command(CommandType cmdType){
	type = cmdType;
}

int Command::getParameter(){
	return parameter;
}

void Command::setParameter(std::string inChar){
	int sign;
	int result = 0;

	if (inChar[0]==' '){
		sign = 1;
	}else if(inChar[0]=='\t'){
		sign = -1;
	}

	int len = inChar.length();

	for (int i = 1; i <= len; i++){
		if (inChar[i] == '\t'){
			result = result | (1 << (len - i - 1));
		}
	}

	parameter = result;
}

CommandType Command::getType(){
	return type;
}
