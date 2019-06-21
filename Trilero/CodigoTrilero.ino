//LIBRERIAS

#include <Servo.h>  //incluye librería servo
#include <CapacitiveSensor.h>  //incluye librería sensor capacitivo
#include <Wire.h>  //incluye 1º librería LCD
#include <LiquidCrystal_I2C.h>  //incluye 2º librería LCD


//PINES ARDUINO

const int hallLpin = A0; //pin sensor hall izquierda
const int hallCpin = A1; //pin sensor hall centro
const int hallRpin = A2; //pin sensor hall derecha
Servo myservoH;  //declara servo horizontal
Servo myservoV;  //declara servo vertical
CapacitiveSensor sensor = CapacitiveSensor(2, 3);  //pines sensor capacitivo
LiquidCrystal_I2C lcd(0x27, A4, A5);  //pines pantalla LCD

//VARIABLES
int sensorValueL = 0; //variable para sensor hall izquierdo
int sensorValueC = 0; //variable para sensor hall centro
int sensorValueR = 0; //variable para sensor hall derecho

//SE REALIZA UNA SOLA VEZ

void setup() {
 
  myservoH.attach(13);  //pin servo horizontal
  myservoV.attach(12);  //pin servo vertical
  myservoV.write(90);  //declara posición de inicio servo vertical
  myservoH.write(90);  //declara posición de inicio servo horizontal
  lcd.init();  //para controlar mediante módulo I2C
  lcd.backlight();  //para encender el fondo
  lcd.setCursor(0, 0);  //para posicionar el texto
}

//SE REALIZA POR SIEMPRE

void loop() {
 
  //LECTURA DE SENSORES
  //lecturas de sensores analogicos tipo hall
  sensorValueL = analogRead(hallLpin);
  sensorValueC = analogRead(hallCpin);
  sensorValueR = analogRead(hallRpin);
  //lectura de sensor capacitivo
  long lectura =  sensor.capacitiveSensor(30);
 
// MOSTRAR EN LA LCD DONDE ESTA
  if  (sensorValueL > 600 || sensorValueL < 300) {  //valores del sensor para saber donde esta la bolita
    lcd.clear();  //borrar texto LCD
    lcd.print("IZQUIERDA");  //texto que escribe en la LCD
  }
  else if  (sensorValueC > 600 || sensorValueC < 300) {  //valores del sensor para saber donde esta la bolita
    lcd.clear();  //borrar texto LCD
    lcd.print("CENTRO");  //texto que escribe en la LCD
  }

  else if  (sensorValueR > 600 || sensorValueR < 300) {  //valores del sensor para saber donde esta la bolita
    lcd.clear();  //borrar texto LCD
    lcd.print("DERECHA");  //texto que escribe en la LCD
  }
  else {
    lcd.clear();  //borrar texto LCD
    lcd.print("NO HAY BOLITA");  //texto que escribe en la LCD
  }

  // CD ACCIONAMOS EL ROBOT SE POSICIONA
  if (lectura > 100) {  //valores sensor capacitivo
    // donde esta la bolita
    for (int i = 0; i < 2; i++) {  //veces que debe repetir el movimiento de rastreo
      for (int i = 45; i < 135; i++) {  //declara en los grados que debe moverse el servo horizontal
        myservoH.write(i);  //posicion que debe tomar el servo horizontal
        myservoV.write(0);  //posicion que debe tomar el servo vertical
        delay(12);  //tiempo de espera
      }
      // donde esta la bolita
      for (int i = 135; i > 45; i--) {  //para que haga el rastreo en las dos direcciones
        myservoH.write(i);  //posicion que debe tomar el servo horizontal
        myservoV.write(0);  //posicion que debe tomar el servo vertical
        delay(12);  //tiempo de espera
      }
    }
    if  (sensorValueL > 600 || sensorValueL < 300) {  //valores del sensor para saber donde esta la bolita
      myservoH.write(135);  //posicion que debe tomar el servo horizontal
      myservoV.write(0);  //posicion que debe tomar el servo vertical
      lcd.clear();  //borrar texto LCD
      lcd.print("IZQUIERDA");  //texto que escribe en la LCD
    }

    else if  (sensorValueC > 600 || sensorValueC < 300) {  //valores del sensor para saber donde esta la bolita
      myservoH.write(90);  //posicion que debe tomar el servo horizontal
      myservoV.write(0);  //posicion que debe tomar el servo vertical
      lcd.clear();  //borrar texto LCD
      lcd.print("CENTRO");  //texto que escribe en la LCD
    }

    else if  (sensorValueR > 600 || sensorValueR < 300) {  //valores del sensor para saber donde esta la bolita
      myservoH.write(45);  //posicion que debe tomar el servo horizontal
      myservoV.write(0);  //posicion que debe tomar el servo vertical
      lcd.clear();  //borrar texto LCD
      lcd.print("DERECHA");  //texto que escribe en la LCD
    }
    else {
      myservoH.write(90);  //posicion que debe tomar el servo horizontal
      myservoV.write(90);  //posicion que debe tomar el servo vertical
      lcd.clear();  //borrar texto LCD
      lcd.print("NO HAY BOLITA");  //texto que escribe en la LCD
    }
  }
}






