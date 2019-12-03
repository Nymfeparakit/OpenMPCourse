// MPI_Lab5_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>

using namespace std;

template<size_t n>
void print_matr(int(&a)[n][n]) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << a[i][j] << " ";
		}
		std::cout << endl;
	}

}

//checked
template<size_t n>
void calc_s1_s7(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//B12 - B22 || A12 - A22
	for (int i = 0; i < n / 2; ++i) {
		for (int j = n / 2; j < n;  ++j) {
			s[i][j - n / 2] = a[i][j] - a[i + n / 2][j];
		}
	}

}

//checked
template<size_t n>
void calc_s2_s10(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//A11 + A12
	for (int i = 0; i < n / 2; ++i) {
		for (int j = 0; j < n / 2; ++j) {
			s[i][j] = a[i][j] + a[i][j + n / 2];
		}
	}
}

template<size_t n>
void calc_s3_s8(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//A21 + A22
	for (int i = n / 2; i < n; ++i) {
		for (int j = 0; j < n / 2; ++j) {
			s[i][j] = a[i][j] + a[i][j + n / 2];
		}
	}
}

template<size_t n>
void calc_s4(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//A11 + A12
	for (int i = n / 2; i < n; ++i) {
		for (int j = 0; j < n / 2; ++j) {
			s[i][j] = a[i][j] + a[i][j + n / 2];
		}
	}
}

template<size_t n>
void calc_s5_s6(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//A11 + A22 || B11 + B22
	for (int i = 0; i < n / 2; ++i) {
		for (int j = 0; j < n / 2; ++j) {
			s[i][j] = a[i][j] + a[i + n / 2][j + n / 2];
		}
	}
}

template<size_t n>
void calc_s9(int(&a)[n][n], int(&s)[n / 2][n / 2])
{
	//A11 - A21
	for (int i = 0; i < n / 2; ++i) {
		for (int j = 0; j < n / 2; ++j) {
			s[i][j] = a[i][j] + a[i + n / 2][j];
		}
	}
}

template<size_t n>
void mul(int(&a)[n][n], int(&b)[n][n], int(&c)[n][n])
{
	if (n == 2) {
		c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
		c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
		c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
		c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
		return;
	}

	int s1[n / 2][n / 2];
	int s2[n / 2][n / 2];
	int s3[n / 2][n / 2];
	int s4[n / 2][n / 2];
	int s5[n / 2][n / 2];
	int s6[n / 2][n / 2];
	int s7[n / 2][n / 2];
	int s8[n / 2][n / 2];
	int s9[n / 2][n / 2];
	int s10[n / 2][n / 2];

	//TODO объединить вызовы
	calc_s1_s7(b, s1);
	calc_s2_s10(a, s2);
	calc_s3_s8(a, s3);
	calc_s4(b, s4);
	calc_s5_s6(a, s5);
	calc_s5_s6(b, s6);
	calc_s1_s7(a, s7);
	calc_s3_s8(b, s8);
	calc_s9(a, s9);
	calc_s2_s10(b, s10);

	int p1[n / 2][n / 2];
	int p2[n / 2][n / 2];
	int p3[n / 2][n / 2];
	int p4[n / 2][n / 2];
	int p5[n / 2][n / 2];
	int p6[n / 2][n / 2];
	int p7[n / 2][n / 2];

	int a11[n / 2][n / 2];
	int a22[n / 2][n / 2];
	int b11[n / 2][n / 2];
	int b22[n / 2][n / 2];

	//std::copy(&a[0][0], &a[0][0] + (n / 2)*(n / 2), a11);

	//mul()

	//return c;
} 


int main()
{
	const int size = 4;
	int a[size][size];
	int b[size][size];

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] диапазон

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			a[i][j] = (int)dist6(rng);
			b[i][j] = (int)dist6(rng);
		}
		cout << endl;
	}

	cout << "A: " << endl;
	print_matr(a);
	cout << "B: " << endl;
	print_matr(b);

	int c[size][size];
	mul(a, b, c);
	
	cout << "C: " << endl;
	print_matr(c);

    return 0;
}

