#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

/*
This class deals with the End and period (.) statements in the interpreter.
It will set the interpreter's counter to 1 more than the "actual" number of lines in the program.
*/

class EndStatement: public Statement
{
public:
    ~EndStatement();
    
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif