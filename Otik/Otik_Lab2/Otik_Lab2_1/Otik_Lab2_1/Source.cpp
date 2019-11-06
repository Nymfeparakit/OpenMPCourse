#pragma once

#include "Coder.hpp"
#include "Decoder.hpp"
#include "CodesTree.hpp"

int main() {

	Coder coder("1.txt");
	CodesTree tree = coder.compress();
	Decoder decoder;
	decoder.decompress("encoded.bin", tree);
}