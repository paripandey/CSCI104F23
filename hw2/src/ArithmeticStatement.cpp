// ArithmeticStatement.cpp:
#include "ArithmeticStatement.h"

// Initializes the arithmetic statement
ArithmeticStatement::ArithmeticStatement(std::string variableName, std::string value, std::string operator_)
	: m_variableName( variableName ), m_value( value ), m_operator(operator_)
{}

ArithmeticStatement::~ArithmeticStatement() {}

void ArithmeticStatement::execute(ProgramState * state, std::ostream &outf)
{
	int value;

	// In case the value is a variable, find its actual value
	if (m_value[0] != '-' && (m_value[0] < '0' || m_value[0] > '9')) {
		value = state->retrieveValue(m_value);
	}

	// If not, cast the value to an int
	else {
		value = stoi(m_value);
	}

	// Division by 0 exception
	if (!value && m_operator == "/") {
		outf << "Divide by 0 exception" << std::endl;
		// Quits the program
		state->setCounter(state->getNumLines());
		return;
	}

	else {
		state->arithmeticStatement(m_variableName, value, m_operator);
		// Moves to the next instruction
		state->setCounter(state->getCounter()+1);
	}
}