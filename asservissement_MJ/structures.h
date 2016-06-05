/* Copyright (c) Galileo, Mayeul Cantan 2016. Tous droits réservés. */

/* Ce fichier contient les structures utilisées pour le passage
 * de paramètres à différents emplacemnts du code.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "define.h"
#include "communication.h"

struct T_Commande{
    int16_t param[MAXPARAM]={0}; //X,Y,V,T
    bool isParamSet[MAXPARAM]={0}; //X,Y,V,T // Pas super optimisé, mais au point où nous en sommes...
    int nSet=0;
    char special='N';
};


struct T_Position{
  int X,Y;
  float Angle;
};


#endif // STRUCTURES_H

