#include "CodesTree.hpp"
#include <fstream>
#include <sstream>

class Coder {

public :
	std::string fileName;
	std::map<char, int> symbolsFrequencies;

	Coder(std::string _fileName) 
	: fileName(_fileName) {
	}
	
	//считает частоты в файле
	void countSymbolsFrequencies() {

		int a = 0;

		std::ifstream file(fileName);
		std::string line;
		//while (std::getline(file, line)) { //читаем файл построчно

			//std::istringstream iss(line);
			char c;
			//while (!iss.eof()) {
			//while (iss >> std::noskipws >> c) {
				//iss >> std::noskipws >> c;
			while (file.get(c)) {
				std::map<char, int>::iterator it = symbolsFrequencies.find(c);
				if (it != symbolsFrequencies.end()) { //если символ найден
					++symbolsFrequencies[c]; //увеличиваем количество
				}
				else { //иначе вставляем новый элемент
					symbolsFrequencies.insert({ c, 1 });
				}
			}
				
			//}
		//}
	}

	void encodeFile(CodesTree& tree) {
		std::ifstream fileInit(fileName, std::ios::binary | std::ios::ate);
		int leng_of_orig_file = fileInit.tellg();
		fileInit.close();

		std::ifstream file(fileName);
		std::string line;

		std::ofstream fs;
		std::string newFileName = "encoded.bin";
		fs.open(newFileName, std::fstream::out | std::fstream::trunc);

		// Размер исходного файла
		//std::string s = std::to_string(leng_of_orig_file);
		//char const *pchar = s.c_str();
		fs.write((char*)&leng_of_orig_file, sizeof(leng_of_orig_file));

		// Записываем данные по таблице сжатия
		int keys_number = symbolsFrequencies.size();
		fs.write((char*)&keys_number, sizeof(keys_number));
		std::map<char, int>::iterator itr = symbolsFrequencies.begin();
		for (;itr != symbolsFrequencies.end(); ++itr)
		{
			char key = itr->first;
			int freq = itr->second;

			fs << key;
			fs.write((char*)&freq, sizeof(freq));
		}

		// Записываем сжатую информацию
		char c;
		int written_bits = 0;//биты, которые уже были записаны
		char byte_to_write = 0;
		while (file.get(c)) { //читаем из файла по байту
			std::vector<char> code = tree.getSymbolsCode(c);//получаем код для символа в виде строки
			for (char c2 : code) {
				c2 <<= 7 - written_bits;
				byte_to_write |= c2;
				++written_bits;
				if (written_bits == 8) {
					fs << byte_to_write;
					byte_to_write = 0;
					written_bits = 0;
				}
			}
		}
		if (written_bits < 8 && written_bits > 0)
		{
			fs << byte_to_write;
		}

		fs.close();
	}



	CodesTree compress() 
	{
		countSymbolsFrequencies();
		CodesTree tree(symbolsFrequencies);
		encodeFile(tree);
		return tree;
	}

};