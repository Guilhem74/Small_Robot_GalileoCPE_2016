#ifndef DEFINES_H
#define DEFINES_H
#include "pins.h"
#include "global.h"
#include "defines.h"

#define SEPARATEUR           ';'
//Servo1 Bras
//Servo 2 aimant
#define SERVO1_INIT 10
#define SERVO1_LIBERATION 60
#define SERVO1_FINAL 100

#define SERVO2_INIT 130//Aimant collé  aux bras
#define SERVO2_FINAL 180//Aimant loin du bras

#define TEMPS_MATCH 90000 //Fin du match au bout de X ms
#define NOMBRE_ETAPES 6


#define SENSI_ 250
#define CAPTEUR_AVANT_DROIT_SENSI SENSI_
#define CAPTEUR_AVANT_GAUCHE_SENSI SENSI_
#define CAPTEUR_ARRIERE_DROIT_SENSI SENSI_
#define CAPTEUR_ARRIERE_GAUCHE_SENSI SENSI_

#define TEMPS_MAX_ATTENTE 3000
#define TIME_OUT_DEPLACEMENT 10000
#define TEMP_RAPPEL_DETECTION 4000
#define DEBUG true
#define DEBUG_BRAS false
#define DEBUG_CAPTEUR true
#define DEBUG_SERIAL1 false
#define DEBUG_SERIAL2 false

#define BAUDRATE_MASTER 38400

#endif
