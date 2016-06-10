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
    int delayAction;
    int Time_out;
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
/*Objectif commun aux strats violet
 * Porte: 
 */
 /*
  * 
  */
 //violet config 1
Objectif ObjectifVLT1_Fin = {"Objectif de Fin",.X=200,.Y=-1100,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};

Objectif ObjectifVLT1_pos12 = {"Pousse porte",.X=200,.Y=-1100,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_Fin};
Objectif ObjectifVLT1_pos11 = {"Approche porte 1",.X=200,.Y=-800,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos12};
Objectif ObjectifVLT1_pos10 = {"Recule serviette",.X=-300,.Y=0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos11};
Objectif ObjectifVLT1_pos9 = {"legere rotation depose palet",.X=0,.Y=0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos10};
Objectif ObjectifVLT1_pos8 = {"Direction la serviette",.X=0,.Y=0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos9};
Objectif ObjectifVLT1_pos7 = {"Pousse palet",.X=-50,.Y=800,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos8};
Objectif ObjectifVLT1_pos6 = {"Contournement 2",.X=-300,.Y=800,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos7};
Objectif 
ObjectifVLT1_pos5 = {"Contournement 1",.X=-360,.Y=125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos6};
Objectif ObjectifVLT1_pos4 = {"Recule Palet",.X=-210,.Y=125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos5};
Objectif ObjectifVLT1_pos3 = {"Attrape palet",.X=0,.Y=-0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos4};
Objectif ObjectifVLT1_pos2 = {"Placement palet",.X=-1200,.Y=800,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos3};
Objectif ObjectifVLT1_pos1 = {"Contournement palet",.X=-1300,.Y=500,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos2};


/*Stratégie Violet Homologation*/
Objectif ObjectifVLTH_Fin = {"Objectif violet d'homologation de Fin",.X=-400,.Y=400,.Angle=180,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLTH_pos1 = {"Objectif VH n°1",.X=-400,.Y=400,.Angle=180,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTH_Fin};
/*Objectif commun aux strats violet
 * Bloc du millieu : 
 */
Objectif ObjectifVLTCommun_Fin = {"VLT:Transition vers stratégie",.X=-210,.Y=-125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos1};
Objectif ObjectifVLTCommun_pos3 = {"VLT:Eloignement des cubes",.X=-210,.Y=-125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTCommun_Fin};
Objectif ObjectifVLTCommun_pos2 = {"VLT:Pousse cube",.X=-610,.Y=-125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTCommun_pos3};
Objectif ObjectifVLTCommun_pos1 = {"VLT:Alignement avec les cubes",.X=-150,.Y=-125,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTCommun_pos2};
Objectif ObjectifVLTCommun_Init = {"VLT:Départ du robot",.X=0,.Y=0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTCommun_pos1};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Objectif commun aux strats Verte
 * Porte: 
 */
 /*
  * 
  */

 //Vert config 1
Objectif ObjectifVRT1_Fin = {"Objectif de Fin",.X=0,.Y=1200,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};

Objectif ObjectifVRT1_pos12 = {"Pousse porte",.X=-300,.Y=1100,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_Fin};
Objectif ObjectifVRT1_pos11 = {"Approche porte 1",.X=-300,.Y=1100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos12};
Objectif ObjectifVRT1_pos10 = {"Recule serviette",.X=-300,.Y=100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos11};
Objectif ObjectifVRT1_pos9 = {"Eloignement ",.X=-300,.Y=100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos10};
Objectif ObjectifVRT1_pos8 = {"Eloignement serviette",.X=-300,.Y=100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos9};
Objectif ObjectifVRT1_pos7 = {"Pousse palet",.X=-50,.Y=100,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos8};
Objectif ObjectifVRT1_pos6 = {"Contournement 2",.X=0,.Y=-600,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos7};
Objectif ObjectifVRT1_pos5 = {"Contournement 1",.X=-300,.Y=-600,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos6};
Objectif ObjectifVRT1_pos4 = {"Pousse des palets Palet",.X=-100,.Y=100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos5};
Objectif ObjectifVRT1_pos3 = {"Approche des palets",.X=-100,.Y=-100,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos4};
Objectif ObjectifVRT1_pos2 = {"Placement palet",.X=-1300,.Y=-750,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos3};
Objectif ObjectifVRT1_pos1 = {"Contournement palet",.X=-1300,.Y=-600,.Angle=90,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos2};

/*Stratégie Vert Homologation*/
Objectif ObjectifVRTH_Fin = {"Objectif VRTH de Fin",.X=400,.Y=-400,.Angle=180,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRTH_pos1 = {"Objectif VRTH n°1",.X=-400,.Y=-400,.Angle=180,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTH_Fin};

/*Objectif commun aux strats Verte
 * 
 */
Objectif ObjectifVRTCommun_Fin = {"VRT:Transition vers stratégie",.X=-210,.Y=120,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos1};
Objectif ObjectifVRTCommun_pos3 = {"VRT:Eloignement des cubes",.X=-210,.Y=120,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTCommun_Fin};
Objectif ObjectifVRTCommun_pos2 = {"VRT:Pousse cube",.X=-610,.Y=120,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTCommun_pos3};
Objectif ObjectifVRTCommun_pos1 = {"VRT:Alignement avec les cubes",.X=-150,.Y=120,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTCommun_pos2};
Objectif ObjectifVRTCommun_Init = {"VRT:Départ du robot",.X=0,.Y=0,.Angle=0,.delayAction=0,.Time_out=10000,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTCommun_pos1};

/*Règle*/
Objectif ObjectifVLT_Init ={"Initialisation VLT",0,0,0,0,0,true,false,false,.Objectif_suivant=&ObjectifVLTCommun_Init}; //Init de couleur Violet
Objectif ObjectifVRT_Init ={"Initialisation VRT",0,0,0,0,0,true,false,false,.Objectif_suivant=&ObjectifVRTCommun_Init}; //Init de couleur Vert


Objectif Objectif_Init ={"Initialisation",0,0,0,0,0,true,false,false,.Objectif_suivant=&ObjectifVLT_Init};

#endif


