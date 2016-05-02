#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>
//Communication, ASSERG
int cnt = 0; // nombre de données découpées
String data[10]; // stockage des données découpées
String inputString = "";   // chaine de caractères pour contenir les données
boolean stringComplete = false;  // pour savoir si la chaine est complète
boolean Notif_arrive=false;
//

int32_t D = 0;//compteur canal 1
int32_t G = 0;//compteur canal 2
int32_t temp_D = 0;
int32_t temp_G = 0;

int32_t Dmm = D_INITIALE;
int32_t Gmm = G_INITIALE;

int angle = ANGLE_INITIAL; //10ieme de degres
int X = X_INITIALE;
int Y = Y_INITIALE;

//pour la version 2.0
///////////////////////////////////////
/*
        X    
        ^
        |
        |
        |
Y<--------------   
*/ 
  boolean MARCHE_ARRIERE = false; //inverse le vecteur direction en appliquant une rotation de PI
  int X_COMMANDE = 0;//Coordonnée verticale en mm
  int Y_COMMANDE = 0;//Coordonnée horizontale en mm
  float ANGLE_COMMANDE = 0;//en degre
  
#if GROSROBOT  
  int SPEED_OUT_MAX = 220; //vitesse max de sortie (entre 0 et 255) testée jusqu'a 220
  int ANGLE_OUT_MAX = (int)(SPEED_OUT_MAX/3);//stable quand la vitesse de l'angle est à cette fraction de vitesse en ligne droite
#else 
  int SPEED_OUT_MAX = 255; //vitesse max de sortie (entre 0 et 255)
  int ANGLE_OUT_MAX = 120;//stable quand la vitesse de l'angle est à cette fraction de vitesse en ligne droite
#endif
  
  boolean is_close_to_goal = false;
  int last_X = X_INITIALE;
  int last_Y = Y_INITIALE;
  float angle_radian = ANGLE_INITIAL;//radian!!
  float angle_degre = ANGLE_INITIAL;//radian!!
  float temp_angle = 0;
  int32_t erreur_moyenne_fuzzy = 0;
  float erreur_angle_fuzzy = 0;
  int vitesse_moyenne_fuzzy=0;
  int vitesse_angle_fuzzy = 0;
//////////////////////////////////////////:

long top_millis =   0;
long temp_millis =  0;

int vitesse_D =     0;
int vitesse_G =     0;
int vitesse_moyenne=0;
int vitesse_angle = 0;

int erreur_D =0;
int erreur_G =0;
int erreur_moyenne =0;
float erreur_angle =  0;

char octet = ' ';
char octet_tmp = ' ';

//Init Fuzzy control
Fuzzy* fuzzy = new Fuzzy();
 
FuzzySet* NB_erreur = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_ERREUR);
FuzzySet* NS_erreur = new FuzzySet(-10000, -SENSIBILITE_ERREUR, -SENSIBILITE_ERREUR, 0);
FuzzySet* Z_erreur  = new FuzzySet(-SENSIBILITE_ERREUR, 0, 0, SENSIBILITE_ERREUR);
FuzzySet* PS_erreur = new FuzzySet(0, SENSIBILITE_ERREUR, SENSIBILITE_ERREUR, 10000);
FuzzySet* PB_erreur = new FuzzySet(SENSIBILITE_ERREUR, 10000, 15000, 15000);

FuzzySet* NB_speed_IN = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_VITESSE_IN);
FuzzySet* NS_speed_IN = new FuzzySet(-10000, -SENSIBILITE_VITESSE_IN, -SENSIBILITE_VITESSE_IN, 0);
FuzzySet* Z_speed_IN  = new FuzzySet(-SENSIBILITE_VITESSE_IN, 0, 0, SENSIBILITE_VITESSE_IN);
FuzzySet* PS_speed_IN = new FuzzySet(0, SENSIBILITE_VITESSE_IN, SENSIBILITE_VITESSE_IN, 10000);
FuzzySet* PB_speed_IN = new FuzzySet(SENSIBILITE_VITESSE_IN, 10000, 15000, 15000);

FuzzySet* NB_erreur_angle = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_ERREUR);
FuzzySet* NS_erreur_angle = new FuzzySet(-10000, -SENSIBILITE_ERREUR, -SENSIBILITE_ERREUR, 0);
FuzzySet* Z_erreur_angle  = new FuzzySet(-SENSIBILITE_ERREUR, 0, 0, SENSIBILITE_ERREUR);
FuzzySet* PS_erreur_angle = new FuzzySet(0, SENSIBILITE_ERREUR, SENSIBILITE_ERREUR, 10000);
FuzzySet* PB_erreur_angle = new FuzzySet(SENSIBILITE_ERREUR, 10000, 15000, 15000);

FuzzySet* NB_speed_angle_IN = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_VITESSE_IN);
FuzzySet* NS_speed_angle_IN = new FuzzySet(-10000, -SENSIBILITE_VITESSE_IN, -SENSIBILITE_VITESSE_IN, 0);
FuzzySet* Z_speed_angle_IN  = new FuzzySet(-SENSIBILITE_VITESSE_IN, 0, 0, SENSIBILITE_VITESSE_IN);
FuzzySet* PS_speed_angle_IN = new FuzzySet(0, SENSIBILITE_VITESSE_IN, SENSIBILITE_VITESSE_IN, 10000);
FuzzySet* PB_speed_angle_IN = new FuzzySet(SENSIBILITE_VITESSE_IN, 10000, 15000, 15000);

FuzzySet* NB_speed_OUT = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_VITESSE_OUT);
FuzzySet* NS_speed_OUT = new FuzzySet(-10000, -SENSIBILITE_VITESSE_OUT, -SENSIBILITE_VITESSE_OUT, 0);
FuzzySet* Z_speed_OUT  = new FuzzySet(-SENSIBILITE_VITESSE_OUT, 0, 0, SENSIBILITE_VITESSE_OUT);
FuzzySet* PS_speed_OUT = new FuzzySet(0, SENSIBILITE_VITESSE_OUT, SENSIBILITE_VITESSE_OUT, 10000);
FuzzySet* PB_speed_OUT = new FuzzySet(SENSIBILITE_VITESSE_OUT, 10000, 15000, 15000);

FuzzySet* NB_speed_angle_OUT = new FuzzySet(-15000, -15000, -10000, -SENSIBILITE_VITESSE_OUT);
FuzzySet* NS_speed_angle_OUT = new FuzzySet(-10000, -SENSIBILITE_VITESSE_OUT, -SENSIBILITE_VITESSE_OUT, 0);
FuzzySet* Z_speed_angle_OUT  = new FuzzySet(-SENSIBILITE_VITESSE_OUT, 0, 0, SENSIBILITE_VITESSE_OUT);
FuzzySet* PS_speed_angle_OUT = new FuzzySet(0, SENSIBILITE_VITESSE_OUT, SENSIBILITE_VITESSE_OUT, 10000);
FuzzySet* PB_speed_angle_OUT = new FuzzySet(SENSIBILITE_VITESSE_OUT, 10000, 15000, 15000);



