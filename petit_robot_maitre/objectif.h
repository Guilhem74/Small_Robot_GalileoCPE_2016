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
 /*Stratégie Violet 1*//*
Objectif ObjectifVLT1_Fin = {"Objectif VLT1 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT1_pos6 = {"Objectif VLT1 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_Fin};
Objectif ObjectifVLT1_pos5 = {"Objectif VLT1 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos6};
Objectif ObjectifVLT1_pos4 = {"Objectif VLT1 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos5};
Objectif ObjectifVLT1_pos3 = {"Objectif VLT1 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos4};
Objectif ObjectifVLT1_pos2 = {"Objectif VLT1 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos3};
Objectif ObjectifVLT1_pos1 = {"Objectif VLT1 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos2};
/*Stratégie Violet 2*/
Objectif ObjectifVLT1_Fin = {"Objectif de Fin",.X=-1320,.Y=380,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT1_pos6 = {"Objectif n°6",.X=-1320,.Y=380,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_Fin};
Objectif ObjectifVLT1_pos5 = {"Objectif n°5",.X=-1830,.Y=300,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos6};
Objectif ObjectifVLT1_pos4 = {"Objectif n°4",.X=-1820,.Y=280,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos5};
Objectif ObjectifVLT1_pos3 = {"Objectif n°3",.X=-1570,.Y=-100,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos4};
Objectif ObjectifVLT1_pos2 = {"Objectif n°2",.X=-950,.Y=-410,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos3};
Objectif ObjectifVLT1_pos1 = {"Objectif n°1",.X=-600,.Y=20,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT1_pos2};

Objectif ObjectifVLT2_Fin = {"Objectif VLT2 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT2_pos6 = {"Objectif VLT2 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_Fin};
Objectif ObjectifVLT2_pos5 = {"Objectif VLT2 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_pos6};
Objectif ObjectifVLT2_pos4 = {"Objectif VLT2 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_pos5};
Objectif ObjectifVLT2_pos3 = {"Objectif VLT2 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_pos4};
Objectif ObjectifVLT2_pos2 = {"Objectif VLT2 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_pos3};
Objectif ObjectifVLT2_pos1 = {"Objectif VLT2 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT2_pos2};
/*Stratégie Violet 3*/
Objectif ObjectifVLT3_Fin = {"Objectif VLT3 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT3_pos6 = {"Objectif VLT3 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_Fin};
Objectif ObjectifVLT3_pos5 = {"Objectif VLT3 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_pos6};
Objectif ObjectifVLT3_pos4 = {"Objectif VLT3 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_pos5};
Objectif ObjectifVLT3_pos3 = {"Objectif VLT3 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_pos4};
Objectif ObjectifVLT3_pos2 = {"Objectif VLT3 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_pos3};
Objectif ObjectifVLT3_pos1 = {"Objectif VLT3 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT3_pos2};
/*Stratégie Violet 4*/
Objectif ObjectifVLT4_Fin = {"Objectif VLT4 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT4_pos6 = {"Objectif VLT4 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_Fin};
Objectif ObjectifVLT4_pos5 = {"Objectif VLT4 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_pos6};
Objectif ObjectifVLT4_pos4 = {"Objectif VLT4 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_pos5};
Objectif ObjectifVLT4_pos3 = {"Objectif VLT4 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_pos4};
Objectif ObjectifVLT4_pos2 = {"Objectif VLT4 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_pos3};
Objectif ObjectifVLT4_pos1 = {"Objectif VLT4 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT4_pos2};
/*Stratégie Violet 5*/
Objectif ObjectifVLT5_Fin = {"Objectif VLT5 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLT5_pos6 = {"Objectif VLT5 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_Fin};
Objectif ObjectifVLT5_pos5 = {"Objectif VLT5 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_pos6};
Objectif ObjectifVLT5_pos4 = {"Objectif VLT5 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_pos5};
Objectif ObjectifVLT5_pos3 = {"Objectif VLT5 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_pos4};
Objectif ObjectifVLT5_pos2 = {"Objectif VLT5 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_pos3};
Objectif ObjectifVLT5_pos1 = {"Objectif VLT5 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLT5_pos2};

/*Stratégie Violet Homologation*/
Objectif ObjectifVLTH_Fin = {"Objectif violet d'homologation de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVLTH_pos1 = {"Objectif VH n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVLTH_Fin};



 /*Stratégie Vert 1*/
Objectif ObjectifVRT1_Fin = {"Objectif VRT1 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRT1_pos6 = {"Objectif VRT1 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_Fin};
Objectif ObjectifVRT1_pos5 = {"Objectif VRT1 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos6};
Objectif ObjectifVRT1_pos4 = {"Objectif VRT1 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos5};
Objectif ObjectifVRT1_pos3 = {"Objectif VRT1 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos4};
Objectif ObjectifVRT1_pos2 = {"Objectif VRT1 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos3};
Objectif ObjectifVRT1_pos1 = {"Objectif VRT1 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT1_pos2};
/*Stratégie Vert 2*/
Objectif ObjectifVRT2_Fin = {"Objectif VRT2 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRT2_pos6 = {"Objectif VRT2 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_Fin};
Objectif ObjectifVRT2_pos5 = {"Objectif VRT2 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_pos6};
Objectif ObjectifVRT2_pos4 = {"Objectif VRT2 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_pos5};
Objectif ObjectifVRT2_pos3 = {"Objectif VRT2 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_pos4};
Objectif ObjectifVRT2_pos2 = {"Objectif VRT2 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_pos3};
Objectif ObjectifVRT2_pos1 = {"Objectif VRT2 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT2_pos2};
/*Stratégie Vert 3*/
Objectif ObjectifVRT3_Fin = {"Objectif VRT3 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRT3_pos6 = {"Objectif VRT3 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_Fin};
Objectif ObjectifVRT3_pos5 = {"Objectif VRT3 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_pos6};
Objectif ObjectifVRT3_pos4 = {"Objectif VRT3 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_pos5};
Objectif ObjectifVRT3_pos3 = {"Objectif VRT3 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_pos4};
Objectif ObjectifVRT3_pos2 = {"Objectif VRT3 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_pos3};
Objectif ObjectifVRT3_pos1 = {"Objectif VRT3 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT3_pos2};
/*Stratégie Vert 4*/
Objectif ObjectifVRT4_Fin = {"Objectif VRT4 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRT4_pos6 = {"Objectif VRT4 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_Fin};
Objectif ObjectifVRT4_pos5 = {"Objectif VRT4 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_pos6};
Objectif ObjectifVRT4_pos4 = {"Objectif VRT4 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_pos5};
Objectif ObjectifVRT4_pos3 = {"Objectif VRT4 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_pos4};
Objectif ObjectifVRT4_pos2 = {"Objectif VRT4 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_pos3};
Objectif ObjectifVRT4_pos1 = {"Objectif VRT4 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT4_pos2};
/*Stratégie Vert 5*/
Objectif ObjectifVRT5_Fin = {"Objectif VRT5 de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRT5_pos6 = {"Objectif VRT5 n°6",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_Fin};
Objectif ObjectifVRT5_pos5 = {"Objectif VRT5 n°5",.X=-1100,.Y=670,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_pos6};
Objectif ObjectifVRT5_pos4 = {"Objectif VRT5 n°4",.X=-500,.Y=-120,.Angle=0,.Sens_Arriere=false,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_pos5};
Objectif ObjectifVRT5_pos3 = {"Objectif VRT5 n°3",.X=-600,.Y=-110,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_pos4};
Objectif ObjectifVRT5_pos2 = {"Objectif VRT5 n°2",.X=-190,.Y=-130,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_pos3};
Objectif ObjectifVRT5_pos1 = {"Objectif VRT5 n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRT5_pos2};

/*Stratégie Vert Homologation*/
Objectif ObjectifVRTH_Fin = {"Objectif VRTH de Fin",.X=160,.Y=-280,.Angle=0,.Sens_Arriere=true,.Detection_Active=false,.Dernier_Objectif=true,.Objectif_suivant=NULL};
Objectif ObjectifVRTH_pos1 = {"Objectif VRTH n°1",.X=0,.Y=-10,.Angle=0,.Sens_Arriere=true,.Detection_Active=true,.Dernier_Objectif=false,.Objectif_suivant=&ObjectifVRTH_Fin};

/*Règle*/
Objectif ObjectifVLT_Init ={"Initialisation VLT",0,0,0,true,false,false,.Objectif_suivant=&ObjectifVLT1_pos1}; //Init de couleur Violet
Objectif ObjectifVRT_Init ={"Initialisation VRT",0,0,0,true,false,false,.Objectif_suivant=&ObjectifVRT1_pos1}; //Init de couleur Vert


Objectif Objectif_Init ={"Initialisation",0,0,0,true,false,false,.Objectif_suivant=&ObjectifVLT_Init};

#endif


