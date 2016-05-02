#include <Arduino.h>




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


void Reception_ordre()
{
   if (stringComplete)
  {
    Serial.println("Parlons un peu");

    // on le découpe à chaque espace ' '
    // et on stocke les bouts dans un tableau
    splitString(inputString, SEPARATEUR);
   Serial.println(inputString);
    if(data[0]=="X")
    {
      X_COMMANDE= data[1].toInt();
      Notif_arrive=true;//Apres chaque demande, on attendra une réponse, on doit donc notifier

    }
    if(data[0]=="Y")
    {
      Y_COMMANDE= data[1].toInt();
      Notif_arrive=true;//Apres chaque demande, on attendra une réponse, on doit donc notifier
    }
    if(data[0]=="A")
    {
      ANGLE_COMMANDE= data[1].toInt();
      Notif_arrive=true;//Apres chaque demande, on attendra une réponse, on doit donc notifier
    }
    if(data[0]=="W")//Where, renvoie les coordonnées
    {
     Serial2.print("W;");
     Serial2.print(last_X);
     Serial2.print(";");
     Serial2.print(last_Y);
     Serial2.print(";");
     Serial2.println(ANGLE_COMMANDE);
    }
     if(data[0]=="XY")//Deux commande fournis
    {
     X_COMMANDE= data[1].toInt();
     Y_COMMANDE= data[2].toInt();
     Notif_arrive=true;//Apres chaque demande, on attendra une réponse, on doit donc notifier
    }
    if(data[0]=="XYA"||data[0]=="T")//Trois commande fournis ou T
    {
     X_COMMANDE= data[1].toInt();
     Y_COMMANDE= data[2].toInt();
     ANGLE_COMMANDE= data[3].toInt();
     Notif_arrive=true;//Apres chaque demande, on attendra une réponse, on doit donc notifier
    }
    if(data[0]=="S")
    {
     X_COMMANDE=last_X;
     Y_COMMANDE=last_Y;
     Notif_arrive=false;
    }
    if(data[0]=="B")//Blabla
    {
     Serial.println("NINJA");
    }

    for(int i=0; i<10;i++)
    {
      data[i]="";
    }
    // vide la chaine
    inputString = "";
    stringComplete = false;

    }

}
