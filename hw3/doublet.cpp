#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include "MinHeap.h"
using namespace std;

struct Node { // THIS NODE STRUCT WILL STORE SEVERAL PROPERTIES OF EACH WORD IN THE LIST.
    string word; // THE ACTUAL WORD (ITS UPPERCASE VERSION)
    int distance; // THE "DISTANCE" (G-VALUE) OF THE WORD
    int heuristic; // THE HEURISTIC (H-VALUE) OF THE WORD
    int function; // THE F-VALUE OF THE WORD (G-VALUE + H-VALUE)
    int priority; // THE PRIORITY OF THE WORD
    bool visited; // WHETHER THE WORD HAS BEEN VISITED (CLOSED LIST)
    set<string> neighbors; // THE WORD'S NEIGHBORS
    Node* pred; // THE PREDECESSOR OF THE WORD
    
    // DEFAULT CONSTRUCTOR
    Node()
    : word(""), distance(0), heuristic(0), function(0), priority(0), visited(false), pred(nullptr)
    {}  
};

int main(int argc, char* argv[]) {
    // STORES THE STARTING WORD, ENDING WORD, AND FILE INPUT STREAM
    if (argc < 3) {
        return 0;
    }
    
    string starting_word = argv[1];
    string ending_word = argv[2];
    ifstream input_file(argv[3]);

    int num_words = 0;
    int steps = 0;
    int expansions = 0;
    Node* goal_node = nullptr;

    map<string, Node> word_list; // WILL MAP EACH WORD TO A NODE

    // CONVERTS THE STARTING AND ENDING WORDS TO THEIR UPPERCASE VERSIONS
    for (unsigned int i = 0; i < starting_word.length(); i++) {
        if (starting_word[i] > 90) {
            starting_word[i] -= 32;
        }

        if (ending_word[i] > 90) {
            ending_word[i] -= 32;
        }
    }

    input_file >> num_words; // STORES THE NUMBER OF WORDS
    Node* graph = new Node[num_words]; // ALLOCATES THE DESIRED NUMBER OF NODES

    // READS EACH WORD IN THE LIST
    for (int i = 0; i < num_words; ++i) {
        input_file >> graph[i].word;

        // CONVERTS THE WORD TO ITS UPPERCASE VERSION
        for (unsigned int j = 0; j < graph[i].word.length(); j++) {
            if (graph[i].word[j] > 90) {
                graph[i].word[j] -= 32;
            }
        }

        graph[i].heuristic = graph[i].word.length();
    
        if (graph[i].word.length() == ending_word.length()) {
            // CALCULATES THE HEURISTIC OF THE WORD
            for (unsigned int j = 0; j < graph[i].word.length(); ++j) {
                if ((graph[i].word[j] == ending_word[j])) {
                    graph[i].heuristic--;
                }
            }
        }

        // ALL WORDS EXCEPT THE STARTING WORD START WITH AN "INFINITE" DISTANCE/F-VALUE/PRIORITY
        if (graph[i].word != starting_word) {
            graph[i].distance = starting_word.length();
            graph[i].function = graph[i].distance + graph[i].heuristic;
            graph[i].priority = graph[i].function * (graph[i].word.length()+1) + graph[i].heuristic;
        }

        word_list[graph[i].word] = graph[i]; // ADDS THE WORD:NODE PAIR TO THE MAP
    }

    goal_node = &word_list[ending_word]; // STORES THE ADDRESS OF THE ENDING WORD'S NODE


    // PART 1: BUILDS THE GRAPH. GENERATES EACH WORD'S NEIGHBORS.
    for (int node = 0; node < num_words; node++) {
        string curr_word = graph[node].word; // CREATES A COPY OF THE WORD FOR MUTATION
        
        // LOOKS AT EACH LETTER IN THE WORD
        for (int letter_index = curr_word.length() - 1; letter_index >= 0; --letter_index) {
            char original_letter = curr_word[letter_index];

            // GENERATES ALL POSSIBLE PERMUTATIONS OF THE WORD (DIFFERING BY 1 LETTER)
            for (char letter = 'A'; letter <= 'Z'; letter++) {
                // WE DON'T WANT A REPEAT OF THE ORIGINAL WORD
                if (letter != original_letter) {
                    curr_word[letter_index] = letter;

                    // THE PERMUTATION EXISTS IN THE WORD LIST
                    if (word_list.find(curr_word) != word_list.end()) {
                        // WILL AUTOMATICALLY NOT ADD DUPLICATE NEIGHBORS
                        graph[node].neighbors.insert(curr_word);
                        word_list[curr_word].neighbors.insert(graph[node].word);
                    }
                }
            }

            curr_word[letter_index] = original_letter; // RESETS THE WORD
        }
    }

    // PART2: A* SEARCH ALGORITHM

    MinHeap<string> open_list(2); // CREATES A BINARY HEAP

    // ADDS THE STARTING WORD TO THE HEAP
    open_list.add(starting_word, word_list[starting_word].priority);

    while (!open_list.isEmpty()) {
        // STORES THE ADDRESS OF THE WORD WITH THE LOWEST PRIORITY
        Node* s = &word_list[open_list.peek()];
        s->visited = true; // MARKS THE WORD AS VISITED (CLOSED LIST)
        
        if (s == goal_node) { // THE WORD IS THE ENDING WORD
            break;
        }

        else {
            open_list.remove(); // REMOVES THE WORD FROM THE OPEN LIST
            expansions++; // INCREMENTS THE NUMBER OF EXPANSIONS (WORDS EXPLORED)
            
            // FOR EACH OF THE WORD'S NEIGHBORS
            set<string>::iterator it;
            for (it = s->neighbors.begin(); it != s->neighbors.end(); ++it) {
                Node* neighbor = &word_list[*it];

                // THE NEIGHBOR HASN'T BEEN VISITED
                if (neighbor->visited == false) {
                    neighbor->pred = s; // SETS ITS PREDECESSOR TO THE CURRENT WORD
                    // EDITS ITS DISTANCE, F-VALUE, AND PRIORITY
                    neighbor->distance = s->distance + 1;
                    neighbor->function = neighbor->distance + neighbor->heuristic;
                    neighbor->priority = neighbor->function * (neighbor->word.length()+1) + neighbor->heuristic;
                    open_list.add(neighbor->word, neighbor->priority); // ADDS THE ITEM TO THE HEAP
                    neighbor->visited = true; // MARKS THE NEIGHBOR AS VISITED (CLOSED LIST)
                }

                // THE NEIGHBOR HAS BEEN VISITED BEFORE
                else {
                    int new_distance = s->distance + 1; // CALCULATES THE NEIGHBORS'S DISTANCE ON THIS PATH

                    if (new_distance < neighbor->distance) { // THIS PATH IS SHORTER THAN THE NEIGHBOR'S CURRENT PATH
                        neighbor->pred = s; // SETS THE NEIGHBOR'S PREDECESSOR TO THE CURRENT WORD
                        
                        // UPDATES THE NEIGHBOR'S DISTANCE, F-VALUE, AND PRIORITY
                        neighbor->distance = new_distance;
                        neighbor->function = new_distance + neighbor->heuristic;
                        neighbor->priority = neighbor->function * (neighbor->word.length()+1) + neighbor->heuristic;

                        open_list.add(neighbor->word, neighbor->priority); // UPDATES THE NEIGHBOR'S PRIORITY IN THE HEAP
                    }

                    // TIE-BREAKER: WHICH PATH TO CHOOSE?
                    else if ((new_distance == neighbor->distance) && (s->word < neighbor->pred->word)) {
                        neighbor->pred = s; // UPDATES THE NEIGHBOR'S PREDECESSOR
                    }
                }   
            }
        }   
    }

    // THE ENDING WORD WAS MADE
    if (goal_node->pred != nullptr) {
        Node* curr_node = goal_node;
        while (curr_node->pred != nullptr) {
            curr_node = curr_node->pred;
            steps++;
        }
        cout << steps << endl; // NUMBER OF TRANSFORMATIONS (WORDS IN THE PATH)
    }

    // THE ENDING WORD WAS NOT MADE
    else {
        cout << "No transformation" << endl;
    }

    cout << expansions << endl; // NUMBER OF WORDS EXPLORED
        
    // DELETES THE GRAPH
    delete [] graph;

    return 0;
}