#include "Matrix.h"

#include <Arduino.h>


Matrix::Matrix(int rows, int columns) {

  if ((columns * rows * sizeof(float)) > MATRIX_MAX_SIZE) {
    if (Serial)
      Serial.println("Matrix too big! change max size or make the matrix smaller.");
    while(1);
  }

  _matrixArray = (float *) malloc(sizeof(float) * rows * columns);

  if (_matrixArray == NULL) {
    if (Serial)
      Serial.println("Not enough memory to create matrix!");
    while(1);   // should probably have something else here later
  }

  _rows = rows;
  _columns = columns;

  // make matrix a zero matrix first
  setAll(0);

};

bool Matrix::rotate(Rotation rotation, AngleUnit unit, float angleRotation) {

  //verify that rotation is applied to a 1x3 matrix
  if ((_rows != 1) || (_columns != 3 && _columns != 2))
    return false;

  float angle = angleRotation;
  float newMatrix[_columns];        // only 1 row, so only need to consider columns
  float X = _matrixArray[_getIndex(1, 1)];
  float Y = _matrixArray[_getIndex(1, 2)];
  float Z = _matrixArray[_getIndex(1, 3)];

  //convert everything to radians
  if (unit == DEGREES)
    angle = ((angle * PI) / 180);


  if (rotation == ROTATION_X) {
    newMatrix[0] = X;                                   //X
    newMatrix[1] = (Y * cos(angle) + Z * sin(angle));   //Y
    newMatrix[2] = (Z * cos(angle) - Y * sin(angle));   //Z
  }
  else if (rotation == ROTATION_Y) {
    newMatrix[0] = (X * cos(angle) - Z * sin(angle));   //X
    newMatrix[1] = Y;                                   //Y
    newMatrix[2] = (X * sin(angle) + Z * cos(angle));   //Z
  }
  else if (rotation == ROTATION_Z) {
    newMatrix[0] = (X * cos(angle) + Y * sin(angle));   //X
    newMatrix[1] = (Y * cos(angle) - X * sin(angle));   //Y
    newMatrix[2] = Z;                                   //Z
  }
  else if (rotation == ROTATION_2D) {
    newMatrix[0] = (X * cos(angle) + Y * sin(angle));   //X
    newMatrix[1] = (Y * cos(angle) - X * sin(angle));   //Y
  }
  else 
    return false;

  for (int i = 1; i <= _columns; i++) {
  _matrixArray[_getIndex(1, i)] = newMatrix[i - 1];
  }

  return true;
}


void Matrix::print() {
  if (!Serial)
    return;
  
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
};


void Matrix::setValue(int row, int column, float value) {
  _matrixArray[_getIndex(row, column)] = value;
};


float Matrix::getValue(int row, int column) {
  return (float) _matrixArray[_getIndex(row, column)];
};

void Matrix::multiplyConstant(float value) {
  for (int i = 1; i <= _rows; i++) {
    for (int j = 1; j <= _columns; j++) {
      _matrixArray[_getIndex(i, j)] *= value;
    }
  }
};


void Matrix::setAll(float value) {
  for (int i = 1; i <= _rows; i++) {
    for (int j = 1; j <= _columns; j++) {
      setValue(i,j,value);
    }
  }
};

int Matrix::_getIndex(int row, int column) {
  return (((row - 1) * _columns) + (column - 1));
};