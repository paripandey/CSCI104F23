#include <string>
#include <iostream>

// 2 helper function prototypes
void swap(std::string& in, int x, int y);
void helper(std::string prefix, std::string in);

void permutations(std::string in) {
    // Prefix of the original string "in" is the empty string ("")
    std::string prefix = "";
    // This prefix is called with "in" during the first helper function call
    helper(prefix, in);
}

void swap(std::string& in, int x, int y) {
    // Swaps the characters in indices x and y of the string "in"
    char a = in[x];
    char b = in[y];
    in[x] = b;
    in[y] = a;
}

void helper(std::string prefix, std::string in) {
    if (in.length() == 1) {
        // Prints the current prefix and the last letter of the combination
        std::cout << prefix + in << std::endl;
        return;
    }
    
    for (int i = 0; i < in.length(); ++i) {
        // Makes a copy of the original input 
        std::string in_copy = in;
        // Swaps the first letter with every other letter in the input
        swap(in_copy, 0, i);
        // Adds the 1st letter of the respective combination to the prefix
        // Recursively calls the helper function on the rest of the string
        helper(prefix + in_copy[0], in_copy.substr(1, in_copy.length()-1));
    }
}