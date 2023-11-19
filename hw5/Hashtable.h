#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <string>
#include <iostream>
#include <cmath>
#include <utility>
#include <map>


template<typename T>
class Hashtable
{
public:

	Hashtable(bool debug = false, unsigned int size = 11);

	~Hashtable();

	int add(std::string k, const T& val);

	const T& lookup(std::string k) const;

	void reportAll(std::ostream& out) const;

	int hash(std::string k) const;

private:
	std::pair<std::string, const T>** array; // stores the hashtable
	std::map<std::string, T> map_; // stores the key-value pairs
	long insertions; // stores the number of elements present in the hashtable
	bool debug; // stores whether debug mode is true or false
	long m; // stores the size of the hashtable

	// stores the array of sizes that the hashtable would resize to
	const long prime_sizes[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
	
	int new_m_i; // stores the index of the "next" size that the hashtable would resize to (from the array above)
	
	long r[5]; // stores r1-r5

	void resize(); // the resize method
};



template<typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size) {
	m = (long) size; // stores the size of the hashtable
	insertions = 0; // there are currently no elements in the hashtable
	array = new std::pair<std::string, const T>*[m](); // pointer of m std::pair pointers
	
	// stores the index of the "next" size the hashtable would resize to
	// this loop only iterates once, even if there are multiple resizes!
	for (new_m_i = 0; new_m_i < 17 && prime_sizes[new_m_i] <= m; new_m_i++);
	
	this->debug = debug; // stores debug mode

	if (debug) { // default values given in the instructions
		r[0] = 983132572;
		r[1] = 1468777056;
		r[2] = 552714139;
		r[3] = 984953261;
		r[4] = 261934300;
	}

	else { // generate random r1-r5 values
		for (int i = 0; i < 5; i++) {
			r[i] = rand() % m;
		}
	}
}

template<typename T>
Hashtable<T>::~Hashtable() {
	for (int i = 0; i < m; ++i) {
		delete array[i]; // deletes the dynamically allocated std::pair
	}
	delete [] array; // deletes the dynamically allocated std::pair pointers
}

template<typename T>
int Hashtable<T>::add(std::string k, const T& val) {
	
	// The "new' loading factor would be greater than 0.5
	if ((insertions + 1) > (m/2.0)) {
		resize();
	}

	long i = 0; // represents the number of probes
	long h_k = hash(k); // h(k)
	long quad_prob = h_k % m; // same as h(k) at first

	// There's a collision with a different key!
	while (array[quad_prob] != nullptr && array[quad_prob]->first != k) {
		i++; // increments the number of probes
		quad_prob = (h_k + i * i) % m; // quadratic probing
	}

	// array[quad_prob] is not filled yet (could be the same as h(k))
	array[quad_prob] = new std::pair<std::string, const T>(k, val);
	insertions++;
	map_[k] = val; // stores the key-value pair for faster lookup
	return (int) i; // returns the number of probes required
}

template<typename T>
const T& Hashtable<T>::lookup(std::string k) const {

	// if the key is in the map
	if (map_.find(k) != map_.end()) {
		return map_.at(k);
	}

	// else, returns the value of the 1st key in the map (alphabetical)
	else {
		return map_.begin()->second;
	}

}

template<typename T>
void Hashtable<T>::reportAll(std::ostream& out) const {
	for (long i = 0; i < m; i++) {
		if (array[i] != nullptr) {
			out << array[i]->first << " " << array[i]->second << std::endl;
		}
	}
}

template<typename T>
int Hashtable<T>::hash(std::string k) const {

	long w[5] = {0, 0, 0, 0, 0}; // all initialized to 0
	int curr_index = (int) k.length() - 1;
	int w_index = 4;
	int letter = 0;
	std::string curr_word = "";

	// Divides the key into 6 letter chunks, starting from the end
	while (curr_index - 5 >= 0) {
		curr_word = k.substr(curr_index - 5, 6);

		for (int i = 0; i < 6; i++) {
			letter = curr_word[5 - i] - 96; // stores the letter in the chunk from 1-26

			// the relationship between the order of the letter and the power of 27
			w[w_index] += letter * pow(27, i);
		}

		curr_index -= 6;
		w_index--;
	}

	// in case the last chunk has less than 6 letters
	curr_word = k.substr(0, curr_index + 1);
	int curr_word_length = curr_word.length();
	
	// same process as while loop above, except w already accounts for leading 0s
	for (int i = 0; i < curr_word_length; i++) {
		letter = curr_word[curr_word_length - 1 - i] - 96;
		w[w_index] += letter * pow(27, i);
	} 

	long long result = 0;

	for (int i = 0; i < 5; i++) {
		result += r[i] * w[i]; // stores the intermediate result
	}

	return (int) (result % m); // h(k)
}

template<typename T>
void Hashtable<T>::resize() {
	long old_m = m;
	std::pair<std::string, const T>** old_array = array;
	
	m = prime_sizes[new_m_i]; // stores the new value of m, found at the start
	array = new std::pair<std::string, const T>*[m](); // new hashtable
	insertions = 0; // 0 elements currently present in the new hashtable
	// no need to edit the map
	
	if (!debug) {
		for (int i = 0; i < 5; i++) {
			r[i] = rand() % m; // regenerates r1-r5
		}
	}

	// rehashes the elements in the original hashtable in the order they appear
	for (long i = 0; i < old_m; i++) {
		if (old_array[i] != nullptr) {
			add(old_array[i]->first, old_array[i]->second);
		}

		delete old_array[i]; // deletes each dynamically allocated pair from the old hashtable
	}
	
	delete [] old_array; // deletes the old hashtable

	new_m_i++; // stores the "next" size for resizing: a cheap operation!
}

#endif