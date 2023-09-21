// PrintStatement.cpp:
#include "PrintStatement.h"
#include <string>

// Initializes the Print statement
PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{
}

PrintStatement::~PrintStatement() {}

void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	// If we want to print the value of a single variable
	if (m_variableName != "") {
		outf << state->retrieveValue(m_variableName) << std::endl;
	}

	// If we want to print all the variables and their values (PrintAll statement)
	else {
		state->printAll(outf);
	}

	// Moves to the next statement
	state->setCounter(state->getCounter()+1);
}
