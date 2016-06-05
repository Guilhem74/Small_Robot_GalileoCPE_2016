#ifndef fonction
#define fonction
#include "global.h"
#include <Arduino.h>
#include "pins.h"
#include "defines.h"
void function_test_bras();
void function_test_capteur();

void Analyse_Objectif()
{

Serial.print("Objectif courant : ");
Serial.println(Objectif);

#if VERT
if(Objectif==D1||Objectif==D5)
{
  Pecher();
}
if(Objectif==D2||Objectif==D6)
{
  Ferrer();
}
if(Objectif==D3||Objectif==D7)
{
  Liberer();
}
#else
if(Objectif==D1)
{
  Pecher();
}
if(Objectif==D2)
{
  Ferrer();
}
if(Objectif==D3)
{
  Liberer();
}

#endif
  if(Objectif ==Objectif_Fin)
  {
      
      Robot=Stop;
  }
  if(Objectif < NBR_ETAPES)
  {
      X_DEPLACEMENT=X_COORDONNES[Objectif];
      Y_DEPLACEMENT=Y_COORDONNES[Objectif];
      ANGLE_DEPLACEMENT=ANGLE_COORDONNES[Objectif];
      Robot=Avance;
  }
  else
  {
    Robot=Fin;
    
      Serial.println("FIN");
  }
 
}
void Arreter()
{
  Serial2.println("S:");
  Validation_Message=0;//On RAZ l'esclave -> plus de réponse
}

void Se_Deplacer(int X,int Y,int ANGLE)
{
  if(Validation_Message==0)//Si on est a jour sur les échanges avec l'esclave
  {


    temp_derniere_action=millis();//envoie d'une commande a l'esclave a t = temp_derniere_actio
    /*if(!VERT&&Objectif==D2)//Est ce valide ?
    {
      Serial2.print('R');
      Serial2.print(':');
      Serial2.print(X);
      Serial2.print(';');
      Serial2.print(Y);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE);
      Serial2.print('\n');
      Validation_Message--;
    }
    else//Marchait bien en demi-tour, a verifier
    {*/
      Serial2.print(X);
      Serial2.print(';');
      Serial2.print(Y);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE);
      Serial2.print('\n');
      Validation_Message--;
    //}
    if(DEBUG)
    {
      Serial.print(X);
      Serial.print(';');
      Serial.print(Y);
      Serial.print(';');
      Serial.print(';');
      Serial.print(ANGLE);
      Serial.print('\n');
    }
  }
}

void Pecher()
{
 
    //servo2.write(20)//SERVO2_INIT)//On s'assure que l'aimant est collé au bras
    servo1.write(100);//SERVO1_FINAL) //On descend le bras
    delay(100);
 
}
void Ferrer()
{
   
      servo1.write(40);
      delay(100);
      
}
void Liberer()
{

    servo1.write(90);//Descente du bras
    delay(100);
    servo2.write(40);//Decrochage des aimants

    delay(1000);//Decrochage des poissons, petite attente
    servo2.write(SERVO2_INIT);//On remet le bras dans sa position pour pecher
    servo1.write(SERVO1_INIT); //On remonte le bras
    delay(15);
}
void Detection(Capteur cpt)
{
   int AV_Dr=0;
   int AV_Gc=0;
   int AR_Dr=0;
   int AR_Gc=0;
  Capteur_detection_avant=false;
  Capteur_detection_arriere=false;


    AV_Dr=analogRead(CAPTEUR_AVANT_DROIT_PIN);
    AV_Gc=analogRead(CAPTEUR_AVANT_GAUCHE_PIN);
    AR_Dr=analogRead(CAPTEUR_ARRIERE_DROIT_PIN);
    AR_Gc=analogRead(CAPTEUR_ARRIERE_GAUCHE_PIN);
  switch(cpt)
  {
    case Avant:
        if (AV_Gc > CAPTEUR_SENSI|| AV_Dr > CAPTEUR_SENSI)
        {
          Capteur_detection_avant=true;
          Serial.println("Detection capteur avant");
        }
        break;
    case Arriere:
        if (AR_Gc >CAPTEUR_SENSI|| AR_Dr >CAPTEUR_SENSI)
          {
            Capteur_detection_arriere=true;
          }
        break;
    default:
        Capteur_detection_avant=false;
        Capteur_detection_arriere=false;
        break;
  }
  return;
}


#endif
