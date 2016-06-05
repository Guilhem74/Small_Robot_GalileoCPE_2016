#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H
#include "structures.h"

enum type_commande{AUCUNE, COMMANDE_MIXTE, COMMANDE_POSITION, COMMANDE_ANGLE};
extern T_Position g_actuelle, g_consigne;
extern int16_t g_vitesse;
extern enum type_commande g_consigne_en_cours;

void executerCommande(T_Commande c);
void verifierSiConsigneAtteinte();

#endif // TRAJECTOIRE_H
