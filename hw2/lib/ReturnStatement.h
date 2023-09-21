#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class ReturnStatement: public Statement
{
	
public:
	~ReturnStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif