
#include "global.h"
void setup() {
    Serial.begin(BAUDRATE_MASTER);
    Serial2.begin(BAUDRATE_MASTER);
    delay(100);
//Tirette
    pinMode(2,OUTPUT);
    pinMode(3,INPUT_PULLUP);
    digitalWrite(2,LOW);
//fin Tirette
    delay(1000);
}

void loop()
{
    if( Robot!=Prechauff)
    {//Tirette détaché
        if( millis()-temp_match < TEMPS_MATCH)
        {//Si ca fait moins de 90 s et que le signal a été lancé

           switch(Robot)
           {//machine d'etat
            case Avance:
                if (Capteur_detection_avant&&Objectif_En_Cours.Detection_Active)
                {
                  Robot=Stop;
                }
                else
                {
                  Se_Deplacer_Avant();
                }

                break;
             case Recule:
                if (Capteur_detection_arriere&&Objectif_En_Cours.Detection_Active)
                {
                  Robot=Stop;
                }
                else
                {
                  Se_Deplacer_Arriere();
                }

                break;
            case Attente:
                if((millis()-temp_attente)>TEMPS_MAX_ATTENTE)//Si on a detecte il y a plus de TEMPS_MAX_ATTENTE ms
                {
                  Robot=Libre;
                }
                break;
            case Libre:
                Analyse_Objectif();
                break;
            case Arrive://Le robot est arrivé a destination, on passe a l'objectif suivant
            if(Objectif_En_Cours.Objectif_suivant!=NULL&&Objectif_En_Cours.Dernier_Objectif==false)
            {
                Objectif_En_Cours = *(Objectif_En_Cours.Objectif_suivant);
                Robot=Libre;
            }
            else
            {
              Robot=Fin;
            }
                break;
                
            case Fin:
                  Arreter();
                  while(1);
                  break;
            case Stop:
                  Arreter();
                  temp_attente=millis();
                  Robot=Attente;
                break;
            default:
                 Robot=Libre;
                 break;
           }

          if(Reception_Slave())//Reception d'un message de l'esclave
          {
          	Validation_Message=0;
          	Robot=Arrive;
          }
          #if DETECTION_ACTIVATION
          Reception_Detection();//Reception d'un message de l'esclave
          #endif
          

        }
        else
        {//Fin du match dépassé
          //Dit stop a l'esclave
          Robot=Fin;
          Arreter();
          while(1);
        }

    }
    else
    {//Signal non lancé
     if(digitalRead(3)==HIGH)
     {
      Robot=Avance;
      temp_match=millis();
     }
    }
  

}


void serialEvent2() {
  while (Serial2.available()) {
    // récupérer le prochain octet (byte ou char) et l'enlever
    char inChar = (char)Serial2.read();
    // concaténation des octets reçus
    inputString_Slave += inChar;
    // caractère de fin pour notre chaine
    if (inChar == '\n') {
      stringComplete_Slave = true;
    }
  }
 }
#if DETECTION_ACTIVATION
void serialEvent() {
  while (Serial.available()) {
    // récupérer le prochain octet (byte ou char) et l'enlever
    char inChar = (char)Serial.read();
    // concaténation des octets reçus
    inputString_Detection += inChar;
    // caractère de fin pour notre chaine
    if (inChar == '\n') {
      stringComplete_Detection = true;
    }
  }
 }
 #endif
