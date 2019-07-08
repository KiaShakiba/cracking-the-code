#ifndef _TRANSACTION_HPP_
#define _TRANSACTION_HPP_

using namespace std;

class Transaction {
	string sender;
	string receiver;
	int amount;

	public:
		Transaction(string, string, int);

		string getSerialized();

		void print();
};

#endif
