#ifndef Communication
#define Communication
#include <Arduino.h>
#include "global.h"
#include "pins.h"
#include "defines.h"
void vide_data();

void splitString(String message, char separator) {
  int index = 0;

  cnt = 0;
    do {
      index = message.indexOf(separator);
      // s'il y a bien un caractère séparateur
      if(index != -1) {
          // on découpe la chaine et on stocke le bout dans le tableau
          data[cnt] = message.substring(0,index);
          cnt++;
          // on enlève du message le bout stocké
          message = message.substring(index+1, message.length());
      } else {
         // après le dernier espace
         // on s'assure que la chaine n'est pas vide
         if(message.length() > 0) {
           data[cnt] = message.substring(0,index); // dernier bout
           cnt++;
         }
      }
   } while(index >=0); // tant qu'il y a bien un séparateur dans la chaine

}


bool Reception()
{

   if (stringComplete)
  {
    Serial.println("inputString : " + inputString);
    // on le découpe à chaque espace ' '
    // et on stocke les bouts dans un tableau
    splitString(inputString, SEPARATEUR);
    if(data[0]=="K")
    {
      Serial.println("DDDDRecept");
      vide_data();

     return true;
    }
    if(data[0]=="W")
    {
      X_POSITION= data[1].toInt();
      Y_POSITION= data[2].toInt();
      ANGLE_POSITION= data[3].toInt();
    }

    vide_data();
    // vide la chaine

   }
    return false;

}

void vide_data()
{
  inputString = "";
  stringComplete = false;
  for(int i=0; i<10;i++)
    {
      data[i]="";
    }
}
#endif
