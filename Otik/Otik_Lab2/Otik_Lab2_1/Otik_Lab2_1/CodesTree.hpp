#pragma once

#include <map>
#include <vector>
#include <functional>
#include <algorithm>

class CodesTree{

public: 
	
	struct Node {
		int frequency;
		char symbol;
		struct Node *left, *right;
		Node(char _symbol, int _frequency) {
			symbol = _symbol;
			frequency = _frequency;
			left = NULL;
			right = NULL;
		}
	};

	Node *rootNode;
	std::map <char, std::vector<char>> symbolsCodes;

	CodesTree(const std::map<char, int>& symbolsFreqs) {
		make(symbolsFreqs);
	}

	std::vector<char>& getSymbolsCode(char symbol) {
		return symbolsCodes[symbol];
	}

	//���������� �� ������, ����� ��������� ���� ��������
	void traverseToCreateCodes(Node* node, std::vector<char> code) {

		if (node == NULL) return;

		if (node->symbol != NULL) {
			symbolsCodes.insert({ node->symbol, code });
			return;
		}

		std::vector<char> leftCode(code);
		leftCode.push_back(0);
		traverseToCreateCodes(node->left, leftCode);
		std::vector<char> rightCode(code);
		rightCode.push_back(1);
		traverseToCreateCodes(node->right, rightCode);

	}

	//������ ������ �� ������ ������
	void make(std::map <char, int> symbolsFrequencies) {

		std::vector<Node*> orphans;//���� ��� ���������
		typedef std::function<bool(Node* node1, Node* node2)> Comparator;
		//comparator ��� ���������� ����� �� ��������
		Comparator compFunctor =
			[](Node* node1, Node* node2) {
			return node1->frequency > node2->frequency;
		};
		//� ������ ��� ���� �� ����� ��������
		for (std::map<char, int>::iterator it = symbolsFrequencies.begin();
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
			orphans.pop_back(); //����������� ��, �.�. ������ � ��� ���� ��������
			orphans.pop_back();
			//������� ��� ��� ��������
			Node* parentNode = new Node(NULL, leftNode->frequency + rightNode->frequency);
			parentNode->left = leftNode;
			parentNode->right = rightNode;
			orphans.push_back(parentNode);//������ ���� ���� �� ����� ��������
			sort(orphans.begin(), orphans.end(), compFunctor);//����� ��������� �� ��������
		}
		rootNode = orphans.front();//������������ ���������� ���� �������� ������ ������
		std::vector<char> code;
		traverseToCreateCodes(rootNode, code);//���������� �� ������, ����� ��������� ����
		int a = 0;
	}

	char findFirstSymbolInCode(unsigned short code, int& last_bit_pos) // ���� char code
	{

		char firstSymbol = 0;
		last_bit_pos = 0;
		//���������� �� ������ �� ��� ���, ���� �� ������ ������
		Node *currNode = rootNode;
		while (last_bit_pos < 16) {
			char first_bit = code >> 15;//�������� �������� ���������� ����
			if (first_bit) { //��������� � ��������� ���� � ������������ � �����
				currNode = currNode->right;
			}
			else {
				currNode = currNode->left;
			}
			++last_bit_pos;
			//���������, �� �������� �� ���� ������
			if (currNode->symbol != NULL)
				return currNode->symbol;
			code <<= 1;
		}
		
		return NULL;

	}

};