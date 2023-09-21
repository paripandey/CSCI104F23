#ifndef ARITHMETIC_STATEMENT_INCLUDED
#define ARITHMETIC_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <string>

/*
This class deals with the 4 arithmetic operations (ADD: +, SUB: -. MULT: *, and DIV: /) in the interpreter.
The specific operation in question is stored as a string, and dealt with accordingly in the implementation.
*/

class ArithmeticStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_value;
    std::string m_operator;
	
public:
	~ArithmeticStatement();
	ArithmeticStatement(std::string variableName, std::string value, std::string operator_);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif