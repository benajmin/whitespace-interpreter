#include "Command.h"

Command::Command(CommandType cmdType){
	type = cmdType;
}

int Command::getParameter(){
	return parameter;
}

//return true if character is not used in any syntax (non-whitespace character)
bool isInvalid(const char &c){
	switch(c){
		case ' ':
		case '\t':
		case '\n':
			return false;
		default:
			return true;
	}
}

//converts whitespace label or number to an integer and saves to parameter
void Command::setParameter(std::string input){
	int sign;
	int result = 0;

	//remove non-whitespace characters
	input.erase(std::remove_if(input.begin(), input.end(), isInvalid), input.end());

	//determine if number is positive or negative
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

//returns map of command strings to enum values
std::map<std::string, CommandType> Command::getCommandMap(){
	std::map<std::string, CommandType> commandMap;

	commandMap["Push"] = Push;
	commandMap["Duplicate"] = Duplicate;
	commandMap["Swap"] = Swap;
	commandMap["Pop"] = Pop;
	commandMap["Add"] = Add;
	commandMap["Subtract"] = Subtract;
	commandMap["Multiply"] = Multiply;
	commandMap["Divide"] = Divide;
	commandMap["Mod"] = Mod;
	commandMap["Store"] = Store;
	commandMap["Retrieve"] = Retrieve;
	commandMap["Mark"] = Mark;
	commandMap["Call"] = Call;
	commandMap["Jump"] = Jump;
	commandMap["JumpZero"] = JumpZero;
	commandMap["JumpNegative"] = JumpNegative;
	commandMap["EndSub"] = EndSub;
	commandMap["End"] = End;
	commandMap["OutChar"] = OutChar;
	commandMap["OutInt"] = OutInt;
	commandMap["InChar"] = InChar;
	commandMap["InInt"] = InInt;

	return commandMap;
}

