#include <Arduino.h>

#include "define.h"
#include "global.h"
#include "pin.h"

void setup()
{
  config_fuzzy();
    
  Serial2.begin(BAUDRATE_MASTER);
  Serial1.begin(BAUDRATE_COMPTEUR);
  Serial.begin(BAUDRATE_MASTER);
  
  pinMode(PIN_MOTEUR_DROITE_VITESSE, OUTPUT);
  pinMode(PIN_MOTEUR_DROITE_SENS, OUTPUT);
  pinMode(PIN_MOTEUR_GAUCHE_VITESSE, OUTPUT);
  pinMode(PIN_MOTEUR_GAUCHE_SENS, OUTPUT);
  if(DEBUG)
    Serial.println("Démarrage en mode DEBUG");
  delay(100);
  Serial1.write('r');
  delay(1000);
}

void loop() { 
  //recuperation des deux valeurs de codeuses
  recuperer(0);
  recuperer(1);

  temp_millis = top_millis;
  top_millis = millis(); 

  asservire();
  print_debug();
  Reception_ordre();
  
}


void serialEvent2() {
  while (Serial2.available()) {
    // récupérer le prochain octet (byte ou char) et l'enlever
    char inChar = (char)Serial2.read(); 
    // concaténation des octets reçus
    inputString += inChar;
    // caractère de fin pour notre chaine
    if (inChar == '\n') {  
      stringComplete = true;
    }
  }
}
#if DEBUG_SERIAL

void serialEvent() {
  while (Serial.available()) {
    // récupérer le prochain octet (byte ou char) et l'enlever
    char inChar = (char)Serial.read(); 
    // concaténation des octets reçus
    inputString += inChar;
    // caractère de fin pour notre chaine
    if (inChar == '\n') {  
      stringComplete = true;
    }
  }
 }
#endif


