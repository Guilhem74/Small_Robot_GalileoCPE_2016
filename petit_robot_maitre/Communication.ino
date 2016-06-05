#ifndef Communication
#define Communication


void vide_data_Slave();

void splitString(String message, char separator,String* data) {
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


bool Reception_Slave()
{
  if (stringComplete_Slave)
  {
    Serial.println("inputString_Slave : " + inputString_Slave);
    // on le découpe à chaque  ';'
    // et on stocke les bouts dans un tableau data
    splitString(inputString_Slave, SEPARATEUR,data_Slave);
    if(data_Slave[0]=="K")
    {
      vide_data_Slave();
     return true;
    }
    vide_data_Slave();
   }
    return false;

}

void Reception_Detection()
{
  if (stringComplete_Detection)
  {
    Serial.println("inputString_Detection : " + inputString_Detection);
    // on le découpe à chaque  ';'
    // et on stocke les bouts dans un tableau data
    splitString(inputString_Detection, SEPARATEUR,data_Detection);
    if(data_Detection[0]=="Z")
    {
      Capteur_detection_avant=true;
      vide_data_Detection();
      return;
    }
    if(data_Detection[0]=="S")
    {
      Capteur_detection_arriere=true;
      vide_data_Detection();
      return;
    }
    vide_data_Detection();
    return;
   }
   Capteur_detection_avant=false;
   Capteur_detection_arriere=false;

    return;

}



void vide_data_Slave()
{
  inputString_Slave = "";
  stringComplete_Slave = false;
  for(int i=0; i<10;i++)
    {
      data_Slave[i]="";
    }
}

void vide_data_Detection()
{
  inputString_Slave = "";
  stringComplete_Slave = false;
  for(int i=0; i<10;i++)
    {
      data_Detection[i]="";
    }
}
#endif
