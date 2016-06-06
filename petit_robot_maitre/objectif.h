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

/*
 * |------------>Y
 * |
 * |
 * |
 * |
 * |
 * v
 * X
 */
 /*
 Objectif Objectif_Fin = {"FIN",500,0,0,false,false,true,.Objectif_suivant=NULL};
Objectif Objectif_Rpos2 = {"Recule, Pousse des blocs",.X=-350,.Y=-125,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_Fin};
Objectif Objectif_Rpos1 = {"Recule, approche des blocs",.X=-150,.Y=-125,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_Fin};
Objectif Objectif_Init ={"Initialisation",0,0,0,false,false,false,.Objectif_suivant=&Objectif_Avancer}; //{X :0,Objectif_suivant :&Objectif_Avancer}; 
*/Objectif Objectif_Fin = {"Objectif de Fin",.X=580,.Y=-1881,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif Objectif_pos4 = {"Objectif n°4",.X=580,.Y=-1881,.Angle=0,.Sens_Arriere=false,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_Fin};
Objectif Objectif_pos3 = {"Objectif n°3",.X=1519,.Y=-1393,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_pos4};
Objectif Objectif_pos2 = {"Objectif n°2",.X=1330,.Y=-838,.Angle=0,.Sens_Arriere=false,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_pos3};
Objectif Objectif_pos1 = {"Objectif n°1",.X=888,.Y=-512,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=false,.Objectif_suivant=&Objectif_pos2};
Objectif Objectif_Init ={"Initialisation",0,0,0,false,false,false,.Objectif_suivant=&Objectif_pos1};
#endif


