#ifndef _BLOCKCHAIN_HPP_
#define _BLOCKCHAIN_HPP_

#include <vector>

#include <block.hpp>

using namespace std;

class Blockchain {
	vector<Block *> blocks;

	public:
		Blockchain();

		void addBlock(Block *);

		void mineLatestBlock();

		void loadFromFile(string);
		void destroy();
		void print();

	private:
		vector<string> parseDataLine(string);
};

#endif
