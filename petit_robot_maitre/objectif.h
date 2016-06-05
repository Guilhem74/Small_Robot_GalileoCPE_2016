#ifndef OBJECTIF_H
#define OBJECTIF_h
#include "global.h"
#include "pins.h"
#include "defines.h"

typedef struct Objectif {
  String nom;
    int X;//Coordonnées du plateau
    int Y;
    int Angle;
    bool Sens_Arriere;// True pour avancer, False pour reculer
    bool Detection_Active;//True pour activer la detection, false sinon
    bool Dernier_Objectif;//Permet d'arreter le robot
    struct Objectif * Objectif_suivant;// Afin d'effectuer une liste chainée
} Objectif;
/*
 * Declaration, deux méthode,
 * A la zeub, {param1,param2....}
 * Propre: {.Paramètre=valeur}
 */

 Objectif Objectif_Fin = {"FIN",500,0,0,false,false,true,.Objectif_suivant=NULL};
Objectif Objectif_Avancer = {"Avance de 500",.X=500,.Y=0,.Angle=0,.Sens_Arriere=false,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_Fin};
Objectif Objectif_Init ={"Initialisation",0,0,0,false,false,false,.Objectif_suivant=&Objectif_Fin}; //{X :0,Objectif_suivant :&Objectif_Avancer}; 
#endif


