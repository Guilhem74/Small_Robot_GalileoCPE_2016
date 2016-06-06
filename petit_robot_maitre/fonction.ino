#ifndef fonction
#define fonction
#include "global.h"

void Arreter()
{
  Serial2.println("S:");
  Validation_Message=-1;//On RAZ l'esclave on attend une seule réponse
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
  if(Objectif_En_Cours.Sens_Arriere)Robot=Recule;
  else Robot=Avance;
}



#endif
