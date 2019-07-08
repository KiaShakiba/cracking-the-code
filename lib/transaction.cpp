#include <iostream>

#include <transaction.hpp>

using namespace std;

Transaction::Transaction(string sender, string receiver, int amount) {
	this->sender = sender;
	this->receiver = receiver;
	this->amount = amount;
}

string Transaction::getSerialized() {
	return this->sender +
		"-" + this->receiver +
		":" + to_string(this->amount);
}

void Transaction::print() {
	cout << "> "
		<< this->sender << " -> "
		<< this->receiver << ": "
		<< this->amount << endl;
}
