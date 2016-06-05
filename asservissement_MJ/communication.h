/* Copyright (c) Galileo, Mayeul Cantan 2016. Tous droits r�serv�s. */

/* Ce fichier contient les d�clarations pour les fonctions de
 * communication, ainsi que la description du protocole
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "define.h"

/**
  Description du protocole :
  Chaque message envoy� est compos� d'un ou plusieurs mots-cl�s s�par�s par le
  caract�re SEPARATEUR (";"), et est termin� par le caract�re de fin de transmission
  ("\n"). Apr�s r�ception d'un message valide, le MESSAGE_ARRIVEE est retourn� ("K\n").
  Commandes (pr�sentes par souci de r�trocompatibilit�) :
   -> "POS?\n"
       effet : aucun
       retourne : la position actuelle du robot (X;Y;ANGLE)
   -> "STOP!\n"
       effet : arrete instantan�ment le robot
       retourne : aucun
  Commandes de base pour le d�placement :
   -> "X;Y\n"
       effet : ordone au robot de se d�placer aux coordonn�es indiqu�es
       retourne : aucun
   -> "X;Y;V\n"
       effet : idem, mais � la vitesse indiqu�e. Si V=0, la vitesse est celle d'�cretage
       retourne : aucun
   -> "X;Y;V;T\n"
       effet : idem, mais avec l'angle final en plus.
  Commandes �tendues (nouveaut� 2016 ! ) :
   -> "N:" + commande : Modificateur de consigne, o� N peut etre :
      * R : Marche arri�re
      * N : Normal
      * Q : identique � "POS?\n" peut s'utiliser sous la forme "Q:\n"
      * S : Identique � "STOP!\n"
      * V : Affiche le num�ro de version (la date et heure de compilation).
   Le protocole est plus facilement extensible ainsi.
*/

#define BAUDRATE_MASTER 115200
#define BAUDRATE_COMPTEUR 115200

#define FIN_TRANSMISSION     '\n'
#define SEPARATEUR           ';'
#define SEPARATEUR_ETENDU    ':'
#define MESSAGE_ARRIVEE      "K\n"
#define MAXPARAM 4

#define IBUF_MAXLENGTH 64

void processChar(char c);

#endif // COMMUNICATION_H
