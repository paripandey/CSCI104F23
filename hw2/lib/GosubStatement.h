#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

/*
This class deals with the GoSub statement. It will modify the ProgramState's stack. It will push the
statement's line number to it and set the interpreter's counter equal to the line number to go to,
accounting for any exceptions.
*/

class GosubStatement: public Statement
{
private:
	int goto_;
    int linenum_;

public:
	~GosubStatement ();
	GosubStatement(int go_to, int line_num);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif