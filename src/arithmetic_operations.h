#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>  // for setprecision

// This file includes functions for basic matrices operations

// function to allocate memory for a matrix dynamically
int** allocateIntMatrix(int rows, int cols) {
  
  int** matrix;
  matrix = new int* [rows];
  for (int i=0; i<rows; ++i) {
    matrix[i] = new int[cols];
  }
  return matrix;
}

// function to free memory of a matrix
void deleteMatrix(int rows, int** matrix) {
  for (int i=0; i<rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void matrixSetValue(int ** A, int rows_A, int cols_A, int val) {
  for (int i=0; i<rows_A; ++i) {
    for (int j=0; j<cols_A; ++j) {
      A[i][j] = val;
    }
  }
}

