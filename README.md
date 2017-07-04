# Whitespace Interpreter

## Getting Started

### Prerequisites

### Installing

## Usage

### Syntax

The only lexical tokens in	the	whitespace language	are	Space	(ASCII 32),	Tab	(ASCII 9) and Line Feed	(ASCII 10). 

Each command consists of	a	series	of tokens, beginning	with the Instruction	Modification	Parameter (IMP). These are listed	in the	table below.


|IMP         |Meaning           |
|------------|------------------|
|[Space]     |Stack Manipulation|
|[Tab][Space]|Arithmetic        |
|[Tab][Tab]  |Heap access       |
|[LF]        |Flow Control      |
|[Tab][LF]   |I/O               |

The virtual machine on which programs	run	has a stack and a	heap. The	programmer	is free to push arbitrary	width	integers	onto the stack . The heap	can also be accessed by the user as	a	permanent store	of	variables	and data structures.

Many	commands require numbers	or labels as parameters. Numbers	can	be	any number of	bits wide,	and	are simply represented as a	series of	[Space] and [Tab], terminated by	a	[LF]. [Space]	represents	the binary	digit 0,	[Tab]	represents 1. The sign of	a number	is	given by its first character,	[Space]	for positive and [Tab]	for negative. Note	that	this is not twos complement,	it just indicates a sign.

Labels	are simply [LF]	terminated lists	of spaces	and	tabs. There is only one	global namespace	so all labels must be	unique.

#### Stack Manipulation [Space]	

|Command      |Parameter|Meaning                      |
|-------------|---------|-----------------------------|
| [Space]     | Number  | Push number onto stack      |
| [LF][Space] | -       | Duplicate top item on stack |
| [LF][Tab]   | -       | Swap top 2 items on stack   |
| [LF][LF]    | -       | Discard top item on stack   |

#### Arithmetic [Tab][Space]

Arithmetic commands operate	on the	top two items on the stack, and	replace them with the	result of	the	operation. The first item pushed	is considered	to be left of the operator.

| Command        | Parameter | Meaning          |
|----------------|-----------|------------------|
| [Space][Space] | -         | Addition         |
| [Space][Tab]   | -         | Subtraction      |
| [Space][LF]    | -         | Multiplication   |
| [Tab][Space]   | -         | Integer Division |
| [Tab][Tab]     | -         | Modulo           |

#### Heap Access [Tab][Tab]

| Command | Parameter | Meaning                                              |
|---------|-----------|------------------------------------------------------|
| [Space] | -         | Pop value _a_ then address _b_ <br> Store _a_ at _b_ |
| [Tab]   | -         | Pop address _a_ <br> Push value stored at _a_        |

#### Flow Control [LF]

| Command        | Parameter | Meaning                                                  |
|----------------|-----------|----------------------------------------------------------|
| [Space][Space] | Label     | Mark location in program                                 |
| [Space][Tab]   | Label     | Call subroutine                                          |
| [Space][LF]    | Label     | Jump to label                                            |
| [Tab][Space]   | Label     | Pop value off stack & jump to label if value is zero     |
| [Tab][Tab]     | Label     | Pop value off stack & jump to label if value is negative |
| [Tab][LF]      | -         | End subroutine                                           |
| [LF][LF]       | -         | End program                                              |

#### I/O [Tab][LF]

| Command        | Parameter | Meaning                                 |
|----------------|-----------|-----------------------------------------|
| [Space][Space] | -         | Output character                        |
| [Space][Tab]   | -         | Output number                           |
| [Tab][Space]   | -         | Pop address _a_, input character to _a_ |
| [Tab][Tab]     | -         | Pop address _a_, input number to _a_    |