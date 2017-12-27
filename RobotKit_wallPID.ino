// @author Tomas de Camino Beck
// Dic 2017

#include <RobotKit.h>

int error=0;
int dif,difAnt=0;
const float Kp=1.1;
const float Kd=1.3;

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  dif = analogRead(A0) - analogRead(A2);
  error = floor(Kp*(dif)+Kd*(difAnt-dif));
  difAnt=dif;
  int d0 = constrain(255 - error, 0, 255);//velocidad izquierda
  int d1 = constrain(255 + error, 0, 255);//velcidad derecha
  //revisa el sensor central para dar vuelta
  if (analogRead(A1) < 980){
    stopMotors();
    delay(200);
    backward(150, 100);
    pivotLeft(200, 450);
  }
  //avanza hacia adelante con las velocidades calculadas
  forward(d0, d1,5);
}
