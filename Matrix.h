#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <Arduino.h>

#include "enums.h"

class Matrix {
  public:
  
    Matrix(int rows = 3, int columns = 3);

    bool rotate(Rotation rotation, AngleUnit unit, float angle); 

    void multiplyConstant(float value);

    void setValue(int row, int column, float value);
    
    float getValue(int row, int column);

    void setAll(float value);

    void print();

  private:

    int _getIndex(int row, int column);

    float * _matrixArray;

    int _rows;
    int _columns;

};




#endif