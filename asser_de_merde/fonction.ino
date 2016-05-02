#include <Arduino.h>


void asservire()
{
  mise_a_jour_POS();

  calcul_erreur();

  vitesse_D=1000*((Dmm-temp_D)/(float)(top_millis-temp_millis));  //10 = 10000/1000 normalisation de la vitesse pour fuzzification //800 car vitesse max =80cm sec
  vitesse_G=1000*((Gmm-temp_G)/(float)(top_millis-temp_millis));  //10 = 10000/1000 normalisation de la vitesse pour fuzzification
  vitesse_moyenne=(vitesse_D + vitesse_G)/2.0f;
  float k_fuzzy_vitesse = 10000/(float)VITESSE_MAX;
  vitesse_moyenne_fuzzy=k_fuzzy_vitesse*vitesse_moyenne;

  vitesse_angle=1000*(float)((angle_degre-temp_angle)/(float)(top_millis-temp_millis));
  float k_fuzzy_vitesse_angle=(float)10000/(float)VITESSE_ANGLE_MAX;
  vitesse_angle_fuzzy = vitesse_angle*k_fuzzy_vitesse_angle;

  //fuzzification des paramètres d'entrée de l'asservissement (erreur, vitesse)
  fuzzy->setInput(1, erreur_moyenne_fuzzy);
  fuzzy->setInput(2, vitesse_moyenne_fuzzy);
  fuzzy->setInput(3, erreur_angle_fuzzy);
  fuzzy->setInput(4, vitesse_angle_fuzzy);
  fuzzy->fuzzify();

  //defuzzification du bordel
  float direct_speed = fuzzy->defuzzify(1);
  float angle_speed = fuzzy->defuzzify(2);

  //Serial.print("direct_speed\t");
  //Serial.print(direct_speed);
  //Serial.print("\tangle_speed\t");
  //Serial.println(angle_speed);

  setRobotSpeed(direct_speed,angle_speed);
}

void mise_a_jour_POS()
{
  //voir https://www.cs.princeton.edu/courses/archive/fall11/cos495/COS495-Lecture5-Odometry.pdf
  temp_D=Dmm;
  temp_G=Gmm;
  Dmm=D*PI*DIAMETRE_ROUE*COEFF_MAGIQUE_ROUE_DROITE/TICCODEUSE;//conversion tic2mm
  Gmm=G*PI*DIAMETRE_ROUE*COEFF_MAGIQUE_ROUE_GAUCHE/TICCODEUSE;//conversion tic2mm
  int delta_Dmm = Dmm-temp_D;//TODO passer en int?
  int delta_Gmm = Gmm-temp_G;

  static float localX = X_INITIALE, localY = Y_INITIALE;
  localX += (float)(((delta_Dmm+delta_Gmm)/2.0f)*cos(angle_radian + (delta_Dmm-delta_Gmm)/float(2*ECARTEMENT_ROUES)));
  localY += (float)(((delta_Dmm+delta_Gmm)/2.0f)*sin(angle_radian + (delta_Dmm-delta_Gmm)/float(2*ECARTEMENT_ROUES)));
  last_X = X;
  last_Y = Y;
  X = X + int(localX);
  Y = Y + int(localY);

  localX -= (int)(localX);
  localY -= (int)(localY);

  temp_angle=angle_degre;
  angle_radian += ((float)(delta_Dmm-delta_Gmm)/ECARTEMENT_ROUES);//toutes les distances doivent avoir les mêmes unités!
  angle_degre=(angle_radian*360/(float)(2*PI));
}

void calcul_erreur()
{
  //voir http://www.dca.ufrn.br/~adelardo/artigos/ICINCO04a.pdf
  float erreur_angle_radian=0;
  int32_t dx = X_COMMANDE-X, dy = Y_COMMANDE-Y;
  if(sqrt(dx*dx+dy*dy)<50)//cerle proche du but dans lequel on se met à l'angle final
  {
    if(sqrt(dx*dx+dy*dy)<30)//cerle proche du but dans lequel on se met à l'angle final
    {
      is_close_to_goal = true;
    }
    else//entre 4 et 2 cm on continu d'avancer vers le but sans corriger l'angle (la correction d'angle fait sortir du cercle)
    {
       erreur_angle_fuzzy = 0;
    }
  }
  else is_close_to_goal = false;

  erreur_angle_radian=atan2(Y_COMMANDE-Y,X_COMMANDE-X)-angle_radian-PI*MARCHE_ARRIERE;//angle entre le vecteur perpendiculaire à l'axe des roues et le vecteur pointant sur la destination
  erreur_angle_radian = fmod(erreur_angle_radian,PI+0.01);// compris entre -PI et PI, on rajoute 0.01 pour les 180° et pour que la marche arriere soit prise en compte

  if(is_close_to_goal==true)//si on est proche du but on cherche à se mettre dans l'angle final commandé
  {
    erreur_angle=ANGLE_COMMANDE-angle_degre;//erreur entre l'angle actuel et l'angle commandé
    erreur_angle=fmod(erreur_angle,180);
    if((abs(erreur_angle)<5) && Notif_arrive==true)
      {
       Notif_arrive=false;//La notification est envoyé, on ne doit plus notifier
       Serial2.println("K;");
      }

  }
  else
  {
    erreur_angle=erreur_angle_radian*360/(float)(2*PI);
  }

  erreur_moyenne=(float)sqrt(dx*dx+dy*dy)*(float)cos(erreur_angle_radian-PI*MARCHE_ARRIERE); // projection de la distance séparant de la cible sur le vecteur perpendicualire à l'axe des roues
  float k_erreur_moyenne = 10000/ERREUR_MAX;
  float k_erreur_angle = 10000/ERREUR_MAX_ANGLE;


  static boolean in_hysteresis = false;
  if(abs(sqrt(dx*dx+dy*dy))<HYST_IN)//cerle proche du but dans lequel on se met à l'angle final
  {
    in_hysteresis = true;
    is_close_to_goal = true;
  }
  else if (abs(sqrt(dx*dx+dy*dy))<HYST_OUT && in_hysteresis)
  {
    //on ne change rien
  }
  else
  {
    is_close_to_goal = false;
    in_hysteresis = false;
  }

  erreur_moyenne_fuzzy=erreur_moyenne * k_erreur_moyenne;
  erreur_angle_fuzzy=erreur_angle * k_erreur_angle;
}

void setRobotSpeed(float output,float angle_speed)
{
  boolean sens_D=ETAT_MOTEUR_AVANCE;
  boolean sens_G=ETAT_MOTEUR_AVANCE;

  int speed_out_D =0;
  int speed_out_G =0;

  float k_vitesse=SPEED_OUT_MAX/(float)10000;// inverser /
  float k_vitesse_angulaire=ANGLE_OUT_MAX/(float)10000;
  speed_out_D=output*k_vitesse+angle_speed*k_vitesse_angulaire;
  speed_out_G=output*k_vitesse-angle_speed*k_vitesse_angulaire;


//  Serial.print(output,10);
//  Serial.print('\t');
//  Serial.println(angle_speed,10);

  if(speed_out_D <0)
  {
    sens_D=!(sens_D);
    speed_out_D=-speed_out_D;
  }
  if(speed_out_G <0)
  {
    sens_G=!(sens_G);
    speed_out_G=-speed_out_G;
  }

  if (speed_out_D>255)speed_out_D=255;
  if (speed_out_G>255)speed_out_G=255;
  if (speed_out_D<0)speed_out_D=0;//on sait jamais
  if (speed_out_G<0)speed_out_G=0;

  digitalWrite(PIN_MOTEUR_DROITE_SENS, sens_D);
  digitalWrite(PIN_MOTEUR_GAUCHE_SENS, sens_G);
  delay(1);
  analogWrite(PIN_MOTEUR_DROITE_VITESSE, speed_out_D);
  analogWrite(PIN_MOTEUR_GAUCHE_VITESSE, speed_out_G);

  static int compt=0;
  compt=(compt+1)%100;

  if(compt)
    return;
  if(DEBUG_VITESSE&&DEBUG)
  {
  Serial.print("output: ");
  Serial.print(speed_out_D);
  Serial.print("\t");
  Serial.println(speed_out_G);
  }


}

void recuperer(byte A)
{

  String inputString = "";
  bool fini=true;
  if(A==0)//Droite
      Serial1.write("x");

  if(A==1)//Gauche
      Serial1.write("y");

  while (Serial1.available()&& fini)
  {
    char inChar = (char)Serial1.read();

    inputString += inChar;

    if (inChar == '\n')
    { inputString += inChar;
      if(A==0)
        {
          D=inputString.toInt();
          if(PETITROBOT)
          {
            D=-D;//Les moteurs sont inversés sur le petit Robot
          }
          if(DEBUG&&DEBUG_ENCODEUR)
          {
          Serial.println("D");
          Serial.println(D);
          }
        }
      if(A==1)
        {
          G=inputString.toInt();
          if(DEBUG&&DEBUG_ENCODEUR)
          {
          Serial.println("G");
          Serial.println(G);
          }
        }
         if(DEBUG&&DEBUG_ENCODEUR)
          {
            Serial.println("Fin");
          }
      fini=false;
    }
  }

}
void print_debug()
{
  if(!DEBUG)
    return;
  //affichage une fois sur 500 sinon utiliser un if(val) pour l'afficher uniquement quand !=0
  static int compt=0;
  compt=(compt+1)%20;

  if(compt)
    return;

//  Serial.print("E_moy ");
//  Serial.print(erreur_moyenne);
//  Serial.print("\tV_moy ");
//  Serial.print(vitesse_moyenne);
//  Serial.print("\tE_angle ");
//  Serial.print(erreur_angle);
//  Serial.print("\tV_angle ");
//  Serial.println(vitesse_angle);
//
//  Serial.print("E_moy_F ");
//  Serial.print(erreur_moyenne_fuzzy);
//  Serial.print("\tV_moy_F ");
//  Serial.print(vitesse_moyenne_fuzzy);
//  Serial.print("\tE_angle_F ");
//  Serial.print(erreur_angle_fuzzy);
//  Serial.print("\tV_angle_F ");
//  Serial.println(vitesse_angle_fuzzy);

//  Serial.print("angle\t");
//  Serial.print(angle_degre);
//  Serial.print("\tX\t");
//  Serial.print(X);
//  Serial.print("\tY\t");
//  Serial.println(Y);

//  if(DEBUG_VITESSE)
//  {
//  Serial.print("vitesse_D: ");
//  Serial.print(vitesse_D);
//  Serial.print(" vitesse_G: ");
//  Serial.print(vitesse_G);
//  Serial.print(" vitesse_moyenne: ");
//  Serial.print(vitesse_moyenne);
//  }
  if(DEBUG_ANGLE)
  {
  Serial.print(" erreur_D: ");
  Serial.print(erreur_D);
  Serial.print(" erreur_G: ");
  Serial.print(erreur_G);
  Serial.print(" erreur_moyenne: ");
  Serial.print(erreur_moyenne);
  Serial.print(" angle: ");
  Serial.print(angle);
  Serial.print(" erreur_angle: ");
  Serial.println(erreur_angle);
  }

  Serial.println(" ");
}

void config_fuzzy()
{
  // FuzzyInput
  FuzzyInput* erreur = new FuzzyInput(1);
  erreur->addFuzzySet(NB_erreur);
  erreur->addFuzzySet(NS_erreur);
  erreur->addFuzzySet(Z_erreur);
  erreur->addFuzzySet(PB_erreur);
  erreur->addFuzzySet(PS_erreur);
  fuzzy->addFuzzyInput(erreur);

  // FuzzyInput
  FuzzyInput* inputSpeed = new FuzzyInput(2);
  inputSpeed->addFuzzySet(NB_speed_IN);
  inputSpeed->addFuzzySet(NS_speed_IN);
  inputSpeed->addFuzzySet(Z_speed_IN);
  inputSpeed->addFuzzySet(PS_speed_IN);
  inputSpeed->addFuzzySet(PB_speed_IN);
  fuzzy->addFuzzyInput(inputSpeed);

  // FuzzyInput
  FuzzyInput* erreur_angle = new FuzzyInput(3);
  erreur_angle->addFuzzySet(NB_erreur_angle);
  erreur_angle->addFuzzySet(NS_erreur_angle);
  erreur_angle->addFuzzySet(Z_erreur_angle);
  erreur_angle->addFuzzySet(PB_erreur_angle);
  erreur_angle->addFuzzySet(PS_erreur_angle);
  fuzzy->addFuzzyInput(erreur_angle);

  // FuzzyInput
  FuzzyInput* inputSpeed_angle = new FuzzyInput(4);
  inputSpeed_angle->addFuzzySet(NB_speed_angle_IN);
  inputSpeed_angle->addFuzzySet(NS_speed_angle_IN);
  inputSpeed_angle->addFuzzySet(Z_speed_angle_IN);
  inputSpeed_angle->addFuzzySet(PS_speed_angle_IN);
  inputSpeed_angle->addFuzzySet(PB_speed_angle_IN);
  fuzzy->addFuzzyInput(inputSpeed_angle);

  // FuzzyOutput
  // adding speed as output too
  FuzzyOutput* outputSpeed = new FuzzyOutput(1);
  outputSpeed->addFuzzySet(NB_speed_OUT);
  outputSpeed->addFuzzySet(NS_speed_OUT);
  outputSpeed->addFuzzySet(Z_speed_OUT);
  outputSpeed->addFuzzySet(PS_speed_OUT);
  outputSpeed->addFuzzySet(PB_speed_OUT);
  fuzzy->addFuzzyOutput(outputSpeed);

  FuzzyOutput* outputSpeed_angle = new FuzzyOutput(2);
  outputSpeed_angle->addFuzzySet(NB_speed_angle_OUT);
  outputSpeed_angle->addFuzzySet(NS_speed_angle_OUT);
  outputSpeed_angle->addFuzzySet(Z_speed_angle_OUT);
  outputSpeed_angle->addFuzzySet(PS_speed_angle_OUT);
  outputSpeed_angle->addFuzzySet(PB_speed_angle_OUT);
  fuzzy->addFuzzyOutput(outputSpeed_angle);

  //antécédents
  FuzzyRuleAntecedent* ifNB_erreurAndNB_speed_IN = new FuzzyRuleAntecedent();
  ifNB_erreurAndNB_speed_IN->joinWithAND(NB_erreur, NB_speed_IN);
  FuzzyRuleAntecedent* ifNS_erreurAndNB_speed_IN = new FuzzyRuleAntecedent();
  ifNS_erreurAndNB_speed_IN->joinWithAND(NS_erreur, NB_speed_IN);
  FuzzyRuleAntecedent* ifZ_erreurAndNB_speed_IN = new FuzzyRuleAntecedent();
  ifZ_erreurAndNB_speed_IN->joinWithAND(Z_erreur, NB_speed_IN);
  FuzzyRuleAntecedent* ifPS_erreurAndNB_speed_IN = new FuzzyRuleAntecedent();
  ifPS_erreurAndNB_speed_IN->joinWithAND(PS_erreur, NB_speed_IN);
  FuzzyRuleAntecedent* ifPB_erreurAndNB_speed_IN = new FuzzyRuleAntecedent();
  ifPB_erreurAndNB_speed_IN->joinWithAND(PB_erreur, NB_speed_IN);

  FuzzyRuleAntecedent* ifNB_erreurAndNS_speed_IN = new FuzzyRuleAntecedent();
  ifNB_erreurAndNS_speed_IN->joinWithAND(NB_erreur, NS_speed_IN);
  FuzzyRuleAntecedent* ifNS_erreurAndNS_speed_IN = new FuzzyRuleAntecedent();
  ifNS_erreurAndNS_speed_IN->joinWithAND(NS_erreur, NS_speed_IN);
  FuzzyRuleAntecedent* ifZ_erreurAndNS_speed_IN = new FuzzyRuleAntecedent();
  ifZ_erreurAndNS_speed_IN->joinWithAND(Z_erreur, NS_speed_IN);
  FuzzyRuleAntecedent* ifPS_erreurAndNS_speed_IN = new FuzzyRuleAntecedent();
  ifPS_erreurAndNS_speed_IN->joinWithAND(PS_erreur, NS_speed_IN);
  FuzzyRuleAntecedent* ifPB_erreurAndNS_speed_IN = new FuzzyRuleAntecedent();
  ifPB_erreurAndNS_speed_IN->joinWithAND(PB_erreur, NS_speed_IN);

  FuzzyRuleAntecedent* ifNB_erreurAndZ_speed_IN = new FuzzyRuleAntecedent();
  ifNB_erreurAndZ_speed_IN->joinWithAND(NB_erreur, Z_speed_IN);
  FuzzyRuleAntecedent* ifNS_erreurAndZ_speed_IN = new FuzzyRuleAntecedent();
  ifNS_erreurAndZ_speed_IN->joinWithAND(NS_erreur, Z_speed_IN);
  FuzzyRuleAntecedent* ifZ_erreurAndZ_speed_IN = new FuzzyRuleAntecedent();
  ifZ_erreurAndZ_speed_IN->joinWithAND(Z_erreur, Z_speed_IN);
  FuzzyRuleAntecedent* ifPS_erreurAndZ_speed_IN = new FuzzyRuleAntecedent();
  ifPS_erreurAndZ_speed_IN->joinWithAND(PS_erreur, Z_speed_IN);
  FuzzyRuleAntecedent* ifPB_erreurAndZ_speed_IN = new FuzzyRuleAntecedent();
  ifPB_erreurAndZ_speed_IN->joinWithAND(PB_erreur, Z_speed_IN);

  FuzzyRuleAntecedent* ifNB_erreurAndPS_speed_IN = new FuzzyRuleAntecedent();
  ifNB_erreurAndPS_speed_IN->joinWithAND(NB_erreur, PS_speed_IN);
  FuzzyRuleAntecedent* ifNS_erreurAndPS_speed_IN = new FuzzyRuleAntecedent();
  ifNS_erreurAndPS_speed_IN->joinWithAND(NS_erreur, PS_speed_IN);
  FuzzyRuleAntecedent* ifZ_erreurAndPS_speed_IN = new FuzzyRuleAntecedent();
  ifZ_erreurAndPS_speed_IN->joinWithAND(Z_erreur, PS_speed_IN);
  FuzzyRuleAntecedent* ifPS_erreurAndPS_speed_IN = new FuzzyRuleAntecedent();
  ifPS_erreurAndPS_speed_IN->joinWithAND(PS_erreur, PS_speed_IN);
  FuzzyRuleAntecedent* ifPB_erreurAndPS_speed_IN = new FuzzyRuleAntecedent();
  ifPB_erreurAndPS_speed_IN->joinWithAND(PB_erreur, PS_speed_IN);

  FuzzyRuleAntecedent* ifNB_erreurAndPB_speed_IN = new FuzzyRuleAntecedent();
  ifNB_erreurAndPB_speed_IN->joinWithAND(NB_erreur, PB_speed_IN);
  FuzzyRuleAntecedent* ifNS_erreurAndPB_speed_IN = new FuzzyRuleAntecedent();
  ifNS_erreurAndPB_speed_IN->joinWithAND(NS_erreur, PB_speed_IN);
  FuzzyRuleAntecedent* ifZ_erreurAndPB_speed_IN = new FuzzyRuleAntecedent();
  ifZ_erreurAndPB_speed_IN->joinWithAND(Z_erreur, PB_speed_IN);
  FuzzyRuleAntecedent* ifPS_erreurAndPB_speed_IN = new FuzzyRuleAntecedent();
  ifPS_erreurAndPB_speed_IN->joinWithAND(PS_erreur, PB_speed_IN);
  FuzzyRuleAntecedent* ifPB_erreurAndPB_speed_IN = new FuzzyRuleAntecedent();
  ifPB_erreurAndPB_speed_IN->joinWithAND(PB_erreur, PB_speed_IN);

  //angle
  FuzzyRuleAntecedent* ifNB_erreur_angleAndNB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNB_erreur_angleAndNB_speed_angle_IN->joinWithAND(NB_erreur_angle, NB_speed_angle_IN);
  FuzzyRuleAntecedent* ifNS_erreur_angleAndNB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNS_erreur_angleAndNB_speed_angle_IN->joinWithAND(NS_erreur_angle, NB_speed_angle_IN);
  FuzzyRuleAntecedent* ifZ_erreur_angleAndNB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifZ_erreur_angleAndNB_speed_angle_IN->joinWithAND(Z_erreur_angle, NB_speed_angle_IN);
  FuzzyRuleAntecedent* ifPS_erreur_angleAndNB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPS_erreur_angleAndNB_speed_angle_IN->joinWithAND(PS_erreur_angle, NB_speed_angle_IN);
  FuzzyRuleAntecedent* ifPB_erreur_angleAndNB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPB_erreur_angleAndNB_speed_angle_IN->joinWithAND(PB_erreur_angle, NB_speed_angle_IN);

  FuzzyRuleAntecedent* ifNB_erreur_angleAndNS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNB_erreur_angleAndNS_speed_angle_IN->joinWithAND(NB_erreur_angle, NS_speed_angle_IN);
  FuzzyRuleAntecedent* ifNS_erreur_angleAndNS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNS_erreur_angleAndNS_speed_angle_IN->joinWithAND(NS_erreur_angle, NS_speed_angle_IN);
  FuzzyRuleAntecedent* ifZ_erreur_angleAndNS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifZ_erreur_angleAndNS_speed_angle_IN->joinWithAND(Z_erreur_angle, NS_speed_angle_IN);
  FuzzyRuleAntecedent* ifPS_erreur_angleAndNS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPS_erreur_angleAndNS_speed_angle_IN->joinWithAND(PS_erreur_angle, NS_speed_angle_IN);
  FuzzyRuleAntecedent* ifPB_erreur_angleAndNS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPB_erreur_angleAndNS_speed_angle_IN->joinWithAND(PB_erreur_angle, NS_speed_angle_IN);

  FuzzyRuleAntecedent* ifNB_erreur_angleAndZ_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNB_erreur_angleAndZ_speed_angle_IN->joinWithAND(NB_erreur_angle, Z_speed_angle_IN);
  FuzzyRuleAntecedent* ifNS_erreur_angleAndZ_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNS_erreur_angleAndZ_speed_angle_IN->joinWithAND(NS_erreur_angle, Z_speed_angle_IN);
  FuzzyRuleAntecedent* ifZ_erreur_angleAndZ_speed_angle_IN = new FuzzyRuleAntecedent();
  ifZ_erreur_angleAndZ_speed_angle_IN->joinWithAND(Z_erreur_angle, Z_speed_angle_IN);
  FuzzyRuleAntecedent* ifPS_erreur_angleAndZ_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPS_erreur_angleAndZ_speed_angle_IN->joinWithAND(PS_erreur_angle, Z_speed_angle_IN);
  FuzzyRuleAntecedent* ifPB_erreur_angleAndZ_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPB_erreur_angleAndZ_speed_angle_IN->joinWithAND(PB_erreur_angle, Z_speed_angle_IN);

  FuzzyRuleAntecedent* ifNB_erreur_angleAndPS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNB_erreur_angleAndPS_speed_angle_IN->joinWithAND(NB_erreur_angle, PS_speed_angle_IN);
  FuzzyRuleAntecedent* ifNS_erreur_angleAndPS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNS_erreur_angleAndPS_speed_angle_IN->joinWithAND(NS_erreur_angle, PS_speed_angle_IN);
  FuzzyRuleAntecedent* ifZ_erreur_angleAndPS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifZ_erreur_angleAndPS_speed_angle_IN->joinWithAND(Z_erreur_angle, PS_speed_angle_IN);
  FuzzyRuleAntecedent* ifPS_erreur_angleAndPS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPS_erreur_angleAndPS_speed_angle_IN->joinWithAND(PS_erreur_angle, PS_speed_angle_IN);
  FuzzyRuleAntecedent* ifPB_erreur_angleAndPS_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPB_erreur_angleAndPS_speed_angle_IN->joinWithAND(PB_erreur_angle, PS_speed_angle_IN);

  FuzzyRuleAntecedent* ifNB_erreur_angleAndPB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNB_erreur_angleAndPB_speed_angle_IN->joinWithAND(NB_erreur_angle, PB_speed_angle_IN);
  FuzzyRuleAntecedent* ifNS_erreur_angleAndPB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifNS_erreur_angleAndPB_speed_angle_IN->joinWithAND(NS_erreur_angle, PB_speed_angle_IN);
  FuzzyRuleAntecedent* ifZ_erreur_angleAndPB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifZ_erreur_angleAndPB_speed_angle_IN->joinWithAND(Z_erreur_angle, PB_speed_angle_IN);
  FuzzyRuleAntecedent* ifPS_erreur_angleAndPB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPS_erreur_angleAndPB_speed_angle_IN->joinWithAND(PS_erreur_angle, PB_speed_angle_IN);
  FuzzyRuleAntecedent* ifPB_erreur_angleAndPB_speed_angle_IN = new FuzzyRuleAntecedent();
  ifPB_erreur_angleAndPB_speed_angle_IN->joinWithAND(PB_erreur_angle, PB_speed_angle_IN);

  //conséquences
  FuzzyRuleConsequent* thenNB_speed_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenNB_speed_OUT->addOutput(NB_speed_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenNS_speed_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenNS_speed_OUT->addOutput(NS_speed_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenZ_speed_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenZ_speed_OUT->addOutput(Z_speed_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenPS_speed_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenPS_speed_OUT->addOutput(PS_speed_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenPB_speed_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenPB_speed_OUT->addOutput(PB_speed_OUT);// Adding corresponding FuzzySet to Consequent object

  FuzzyRuleConsequent* thenNB_speed_angle_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenNB_speed_angle_OUT->addOutput(NB_speed_angle_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenNS_speed_angle_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenNS_speed_angle_OUT->addOutput(NS_speed_angle_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenZ_speed_angle_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenZ_speed_angle_OUT->addOutput(Z_speed_angle_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenPS_speed_angle_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenPS_speed_angle_OUT->addOutput(PS_speed_angle_OUT);// Adding corresponding FuzzySet to Consequent object
  FuzzyRuleConsequent* thenPB_speed_angle_OUT = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
  thenPB_speed_angle_OUT->addOutput(PB_speed_angle_OUT);// Adding corresponding FuzzySet to Consequent object

  //règles
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifNB_erreurAndNB_speed_IN, thenNB_speed_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifNS_erreurAndNB_speed_IN, thenNB_speed_OUT);
  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifZ_erreurAndNB_speed_IN, thenNS_speed_OUT);
  FuzzyRule* fuzzyRule04 = new FuzzyRule(4, ifPS_erreurAndNB_speed_IN, thenNS_speed_OUT);
  FuzzyRule* fuzzyRule05 = new FuzzyRule(5, ifPB_erreurAndNB_speed_IN, thenZ_speed_OUT);

  FuzzyRule* fuzzyRule06 = new FuzzyRule(6, ifNB_erreurAndNS_speed_IN, thenNB_speed_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule07 = new FuzzyRule(7, ifNS_erreurAndNS_speed_IN, thenNS_speed_OUT);
  FuzzyRule* fuzzyRule08 = new FuzzyRule(8, ifZ_erreurAndNS_speed_IN, thenNS_speed_OUT);
  FuzzyRule* fuzzyRule09 = new FuzzyRule(9, ifPS_erreurAndNS_speed_IN, thenZ_speed_OUT);
  FuzzyRule* fuzzyRule10 = new FuzzyRule(10, ifPB_erreurAndNS_speed_IN, thenPS_speed_OUT);

  FuzzyRule* fuzzyRule11 = new FuzzyRule(11, ifNB_erreurAndZ_speed_IN, thenNS_speed_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule12 = new FuzzyRule(12, ifNS_erreurAndZ_speed_IN, thenNS_speed_OUT);
  FuzzyRule* fuzzyRule13 = new FuzzyRule(13, ifZ_erreurAndZ_speed_IN, thenZ_speed_OUT);
  FuzzyRule* fuzzyRule14 = new FuzzyRule(14, ifPS_erreurAndZ_speed_IN, thenPS_speed_OUT);
  FuzzyRule* fuzzyRule15 = new FuzzyRule(15, ifPB_erreurAndZ_speed_IN, thenPS_speed_OUT);

  FuzzyRule* fuzzyRule16 = new FuzzyRule(16, ifNB_erreurAndPS_speed_IN, thenNS_speed_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule17 = new FuzzyRule(17, ifNS_erreurAndPS_speed_IN, thenZ_speed_OUT);
  FuzzyRule* fuzzyRule18 = new FuzzyRule(18, ifZ_erreurAndPS_speed_IN, thenPS_speed_OUT);
  FuzzyRule* fuzzyRule19 = new FuzzyRule(19, ifPS_erreurAndPS_speed_IN, thenPS_speed_OUT);
  FuzzyRule* fuzzyRule20 = new FuzzyRule(20, ifPB_erreurAndPS_speed_IN, thenPB_speed_OUT);

  FuzzyRule* fuzzyRule21 = new FuzzyRule(21, ifNB_erreurAndPB_speed_IN, thenZ_speed_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule22 = new FuzzyRule(22, ifNS_erreurAndPB_speed_IN, thenPS_speed_OUT);
  FuzzyRule* fuzzyRule23 = new FuzzyRule(23, ifZ_erreurAndPB_speed_IN, thenPS_speed_OUT);
  FuzzyRule* fuzzyRule24 = new FuzzyRule(24, ifPS_erreurAndPB_speed_IN, thenPB_speed_OUT);
  FuzzyRule* fuzzyRule25 = new FuzzyRule(25, ifPB_erreurAndPB_speed_IN, thenPB_speed_OUT);

  FuzzyRule* fuzzyRule26 = new FuzzyRule(26, ifNB_erreur_angleAndNB_speed_angle_IN, thenNB_speed_angle_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule27 = new FuzzyRule(27, ifNS_erreur_angleAndNB_speed_angle_IN, thenNB_speed_angle_OUT);
  FuzzyRule* fuzzyRule28 = new FuzzyRule(28, ifZ_erreur_angleAndNB_speed_angle_IN, thenNS_speed_angle_OUT);
  FuzzyRule* fuzzyRule29 = new FuzzyRule(29, ifPS_erreur_angleAndNB_speed_angle_IN, thenNS_speed_angle_OUT);
  FuzzyRule* fuzzyRule30 = new FuzzyRule(30, ifPB_erreur_angleAndNB_speed_angle_IN, thenZ_speed_angle_OUT);

  FuzzyRule* fuzzyRule31 = new FuzzyRule(31, ifNB_erreur_angleAndNS_speed_angle_IN, thenNB_speed_angle_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule32 = new FuzzyRule(32, ifNS_erreur_angleAndNS_speed_angle_IN, thenNS_speed_angle_OUT);
  FuzzyRule* fuzzyRule33 = new FuzzyRule(33, ifZ_erreur_angleAndNS_speed_angle_IN, thenNS_speed_angle_OUT);
  FuzzyRule* fuzzyRule34 = new FuzzyRule(34, ifPS_erreur_angleAndNS_speed_angle_IN, thenZ_speed_angle_OUT);
  FuzzyRule* fuzzyRule35 = new FuzzyRule(35, ifPB_erreur_angleAndNS_speed_angle_IN, thenPS_speed_angle_OUT);

  FuzzyRule* fuzzyRule36 = new FuzzyRule(36, ifNB_erreur_angleAndZ_speed_angle_IN, thenNS_speed_angle_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule37 = new FuzzyRule(37, ifNS_erreur_angleAndZ_speed_angle_IN, thenNS_speed_angle_OUT);
  FuzzyRule* fuzzyRule38 = new FuzzyRule(38, ifZ_erreur_angleAndZ_speed_angle_IN, thenZ_speed_angle_OUT);
  FuzzyRule* fuzzyRule39 = new FuzzyRule(39, ifPS_erreur_angleAndZ_speed_angle_IN, thenPS_speed_angle_OUT);
  FuzzyRule* fuzzyRule40 = new FuzzyRule(40, ifPB_erreur_angleAndZ_speed_angle_IN, thenPS_speed_angle_OUT);

  FuzzyRule* fuzzyRule41 = new FuzzyRule(41, ifNB_erreur_angleAndPS_speed_angle_IN, thenNS_speed_angle_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule42 = new FuzzyRule(42, ifNS_erreur_angleAndPS_speed_angle_IN, thenZ_speed_angle_OUT);
  FuzzyRule* fuzzyRule43 = new FuzzyRule(43, ifZ_erreur_angleAndPS_speed_angle_IN, thenPS_speed_angle_OUT);
  FuzzyRule* fuzzyRule44 = new FuzzyRule(44, ifPS_erreur_angleAndPS_speed_angle_IN, thenPS_speed_angle_OUT);
  FuzzyRule* fuzzyRule45 = new FuzzyRule(45, ifPB_erreur_angleAndPS_speed_angle_IN, thenPB_speed_angle_OUT);

  FuzzyRule* fuzzyRule46 = new FuzzyRule(46, ifNB_erreur_angleAndPB_speed_angle_IN, thenZ_speed_angle_OUT); // Passing the Antecedent and the Consequent of expression
  FuzzyRule* fuzzyRule47 = new FuzzyRule(47, ifNS_erreur_angleAndPB_speed_angle_IN, thenPS_speed_angle_OUT);
  FuzzyRule* fuzzyRule48 = new FuzzyRule(48, ifZ_erreur_angleAndPB_speed_angle_IN, thenPS_speed_angle_OUT);
  FuzzyRule* fuzzyRule49 = new FuzzyRule(49, ifPS_erreur_angleAndPB_speed_angle_IN, thenPB_speed_angle_OUT);
  FuzzyRule* fuzzyRule50 = new FuzzyRule(50, ifPB_erreur_angleAndPB_speed_angle_IN, thenPB_speed_angle_OUT);

  fuzzy->addFuzzyRule(fuzzyRule01); // Adding FuzzyRule to Fuzzy object
  fuzzy->addFuzzyRule(fuzzyRule02);
  fuzzy->addFuzzyRule(fuzzyRule03);
  fuzzy->addFuzzyRule(fuzzyRule04);
  fuzzy->addFuzzyRule(fuzzyRule05);
  fuzzy->addFuzzyRule(fuzzyRule06);
  fuzzy->addFuzzyRule(fuzzyRule07);
  fuzzy->addFuzzyRule(fuzzyRule08);
  fuzzy->addFuzzyRule(fuzzyRule09);
  fuzzy->addFuzzyRule(fuzzyRule10);
  fuzzy->addFuzzyRule(fuzzyRule11);
  fuzzy->addFuzzyRule(fuzzyRule12);
  fuzzy->addFuzzyRule(fuzzyRule13);
  fuzzy->addFuzzyRule(fuzzyRule14);
  fuzzy->addFuzzyRule(fuzzyRule15);
  fuzzy->addFuzzyRule(fuzzyRule16);
  fuzzy->addFuzzyRule(fuzzyRule17);
  fuzzy->addFuzzyRule(fuzzyRule18);
  fuzzy->addFuzzyRule(fuzzyRule19);
  fuzzy->addFuzzyRule(fuzzyRule20);
  fuzzy->addFuzzyRule(fuzzyRule21);
  fuzzy->addFuzzyRule(fuzzyRule22);
  fuzzy->addFuzzyRule(fuzzyRule23);
  fuzzy->addFuzzyRule(fuzzyRule24);
  fuzzy->addFuzzyRule(fuzzyRule25);
  fuzzy->addFuzzyRule(fuzzyRule26);
  fuzzy->addFuzzyRule(fuzzyRule27);
  fuzzy->addFuzzyRule(fuzzyRule28);
  fuzzy->addFuzzyRule(fuzzyRule29);
  fuzzy->addFuzzyRule(fuzzyRule30);
  fuzzy->addFuzzyRule(fuzzyRule31);
  fuzzy->addFuzzyRule(fuzzyRule32);
  fuzzy->addFuzzyRule(fuzzyRule33);
  fuzzy->addFuzzyRule(fuzzyRule34);
  fuzzy->addFuzzyRule(fuzzyRule35);
  fuzzy->addFuzzyRule(fuzzyRule36);
  fuzzy->addFuzzyRule(fuzzyRule37);
  fuzzy->addFuzzyRule(fuzzyRule38);
  fuzzy->addFuzzyRule(fuzzyRule39);
  fuzzy->addFuzzyRule(fuzzyRule40);
  fuzzy->addFuzzyRule(fuzzyRule41);
  fuzzy->addFuzzyRule(fuzzyRule42);
  fuzzy->addFuzzyRule(fuzzyRule43);
  fuzzy->addFuzzyRule(fuzzyRule44);
  fuzzy->addFuzzyRule(fuzzyRule45);
  fuzzy->addFuzzyRule(fuzzyRule46);
  fuzzy->addFuzzyRule(fuzzyRule47);
  fuzzy->addFuzzyRule(fuzzyRule48);
  fuzzy->addFuzzyRule(fuzzyRule49);
  fuzzy->addFuzzyRule(fuzzyRule50);
}
