#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

/*
This class deals with the Goto statement. It will set the interpreter's counter equal to the
specific line number to go to, accounting for any exceptions.
*/

class GotoStatement: public Statement
{
private:
	int line_num;

public:
	~GotoStatement();
	GotoStatement(int linenum);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif