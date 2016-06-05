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



Servo servo1, servo2;
int32_t temp_match=0;
int32_t temp_attente=0;
int32_t temp_stop=0;
int32_t temp_derniere_action=0;
int Nombre_passage=0;

int CAPTEUR_SENSI=600;
bool detection_capteur=false;

int Validation_Message=0;
bool Robot_fin=false;


#if VERT
enum OBJECTIF{
  Init0, D0,D1,D2,D3,Capteur_Debut,D4,D5,D6,D7,Objectif_Fin
};
// Pour les Verts 
// Rag ds l'enum    i0   D0   R0   D1   R1   D2   R2   D3   R3   D4   R4    D5    R5     D6    R6   D7   R7  D8   R8    D9  R9  D10   R0   
// point sur la carte     2    2    3    3    4    4    5    5    6    6     7     7      8     8    9    9   10   10   11    11  12   12  13   13    14    14    15    15    16   16
int X_COORDONNES[]={ 0,100,200, 800,810,810,100,605, 800,810,810};
int Y_COORDONNES[]={ 0,0,0,880,880,880,875,880,880,880,880};
int ANGLE_COORDONNES[]={0,0,0,0,0,0,0,0,0,0,0,0};
#else
enum OBJECTIF{
  Init0, D0,D1,D2,D3,Capteur_Debut,D4,D5,D6,D7,Objectif_Fin, D9, R1, D8
};
int X_COORDONNES[]={0,600 ,  85, 800, 810, 600,  85, 800, 810, 810,810,810};
int Y_COORDONNES[]={0,-775,-770,-770,-770,-775,-770,-770,-770,-770,-770,-770};
int ANGLE_COORDONNES[]={0,180, 180,180,180,180, 180,180,180,180,180,180};
#endif



OBJECTIF Objectif = Init0;
Etat Robot = Prechauff;

int NBR_ETAPES=Objectif_Fin;

int X_POSITION=0;
int Y_POSITION=0;
int ANGLE_POSITION=0;

int X_DEPLACEMENT=0;
int Y_DEPLACEMENT=0;
int ANGLE_DEPLACEMENT=0;

bool Capteur_detection_avant=false;
bool Capteur_detection_arriere=false;

//Communication
int cnt = 0; // nombre de données découpées
String data[10]; // stockage des données découpées
String inputString = "";   // chaine de caractères pour contenir les données
bool stringComplete = false;  // pour savoir si la chaine est complète
bool Notif_arrive=false;

#endif
