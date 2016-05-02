
#ifndef DEFINE_H
#define DEFINE_H

  #define GROSROBOT false //Pour gros robot :true
  #define PETITROBOT !GROSROBOT //Pour la compréhension

  #define DEBUG true
  #define DEBUG_VITESSE false
  #define DEBUG_ANGLE false
  #define DEBUG_ENCODEUR false
  #define DEBUG_SERIAL false
#define HYST_IN 30
#define HYST_OUT 70
#define BAUDRATE_COMPTEUR 115200
#define BAUDRATE_MASTER 38400

#define FIN_TRANSMISSION     '\n'
#define SEPARATEUR           ';'
#define SEPARATEUR_ETENDU    ':'
#define MESSAGE_ARRIVEE      "K\n"
#define MAXPARAM 4

#define COMMANDE 0 //distance a parcourir en mm
#define COMMANDE_ANGLE 0 //en 10ieme de degre

#define ANGLE_INITIAL   0
#define D_INITIALE  0
#define G_INITIALE  0

#define X_INITIALE  0
#define Y_INITIALE  0

#if GROSROBOT

    #define ETAT_MOTEUR_AVANCE HIGH

    #define DIAMETRE_ROUE 41.25 // en mm
    #define ECARTEMENT_ROUES 186 //en mm

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

    //Correction imperfection des roues:
    #define COEFF_MAGIQUE_ROUE_DROITE 0.992
    #define COEFF_MAGIQUE_ROUE_GAUCHE 1

  #else

      #define ETAT_MOTEUR_AVANCE LOW
      #define DIAMETRE_ROUE 50 // en mm
      #define ECARTEMENT_ROUES 108 //en mm
      #define TICCODEUSE 1538 //Tick par tour de roue

      #define VITESSE_MAX 800 //mm par sec
      #define VITESSE_ANGLE_MAX 200 // deg par sec
      #define ERREUR_MAX 80 //erreur mm pour laquelle le comportement reste max
      #define ERREUR_MAX_ANGLE 25 //degres
      //SPEED_OUT_MAX dans global.h

      //defini entre 0 et 10000
      #define SENSIBILITE_ERREUR      2000
      #define SENSIBILITE_VITESSE_IN  7000
      #define SENSIBILITE_VITESSE_OUT 7000 //doit être identique à IN? pour stabilité?

       //Correction imperfection des roues:
      #define COEFF_MAGIQUE_ROUE_DROITE 1
      #define COEFF_MAGIQUE_ROUE_GAUCHE 1

#endif
#endif
