#ifndef _MATRIX_ENUMS_
#define _MATRIX_ENUMS_

#define MATRIX_MAX_SIZE 50 //bytes; 50/2 = 25 is the maximum number of items in the buffer 

typedef enum {
  ROTATION_X, ROTATION_Y, ROTATION_Z, ROTATION_2D
} Rotation;

typedef enum {
  DEGREES, RADIANS
} AngleUnit;

#endif