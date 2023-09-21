#include "GotoStatement.h"

// Initializes the Goto statement
GotoStatement::GotoStatement(int linenum) : line_num(linenum) {

}

GotoStatement::~GotoStatement() {}

void GotoStatement::execute(ProgramState * state, std::ostream &outf) {

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