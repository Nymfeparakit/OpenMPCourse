#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "time.h"
#include "fstream"
#include "vector"
#include "windows.h"
#include "math.h"

using namespace std;

class longint
{
public:
	vector<char> number;
	longint operator=(const longint &inumber)
	{
		number = inumber.number;
		return *this;
	}
	bool operator>(const longint &inumber)
	{
		int i;
		if (number.size() > inumber.number.size())
			return true;
		if (number.size() < inumber.number.size())
			return false;
		for (i = number.size() - 1; i >= 0; i--)
		{
			if (number[i] > inumber.number[i])
				return true;
			if (number[i] < inumber.number[i])
				return false;
		}
		return false;
	}
	bool operator==(const longint &inumber)
	{
		return number == inumber.number;
	}
	longint()
	{
		number = vector<char>(1, 0);
	}
	longint(char* filename)
	{
		FILE* in = fopen(filename, "r");
		char buf;
		int read = fscanf(in, "%c", &buf);
		while (read != -1)
		{
			number.push_back(buf - 48);
			read = fscanf(in, "%c", &buf);
		}
		fclose(in);
	}
	longint(const longint &inumber)
	{
		number = inumber.number;
	}
	longint(const vector<char>& ivec)
	{
		number = ivec;
	}
	longint(long numb)
	{
		if (numb == 0)
			number.push_back(0);
		while (numb > 0)
		{
			number.push_back(numb & 1);
			numb >>= 1;
		}
	}
	void print()
	{
		for (int i = number.size() - 1; i >= 0; i--)
		{
			printf("%c", number[i] + 48);
		}
		printf("\n");
	}
	void print(char* str)
	{
		FILE* out = fopen(str, "w");
		for (int i = number.size() - 1; i >= 0; i--)
		{
			fprintf(out, "%c", number[i] + 48);
		}
		printf("\n");
		fclose(out);
	}
	bool iszero()
	{
		return (number.size() == 1) && (number[0] == 0);
	}
	size_t size()
	{
		return number.size();
	}
	//операции сдвига с сохранением числа разрядов
	void lshift()
	{
		number.pop_back();
		number.insert(number.begin(), 0);
	}
	void lshift(int k)
	{
		int i;
		for (i = 0; i < k; i++)
		{
			number.pop_back();
			number.insert(number.begin(), 0);
		}
	}
	void rshift()
	{
		number.erase(number.begin());
		number.push_back(0);
	}
	void rshift(int k)
	{
		int i;
		for (i = 0; i < k; i++)
		{
			number.erase(number.begin());
			number.push_back(0);
		}
	}
	//операции умножения и целочисленного деления на два
	void mult2()
	{
		number.insert(number.begin(), 0);
	}
	void mult2(int k)
	{
		number.insert(number.begin(), k, 0);
	}
	void div2()
	{
		number.erase(number.begin());
		if (number.empty())
			number = vector<char>(1, 0);
	}
	void div2(int k)
	{
		int m = min(number.size(), k);
		number.erase(number.begin(), number.begin() + m);
		if (number.empty())
			number = vector<char>(1, 0);
	}
	//сложение
	void add(const longint inumber)
	{
		if (inumber.number.size() == 1 && inumber.number[0] == 0)
			return;
		vector<char> result(max(number.size(), inumber.number.size()) + 1);
		vector<char> minlength = (number.size() > inumber.number.size()) ? inumber.number : number;
		vector<char> maxlength = (number.size() <= inumber.number.size()) ? inumber.number : number;
		int min_length = (number.size() > inumber.number.size()) ? inumber.number.size() : number.size();
		int max_length = (number.size() <= inumber.number.size()) ? inumber.number.size() : number.size();
		int i;
		char bitcarry = 0;
		for (i = 0; i < min_length; i++)
		{
			result[i] = minlength[i] ^ maxlength[i] ^ bitcarry;
			bitcarry = (minlength[i] ^ maxlength[i]) & bitcarry | (minlength[i] & maxlength[i]);
		}
		for (i = min_length; i < result.size() - 1; i++)
		{
			result[i] = maxlength[i] ^ bitcarry;
			bitcarry = maxlength[i] & bitcarry;
		}
		result[result.size() - 1] = bitcarry;
		number = result;
		while (number[number.size() - 1] == 0 && number.size() > 1)
		{
			number.pop_back();
		}
	}
	//добавление числа, сдвинутого на k разрядов влево
	void add(const longint inumber, int k)
	{
		if (inumber.number.size() == 1 && inumber.number[0] == 0)
			return;
		vector<char> result(max(number.size(), inumber.number.size()) + k + 1);

		vector<char> first = number;
		vector<char> second = inumber.number;

		if (first.size() < result.size())
			first.insert(first.end(), result.size() - first.size(), 0);
		if (second.size() < result.size())
			second.insert(second.end(), result.size() - second.size() - k, 0);


		int i;
		char bitcarry = 0;
		for (i = 0; i < k; i++)
			result[i] = first[i];
		for (i = k; i < result.size(); i++)
		{
			result[i] = first[i] ^ second[i - k] ^ bitcarry;
			bitcarry = (first[i] ^ second[i - k]) & bitcarry | (first[i] & second[i - k]);
		}
		number = result;
		while (number[number.size() - 1] == 0 && number.size() > 1)
		{
			number.pop_back();
		}
	}
	//вычитание
	void sub(const longint inumber)
	{

		vector<char> result(max(number.size(), inumber.number.size()));
		vector<char> b = inumber.number;
		vector<char> a = number;
		int b_length = inumber.number.size();
		int a_length = number.size();
		int i;
		char bitcarry = 0;
		for (i = 0; i < b_length; i++)
		{
			result[i] = b[i] ^ a[i] ^ bitcarry;
			bitcarry = (bitcarry ^ 1) & (a[i] ^ 1) & b[i] | bitcarry & (a[i] ^ 1 | b[i]);
		}
		for (i = b_length; i < result.size(); i++)
		{
			result[i] = a[i] ^ bitcarry;
			bitcarry = (a[i] ^ 1) & bitcarry;
		}
		number = result;
		while (number[number.size() - 1] == 0 && number.size() > 1)
		{
			number.pop_back();
		}
	}
	//противоположный элемент по модулю 2^n+1, где n - количество бит в записи числа
	void inv(int n)
	{
		if (number.size() == 1 && number[0] == 0)
			return;
		longint module(1);
		module.mult2(n);
		module.add(longint(1));

		longint temp(number);

		while (temp > module)
			temp.sub(module);

		module.sub(temp);
		number = module.number;

	}

	longint operator+(const longint &inumber)
	{
		longint result(number);
		result.add(inumber);
		return result;
	}
	longint operator-(const longint &inumber)
	{
		longint result(number);
		result.sub(inumber);
		return result;
	}

	//отбросить старшие разряды, начиная с n
	void lowbits(int n)
	{
		if (number.size() > n)
			number.erase(number.begin() + n, number.end());
	}
	//удаление незначащих нулей
	void delete_zeros()
	{
		while (number[number.size() - 1] == 0 && (number.size() > 1))
			number.pop_back();
	}


};