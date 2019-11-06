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

	//проходится по дереву, чтобы составить коды символов
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

	//строит дерево на основе частот
	void make(std::map <char, int> symbolsFrequencies) {

		std::vector<Node*> orphans;//узлы без родителей
		typedef std::function<bool(Node* node1, Node* node2)> Comparator;
		//comparator для сортировки узлов по частотам
		Comparator compFunctor =
			[](Node* node1, Node* node2) {
			return node1->frequency > node2->frequency;
		};
		//в начале все узлы не имеют родителя
		for (std::map<char, int>::iterator it = symbolsFrequencies.begin();
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
			orphans.pop_back(); //выталкиваем их, т.к. теперь у них есть родители
			orphans.pop_back();
			//Создаем для них родителя
			Node* parentNode = new Node(NULL, leftNode->frequency + rightNode->frequency);
			parentNode->left = leftNode;
			parentNode->right = rightNode;
			orphans.push_back(parentNode);//теперь этот узел не имеет родителя
			sort(orphans.begin(), orphans.end(), compFunctor);//снова сортируем по частотам
		}
		rootNode = orphans.front();//единственный оставшийся узел является корнем дерева
		std::vector<char> code;
		traverseToCreateCodes(rootNode, code);//проходимся по дереву, чтобы составить коды
		int a = 0;
	}

	char findFirstSymbolInCode(unsigned short code, int& last_bit_pos) // Было char code
	{

		char firstSymbol = 0;
		last_bit_pos = 0;
		//проходимся по дереву до тех пор, пока не найдем символ
		Node *currNode = rootNode;
		while (last_bit_pos < 16) {
			char first_bit = code >> 15;//получаем значение следующего бита
			if (first_bit) { //переходим к дочернему узлу в соответствии с битом
				currNode = currNode->right;
			}
			else {
				currNode = currNode->left;
			}
			++last_bit_pos;
			//проверяем, не является ли узел листом
			if (currNode->symbol != NULL)
				return currNode->symbol;
			code <<= 1;
		}
		
		return NULL;

	}

};