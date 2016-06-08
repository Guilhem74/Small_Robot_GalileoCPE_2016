#ifndef GLOBAL_H
#define GLOBAL_H
#include "pins.h"
#include "global.h"
#include "defines.h"
#include "objectif.h"
#include <Wire.h>
#include <LCD03.h>
 LCD03 lcd;


enum Etat{
  Prechauff,
  Avance,
  Recule,
  Attente,
  Libre,
  Arrive,
  Stop,
  Fin
};
Objectif Objectif_En_Cours=Objectif_Init;
int32_t temp_match=0;
int32_t temp_attente=0;



int Validation_Message=0;


Etat Robot = Prechauff;



int X_DEPLACEMENT=0;
int Y_DEPLACEMENT=0;
int ANGLE_DEPLACEMENT=0;

bool Capteur_detection_avant=false;
bool Capteur_detection_arriere=false;

bool Couleur_Verte=false;
bool Lancement_config=false;
bool Tirette_passe=false;
bool Detection_active=true;
//Communication
int cnt = 0; // nombre de données découpées
String data_Slave[10]; // stockage des données découpées
bool stringComplete_Slave = false;  // pour savoir si la chaine est complète
String inputString_Slave = "";   // chaine de caractères pour contenir les données

String data_Detection[10];
bool stringComplete_Detection=false;
String inputString_Detection= "";

bool Notif_arrive=false;


#endif
