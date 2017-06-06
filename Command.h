#ifndef command
#define command

#include <string>

enum CommandType {Push, Duplicate, Swap, Pop, Add, Subtract, Multiply, Divide, Mod,
	Store, Retrieve, Mark, Call, Jump, JumpZero, JumpNegative, EndSub, End,
	OutChar, OutInt, InChar, InInt};


class Command
{
	private:
		CommandType type;
		int parameter;
	public:
		Command(CommandType type);
		int getParameter();
		void setParameter(std::string input);
		CommandType getType();
};

#endif
