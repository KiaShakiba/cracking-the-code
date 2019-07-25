#include <iostream>
#include <regex>

#include <verify.hpp>
#include <md5.hpp>

using namespace std;

/*
 * serialized: a string version of the current ledge
 * previous_proof_of_work: the proof of work from the previous block
 * proof_of_work: the proof_of_work of the current block
 */
bool verify(string serialized, string previous_proof_of_work, string proof_of_work) {
	return false;
}
