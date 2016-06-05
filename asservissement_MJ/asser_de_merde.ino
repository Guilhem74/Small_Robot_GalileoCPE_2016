#include "define.h"
#include "global.h"
#include "communication.h"
#include "pin.h"
#include "trajectoire.h"

void setup()
{
  config_fuzzy();
    
  SerialMaster.begin(BAUDRATE_MASTER);
  Serial1.begin(BAUDRATE_COMPTEUR);
  
  pinMode(PIN_MOTEUR_DROITE_VITESSE, OUTPUT);
  pinMode(PIN_MOTEUR_DROITE_SENS, OUTPUT);
  pinMode(PIN_MOTEUR_GAUCHE_VITESSE, OUTPUT);
  pinMode(PIN_MOTEUR_GAUCHE_SENS, OUTPUT);
  if(DEBUG)
    SerialDebug.println("Démarrage en mode DEBUG");
    
  delay(100);
  Serial1.write('r');
  delay(100);
}

void loop() { 
 if(SerialMaster.available())
    processChar(SerialMaster.read());
  //recuperation des deux valeurs de codeuses
  recuperer(0);
  recuperer(1);

  temp_millis = top_millis;
  top_millis = millis(); 

  asservir();
  print_debug();

  if(g_consigne_en_cours!=AUCUNE)
    verifierSiConsigneAtteinte();

}
