#ifndef _MATRIX_H_
#define _MATRIX_

#include <Arduino.h>

#define MATRIX_MAX_SIZE 50 //bytes; 50/2 = 25 is the maximum number of items in the buffer

class Matrix {
  public:
  
    Matrix(int rows = 3, int columns = 3);

    void setValue(int row, int column, int value);
    
    void setZero();

    void print();

  private:

    int _getIndex(int row, int column);

    int * _matrixArray;

    int _rows;
    int _columns;

};




#endif