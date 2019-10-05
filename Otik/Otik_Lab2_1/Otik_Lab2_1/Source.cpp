#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <functional>
#include <set>
#include <vector>
#include <algorithm>

void countSymbolsFrequencies(std::string fileName, std::map <wchar_t, int> &symbolsFrequencies) {

	std::wifstream file(fileName);
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	std::wstring line;
	while (std::getline(file, line)) { //читаем файл построчно
	
		std::wistringstream iss(line);
		wchar_t c;
		//while (!iss.eof()) {
		while (iss >> std::noskipws >> c) {
			//iss >> std::noskipws >> c;
			std::map<wchar_t, int>::iterator it = symbolsFrequencies.find(c);
			if (it != symbolsFrequencies.end()) { //если символ найден
				++symbolsFrequencies[c]; //увеличиваем количество
			}
			else { //иначе вставляем новый элемент
				symbolsFrequencies.insert({ c, 1 });
			}
		}
	}
}

void writeFrequencies(std::map <wchar_t, int> symbolsFrequencies, std::string fileName) {

	std::wofstream fs;
	fs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	//size_t dot_pos = fileName.find(".");
	std::string newFileName = "freq " + fileName.substr(0, fileName.find(".")) + ".txt";
	//std::string newFileName = "freq" + std::to_string(count) + ".txt";
	fs.open(newFileName, std::fstream::out | std::fstream::trunc);
	std::map<wchar_t, int>::iterator it;
	for (it = symbolsFrequencies.begin(); it != symbolsFrequencies.end(); ++it) {
		fs << "|" << std::setw(5) << std::left << it->first << "|"
			<< std::setw(20) << it->second << "|" << std::endl;
	}
	fs.close();

}

struct Node {
	int frequency;
	wchar_t symbol;
	struct Node *left, *right;
	Node(wchar_t _symbol, int _frequency) {
		symbol = _symbol;
		frequency = _frequency;
		left = NULL;
		right = NULL;
	}
};

//проходится по дереву, чтобы составить коды символов
void traverseToCreateCodes(Node* node, std::map <wchar_t, std::string> &symbolsCodes, std::string code) {

	if (node == NULL) return;

	if (node->symbol != NULL) {
		symbolsCodes.insert({ node->symbol, code });
		return;
	}

	traverseToCreateCodes(node->left, symbolsCodes, code + "0");
	traverseToCreateCodes(node->right, symbolsCodes, code + "1");

}

void createSymbolsCodes(std::map <wchar_t, int> symbolsFrequencies, 
	std::map <wchar_t, std::string> &symbolsCodes) {

	std::vector<Node*> orphans;
	typedef std::function<bool(Node* node1, Node* node2)> Comparator;
	Comparator compFunctor =
		[](Node* node1, Node* node2) {
		return node1->frequency > node2->frequency;
	};
	//в начале все узлы не имеют родителя
	for (std::map<wchar_t, int>::iterator it = symbolsFrequencies.begin(); 
		it != symbolsFrequencies.end(); ++it) {
		Node* node = new Node(it->first, it->second);
		orphans.push_back(node);
	}
	sort(orphans.begin(), orphans.end(), compFunctor);//сортируем по убыванию частот

	std::vector<Node*>::iterator it;
	while (orphans.size() != 1) {//пока не остался только один узел без родителя
		//берем два узла с наименьшими частотами
		it = orphans.end() - 1;
		Node* leftNode = *it;
		--it;
		Node* rightNode = *it;
		orphans.pop_back();
		orphans.pop_back();
		//Создаем для них родителя
		Node* parentNode = new Node(NULL, leftNode->frequency + rightNode->frequency);
		parentNode->left = leftNode;
		parentNode->right = rightNode;
		orphans.push_back(parentNode);//теперь этот узел не имеет родителя
		sort(orphans.begin(), orphans.end(), compFunctor);//снова сортируем по частотам
	}
	Node* rootNode = orphans.front();//единственный оставшийся узел является корнем дерева
	traverseToCreateCodes(rootNode, symbolsCodes, "");

}

void encodeMessage(std::string fileName, std::map <wchar_t, std::string> &symbolsCodes) {
	std::wifstream file(fileName);
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	std::wstring line;
	while (std::getline(file, line)) { //читаем файл построчно

		std::wistringstream iss(line);
		wchar_t c;
		//while (!iss.eof()) {
		while (iss >> std::noskipws >> c) {
			std::cout << symbolsCodes[c];
		}
		std::cout << std::endl;
	}
}

void writeSymbolCodesTable(std::map <wchar_t, std::string> &symbolsCodes) {

	std::wofstream fs;
	fs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	std::string newFileName = "codes.txt";
	fs.open(newFileName, std::fstream::out | std::fstream::trunc);
	std::map<wchar_t, std::string>::iterator it;
	for (it = symbolsCodes.begin(); it != symbolsCodes.end(); ++it) {
		std::wstring wstr(it->second.begin(), it->second.end());
		fs << "|" << std::setw(5) << std::left << it->first << "|"
			<< std::setw(20) << wstr << "|" << std::endl;
	}
	fs.close();

}

int main() {
	
	setlocale(LC_ALL, "Russian");
	std::string fileName;
	for (;;) {

		std::map <wchar_t, int> symbolsFrequencies;
		std::map <wchar_t, std::string> symbolsCodes;
		std::cout << "File: ";
		std::getline(std::cin, fileName);
		if (fileName.compare("0") == 0) {
			countSymbolsFrequencies("test.txt", symbolsFrequencies);
			createSymbolsCodes(symbolsFrequencies, symbolsCodes);
			encodeMessage("test.txt", symbolsCodes);
			writeSymbolCodesTable(symbolsCodes);
		}
		else {
			countSymbolsFrequencies(fileName, symbolsFrequencies);
			writeFrequencies(symbolsFrequencies, fileName);
		}

	}
		//system("pause");
	return 0;
}