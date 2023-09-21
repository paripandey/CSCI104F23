#include "ReturnStatement.h"

ReturnStatement::~ReturnStatement() {}

void ReturnStatement::execute(ProgramState * state, std::ostream &outf) {
    if (!state->empty()) {
        // Goes to the statement AFTER the most recent GoSub statement that was called
        state->setCounter(state->peek()+1);
        // Removes the Gosub statement from the stack
        state->pop();
    }
    // Ends the program; no Gosub statement to return to
    else {
        state->setCounter(state->getNumLines());
    }
}