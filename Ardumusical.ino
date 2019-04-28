/*
//USAR ESTE TRECHO DE CÓDIGO PARA CONFIGURAR O SERVIDOR DO ARDUINO QUANDO A CONEXAO FOR RECUSADA
#include "SoftwareSerial.h"

SoftwareSerial ESP_Serial(10, 11); // RX, TX

void setup(){
  Serial.begin(9600);
  ESP_Serial.begin(9600);
}

void loop(){
  if (ESP_Serial.available()){
    Serial.write(ESP_Serial.read());
  }
  if (Serial.available()){
    ESP_Serial.write(Serial.read());
  }
}
*/


#include "SoftwareSerial.h"

#include "pitches.h"
SoftwareSerial ESP_Serial(10, 11); // RX, TX

String message;

int melody[] = {
  //NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_F5, NOTE_E5
};

int noteDurations[] = {
  2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 1 
};

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  ESP_Serial.begin(9600);
}

void loop(){
  if (ESP_Serial.available()){
    Serial.write(ESP_Serial.read());
    message = ESP_Serial.readString();             
    Serial.print("I received from Android: ");
    Serial.println(message);
    if(message.indexOf("ola") > -1){
       tocaMusica();  
    }
  }
  if (Serial.available()){
    ESP_Serial.write(Serial.read());
 
  }
}

void tocaMusica(){
  for (int thisNote = 0; thisNote <= sizeof(melody); thisNote++) {

          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(8, melody[thisNote], noteDuration);
      
          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing:
          noTone(8);
        }  
}
