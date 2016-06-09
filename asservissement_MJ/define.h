
#ifndef DEFINE_H
#define DEFINE_H

#define GROSROBOT false //Pour gros robot :true
#define PETITROBOT !GROSROBOT //Pour la compréhension

#define DEBUG false
#define SerialDebug Serial
#define DEBUG_VITESSE false
#define DEBUG_ANGLE false
#define DEBUG_ENCODEUR false
#define DEBUG_COMMUNICATION false

#define BAUDRATE_COMPTEUR 115200
#define BAUDRATE_MASTER 115200

//#define COMMANDE 0 //distance a parcourir en mm
//#define COMMANDE_ANGLE 3600 //en 10ieme de degre


#define ANGLE_INITIAL   0
#define D_INITIALE  0
#define G_INITIALE  0

#define X_INITIALE  0
#define Y_INITIALE  0

#define HYST_IN 35
#define HYST_OUT 70



#if GROSROBOT
    #define SerialMaster Serial
    #define DEFAULT_SPEED 150
    #define ETAT_MOTEUR_AVANCE HIGH
    #define ANGLE_TOLERANCE 2 // degrés

    #define DIAMETRE_ROUE 41.25 // en mm
    #define ECARTEMENT_ROUES 186 //en mm
    #define PWM_MAX 255
    
    #define RAPPORT_LINEAIRE_ANGULAIRE 3.0f

    #define TICCODEUSE 1024 //Tick par tour de roue
    #define VITESSE_MAX 800 //mm par sec
    #define VITESSE_ANGLE_MAX 200 // deg par sec
    #define ERREUR_MAX 500 //erreur mm pour laquelle le comportement reste max
    #define ERREUR_MAX_ANGLE 35 // degres
    //SPEED_OUT_MAX dans global.h

    //defini entre 0 et 10000
    #define SENSIBILITE_ERREUR      3000
    #define SENSIBILITE_VITESSE_IN  7500
    #define SENSIBILITE_VITESSE_OUT 7500 //doit être identique à IN? pour stabilité?
    #define ETAT_MOTEUR_AVANCE HIGH

    #define COEFF_MAGIQUE_ROUE_DROITE 0.992

  #else
      #define SerialMaster Serial2
      #define ETAT_MOTEUR_AVANCE LOW
      #define ANGLE_TOLERANCE 15 // degrés

      #define DIAMETRE_ROUE 51.7 // en mm
      #define ECARTEMENT_ROUES 115 //en mm
      #define TICCODEUSE 1538 //Tick par tour de roue
      #define PWM_MAX 190
      #define DEFAULT_SPEED 160
      
      #define RAPPORT_LINEAIRE_ANGULAIRE 1.35f
      
      #define VITESSE_MAX 500 //mm par sec
      #define VITESSE_ANGLE_MAX 250 // deg par sec
      #define ERREUR_MAX 40 //erreur mm pour laquelle le comportement reste max
      #define ERREUR_MAX_ANGLE 80 //centieme de degres
      //SPEED_OUT_MAX dans global.h
      
      //defini entre 0 et 10000
      #define SENSIBILITE_ERREUR      3000
      #define SENSIBILITE_VITESSE_IN  5000
      #define SENSIBILITE_VITESSE_OUT 5000 //doit être identique à IN? pour stabilité?
      #define COEFF_MAGIQUE_ROUE_DROITE 1 //specifique aux gros robot

#endif
#endif
