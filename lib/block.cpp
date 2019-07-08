#include <iostream>

#include <block.hpp>
#include <verify.hpp>

using namespace std;

Block::Block(int id) {
	this->id = id;
	this->previous_proof_of_work = "";
}

int Block::getId() {
	return this->id;
}

string Block::getProofOfWork() {
	return this->proof_of_work;
}

string Block::getSerialized() {
	string serialized = "BLOCK<" + to_string(this->id) + ">:";

	for (vector<Transaction *>::const_iterator i=this->transactions.begin(); i!=this->transactions.end(); i++) {
		serialized += (*i)->getSerialized();

		if (i != this->transactions.end() - 1) {
			serialized += "|";
		}
	}

	return serialized;
}

void Block::addTransaction(Transaction *transaction) {
	this->transactions.emplace_back(transaction);
}

void Block::setProofOfWork(string proof_of_work) {
	if (!verify(this->getSerialized(), this->previous_proof_of_work, proof_of_work)) {
		cerr << "Error: block " << this->id << " - "
			<< "invalid proof of work" << endl;

		exit(1);
	}

	this->proof_of_work = proof_of_work;
}

void Block::setPreviousProofOfWork(string previous_proof_of_work) {
	this->previous_proof_of_work = previous_proof_of_work;
}

void Block::destroy() {
	for (vector<Transaction *>::const_iterator i=this->transactions.begin(); i!=this->transactions.end(); i++) {
		free(*i);
	}
}

void Block::print() {
	string container = "********************";

	cout << container << endl
		<< "BLOCK " << this->id << endl;

	for (vector<Transaction *>::const_iterator i=this->transactions.begin(); i!=this->transactions.end(); i++) {
		(*i)->print();
	}

	if (this->proof_of_work != "") {
		cout << "Proof of work: " << this->proof_of_work << endl;
	}

	cout << container << endl;
}
