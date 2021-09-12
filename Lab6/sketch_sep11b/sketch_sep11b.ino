void setup() {
  // put your setup code here, to run once:
  pinMode(PUSH1, INPUT_PULLUP);                         //Se declaran los push como inputs con pullups y los leds como outputs
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PUSH1), J1, CHANGE);    //Los push se configuran como interrupciones que llevan a las rutinas indicadas
  attachInterrupt(digitalPinToInterrupt(PUSH2), J2, CHANGE);
  
}
char mode = 0;
char con1 = 0;
char con2 = 0;
char sas;

void loop() {
  // put your main code here, to run repeatedly: 
  if(mode == 0){                                //En el modo 0 todo está apagado
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
  
  if(mode == 1){                              //En el modo 1 se realiza la secuencia del semáforo
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    delay(1000);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    delay(500);
    mode = 2;                                 //A mitad del semáforo verde se entra al modo 2 para que puedan comenzar a aumentar los contadores
    delay(500);
    digitalWrite(GREEN_LED, LOW);
  }
  if(sas == 1){                               //rutina corta para que el led se ponga morado durante un instante cuando se apache cualquier boton
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    delay(100);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    sas = 0;
  }
  while(con1 >= 8){                           //cuando alguno de los jugadores llegue a 9, se pone en verde o azul y termina el juego
    digitalWrite(GREEN_LED, HIGH);
  }
  while(con2 >= 8){
    digitalWrite(BLUE_LED, HIGH);
  }
  
  
}

void J1(){
  char state1 = digitalRead(PUSH1);
  if(state1 == LOW){                          //Solo se toma la interrupción cuando se oprime, no cuando se suelta
    if(mode == 0){                            //Si está en el modo 0, cualquiera de los push lleva a iniciar el semáforo
      mode = 1;
    }
    if(mode == 2){
      con1++;                                //En el modo 2 se incrementan los contadores y se activa la rutina del led morado  
      sas = 1;
    }
  }
  return;
}

void J2(){
  char state2 = digitalRead(PUSH2);
  if(state2 == LOW){
    if(mode == 0){
      mode = 1;
    }
    if(mode == 2){
      con2++;
      sas = 1;
    }
  }
  return;
}
