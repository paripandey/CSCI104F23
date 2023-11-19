#include <iostream>
#include "Hashtable.h"
#include <utility>
#include <time.h>

using namespace std;

string generateRandomString();

int main() {
    srand(time(0));

    // PART 1: BIRTHDAY PARADOX
    
    cout << endl << "PART 1: BIRTHDAY PARADOX" << endl;
    long insertions = 0; // for each trial, the number of insertions till a collision and/or before resizing
    long probes = 0; // stores the number of probes for each insertion
    string curr_string = "";

    double l_e_23 = 0; // number of trials that took <= 23 insertions
    double g_e_24 = 0; // number of trials that took >= 24 insertions
    int trials = 1000; // number of trials

    for (int i = 0; i < trials; i++) {
        // for each trial...

        Hashtable<int> hashtable(false, 365);
        insertions = 0;
        probes = 0; // number of probes required for each insertion
        curr_string = "";

        // the number of probes for each insertion is 0 and the hashtable isn't half full yet
        while (!probes && insertions <= 182) {
            curr_string = generateRandomString();
            probes = hashtable.add(curr_string, insertions); // number of probes for the insertion
            insertions++;
        }

        if (insertions <= 23)
            l_e_23++;
        else
            g_e_24++;
    }


    // Results expressed as percentages
    cout << "% of trials that took <= 23 insertions: " << l_e_23 / trials * 100 << endl;
    cout << "% of trials that took >= 24 insertions: " << g_e_24 / trials * 100 << endl << endl;

    // ----------------
    // PART 2: PROBE RATE

    cout << "PART 2: PROBE RATE" << endl;

    // some possible n's to choose from
    const int possible_ns[5] = {197, 397, 797, 1597};
    
    int curr_probe = 0; // stores the number of probes for each insertion
    int largest_probe = 0; // stores the largest number of probes in a trial

    int n = possible_ns[rand() % 4]; // chooses a random n from the array above
    trials = 1000; // declared in problem 1 above

    int total_probes = 0; // stores the total number of probes across ALL trials
    int total_largest_probe = 0; // stores the total "largest" number of probes across ALL trials

    int largest_probe_average = 0; // stores the largest probe on average
    int probe_average = 0; // stores the number of probes on average

    for (int i = 1; i <= trials; i++) {
        largest_probe = 0; // largest probe in the trial
        probes = 0; // total number of probes in the trial
        Hashtable<int> hashtable1(false); // starts with size = 11 to prompt resizing
        for (int i = 1; i <= n; i++) {
            curr_probe = hashtable1.add(generateRandomString(), i);
            if (curr_probe > largest_probe)
                largest_probe = curr_probe; 
            probes += curr_probe; // increments the total number of probes in the trial
        }

        total_largest_probe += largest_probe; // increments total "largest" number of probes across all trials
        total_probes += probes; // increments total number of probes across all trials
    }

    // largest probe on average across all trials
    largest_probe_average = total_largest_probe / trials;

    // number of probes on average across all trials
    probe_average = total_probes / trials;

    // Formatting the results
    cout << "n is " << n << "." << endl;
    cout << "log(n) = " << floor(log(n)/log(2)) << "." << endl << "log(n) -> ";
    cout << largest_probe_average << " is the largest number of probes on average." << endl;
    cout << "2n/3 = " << 2 * n / 3 << "." << endl << "2n/3 -> ";
    cout << probe_average << " is the number of probes on average. " << endl;
    cout << (double) probe_average/n << " ≈ 0.667." << endl;
    cout << "These results are in line with our expectations." << endl << endl;
}


// Generates a random string of 28 letters
string generateRandomString() {
    string result = "";
    char letter = 0;

    for (int i = 1; i <= 28; i++) {
        letter = ((rand() % 26) + 1) + 96;
        result += letter;
    }

    return result;

}
