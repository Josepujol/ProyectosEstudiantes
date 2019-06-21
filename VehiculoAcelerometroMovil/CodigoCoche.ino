#include <SoftwareSerial.h>
SoftwareSerial I2CBT(10, 11);// El TX del módulo BT va al pin 10 del Arduino
// El RX del módulo BT va al pin 11 del Arduino
int incomingByte;      // variable para leer los bytes de entrada
int value = 0;  // variable para almacenar el valor numerico
int velocity = 255;
int velocity2 = 255;
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Seleccione qué 'puerto' M1, M2, M3 or M4
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // configurar la biblioteca Serial en 9600 bps
  I2CBT.begin(9600);
  AFMS.begin(1000);  // crear con la frecuencia por defecto 1.6KHz
  // Establezca la velocidad de inicio, de 0 (apagado) a 255 (velocidad máxima)
  velocidadMotores(velocity, velocity, velocity, velocity);
  sentidoMotores(FORWARD, FORWARD, FORWARD, FORWARD);
  sentidoMotores(RELEASE, RELEASE, RELEASE, RELEASE);
}

void loop() {
  if (I2CBT.available() > 0) {
    incomingByte = I2CBT.read();
    Serial.print("Caracter=");
    Serial.println(incomingByte);
    if (incomingByte >= '0' && incomingByte <= '9') {
      //Acumula los datos numericos multiplicando por 10 el valor acumulado
      value = (value * 10) + (incomingByte - '0'); // Resta 48 que es el valor decimal del 0 ASCII
    }
    else if (incomingByte == '>') // uso > como finalizador
    {
      velocity = value;   // Guarda el valor en la variable pwmValue
      velocity2 = velocity - velocity * 0.35;
      Serial.print("Velocidad=");
      Serial.println(velocity);     // Lo imprime por monitor serie
      value = 0;
    }
    else if (incomingByte == 'F') {   //Adelante
      velocidadMotores(velocity, velocity, velocity, velocity);
      sentidoMotores(FORWARD, FORWARD, FORWARD, FORWARD);
    }
    else if (incomingByte == 'D') {   //Adelante en diagonal hacia la derecha
     velocidadMotores(velocity, velocity2, velocity2, velocity);
      sentidoMotores(FORWARD, FORWARD, FORWARD, FORWARD);
    }
    else if (incomingByte == 'A') {   //Adelante en diagonal hacia la izquierda
      velocidadMotores(velocity2, velocity, velocity, velocity2);
      sentidoMotores(FORWARD, FORWARD, FORWARD, FORWARD);
    }
    else if (incomingByte == 'B') {   //Atrás
      velocidadMotores(velocity, velocity, velocity, velocity);
      sentidoMotores(BACKWARD, BACKWARD, BACKWARD, BACKWARD);
    }
    else if (incomingByte == 'I') {   //Atrás en diagonal hacia la izquierda
      velocidadMotores(velocity2, velocity, velocity, velocity2);
      sentidoMotores(BACKWARD, BACKWARD, BACKWARD, BACKWARD);
    }
    else if (incomingByte == 'P') {   //Atrás en diagonal hacia la derecha
      Serial.println("AtrasD");
      velocidadMotores(velocity, velocity2, velocity2, velocity);
      sentidoMotores(BACKWARD, BACKWARD, BACKWARD, BACKWARD);
    }
    else if (incomingByte == 'S') {   //Parado
      sentidoMotores(RELEASE, RELEASE, RELEASE, RELEASE);
    }
    else if (incomingByte == 'R') {   //Derecha(sobre su eje)
      velocidadMotores(velocity, velocity, velocity, velocity);
      sentidoMotores(FORWARD, BACKWARD, BACKWARD, FORWARD);
    }
    else if (incomingByte == 'L') {   //Izquierda(sobre su eje)
      velocidadMotores(velocity, velocity, velocity, velocity);
      sentidoMotores(BACKWARD, FORWARD, FORWARD, BACKWARD);
    }
  }
}
//Ahora van las funciones para acortar el código


void velocidadMotores(int vel1, int vel2, int vel3, int vel4) {
  //Se utiliza esta función para establecer la velocidad de los motores          myMotor->setSpeed(vel1);//Establece velocidad del motor
  myMotor2->setSpeed(vel2);
  myMotor3->setSpeed(vel3);
  myMotor4->setSpeed(vel4);
}

void sentidoMotores(int sent1, int sent2, int sent3, int sent4) {
  //Se utiliza esta función para establecer el sentido de giro de los motores
  myMotor->run(sent1);//Establece sentido de giro del motor
  myMotor2->run(sent2);
  myMotor3->run(sent3);
  myMotor4->run(sent4);
}
