#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int n = 4;

long long costMatrixA[n][n];
long long costMatrixB[n][n];
long long productMat[n][n];

long long minCostMatrixA[n][n];
long long maxCostMatrixB[n][n];

int main() {
	int i, j, k;
	srand(time(0));

	// initialisation
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			costMatrixA[i][j] = 1 + rand() % 10;
			costMatrixB[i][j] = 1 + rand() % 10;
			productMat[i][j] = 0;
		}
	}

	// Cost for last element of A
	minCostMatrixA[n - 1][n - 1] = costMatrixA[n - 1][n - 1];

	// Cost for last row and last column of A
	for (i = n - 2; i >= 0; --i) {
		minCostMatrixA[i][n - 1] = costMatrixA[i][n - 1] + minCostMatrixA[i + 1][n - 1];
		minCostMatrixA[n - 1][i] = costMatrixA[n - 1][i] + minCostMatrixA[n - 1][i + 1];
	}

	// Cost for all other elements of A
	for (i = n - 2; i >= 0; --i) {
		for (j = n - 2; j >= 0; --j) {
			minCostMatrixA[i][j] = costMatrixA[i][j] + min(minCostMatrixA[i + 1][j], minCostMatrixA[i][j + 1]);
		}
	}

	// Same procedure for B, we do them separately to maximize chance of cache hits
	//
	maxCostMatrixB[n - 1][n - 1] = costMatrixB[n - 1][n - 1];

	// Cost for last row and last column
	for (i = n - 2; i >= 0; --i) {
		maxCostMatrixB[i][n - 1] = costMatrixB[i][n - 1] + maxCostMatrixB[i + 1][n - 1];
		maxCostMatrixB[n - 1][i] = costMatrixB[n - 1][i] + maxCostMatrixB[n - 1][i + 1];
	}

	for (i = n - 2; i >= 0; --i) {
		for (j = n - 2; j >= 0; --j) {
			maxCostMatrixB[i][j] = costMatrixB[i][j] + max(maxCostMatrixB[i + 1][j], maxCostMatrixB[i][j + 1]);
		}
	}

	// https://en.wikipedia.org/wiki/Locality_of_reference#Matrix_multiplication
	// Block multiplication from wikipedia
//	for (ii = 0; ii < SIZE; ii += BLOCK_SIZE)
//		for (kk = 0; kk < SIZE; kk += BLOCK_SIZE)
//			for (jj = 0; jj < SIZE; jj += BLOCK_SIZE)
//				maxi = min(ii + BLOCK_SIZE, SIZE);
//	for (i = ii; i < maxi; i++)
//		maxk = min(kk + BLOCK_SIZE, SIZE);
//	for (k = kk; k < maxk; k++)
//		maxj = min(jj + BLOCK_SIZE, SIZE);
//	for (j = jj; j < maxj; j++)
//		C[i][j] = C[i][j] + A[i][k] * B[k][j];

	//creating productMat as explained in the beginning
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++) ;
//				productMat[i][j] += FindMinCostA(i, k, n) * FindMaxCostB(k, j, n);
		}
	}

	//filter of size 4 x n
	long long filterArray[4][n];
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < n; j++)
			filterArray[i][j] = rand() % 2;
	}
	// matrix of dimension (n/c) x 1 where c = 4
	long long finalMat[n / 4];
	// applying the filter
	for (i = 0; i < n - 4; i += 4)
	{
		long long sum = 0;
		// dot product of 4xn portion of productMat
		for (j = 0; j < n; j++)
		{
			for (int filterRow = 0; filterRow < 4; filterRow++)
			{
				sum += productMat[i + filterRow][j];
			}
		}
		finalMat[i / 4] = sum;
	}

	return 0;
}
