// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "EndStatement.h"
#include "ArithmeticStatement.h"
#include "GotoStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include "IfStatement.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


// Turn in assignment with this main(), not the one provided in hw2_tests
int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}


void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine(line) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	int line_num;
	string type;
	string var; // will be converted to an int as necessary
	string val;

	ss << line;
	ss >> line_num;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, stoi(val));
	}

	else if ( type == "PRINT" )
	{
		ss >> var;

		statement = new PrintStatement(var);
	}

	else if ( type == "PRINTALL" )
	{
		// will correspond to ALL variables in the program
		statement = new PrintStatement("");
	}

	else if ( type == "ADD" )
	{
		ss >> var;
		ss >> val;
		statement = new ArithmeticStatement(var, val, "+");
	}

	else if ( type == "SUB" )
	{
		ss >> var;
		ss >> val;

		statement = new ArithmeticStatement(var, val, "-");
	}

	else if ( type == "MULT" )
	{
		ss >> var;
		ss >> val;
		
		statement = new ArithmeticStatement(var, val, "*");
	}


	else if ( type == "DIV" )
	{
		ss >> var;
		ss >> val;

		statement = new ArithmeticStatement(var, val, "/");
	}


	else if ( type == "GOTO" )
	{
		ss >> val;
		// Converts the line number to an int
		statement = new GotoStatement(stoi(val));
	}

	else if ( type == "IF" )
	{
		string operator_, then;
		int linenum;

		ss >> var;
		ss >> operator_;
		ss >> val;
		ss >> then; // absorbs the "THEN"
		ss >> linenum;

		statement = new IfStatement(var, operator_, stoi(val), linenum);
	}


	else if ( type == "GOSUB" )
	{
		// Converts the line number to an int
		ss >> val;
		statement = new GosubStatement(stoi(val), line_num);
	}


	else if ( type == "RETURN" )
	{
		statement = new ReturnStatement();
	}


	else if ( type == "END" || type == ".")
	{
		statement = new EndStatement();
	}

	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement*> program;
	parseProgram( inf, program );
	// Creates the program state based on the number of instructions + 1
	ProgramState* state = new ProgramState(program.size());
	
	// Program runs until the interpreter gets to a line number that doesn't exist
	while (state->getCounter() < program.size()) {
		program[state->getCounter()]->execute(state, outf);
	}

	// Deletes all the statements
	for (unsigned int i = 1; i < program.size(); ++i) {
		delete program[i];
	}

	// Deletes the program state
	delete state;
}