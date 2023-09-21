// LetStatement.cpp:
#include "LetStatement.h"

// Initializes the Let statement
LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
}

LetStatement::~LetStatement() {}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, std::ostream &outf)
{
	state->letStatement(m_variableName, m_value);
	// Moves to the next instruction
	state->setCounter(state->getCounter()+1);
}
