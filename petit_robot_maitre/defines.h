#ifndef DEFINES_H
#define DEFINES_H
#include "pins.h"
#include "global.h"
#include "defines.h"

#define VERT true
#define SEPARATEUR           ';'
//Servo1 Bras
//Servo 2 aimant
#define SERVO1_INIT 20

#define SERVO1_FINAL 100

#define SERVO2_INIT 120//Aimant collé  aux bras
#define SERVO2_FINAL 70//Aimant loin du bras

#define TEMPS_MATCH 82000 //Fin du match au bout de X ms





#define TEMPS_MAX_ATTENTE 3000
#define TIME_OUT_DEPLACEMENT 10000
#define TEMP_RAPPEL_DETECTION 4000
#define DEBUG true
#define DEBUG_BRAS false
#define DEBUG_CAPTEUR false
#define DEBUG_SERIAL1 false
#define DEBUG_SERIAL2 false

#define BAUDRATE_MASTER 115200

#endif
