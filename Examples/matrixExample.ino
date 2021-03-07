#include <Matrix.h>

#define INCREMENT 0.01
#define RATE 10

Matrix matrix(1,3);

void setup() {
  Serial.begin(9600);

  matrix.setAll(0);

//  Serial.println(matrix.rotate(ROTATION_Z, RADIANS, PI));
  matrix.setValue(1,1, matrix.getValue(1,1) + INCREMENT);

}

void loop() {
  matrix.setValue(1,2,trajectory(matrix.getValue(1,1)));

  Serial.println(matrix.getValue(1,2));

  matrix.setValue(1,1, matrix.getValue(1,1) + INCREMENT);
//  Serial.println(matrix.getValue(1,1));


  delay(RATE);
}

float trajectory(float x) {
  return 10*pow(sin(x),1);
}
