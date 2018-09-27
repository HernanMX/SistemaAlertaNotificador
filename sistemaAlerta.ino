//Incluimos la libreria LowPower
#include "LowPower.h"
//Asignacion del reed switch
#define puerta 2
//Asignacion del led de alarma
#define luz  13
//Asignacion del la buzzer para sonido alarma
#define alarma 9
//Declaracion de la varible que contendra la lectura de la puerta
int valorSwitch;
//Declaramos los parametros para emitir el sonido
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int tempo = 150;

void setup() {
  pinMode(puerta, INPUT_PULLUP);
  pinMode(luz, OUTPUT);
  pinMode (alarma, OUTPUT);
  //Se asigna una interrupcion 0 que va ligada a la puerta
  attachInterrupt( 0, activador, FALLING);
  //Se pone a dormir al arduino hasta que se presente una interrupcion
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
}

void loop() {
  //Si se detecta una interrupción en el pin 2 se enciende la
  //la alarma mientras la puerta este abierta
  detachInterrupt(0);
    while (valorSwitch == LOW){
    sonido();
    valorSwitch = digitalRead(puerta);
    }   
  //Se asigna una interrupcion 0 que va ligada a la puerta
  attachInterrupt( 0, activador, FALLING);
  //Se pone a dormir al arduino hasta que se presente una interrupcion
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  
}

void activador(){
  //Leemos el valor del reed switch
  valorSwitch = digitalRead(puerta);
}

void sonido(){ 
  //Metodo para hacer sonar la bocina con una melodia
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    //Pausa entre las notas
    delay(tempo / 2); 
  }
}

void playTone(int tone, int duration) {
  valorSwitch = digitalRead(puerta);
  if( valorSwitch == LOW){
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
      digitalWrite(luz, HIGH);
      digitalWrite(alarma, HIGH);
      delayMicroseconds(tone);
      digitalWrite(luz, LOW);
      digitalWrite(alarma, LOW);
      delayMicroseconds(tone);    
    }
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
