#ifndef fonction
#define fonction
#include "global.h"

void Arreter()
{
  Serial2.println("S:");
  Serial.println("Demande arret");
  Validation_Message=0;//On RAZ l'esclave on attend plus de réponse
  lcd.print("Stop");
  lcd.newLine();
  
}

void Se_Deplacer_Avant()
{
  if(Validation_Message>=0)//Si on est a jour sur les échanges avec l'esclave
  {
      Serial2.print(X_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(Y_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE_DEPLACEMENT);
      Serial2.print('\n');
      
     lcd.print(X_DEPLACEMENT);
     lcd.print(';');
     lcd.print(Y_DEPLACEMENT);
     lcd.print(';');
     lcd.print(';');
     lcd.print(ANGLE_DEPLACEMENT);
     lcd.print('\n');
     lcd.newLine();
      Validation_Message=-1; //on attendra désormais une réponse de l'esclave avant de renvoyé un message
  }
}

void Se_Deplacer_Arriere()
{
  if(Validation_Message>=0)//Si on est a jour sur les échanges avec l'esclave
  {
      Serial2.print("R:");
      Serial2.print(X_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(Y_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE_DEPLACEMENT);
      Serial2.print('\n');
      lcd.print("R:");
       lcd.print(X_DEPLACEMENT);
     lcd.print(';');
     lcd.print(Y_DEPLACEMENT);
     lcd.print(';');
     lcd.print(';');
     lcd.print(ANGLE_DEPLACEMENT);
     lcd.print('\n');
     lcd.newLine();
      Validation_Message=-1; //on attendra désormais une réponse de l'esclave avant de renvoyé un message
  }
}
void Analyse_Objectif()
{

  Serial.write("Objectif courant : ");
  Serial.print(Objectif_En_Cours.nom);
  lcd.clear();
  lcd.print(Objectif_En_Cours.nom);
  lcd.newLine();

  if(Objectif_En_Cours.Dernier_Objectif==true)
  {
      Robot=Fin;
      Serial.println("Dernier Objectif");
      return;
  }
  X_DEPLACEMENT=Objectif_En_Cours.X;
  Y_DEPLACEMENT=Objectif_En_Cours.Y;
  ANGLE_DEPLACEMENT=Objectif_En_Cours.Angle;
  if(Objectif_En_Cours.Sens_Arriere==true){Robot=Recule;}
  else {Robot=Avance;}
}

bool Check_config()
{
  int I[9]={};
  bool Config_Correct=false;
  int i;
  while(I[8]!=1||Config_Correct==false)
  {
    if(digitalRead(A9)==LOW){return false;}
    Config_Correct=false;
  lcd.clear();
    for (i=4;i<= 11;i++)
    {
    I[i-3]=digitalRead(i);
    }
   if(I[1])
  {
    lcd.print("Couleur:Verte");
    Couleur_Verte=true;
    Objectif_En_Cours.Objectif_suivant=&ObjectifVRT_Init;
  }
  else
  {
    lcd.print("Couleur:Violette");
    Couleur_Verte=false;
        Objectif_En_Cours.Objectif_suivant=&ObjectifVLT_Init;
  }:
  lcd.newLine();
  if((I[2]+I[3]+I[4]+I[5]+I[6])==1)
  {//Strategie simple
    if(I[2])
    {
       Config_Correct=true;
      lcd.print("Strategie n°1");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLT1_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRT1_pos1;
    }
    else if(I[3])
    {
       Config_Correct=true;
      lcd.print("Strategie n°2");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLT2_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRT2_pos1;
    }
    else if(I[4])
    {
       Config_Correct=true;
      lcd.print("Strategie n°3");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLT3_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRT3_pos1;
    }
    else if(I[5])
    {
       Config_Correct=true;
      lcd.print("Strategie n°4");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLT3_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRT3_pos1;
    }
    else if(I[6])
    {
       Config_Correct=true;
      lcd.print("Strategie n°5");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLT3_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRT3_pos1;
    }
    else
    {
      Config_Correct=false;
    }
    
  }
  else
  {//Strategie complexe
    if(I[2]&&I[3]&&I[4])
    {
      Config_Correct=true;
      lcd.print("Homologation");
      ObjectifVLT_Init.Objectif_suivant=&ObjectifVLTH_pos1;
      ObjectifVRT_Init.Objectif_suivant=&ObjectifVRTH_pos1;
    }
    else
    {
      Config_Correct=false;
    }
    
  }
  lcd.newLine();
 
  if(I[7])
  {
    lcd.print("Detection :(");
    Detection_active=false;
  }
    lcd.newLine();
  delay(200);
  if(Config_Correct==true)
  {
    lcd.print("I8 pour valider");
    
    delay(1000);
  }
  }

  if(digitalRead(A9)==HIGH)
    {
      Lancement_config=true;
    }
}



#endif
