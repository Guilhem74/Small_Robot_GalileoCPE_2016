#ifndef GLOBAL_H
#define GLOBAL_H
#include "pins.h"
#include "global.h"
#include "defines.h"
#include "WString.h"
#include <Servo.h>



enum Capteur{
  Avant_droit,
  Avant_gauche,
  Avant,
  Arriere_droit,
  Arriere_gauche,
  Arriere,
  Tout
};

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

enum OBJECTIF{
  Approche_poisson, Approche_poisson2, Approche_poisson3, Peche_poisson, Liberation_poisson, Approche_palet, Pousse_palet, Veille
};


OBJECTIF Objectif = Approche_poisson;
Etat Robot = Libre;


Servo servo1, servo2;
int32_t temp_match=0;
int32_t temp_attente=0; 
int32_t temp_stop=0;
int Nombre_passage=0;
int Validation_Message=0;

int X_COORDONNES[NOMBRE_ETAPES]={100,300,0,0,0,0};
int Y_COORDONNES[NOMBRE_ETAPES]={0};
int ANGLE_COORDONNES[NOMBRE_ETAPES]={0};

int X_POSITION=0;
int Y_POSITION=0;
int ANGLE_POSITION=0;

int X_DEPLACEMENT=0;
int Y_DEPLACEMENT=0;
int ANGLE_DEPLACEMENT=0;


//Communication
int cnt = 0; // nombre de données découpées
String data[10]; // stockage des données découpées
String inputString = "";   // chaine de caractères pour contenir les données
bool stringComplete = false;  // pour savoir si la chaine est complète
bool Notif_arrive=false;

#endif
