#include "Matrix.h"

#include <Arduino.h>


Matrix::Matrix(int rows, int columns) {

  if ((columns * rows * sizeof(int)) > MATRIX_MAX_SIZE) {
    if (Serial)
      Serial.println("Matrix too big! change max size or make the matrix smaller.");
    while(1);
  }

  _matrixArray = (int *) malloc(sizeof(int) * rows * columns);

  if (_matrixArray == NULL) {
    if (Serial)
      Serial.println("Not enough memory to create matrix!");
    while(1);   // should probably have something else here later
  }

  _rows = rows;
  _columns = columns;

  // make matrix a zero matrix first
  setZero();

};

void Matrix::print() {
  if (!Serial)
    return;
  
  // matrix coordinates are defined without 0 i.e 1,1 is the first element in the matrix, not 0,0.
Serial.println();
Serial.print("[");

  for (int i = 1; i <= _rows; i++) {
    for (int j = 1; j <= _columns; j++) {
      Serial.print(String(_matrixArray[_getIndex(i,j)]));
      if (j != _columns)
        Serial.print(", ");
      else if (i != _rows)
        Serial.println();
    }
  }
  Serial.print("]");
  Serial.println();
}

void Matrix::setValue(int row, int column, int value) {
  _matrixArray[_getIndex(row, column)] = value;
};

void Matrix::setZero() {
  for (int i = 1; i <= _rows; i++) {
    for (int j = 1; j <= _columns; j++) {
      setValue(i,j,0);
    }
  }
};

int Matrix::_getIndex(int row, int column) {
  return (((row - 1) * _columns) + (column - 1));
};