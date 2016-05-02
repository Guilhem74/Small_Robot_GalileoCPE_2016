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
  switch (Objectif) {
    case Approche_poisson:
      X_DEPLACEMENT=X_COORDONNES[0];
      Y_DEPLACEMENT=Y_COORDONNES[0];
      ANGLE_DEPLACEMENT=ANGLE_COORDONNES[0];
      Robot=Avance;
      break;
    case Approche_poisson2:
      delay(2000);
      X_DEPLACEMENT=X_COORDONNES[1];
      Y_DEPLACEMENT=Y_COORDONNES[1];
      ANGLE_DEPLACEMENT=ANGLE_COORDONNES[1];
      Robot=Avance;
      break;
    default:
      Robot=Fin;
      break;
      // do something
  }
}
void Arreter()
{
  Serial2.println("S;");
  Validation_Message=0;//On RAZ l'esclave -> plus de réponse
}

void Se_Deplacer(int X,int Y,int ANGLE)
{
  if(Validation_Message==0)//Si on est a jour sur les échanges avec l'esclave
  {
    Serial2.print("XYA;");
    Serial2.print(X);
    Serial2.print(";");
    Serial2.print(Y);
    Serial2.print(";");
    Serial2.println(ANGLE);
    Validation_Message--;
  }
}

bool Pecher()
{
  if(Robot==Attente)
  {
    servo2.write(SERVO2_INIT);//On s'assure que l'aimant est collé au bras
    servo1.write(SERVO1_FINAL); //On descend le bras
    delay(1000);
    return 1;
  }
  else
    return 0;
}
bool Ferrer()
{
  if(Robot==Attente)
  {
  servo1.write(SERVO1_INIT); //On remonte le bras
  delay(1000);
  return 1;
  }
  else
    return 0;
}
bool Liberer()
{
  if(Robot==Attente)
  {
    servo1.write(SERVO1_LIBERATION);//Descente du bras
    delay(100);
    servo2.write(SERVO2_FINAL);//Decrochage des aimants

    delay(1000);//Decrochage des poissons, petite attente
    servo2.write(SERVO2_INIT);//On remet le bras dans sa position pour pecher
    servo1.write(SERVO1_INIT); //On remonte le bras
    delay(15);
    return 1;
  }
  else
    return 0;
}
bool Detection(Capteur cpt)
{
  bool Detect=false;
  static int passage=0;
  static int AV_Dr=0;
  static int AV_Gc=0;
  static int AR_Dr=0;
  static int AR_Gc=0;
  passage++;
  if(passage%4==0)//tout les 3 passages RAZ
  {
    AV_Dr=0;
    AV_Gc=0;
    AR_Dr=0;
    AR_Gc=0;
    passage=0;
  }
  
    AV_Dr=AV_Dr+analogRead(CAPTEUR_AVANT_DROIT_PIN);
    AV_Gc=AV_Gc+analogRead(CAPTEUR_AVANT_GAUCHE_PIN);
    AR_Dr=AR_Dr+analogRead(CAPTEUR_ARRIERE_DROIT_PIN);
    AR_Gc=AR_Gc+analogRead(CAPTEUR_ARRIERE_GAUCHE_PIN);
  int x;
  switch(cpt)
  {
    case Avant:
        if (AV_Gc > 1.5*CAPTEUR_AVANT_GAUCHE_SENSI|| AV_Dr > 1.5*CAPTEUR_AVANT_DROIT_SENSI)
        {
          return true;
        }
        break;
    case Arriere:
        if (AR_Gc > 1.5*CAPTEUR_ARRIERE_GAUCHE_SENSI|| AR_Dr > 1.5*CAPTEUR_ARRIERE_DROIT_SENSI)
          {
            return true;
          }
        break;
    default:
        Detect=false;
        break;
  }
  return false;
}

void function_test_bras()
{
      servo1.write(SERVO1_INIT);
      delay(2000);
      servo1.write(SERVO1_FINAL);
      delay(2000);
      servo2.write(SERVO2_INIT);
      delay(2000);
      servo2.write(SERVO2_FINAL);
      delay(2000);

}
void function_test_capteur()
{
  if(Detection(Avant_droit)==true)
  {
    Serial.println("Capteur Avant Droit");
  }
  if(Detection(Avant_gauche)==true)
  {
    Serial.println("Capteur Avant Gauche");
  }
  if(Detection(Arriere_droit)==true)
  {
    Serial.println("Capteur Arriere Droit");
  }
  if(Detection(Arriere_gauche)==true)
  {
    Serial.println("Capteur Arriere Gauche");
  }

}
void debug_test()
{
  if (DEBUG)
   {
      Serial.println("DEBUG");
      if (DEBUG_BRAS)
        function_test_bras();
      while (DEBUG_SERIAL1 && Serial1.available()>0)
        {Serial.write(Serial1.read());}
      while (DEBUG_SERIAL2 && Serial2.available()>0)
        {Serial.write(Serial2.read());}
      if(DEBUG_CAPTEUR)
        function_test_capteur();

    }
}


#endif
