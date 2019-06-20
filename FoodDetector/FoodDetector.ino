#include <SoftwareSerial.h>
SoftwareSerial I2CBT(10, 11);
// El TX del módulo BT va al pin 10 del Arduino
// El RX del módulo BT va al pin 11 del Arduino

int incomingByte;      // variable para leer los bytes de entrada
// variables temperatura
const int fruitSense = A0; // pin conexion
int fruitResistance = 0; // variable almacenar lectura

void setup() {
  // inicializamos la comunicacion serie
  Serial.begin(9600);
  // inicializamos la comunicacion serie BT
  I2CBT.begin(9600);
}

void loop() {

  // leemos el sensor
  // comprobamos si hay datos de entrada
  if (I2CBT.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = I2CBT.read();
    // si el byte es T envia dato de temperatura
    if (incomingByte == 'T') {

      fruitResistance = analogRead(fruitSense);
// clasificamos según la fruta que sea
      Serial.print("Resistance:");
      Serial.print(fruitResistance);

// clasificamos según la fruta que sea
      if (fruitResistance > 40 & fruitResistance < 400) {  // si resistencia entre 400 y 550 se imprime y se envía el dato
        Serial.println("Humano");
        I2CBT.write("H");
      }

      if (fruitResistance > 700 & fruitResistance < 790) {  // si resistencia entre 400 y 550 se imprime y se envía el dato
        Serial.println("Mandarina");
        I2CBT.write("N");
      }

      if (fruitResistance > 790 & fruitResistance < 950) {  // si resistencia entre 600 y 740 se imprime y se envía el dato

        Serial.println("Plátano");
        I2CBT.write("A");

      }


      if (fruitResistance > 950 & fruitResistance < 1050) {  // si resistencia entre 950 y 1000 se imprime y se envía el dato

        Serial.println("Pepinillo");
        I2CBT.write("P");
      }


      // si el valor no está en esos rangos se informa
      if (fruitResistance > 0 & fruitResistance < 40) {
        Serial.println ("Sin comida");
        I2CBT.print("S");
      }

    }
}
}

