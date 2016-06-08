/* Code de la carte d'évitement petit robot 2016 pour la coupe d'europe. */

/* ATTENTION DANS CE CODE L AVANT ET L ARRIERE SONT INVERSE*/
#define BAUDRATE_CAPTEUR 115200
int seuilAv = 70;
int seuilAr = 200;
#define PIN_AVANT_GAUCHE A2
#define PIN_AVANT_DROIT A3
#define PIN_ARRIERE_GAUCHE A1
#define PIN_ARRIERE_MILLIEU A0
#define PIN_ARRIERE_DROIT A4

int AvD = 0;
int ArC = 0;
int AvG = 0;
int ArD = 0;
int ArG = 0;

void setup() {
  
  Serial.begin(BAUDRATE_CAPTEUR);
}


void loop() {
  for (int moy = 0; moy < 7; moy++)
  {
  int AvantDroit = analogRead(PIN_AVANT_DROIT);
  int AvantGauche = analogRead(PIN_AVANT_GAUCHE);
  int ArriereDroit = analogRead(PIN_ARRIERE_DROIT);
  int ArriereCentre = analogRead(PIN_ARRIERE_MILLIEU);
  int ArriereGauche = analogRead(PIN_ARRIERE_GAUCHE);
  AvD = AvD + AvantDroit;
  AvG = AvG + AvantGauche;
  ArC = ArC + ArriereCentre;
  ArD = ArD + ArriereDroit;
  ArG = ArG + ArriereGauche;
  delay(2);
  }
  AvD = AvD/7;
  AvG = AvG/7;
  ArC = ArC/7;
  ArD = ArD/7;
  ArG = ArG/7;
  
  if (AvD < seuilAv || AvG < seuilAv)
  {

    Serial.print('Z');
    Serial.print("\n");
   
  }
  if (ArD > seuilAr || ArG > seuilAr || ArC > seuilAr)
  {
    Serial.print('S');
    
    Serial.print("\n");
  }
  AvD = 0;
  ArC = 0;  
  AvG = 0;
  ArD = 0;
  ArG = 0;  
  delay(10);
}
