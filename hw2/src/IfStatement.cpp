#include "IfStatement.h"

// Initializes the If statement
IfStatement::IfStatement(std::string variableName, std::string operator_, int value, int linenum)
: m_variableName(variableName), m_operator(operator_), m_value(value), line_num(linenum)

{

}

IfStatement::~IfStatement() {}

void IfStatement::execute(ProgramState * state, std::ostream &outf) {

	bool result = false;
	// Retrieves the value of the variable
	int value = state->retrieveValue(m_variableName);

	// Outlines the possible operations
	if (m_operator == "<") {
		result = value < m_value;
	}

	else if (m_operator == ">") {
		result = value > m_value;
	}

	else if (m_operator == "<=") {
		result = value <= m_value;
	}

	else if (m_operator == ">=") {
		result = value >= m_value;
	}

	else if (m_operator == "=") {
		result = value == m_value;
	}

	else if (m_operator == "<>") {
		result = value != m_value;
	}

	// If the comparison evaluates to true
	if (result) {
		// If the line number is non-positive or doesn't exist in the program
		if (line_num <= 0 || line_num >= state->getNumLines()) {
			outf << "Illegal jump instruction" << std::endl;
			// Quits the program
			state->setCounter(state->getNumLines());
			return;
    	}
		// Goes to the specific line number in question
		state->setCounter(line_num);
	}

	// Moves to the next statement
	else {
		state->setCounter(state->getCounter()+1);
	}

}