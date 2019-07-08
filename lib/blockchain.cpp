#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include <blockchain.hpp>
#include <block.hpp>
#include <mine.hpp>

using namespace std;

void Blockchain::addBlock(Block *block) {
	this->blocks.emplace_back(block);
}

void Blockchain::mineLatestBlock() {
	Block *latest_block = this->blocks.back();

	if (latest_block->getProofOfWork() != "") {
		return;
	}

	string previous_proof_of_work = "";

	if (this->blocks.size() > 1) {
		Block *second_latest_block = this->blocks.end()[-2];
		previous_proof_of_work = second_latest_block->getProofOfWork();

		if (previous_proof_of_work == "") {
			cerr << "Error: second last block does not have a proof of work." << endl;
			exit(1);
		}
	}

	cout << "Mining block " << latest_block->getId() << endl;

	string proof_of_work = mine(latest_block->getSerialized(), previous_proof_of_work);

	cout << "POW: " << proof_of_work;
}

void Blockchain::loadFromFile(string file_path) {
	string line;
	ifstream file (file_path);

	int line_number = 0;
	int block_id = -1;

	regex block_regex ("^BLOCK-[0-9]+$");
	regex transaction_regex ("^[a-z]+,[a-z]+,[0-9]+$");
	regex pow_regex ("^POW-[a-zA-Z0-9]+$");

	regex block_remove_regex ("^BLOCK-");
	regex pow_remove_regex ("^POW-");

	Block *block;

	string previous_proof_of_work;

	if (file.is_open()) {
		while (getline(file, line)) {
			line_number++;

			if (regex_match(line, block_regex)) {
				if (block_id > -1) {
					this->addBlock(block);
				}

				block_id = stoi(regex_replace(line, block_remove_regex, ""));

				block = (Block *)malloc(sizeof(Block *));
				block = new Block(block_id);
			} else if (regex_match(line, transaction_regex) && block_id > -1) {
				vector<string> values = this->parseDataLine(line);

				string sender = values.at(0);
				string receiver = values.at(1);
				int amount = stoi(values.at(2));

				Transaction *transaction = (Transaction *)malloc(sizeof(Transaction *));
				transaction = new Transaction(sender, receiver, amount);

				block->addTransaction(transaction);
			} else if (regex_match(line, pow_regex) && block_id > -1) {
				if (block_id > 0) {
					block->setPreviousProofOfWork(previous_proof_of_work);
				}

				block->setProofOfWork(regex_replace(line, pow_remove_regex, ""));
				previous_proof_of_work = block->getProofOfWork();
			} else {
				cerr << "Error: error in data file on line: " << line_number << endl;
				exit(1);
			}
		}

		if (block_id > -1) {
			this->addBlock(block);
		}

		file.close();
	} else {
		this->destroy();

		cerr << "Error: could not open file." << endl;
		exit(1);
	}
}

vector<string> Blockchain::parseDataLine(string line) {
	vector<string> values;

	int i = 0;
	string value;

	while (i < line.length()) {
		if (line[i] != ',') {
			value += line[i];
		} else if (value.length() > 0) {
			values.push_back(value);
			value = "";
		}

		i++;
	}

	if (!value.empty()) {
		values.push_back(value);
	}

	return values;
}

void Blockchain::destroy() {
	for (vector<Block *>::const_iterator i=this->blocks.begin(); i!=this->blocks.end(); i++) {
		(*i)->destroy();
	}
}

void Blockchain::print() {
	for (vector<Block *>::const_iterator i=this->blocks.begin(); i!=this->blocks.end(); i++) {
		(*i)->print();

		if (i != this->blocks.end() - 1) {
			cout << endl << "     |" << endl << endl;
		}
	}
}
