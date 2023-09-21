#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

/*
This class deals with the Print statement. It will either print the value of 1 variable or all the variables,
depending on what's passed in as the input string.
*/


class PrintStatement: public Statement
{
private:
	std::string m_variableName;
	
public:
	PrintStatement(std::string variableName);
	~PrintStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
