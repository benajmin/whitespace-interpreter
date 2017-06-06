#ifndef command
#define command

enum CommandType {Push, Duplicate, Swap, Pop, Add, Subtract, Multiply, Divide, Mod,
	Store, Retrieve, Mark, Call, Jump, JumpZero, JumpNegative, EndSub, End,
	OutChar, OutInt, InChar, InInt};


class Command
{
	private:
		CommandType type;
		int parameter;
	public:
		Command();
		Command(CommandType type);
		int getParameter();
		void setPatameter(InChar);
};

#endif