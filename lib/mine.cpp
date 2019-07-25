#include <iostream>
#include <regex>

#include <mine.hpp>
#include <md5.hpp>

using namespace std;

/*
 * serialized: a string version of the current ledge
 * previous_proof_of_work: the proof of work from the previous block
 */
string mine(string serialized, string previous_proof_of_work) {
	int counter = 0;
	regex why ("^0{5}.*$");

	string digest = md5(previous_proof_of_work + serialized + to_string(counter));

	while (!regex_match(digest, why)) {
		counter++;
		digest = md5(previous_proof_of_work + serialized + to_string(counter));
	}

	return to_string(counter);
}
