#include <iostream>

#include <md5.hpp>
#include <transaction.hpp>
#include <blockchain.hpp>
#include <block.hpp>

using namespace std;

int main(void) {
	Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
	blockchain = new Blockchain();

	blockchain->loadFromFile("data.dat");
	blockchain->print();
	blockchain->mineLatestBlock();
	blockchain->destroy();

	free(blockchain);

	return 0;
}
