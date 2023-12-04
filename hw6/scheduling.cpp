/*Problem 3 (Backtracking, 35%)


5 4 3
aaron    104 170
leia 104   170 350
jarjar  101
finn  270  350
The output should be an assignment of classes to the integers between 1 and the totalber of timeslots, one class per line:

101 1
104 1
170 2
270 1
350 3
There are of course other solutions, you only need to find one that works. If there is no solution for the requested totalber of timeslots, you should output No valid solution.

You must maintain a map of each class to its timeslot, using your AVL implementation. As there is no method to update a value in a Binary Search Tree, you will need to delete the old value and insert the new value.

Since some of the function calls throw exceptions, make sure to use try and catch appropriately, even if you do not expect the catch blocks to be used.

Your Makefile should compile your program into an executable called scheduling*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "avlbst.h"
using namespace std;


// Recursive backtracking function to find a valid assignment
bool assign(int currSlot, int totalSlots, const std::vector<std::vector<int>>& allClasses, AVLTree<int, int>& tree) {
    
    if (currSlot > totalSlots) {
        return true;  // All timeslots are assigned
    }

    for (unsigned int i = 0; i < allClasses.size(); i++) {
        for (unsigned int j = 0; j < allClasses[i].size(); j++) {



            
            if (tree.find(allClasses[i][j]) == tree.end()) {
                // assignments[allClasses[i][j]] = currSlot;
                tree.insert(make_pair(allClasses[i][j], currSlot));

                if (assign(currSlot + 1, totalSlots, allClasses, tree)) {
                    return true; 
                }

                // Backtrack
                tree.remove(allClasses[i][j]);

            }


        }
    }

    return false;  // No valid assignment found for the current timeslot
}



int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Please enter an input file." << std::endl;
        return 1;
    }

    int totalExams, totalStudents, totalSlots;
    vector<string> students;
    vector<vector<int>> allClasses;

    ifstream ifile(argv[1]);

    if (ifile.fail()) {
        std::cerr << "Cannot open input file." << std::endl;
        return 1;
    }

    // Read parameters
    ifile >> totalExams >> totalStudents >> totalSlots;

    string line = "";
    getline(ifile, line);  // Read and discard the rest of the first line

    // Read student students and class schedules
    while (getline(ifile, line)) {
        stringstream ss(line);
        string name;
        ss >> name;
        students.push_back(name);

        std::vector<int> classes;
        int classCode;
        
        while (ss >> classCode) {
            classes.push_back(classCode);
        }

        allClasses.push_back(classes);
    }

    ifile.close();

    std::map<int, int> assignments;
    AVLTree<int, int> tree;

    try {
        bool success = assign(1, totalSlots, allClasses, tree);

        if (success) {

            for (typename AVLTree<int,int>::iterator it = tree.begin(); it != tree.end(); ++it) {
                cout << it->first << " " << it->second << endl;
            }
        
        }
        
        else {
            std::cout << "No solutions." << std::endl;
        }
    }
    
    catch (const std::exception& e) {
        cout << "EXCEPTION: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

