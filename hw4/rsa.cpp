#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void encrypt(const string& filename, const long long& n, const string& message); // ENCRYPTION METHOD

void decrypt(const string& input_file, const string& output_file, const unsigned long long& d, const long long& n); // DECRYPTION METHOD

unsigned long long mod_exp(const long long& b, long long n, const long long& m); // MODULAR EXPONENTIATION ALGORITHM

void euclidean(const long long& p, const long long& q, long long& d); // EUCLIDEAN ALGORITHM


int main(int argc, char* argv[]) {
    long long p = stoll(argv[1]);
    long long q = stoll(argv[2]);
    long long d = -1; // DECRYPTION KEY IS -1 INITIALLY, AND STAYS THAT WAY IF P AND Q ARE NOT VALID CHOICES
    euclidean(p, q, d); // CHANGES D, IF P AND Q ARE VALID CHOICES

    string command = "";
    string input_file = ""; // STORES THE FILE FOR ENCRYPTION, OR THE INPUT FILE FOR DECRYPTION

    // EXECUTES UNTIL THE USER WANTS TO EXIT THE PROGRAM
    while (command != "EXIT") {
        cout << "Enter a command: ";
        cin >> command;

        if (command == "ENCRYPT") {
            long long n = 0; // WILL END UP BEING P * Q
            string message = "";
            cin >> input_file >> n >> ws;
            getline(cin, message); // STORES THE MESSAGE
            encrypt(input_file, n, message);
        }

        else if (command == "DECRYPT") {
            string output_file = ""; // STORES THE OUTPUT FILE
            cin >> input_file >> output_file;

            // THE DECRYPTION KEY IS VALID
            if (d != -1)
                decrypt(input_file, output_file, d, p*q);
        }

        else if (command != "EXIT") {
            // ERROR MESSAGE. WILL PROMPT THE USER FOR ANOTHER COMMAND
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}


/*
    MODULAR EXPONENTIATION ALGORITHM.
    MOSTLY TAKEN FROM LECTURE 16: CRYTOGRAPHY AND LAB 7.
*/
unsigned long long mod_exp(const long long& b, long long n, const long long& m) {
    long long x = 1;
    long long power = b % m;
    
    // THE EXPONENT ISN'T 0
    while (n) {
        // THE EXPONENT IS ODD
        if(n % 2)
            x = (x * power) % m;

        power = (power * power) % m; // SQUARING METHOD
        n /= 2; // HALVES THE EXPONENT
    }

    return x;
}

void encrypt(const string& filename, const long long& n, const string& message) {
    ofstream filename_(filename); // CREATES OUTPUT FILE

    long long e = 65537;
    string m = ""; // WILL STORE THE CHUNK


    if (n < 27) {
        cout << "ERROR: n must be >= 27.";
        return;
    }

    long long x = 1 + log(n/27)/log(100);

    unsigned long long start_index = 0;
    unsigned long long message_length = message.length();

    while (start_index < message_length) {
        for (long long i = 0; i < x; ++i) {
            // WE WANT MORE LETTERS THAN THERE ARE
            if ((start_index + i) >= message_length) {
                m += "00"; // ADDS EXTRA SPACES
            }

            // HANDLES THE SPACES
            else if (message[start_index + i] == ' ') {
                m += "00";
            }

            // HANDLES REGULAR LETTERS
            else {
                // LETTERS A-J
                if ((int(message[start_index + i])-96) < 10) {
                    m += '0'; // PREPENDS THE DIGIT WITH A 0
                }

                // LETTERS J-Z
                m += to_string((int(message[start_index + i])-96));

            }

        }

        unsigned long long c = mod_exp(stoll(m), e, n);
        filename_ << c << " "; // SEPARATES EACH ENCRYPTED WORD WITH A SPACE

        m = ""; // "RESETS" THE CHUNK TO BE ENCRYPTED
        start_index += x; // MOVES TO THE NEXT INDEX
    }

    filename_ << endl; // ADDS A NEWLINE TO THE END OF THE FILE


}

void decrypt(const string& input_file, const string& output_file, const unsigned long long& d, const long long& n) {

   ifstream input_stream(input_file); // INPUT FILE
   ofstream output_stream(output_file); // OUTPUT FILE

   long long c = 0;
   unsigned long long x = 1 + log(n/27)/log(100);

    while (input_stream >> c) {
        unsigned long long m = mod_exp(c, d, n);
        unsigned long long m_length = 0;
        string m_string = to_string(m); // STRING VERISON OF M

        while (m_string.length() != 2*x)
            m_string = '0' + m_string; // ADDS LEADING ZEROS
        
        m_length = m_string.length();
        string remaining_string = m_string; // STORES THE REMAINDER OF THE CHUNK


        unsigned long long i = 0;


        // REMAINING_STRING EVENTUALLY BECOMES -1 TO INDICATE END OF THE STRING
        while (i < m_length && stoi(remaining_string) != -1) {
            int character = stoi(m_string.substr(i, 2)); // INT VERSION OF DIGIT

            // DIGIT IS 0
            if (!character) {
                output_stream << ' '; // ADDS A SPACE TO THE FILE
                if (i + 2 < m_length) { // VALID REMAINDER OF THE STRING
                    remaining_string = m_string.substr(i+2, m_length - i - 2); i++;
                }

                else {
                    remaining_string = "-1"; // END OF THE STRING
                }
                
            }

            // VALID POSITIVE DIGIT
            else if (character <= 26) {
                output_stream << (char) (character + 96);
                if (i + 2 < m_length) // VALID REMAINDER OF THE STRING
                    remaining_string = m_string.substr(i + 2, m_length - i - 2);
                
                else
                    remaining_string = "-1"; // END OF THE STRING
                
                i++; // MOVES THE TRACKER BY 1 (ENDS UP BEING 2 AT THE END OF THE ITERATION)
            }

            
            // DIGIT IS ABOVE 26
            else {
                character /= 10; // FIRST DIGIT OF THE NUMBER
                output_stream << (char)(character + 96);
                if (i + 1 < m_length) // VALID REMAINDER OF THE STRING
                    // REMAINING STRING IS THE 2ND DIGIT ONWARDS
                    remaining_string = m_string.substr(i+1, m_length - i - 1);

                else { // END OF THE STRING
                    remaining_string = "-1";
                }
            }
            // REGULAR INCREMENTER/TRACKER
            i++;
        }
   }

   output_stream << endl; // ENDLINE AT END OF FILE

}


void euclidean(const long long& p, const long long& q, long long& d) {

    // STANDARD EUCLIDEAN ALGORITHM

    long long x = p-1;
    long long y = q-1;

    while (y != 0) {
        long long r = x % y;
        x = y;
        y = r;
    }

    long long L = (p-1)*(q-1)/x;

    if (L <= 65537) {
        cout << "L must be greater than e (65537)." << endl;
        return;
    }

    // EXTENDED EUCLIDEAN ALGORITHM FROM HOMEWORK PAGE
    long long s = 0;
    long long old_s = 1;
    long long t = 1;
    d = 0;
    long long r = 65537;
    long long old_r = L;
    long long quotient;
    long long temp;

    while (r != 0) {
        quotient = old_r/r;
        temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = d - quotient * t;
        d = temp;
    }

    // WHILE THE DECRYPTION KEY IS NEGATIVE
    while (d < 0)
        d += (65537 * L);

    // IF THE GCD ISN'T 1
    if (old_r != 1) {
        cout << "Unfortunate choice of p and q." << endl;
        d = -1;
        return;
    }
   
}