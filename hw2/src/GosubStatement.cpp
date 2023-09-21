#include "GosubStatement.h"

// Initializes the Gosub statement

GosubStatement::GosubStatement(int go_to, int line_num) : goto_(go_to), linenum_(line_num) {

}

GosubStatement::~GosubStatement() {}

void GosubStatement::execute(ProgramState * state, std::ostream &outf) {
    // If the line number is non-positive or doesn't exist in the program
    if (linenum_ <= 0 || linenum_ >= state->getNumLines()) {
        outf << "Illegal jump instruction" << std::endl;
        // Quits the program
		state->setCounter(state->getNumLines());
		return;
    }
    // Pushes the current statement's line number to the stack
    state->push(linenum_);
    // Goes to the specific line number in question
    state->setCounter(goto_);
}