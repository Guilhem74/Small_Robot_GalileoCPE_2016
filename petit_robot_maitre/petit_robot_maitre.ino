#include <Arduino.h>

#include "global.h"
#include "pins.h"
#include "defines.h"



void setup() {
    Serial.begin(BAUDRATE_MASTER);
    Serial2.begin(BAUDRATE_MASTER);
    delay(100);
    servo1.attach(8);
    servo2.attach(9);
    servo2.write(100);
    Serial.println("Pokemon GO");
    delay(3000);
}

Etat old_ = Libre;
void loop()
{

    //debug_test();
    if( Robot!=Prechauff)
    {
        if( millis()-temp_match < TEMPS_MATCH)
        {//Si ca fait moins de 90 s et que le signal a été lancé

           switch(Robot)
           {
            case Avance:
                if (Detection(Avant))
                {
                  Robot=Stop;
                }
                else
                {
                  Se_Deplacer(X_DEPLACEMENT,Y_DEPLACEMENT,ANGLE_DEPLACEMENT);
                }

                break;
            case Attente:
                //if((millis()-temp_attente)>TEMPS_MAX_ATTENTE)//Si on a detecte il y a plus de TEMPS_MAX_ATTENTE ms
                //{
                  //Robot=Libre;
                //}
                
                delay(TEMPS_MAX_ATTENTE);
                Robot = Libre;
                break;
            case Libre:
                Analyse_Objectif();
                break;
            case Arrive://Le robot est arrivé a destination, On incremente pour passer a l'objectif sivant
                Objectif = static_cast<OBJECTIF>(static_cast<int>(Objectif)+1);
                Robot=Libre;
                break;
            case Recule:
                if (Detection(Arriere))
                {
                  Robot=Stop;
                }
                else
                {
                  Se_Deplacer(X_DEPLACEMENT,Y_DEPLACEMENT,ANGLE_DEPLACEMENT);
                }
                break;
            case Fin:
                  Arreter();
                break;
            case Stop:
                  Arreter();
                  //temp_attente=millis();
                  Robot=Attente;
                break;
            default:
                 Robot=Libre;
                 break;
           }

        if(Reception())
        {
        	Validation_Message++;
        	Robot=Arrive;
        }



        }
        else
        {//Fin du match dépassé
          //Dit stop a l'esclave
          Robot=Fin;
          Arreter();

        }

    }
    else
    {//Signal non lancé
      //TODO Check verification
      temp_match=millis();
    }
  

}


void serialEvent2() {
  while (Serial2.available()) {
    // récupérer le prochain octet (byte ou char) et l'enlever
    char inChar = (char)Serial2.read();
    // concaténation des octets reçus
    inputString += inChar;
    // caractère de fin pour notre chaine
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
 }
