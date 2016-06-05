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
  if(Validation_Message>0)//Si on est a jour sur les échanges avec l'esclave
  {
      Serial2.print(X_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(Y_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE_DEPLACEMENT);
      Serial2.print('\n');
      Validation_Message=-1; //on attendra désormais une réponse de l'esclave avant de renvoyé un message
  }
}

void Se_Deplacer_Arriere()
{
  if(Validation_Message>0)//Si on est a jour sur les échanges avec l'esclave
  {
      Serial2.print("R:");
      Serial2.print(X_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(Y_DEPLACEMENT);
      Serial2.print(';');
      Serial2.print(';');
      Serial2.print(ANGLE_DEPLACEMENT);
      Serial2.print('\n');
      Validation_Message=-1; //on attendra désormais une réponse de l'esclave avant de renvoyé un message
  }
}
void Analyse_Objectif()
{

  Serial.print("Objectif courant : ");
  Serial.println(Objectif_En_Cours.nom);

  if(Objectif_En_Cours.Dernier_Objectif)
  {
      Robot=Fin;
      Serial.println("FIN");
      return;
  }
  X_DEPLACEMENT=Objectif_En_Cours.X;
  Y_DEPLACEMENT=Objectif_En_Cours.Y;
  ANGLE_DEPLACEMENT=Objectif_En_Cours.Angle;
  if(Objectif_En_Cours.Sens_Arriere)Robot=Recule;
  else Robot=Avance;
}



#endif
