#ifndef PIN_H
#define PIN_H

#include "define.h"

#if GROSROBOT
  #define PIN_MOTEUR_DROITE_VITESSE 9
  #define PIN_MOTEUR_DROITE_SENS    8
  #define PIN_MOTEUR_GAUCHE_VITESSE 11
  #define PIN_MOTEUR_GAUCHE_SENS 10
#else
   #define PIN_MOTEUR_DROITE_VITESSE 9
  #define PIN_MOTEUR_DROITE_SENS    8
  #define PIN_MOTEUR_GAUCHE_VITESSE 11
  #define PIN_MOTEUR_GAUCHE_SENS 10
#endif


#endif
