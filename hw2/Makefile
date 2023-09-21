BIN_DIR = bin
SRC_DIR = src
LIB_DIR = lib
CXX = g++
CPPFLAGS = -g -Wall -std=c++11 -Ilib

all: $(BIN_DIR)/.dirstamp Interpreter

Interpreter: $(SRC_DIR)/Interpreter.cpp $(BIN_DIR)/ProgramState.o $(BIN_DIR)/ArithmeticStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/GosubStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/ReturnStatement.o
	$(CXX) $(CPPFLAGS) $^ -o $@
	
$(BIN_DIR)/ProgramState.o: $(SRC_DIR)/ProgramState.cpp $(LIB_DIR)/ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/ArithmeticStatement.o: $(SRC_DIR)/ArithmeticStatement.cpp $(LIB_DIR)/ArithmeticStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/EndStatement.o: $(SRC_DIR)/EndStatement.cpp $(LIB_DIR)/EndStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/GosubStatement.o: $(SRC_DIR)/GosubStatement.cpp $(LIB_DIR)/GosubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/GotoStatement.o: $(SRC_DIR)/GotoStatement.cpp $(LIB_DIR)/GotoStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/IfStatement.o: $(SRC_DIR)/IfStatement.cpp $(LIB_DIR)/IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/LetStatement.o: $(SRC_DIR)/LetStatement.cpp $(LIB_DIR)/LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/PrintStatement.o: $(SRC_DIR)/PrintStatement.cpp $(LIB_DIR)/PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/ReturnStatement.o: $(SRC_DIR)/ReturnStatement.cpp $(LIB_DIR)/ReturnStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp