#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define maximum_limit 250
#define minimum_limit 1

using namespace std;
int no_of_rows = 8, no_of_columns = 8;

int rand_number() {
	srand(time(NULL));
	int rand_number = (rand() % ((maximum_limit - minimum_limit) + 1)) + minimum_limit;
	return rand_number;
}
vector<vector <int> > iteration_multiplication(vector<vector <int> > A, vector<vector <int> > B)
{
	int no_of_rows = A.size();
	int no_of_columns = A[0].size();
	int dimZ = B[0].size();

	vector<vector <int> > result;
	result.resize(no_of_rows, vector<int>(dimZ, 0));
	
	for (int i = 0; i < no_of_rows; i++)
		for (int j = 0; j < dimZ; j++) {
			int Addition = 0;
			for (int k = 0; k < no_of_columns; k++)
				Addition = Addition + (A[i][k] * B[k][j]);
			result[i][j] = Addition;
		}
	return result;
}

void print(vector<vector <int> > result)
{
	int no_of_rows = result.size();
	int no_of_columns = result[0].size();
	cout << "\n";
	for (int i = 0; i < no_of_rows; i++) {
		for (int j = 0; j < no_of_columns; j++) {
			if (j == no_of_columns - 1)
				cout << result[i][j];
			else
				cout << result[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

vector<vector <int> > Addition(vector<vector <int> > A, vector<vector <int> > B) {

	int total_size = A.size();
	vector<vector <int> > result;
	result.resize(total_size, vector <int> (total_size, 0));
	int i, j;
	for (i = 0; i < total_size; i++) {
		for (j = 0; j < total_size; j++) {
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return result;
}

vector<vector <int> > Subtration(vector<vector <int> > A, vector<vector <int> > B) {

	int total_size = A.size();
	vector<vector <int> > result;
	result.resize(total_size, vector <int> (total_size, 0));
	int i, j;

	for (i = 0; i < total_size; i++) {
		for (j = 0; j < total_size; j++) {
			result[i][j] = A[i][j] - B[i][j];
		}
	}
	return result;
}

vector<vector <int> > strassen_multiplication(vector<vector <int> > A, vector<vector <int> > B) {

	int total_size = A.size();
	vector<vector <int> > result;
	result.resize(total_size, vector<int>(total_size, 0));
	if (total_size == 1) {
		result[0][0] = A[0][0] * B[0][0];
		return result;
	}
	else {
		vector<vector <int> > a11, a12, a21, a22;
		vector<vector <int> > b11, b12, b21, b22;
		vector<vector <int> > c11, c12, c21, c22;
		vector<vector <int> > p1, p2, p3, p4, p5, p6, p7;

		a11.resize(total_size/2, vector<int>(total_size/2, 0));
		a12.resize(total_size/2, vector<int>(total_size/2, 0));
		a21.resize(total_size/2, vector<int>(total_size/2, 0));
		a22.resize(total_size/2, vector<int>(total_size/2, 0));
		b11.resize(total_size/2, vector<int>(total_size/2, 0));
		b12.resize(total_size/2, vector<int>(total_size/2, 0));
		b21.resize(total_size/2, vector<int>(total_size/2, 0));
		b22.resize(total_size/2, vector<int>(total_size/2, 0));
		c11.resize(total_size/2, vector<int>(total_size/2, 0));
		c12.resize(total_size/2, vector<int>(total_size/2, 0));
		c21.resize(total_size/2, vector<int>(total_size/2, 0));
		c22.resize(total_size/2, vector<int>(total_size/2, 0));
		p1.resize(total_size/2, vector<int>(total_size/2, 0));
		p2.resize(total_size/2, vector<int>(total_size/2, 0));
		p3.resize(total_size/2, vector<int>(total_size/2, 0));
		p4.resize(total_size/2, vector<int>(total_size/2, 0));
		p5.resize(total_size/2, vector<int>(total_size/2, 0));
		p6.resize(total_size/2, vector<int>(total_size/2, 0));
		p7.resize(total_size/2, vector<int>(total_size/2, 0));

		vector<vector <int> > aResult;
		vector<vector <int> > bResult;
		aResult.resize(total_size/2, vector<int>(total_size/2, 0));
		bResult.resize(total_size/2, vector<int>(total_size/2, 0));

		int i, j;

		//divide matrices in 4 Subtration-matrices:
		for (i = 0; i < total_size/2; i++) {
			for (j = 0; j < total_size/2; j++) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + total_size/2];
				a21[i][j] = A[i + total_size/2][j];
				a22[i][j] = A[i + total_size/2][j + total_size/2];
				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + total_size/2];
				b21[i][j] = B[i + total_size/2][j];
				b22[i][j] = B[i + total_size/2][j + total_size/2];
			}
		}

		aResult = Addition(a11, a22); 
		bResult = Addition(b11, b22); 
		p1 = strassen_multiplication(aResult, bResult); 
		aResult = Addition(a21, a22); 
		p2 = strassen_multiplication(aResult, b11); 
		bResult = Subtration(b12, b22); 
		p3 = strassen_multiplication(a11, bResult); 
		bResult = Subtration(b21, b11); 
		p4 = strassen_multiplication(a22, bResult); 
		aResult = Addition(a11, a12); 
		p5 = strassen_multiplication(aResult, b22); 
		aResult = Subtration(a21, a11); 
		bResult = Addition(b11, b12);
		p6 = strassen_multiplication(aResult, bResult); 
		aResult = Subtration(a12, a22);
		bResult = Addition(b21, b22); 
		p7 = strassen_multiplication(aResult, bResult); 

			 //calcule the value of c21, c21, c11 e c22:

		c12 = Addition(p3, p5); 
		c21 = Addition(p2, p4); 
		aResult = Addition(p1, p4); 
		bResult = Addition(aResult, p7); 
		c11 = Subtration(bResult, p5); 
		aResult = Addition(p1, p3); 
		bResult = Addition(aResult, p6); 
		c22 = Subtration(bResult, p2); 
		// Groupe the results obtained in one matrix
		for (i = 0; i < total_size/2; i++) {
			for (j = 0; j < total_size/2; j++) {
				result[i][j] = c11[i][j];
				result[i][j + total_size/2] = c12[i][j];
				result[i + total_size/2][j] = c21[i][j];
				result[i + total_size/2][j + total_size/2] = c22[i][j];
			}
		}
	}
	return result;
}

int main()
{
	vector<vector <int> > A;
	vector<vector <int> > B;

	A.resize(no_of_rows, vector <int> (no_of_columns, 0));
	B.resize(no_of_rows, vector <int> (no_of_columns, 0));

	for (int i = 0; i < no_of_rows; i++) {
		for (int j = 0; j < no_of_columns; j++) {
			A[i][j] = rand_number();
			B[i][j] = rand_number();
		}
	}

	print(iteration_multiplication(A, B));
	print(strassen_multiplication(A, B));
	return 0;
}
