
//Asignacion del reed switch
#define reed 2
//Asignacion del led de alarma
#define led  13
//Asignacion del la buzzer para sonido alarma
#define buzzer 9

int duracion = 350; //Duración del sonido
int fMin = 3000; //Frecuencia más baja que queremos emitir
int fMax = 5000; //Frecuencia más alta que queremos emitir
int i = 0;
int valorSwitch;

void setup() {
  pinMode(reed, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode (buzzer, OUTPUT);
}

void loop() {
  //Asignamos el valor del reed switch a la variable correspondiente
  valorSwitch = digitalRead(reed);

  //Si el sensor es activado sonara la alarma así como se encedera el led
  if (valorSwitch == LOW) {
    digitalWrite(led, HIGH);
  //Se reproduce el tono en el buzzer
    for (i = fMin; i <= fMax; i++)
      tone(buzzer, i, duracion);
    for (i = fMax; i >= fMin; i--)
      tone(buzzer, i, duracion);
           
  } else {
    //Apagamos el led
    digitalWrite(led, LOW);
  }
  delay(1000);
}
