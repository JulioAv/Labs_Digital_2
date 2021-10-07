//Electrónica Digital 2 - Julio Avila
//Lab7 - Almacenamiento SD

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                     //Inicialización de la comunicación UART
  SPI.setModule(0);                                       //Inicialización del módulo SPI0
  pinMode(PA_3, OUTPUT);                                  //Chip Select y Push configurados
  pinMode(PUSH1, INPUT_PULLUP);
  SD.begin(PA_3);
}
    
void loop() {
  // put your main code here, to run repeatedly: 
  int push = digitalRead(PUSH1);                          //Con el push se especifica que se desea leer la tarjeta
  if(push == LOW){
    myFile = SD.open("test1.txt");                        //Se abre la comunicación con la tarjeta y se especifica cual es el archivo a leer
    if (myFile) {                                         //luego lo envía mediante la comunicación UART hacia la consola
      Serial.println("test1.txt:");
  
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
      ///////////////////////////////////////////////////////////////////
      myFile = SD.open("test2.txt");
    if (myFile) {
      Serial.println("test2.txt:");
  
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
      ////////////////////////////////////////////////////////////////////////
      myFile = SD.open("test3.txt");
    if (myFile) {
      Serial.println(".txt:");
  
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    }
  }
}
  }
}
