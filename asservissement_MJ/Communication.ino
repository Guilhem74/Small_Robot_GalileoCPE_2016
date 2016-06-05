/* Copyright (c) Galileo, Mayeul Cantan 2016. Tous droits réservés. */

/* Ce fichier contient les fonctions de communication avec la
 * carte maitre.
 */

#include "structures.h"
#include "communication.h"
#include "trajectoire.h"

void processChar(char c)
{
    static String buffer = ""; // TODO : string.reserve(IBUF_MAXLENGTH) quelque part

    if(c==FIN_TRANSMISSION) // Fin de transmission
    {
        struct T_Commande commande;
        int pos1=buffer.indexOf(SEPARATEUR_ETENDU);
        if(pos1 >= 0)
            commande.special=buffer.charAt(pos1-1);

        int pos2; // Note : pos1 vaut -1 si le caractère n'a pas été trouvé
        byte count =0;
        while( ((( pos2 = buffer.indexOf(SEPARATEUR, pos1+1)) >= 0 ) // Il existe encore un séparateur
                || ( count > 0 && ( (pos2 = buffer.length() ) && pos1 != int(buffer.length()) )) // sinon, on prend la dernière position
                )&& count < MAXPARAM)
        {
            if(pos1 + 1 != pos2)
            {
              commande.param[count] = buffer.substring(pos1 + 1, pos2).toInt();
              commande.isParamSet[count] = true;
              ++commande.nSet;
            }
            else
            {
              commande.isParamSet[count] = false;
            }
            pos1=pos2;
            count++;
        }

        if(count == 0) // Pas de séparateur, donc mot de contrôle ou paramètre invalide
        {
            if(buffer == "POS?")
                commande.special = 'Q';

            if(buffer == "STOP!")
                commande.special = 'S';
        }
        buffer="";
        executerCommande(commande);
    }
    else
    {
      if(buffer.length()<IBUF_MAXLENGTH)
        buffer += c;
      else
        buffer="";
    }
}

void afficherPosition()
{
  SerialDebug.print(g_actuelle.X);
  SerialDebug.print(SEPARATEUR);
  SerialDebug.print(g_actuelle.Y);
  SerialDebug.print(SEPARATEUR);
  SerialDebug.print(g_actuelle.Angle);
  SerialDebug.print(FIN_TRANSMISSION);
}

void afficherVersion()
{
    SerialDebug.print("Compilation le " __DATE__ " à " __TIME__);
    SerialDebug.print(FIN_TRANSMISSION);
}
