#include "ProgramState.h"
#include <iostream>
#include <string>

// Initializes the Program State, which should start at line 1 (Statement 1)
ProgramState::ProgramState(int numLines) : m_numLines(numLines), counter_(1) {
}

// Sets the counter of the interpreter
void ProgramState::setCounter(int counter) {
    counter_ = counter;
}

// Gets the counter of the interpreter
unsigned int ProgramState::getCounter() {
    return counter_;
}

int ProgramState::getNumLines() {
    return m_numLines;
}

// Pushes to the ProgramState's stack (Gosub statement)
void ProgramState::push(int val) {
    stack_.push(val);
}

// Pops from the ProgramState's stack (Return statement)
void ProgramState::pop() {
    stack_.pop();
}

// Returns what's on top of the ProgramState's stack (Return statement)
int ProgramState::peek() {
    return stack_.top();
}

// Returns whether the ProgramState's stack is empty
bool ProgramState::empty() {
    return stack_.empty();
}


// Takes care of the Let statement
void ProgramState::letStatement(std::string varName, int value) {
    // Modifies the map
    tracker[varName] = value;
}

// Returns the value of a variable (0 by default for undeclared variables)
int ProgramState::retrieveValue(std::string varName) {
    std::map<std::string, int>::iterator it = tracker.find(varName);
    if (it == tracker.end()) // we didn't find the element
    {
        tracker[varName] = 0; // Initializes the new variable to 0
    }

    return tracker[varName]; // Returns the variable's value
}

// Prints the variable and its value for all variables
void ProgramState::printAll(std::ostream &outf) {
    std::map<std::string, int>::iterator it;

    for (it = tracker.begin(); it != tracker.end(); ++it) {
        outf << it->first << " " << it->second << std::endl;
    }
}

// Takes care of the Arithmetic (ADD, SUB, MULT, and DIV) statements
void ProgramState::arithmeticStatement(std::string varName, int val, std::string operator_) {
    std::map<std::string, int>::iterator it = tracker.find(varName);

    if (it == tracker.end()) // we didn't find the element
    {
        tracker[varName] = 0; // Initializes the new variable to 0
    }

    // Performs the desired operation
    if (operator_ == "+") {
        tracker[varName] += val;
    }

    else if (operator_ == "-") {
        tracker[varName] -= val;
    }

    else if (operator_ == "*") {
        tracker[varName] *= val;
    }

    else if (operator_ == "/") {
        tracker[varName] /= val;
    }
}