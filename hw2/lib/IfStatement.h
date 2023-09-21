#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"
#include <string>

/*
This class deals with the If statement. If the specific comparison evaluates to true, it will set the
interpreter's counter equal to the specific line number to go to, accounting for any exceptions.
*/

class IfStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_operator;
	int m_value;
	int line_num;
	
public:
	~IfStatement();
	IfStatement(std::string variableName, std::string operator_, int value, int linenum);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif