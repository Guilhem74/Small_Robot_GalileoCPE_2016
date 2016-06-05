#include "trajectoire.h"
#include "global.h"

T_Position g_actuelle={X_INITIALE,Y_INITIALE,0}, g_consigne={X_INITIALE,Y_INITIALE,0};
int16_t g_vitesse = DEFAULT_SPEED;
int16_t g_angle_final=0;
enum type_commande g_consigne_en_cours = AUCUNE;

void executerCommande(T_Commande c)
{
    switch(c.special)
    {
        case 'S': // Stop
            stopperRobot();
			g_consigne_en_cours = AUCUNE; // Afin de ne pas afficher "K"
            return;
        case 'V':
            afficherVersion();
            return;
        case 'Q':
             afficherPosition();
             return;
        case 'N':
        case 'R':
            break;
        default:
            return;
  }
  if(c.nSet == 0) // Aucun paramètre
      return;

  if(( ! c.isParamSet[0] || // Utiliser un xor? (^)
       ! c.isParamSet[1] ))
  {
      if(( c.isParamSet[0] ||
           c.isParamSet[1] ))
        {
          goto erreurXYnotSET; // erreur : un des paramètres réglés, mais pas l'autre.
        }
        // ICI, X et Y non précisés
        g_consigne.X=g_actuelle.X;
        g_consigne.Y=g_actuelle.Y;
  }
  else // X et Y précisés
  {
      g_consigne_en_cours = COMMANDE_POSITION;
      g_consigne.X=c.param[0];
      g_consigne.Y=c.param[1];
  }

   if( !c.isParamSet[2])
      g_vitesse=DEFAULT_SPEED;
   else
      g_vitesse=c.param[2];
   
   if(c.special == 'R')
   {
        g_marche_arriere = true;
   }
   else
        g_marche_arriere = false;
       //g_consigne.Angle = (g_consigne.Angle+ANGLE_MAX/2) % ANGLE_MAX; // TODO : voir si cela fonctionne Il faudra peut-être modifier l'angle, ou mettre une distance opposée.

   if(c.isParamSet[3])
   {
     g_consigne.Angle=c.param[3];
     if(g_consigne_en_cours == COMMANDE_POSITION)
         g_consigne_en_cours = COMMANDE_MIXTE;
    else
        g_consigne_en_cours = COMMANDE_ANGLE;
   }
#if DEBUG_COMMUNICATION
  SerialDebug.print("Commande consigne : X=");
  SerialDebug.print(g_consigne.X);
  SerialDebug.print("; Y=");
  SerialDebug.print(g_consigne.Y);
  SerialDebug.print("; V=");
  SerialDebug.print(g_vitesse);
  SerialDebug.print("; A=");
  SerialDebug.print(g_consigne.Angle);
#endif
  erreurXYnotSET:
  return;
}

//void calculerAngleAttaque()
//{
//    int32_t dx, dy;
//
//    dx=g_consigne.X-g_actuelle.X;
//    dy=g_consigne.Y-g_actuelle.Y;
//
//    g_consigne.Angle = atan2(dy,dx)*(RAD2DEG*ANGLE_MAX/360)/*-g_actuelle.Angle*/;
//#if DEBUG_COMMUNICATION
//    SerialDebug.print("dx=");SerialDebug.print(dx);SerialDebug.print("=");SerialDebug.print(g_consigne.X);SerialDebug.print("-");SerialDebug.print(g_actuelle.X);
//    SerialDebug.print(", dy="); SerialDebug.print(dy);
//    SerialDebug.print(", A= : "); SerialDebug.println(g_consigne.Angle);
//#endif
//}

void verifierSiConsigneAtteinte()
{
    //SerialDebug.println("coucou");
    int32_t dx =  g_consigne.X-g_actuelle.X;
    int32_t dy = g_consigne.Y-g_actuelle.Y;
    if(abs(sqrt(dx*dx+dy*dy))<HYST_IN && abs(g_consigne.Angle-g_actuelle.Angle) < ANGLE_TOLERANCE)//modification de la condition d'angle à tester
    {
            consigneAtteinte();
    }
 }

void consigneAtteinte()
{/*
  if(g_consigne_en_cours==COMMANDE_MIXTE)
  {
      g_consigne_en_cours=COMMANDE_ANGLE;
      return;
  }*/

  SerialMaster.print(MESSAGE_ARRIVEE);
  
  g_consigne_en_cours = AUCUNE;
  // stopperRobot(); // Supprimé pour lmiter l'écart statique
}

void stopperRobot() // Appelé dans le cas où l'on reçoit un ordre de stop ou que le robot a atteint sa consigne.
{
  g_consigne=g_actuelle;
}
