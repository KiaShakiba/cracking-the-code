#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <vector>

#include <transaction.hpp>

using namespace std;

class Block {
	int id;
	vector<Transaction *> transactions;
	string proof_of_work;
	string previous_proof_of_work;

	public:
		Block(int);

		int getId();
		string getProofOfWork();
		string getSerialized();

		void addTransaction(Transaction *);
		void setProofOfWork(string);
		void setPreviousProofOfWork(string);

		void destroy();
		void print();
};

#endif
