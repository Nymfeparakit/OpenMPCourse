// MPI_Lab5_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>
#include <complex>
typedef std::complex<double> dcomp;

using namespace std;

complex<double> **allocate_2d_array(int size) {

	complex<double> *data = new complex<double>[size * size];
	complex<double> **array = new complex<double>*[size];
	for (int i = 0; i<size; i++)
		array[i] = &(data[size*i]);

	return array;

}

void deallocate_2d_array(complex<double> **a, int size) {

	//for (int i = 0; i < size; ++i) {
		delete[] a[0];
	//}
	delete[] a;

}

template<size_t n>
void print_matr(int(&a)[n][n]) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << a[i][j] << " ";
		}
		std::cout << endl;
	}

}

void print_matr(complex<double>** a, int n) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << a[i][j] << " ";
		}
		std::cout << endl;
	}

}

//из общего массива матриц выбирает одну конкретную
void select_matr(complex<double>* matrices, complex<double>**& matr,
	int matr_num, int matr_size)
{
	for (int i = 0; i<matr_size; i++)
		matr[i] = &(matrices[matr_num*matr_size*matr_size + i * matr_size]);
}

void divide_matr(complex<double> **a, complex<double>**& a11,
	complex<double>**& a12, complex<double>**& a21,
	complex<double> **& a22, int size)
{

	a11 = allocate_2d_array(size / 2);
	a12 = allocate_2d_array(size / 2);
	a21 = allocate_2d_array(size / 2);
	a22 = allocate_2d_array(size / 2);

	for (int i = 0; i < size / 2; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			a11[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < size / 2; ++i) {
		for (int j = size / 2; j < size; ++j) {
			a12[i][j - size / 2] = a[i][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			a21[i - size / 2][j] = a[i][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = size / 2; j < size; ++j) {
			a22[i - size / 2][j - size / 2] = a[i][j];
		}
	}

}

void sum_matr(complex<double> **a, complex<double> **b, complex<double> **res, int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			dcomp aa = a[i][j];
			dcomp bb = b[i][j];
			dcomp cc = res[i][j];
			res[i][j] = a[i][j] + b[i][j];
		}
	}
}

void min_matr(complex<double> **a, complex<double> **b, complex<double> **res, int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			res[i][j] = a[i][j] - b[i][j];
		}
	}
}

void split_res_matr(dcomp **p[7], dcomp** c, int size) 
{
	dcomp **c11; dcomp **c12; dcomp **c21; dcomp **c22;
	c11 = allocate_2d_array(size / 2);
	c12 = allocate_2d_array(size / 2);
	c21 = allocate_2d_array(size / 2);
	c22 = allocate_2d_array(size / 2);

	sum_matr(p[3], p[4], c11, size / 2);
	min_matr(c11, p[1], c11, size / 2);
	sum_matr(c11, p[5], c11, size / 2);

	sum_matr(p[0], p[1], c12, size / 2);

	sum_matr(p[2], p[3], c21, size / 2);

	sum_matr(p[4], p[0], c22, size / 2);
	min_matr(c22, p[2], c22, size / 2);
	min_matr(c22, p[6], c22, size / 2);

	for (int i = 0; i < size / 2; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			c[i][j] = c11[i][j];
		}
	}

	for (int i = 0; i < size / 2; ++i) {
		for (int j = size / 2; j < size; ++j) {
			c[i][j] = c12[i][j - size / 2];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			c[i][j] = c21[i - size / 2][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = size / 2; j < size; ++j) {
			c[i][j] = c22[i - size / 2][j - size / 2];
		}
	}

	cout << "c: " << endl;
	print_matr(c, size);

	deallocate_2d_array(c11,size / 2);
	deallocate_2d_array(c12, size / 2);
	deallocate_2d_array(c21, size / 2);
	deallocate_2d_array(c22, size / 2);
}

void mul(complex<double> **a, complex <double> **b, complex <double> **c, int n)
{
	if (n == 2) {
		c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
		c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
		c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
		c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
		return;
	}

	dcomp **s[10];
	for (int i = 0; i < 10; ++i) {
		s[i] = allocate_2d_array(n / 2);
	}

	dcomp **a11; dcomp **a12; dcomp** a21; dcomp** a22;
	dcomp **b11; dcomp **b12; dcomp** b21; dcomp** b22;

	divide_matr(a, a11, a12, a21, a22, n);
	divide_matr(b, b11, b12, b21, b22, n);

	cout << "a11: " << endl;
	print_matr(a11, n / 2);
	cout << "a12: " << endl;
	print_matr(a12, n / 2);
	cout << "a21: " << endl;
	print_matr(a21, n / 2);
	cout << "a22: " << endl;
	print_matr(a22, n / 2);

	min_matr(b12, b22, s[0], n / 2);
	sum_matr(a11, a12, s[1], n / 2);
	sum_matr(a21, a22, s[2], n / 2);
	min_matr(b21, b11, s[3], n / 2);
	sum_matr(a11, a22, s[4], n / 2);
	sum_matr(b11, b22, s[5], n / 2);
	min_matr(a12, a22, s[6], n / 2);
	sum_matr(b21, b22, s[7], n / 2);
	min_matr(a11, a21, s[8], n / 2);
	sum_matr(b11, b12, s[9], n / 2);

	for (int i = 0; i < 10; ++i) {
		cout << "s" << i + 1 << endl;
		print_matr(s[i], n / 2);
		cout << endl;
	}

	dcomp** p[7];
	for (int i = 0; i < 7; ++i) {
		p[i] = allocate_2d_array(n / 2);
	}

	mul(a11, s[0], p[0], n / 2);
	mul(s[1], b22, p[1], n / 2);
	mul(s[2], b11, p[2], n / 2);
	mul(a22, s[3], p[3], n / 2);
	mul(s[4], s[5], p[4], n / 2);
	mul(s[6], s[7], p[5], n / 2);
	mul(s[8], s[9], p[6], n / 2);

	for (int i = 0; i < 7; ++i) {
		cout << "p" << i + 1 << endl;
		print_matr(p[i], n / 2);
		cout << endl;
	}

	for (int i = 0; i < 10; ++i) {
		deallocate_2d_array(s[i], n / 2);
	}

	//c = allocate_2d_array(n);
	split_res_matr(p, c, n);

	cout << "c again: " << endl;
	print_matr(c, n);

	for (int i = 0; i < 7; ++i) {
		deallocate_2d_array(p[i], n / 2);
	}

	deallocate_2d_array(a11, n / 2);
	deallocate_2d_array(a12, n / 2);
	deallocate_2d_array(a21, n / 2);
	deallocate_2d_array(a22, n / 2);
	deallocate_2d_array(b11, n / 2);
	deallocate_2d_array(b12, n / 2);
	deallocate_2d_array(b21, n / 2);
	deallocate_2d_array(b22, n / 2);

} 

int main()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] диапазон
	int number_of_matrices = 20;
	int matrix_size = 4;
	complex<double> *recv_matrices = new complex<double>[number_of_matrices*matrix_size*matrix_size];
	for (int j = 0; j < number_of_matrices*matrix_size*matrix_size; ++j) {
		//recv_matrices[j] = dist6(rng);
		recv_matrices[j] = 1;
		cout << recv_matrices[j] << " ";
		if ((j + 1) % (matrix_size*matrix_size) == 0)
		{
			cout << endl;
		}
	}

	dcomp **first_matr = allocate_2d_array(matrix_size);
	for (int i = 1; i < number_of_matrices; ++i) {

		if (i == 1) {
			select_matr(recv_matrices, first_matr, i - 1, matrix_size);
		}
		dcomp** second_matr = allocate_2d_array(matrix_size);
		select_matr(recv_matrices, second_matr, i, matrix_size);
		mul(first_matr, second_matr, first_matr, matrix_size);

	}

	cout << "result: " << endl;
	print_matr(first_matr, matrix_size);

	/*cout << "third matr: " << endl;
	complex<double> **third_matr = new complex<double>*[matrix_size];
	select_matr(recv_matrices, third_matr, 2, matrix_size);
	print_matr(third_matr, matrix_size);
	
	cout << "fourth matr: " << endl;
	dcomp **fourth_matr = new dcomp*[matrix_size];
	select_matr(recv_matrices, fourth_matr, 3, matrix_size);
	print_matr(fourth_matr, matrix_size);

	dcomp **res = allocate_2d_array(matrix_size);
	mul(third_matr, fourth_matr, res, matrix_size);
	cout << "res: " << endl;
	print_matr(res, matrix_size);*/

    return 0;
}

