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

	
	//std::locale utf8_locale(std::locale(), new gel::stdx::utf8cvt<true>);
	std::wifstream file(fileName);
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	//fs.imbue(utf8_locale);
	//file.imbue(std::locale("zh_CN.UTF-8"));
	//std::map <char, int> symbolsFrequencies;
	std::wstring line;
	while (std::getline(file, line)) { //������ ���� ���������
	
		std::wistringstream iss(line);
		wchar_t c;
		//while (!iss.eof()) {
		while (iss >> std::noskipws >> c) {
			//iss >> std::noskipws >> c;
			std::map<wchar_t, int>::iterator it = symbolsFrequencies.find(c);
			if (it != symbolsFrequencies.end()) { //���� ������ ������
				++symbolsFrequencies[c]; //����������� ����������
			}
			else { //����� ��������� ����� �������
				symbolsFrequencies.insert({ c, 1 });
			}
			//if (iss.eof()) break;
		}
	}
}

//void writeFrequencies(std::map <wchar_t, int> symbolsFrequencies, int count) {
void writeFrequencies(std::map <wchar_t, int> symbolsFrequencies, std::string fileName) {

	std::wofstream fs;
	fs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	//size_t dot_pos = fileName.find(".");
	std::string newFileName = "freq " + fileName.substr(0, fileName.find(".")) + "2.txt";
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

//���������� �� ������, ����� ��������� ���� ��������
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
	
	//��������� ������� �� �����������
	//��������� ����� ����������
	/*typedef std::function<bool(std::pair<wchar_t, int>, std::pair<wchar_t, int>)> Comparator;
	Comparator compFunctor =
		[](std::pair<wchar_t, int> e1, std::pair<wchar_t, int> e2) {
		return e1.second > e2.second;
	};
	//� setOfSymbolsFreqs ��� ������� ����� ������������ �� ����������� �������
	std::set<std::pair<wchar_t, int>, Comparator> setOfSymbolsFreqs(
		symbolsFrequencies.begin(), symbolsFrequencies.end(), compFunctor);

	for (std::pair<wchar_t, int> element : setOfSymbolsFreqs) {

	}*/

	std::vector<Node*> orphans;
	typedef std::function<bool(Node* node1, Node* node2)> Comparator;
	Comparator compFunctor =
		[](Node* node1, Node* node2) {
		return node1->frequency > node2->frequency;
	};
	//� ������ ��� ���� �� ����� ��������
	for (std::map<wchar_t, int>::iterator it = symbolsFrequencies.begin(); 
		it != symbolsFrequencies.end(); ++it) {
		Node* node = new Node(it->first, it->second);
		orphans.push_back(node);
	}
	sort(orphans.begin(), orphans.end(), compFunctor);//��������� �� �������� ������

	std::vector<Node*>::iterator it;
	while (orphans.size() != 1) {//���� �� ������� ������ ���� ���� ��� ��������
		//����� ��� ���� � ����������� ���������
		it = orphans.end() - 1;
		Node* leftNode = *it;
		--it;
		Node* rightNode = *it;
		orphans.pop_back();
		orphans.pop_back();
		//������� ��� ��� ��������
		Node* parentNode = new Node(NULL, leftNode->frequency + rightNode->frequency);
		parentNode->left = leftNode;
		parentNode->right = rightNode;
		orphans.push_back(parentNode);//������ ���� ���� �� ����� ��������
		sort(orphans.begin(), orphans.end(), compFunctor);//����� ��������� �� ��������
	}
	Node* rootNode = orphans.front();//������������ ���������� ���� �������� ������ ������
	traverseToCreateCodes(rootNode, symbolsCodes, "");

}

void encodeMessage(std::string fileName, std::map <wchar_t, std::string> &symbolsCodes) {
	std::wifstream file(fileName);
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	std::wstring line;
	while (std::getline(file, line)) { //������ ���� ���������

		std::wistringstream iss(line);
		wchar_t c;
		//while (!iss.eof()) {
		while (iss >> std::noskipws >> c) {
			std::cout << symbolsCodes[c];
		}
		std::cout << std::endl;
	}
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	std::string fileName;
	int counter = 0;
	for (;;) {
		std::cout << "File: ";
		std::getline(std::cin, fileName);
		++counter;
		std::map <wchar_t, int> symbolsFrequencies;
		countSymbolsFrequencies("test.txt", symbolsFrequencies);
		std::map <wchar_t, std::string> symbolsCodes;
		createSymbolsCodes(symbolsFrequencies, symbolsCodes);
		encodeMessage("test.txt", symbolsCodes);
		//writeFrequencies(symbolsFrequencies, "Lermontov.txt");
		if (counter >= 5) {
			counter = 0;
		}
		//std::cout << std::endl;
	}
		//system("pause");
	return 0;
}