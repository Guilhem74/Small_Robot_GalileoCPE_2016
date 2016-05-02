#include "define.h"
#include "global.h"
#include "pin.h"

void setup()
{
  config_fuzzy();
    
  Serial.begin(BAUDRATE_MASTER);
  Serial1.begin(BAUDRATE_COMPTEUR);
  
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
}
