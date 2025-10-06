#include <Wire.h>
 
 
#include <Arduino.h>

#include <Adafruit_VL6180X.h>
 
#include <ESP32Servo.h>
#include <FastLED.h>
 
#include <cstring>

bool obstacle;
int i;
 
/*// Configuration des LED
#define LED_PIN     5       // Broche numérique où la LED est connectée
#define NUM_LEDS    1       // Nombre de LEDs sur la bande
#define LED_TYPE    WS2812  // Type de LED (peut être WS2812, SK6812, etc.)
#define COLOR_ORDER GRB     // Ordre des couleurs (RGB ou GRB)
CRGB leds[NUM_LEDS];        // Tableau contenant les LEDs
 */

 // Params led
#define ledPin 5
#define ledBrightness 50
#define interrupteur 6
CRGB led; // Init objet LED
CRGB leds[1];
 
// Pins TOF

#define SRCLK_PIN 10  // Broche horloge du SR
#define SDA 20
#define SCL 21

// --- Objets capteurs ---
Adafruit_VL6180X tof[3] = {Adafruit_VL6180X(), Adafruit_VL6180X(), Adafruit_VL6180X()};
const uint8_t tofAdr[3] = {0x30, 0x31, 0x32};
const char* tofName[3] = {"gauche", "milieu", "droit"};

#define tirette 9 //tirette de lancement

//Définition de la couleur de la led
char var_equipe[6]= "a";
 
const uint8_t DETECTION_THRESHOLD = 100;  // Distance seuil (mm)
 


// ----- SERVOMOTEURS -----
 
Servo myServo1;                     // Servo de positionnement 1
 
const int servoPin = 7;          // Broche PWM servo 1
 
// ----- MOTEURS ET ENCODEUR -----
 
#define motor1    0           // Sortie PWM moteur droit
 
#define motor2    1           // Sortie PWM moteur gauche
 
#define encoder_1 3          // Entrée signal encodeur moteur droit ?
 
#define encoder_2 4          // Entrée signal encodeur moteur gauche ?
 
volatile long pulseCount_M1 = 0;      // Compteur impulsions d'encodeur moteur droit M1
volatile long pulseCount_M2 = 0;      // Compteur impulsions d'encodeur moteur gauche M2
bool Start = false; // Variable pour le démarrage du robot
int posServo = 0;                          // position actuelle (0–180)
bool ascending = true;                     // sens du balayage
bool chronoStarted=false;


// ----- MACHINE D'ÉTATS -----
 
enum RobotState {
 
  INITIALISATION,                // Attente avant démarrage
 
  ETAT_1,                        // Avance initiale
 
  ETAT_2,                        // Pivot
 
  ETAT_3,                        // Avance finale
 
  ETAT_SERVOS,                   // Balayage servos
 
  ARRET                          // Arrêt complet
 
};
 
RobotState currentState = INITIALISATION;  // État de départ
 
// ----- DISTANCES EN TICKS -----
 
long x1 = 8000;                   // Distance pour ETAT_1
 
long x2 = 750;                    // Angle/tour pour ETAT_2
 
long x3 = 650;                   // Distance pour ETAT_3
 
 

 
// ----- TEMPS DÉMARRAGE ET ARRÊT -----
 unsigned long previousMillis_1 = 0;  // Mémorisation du temps
unsigned long previousMillis_2 = 0;  // Mémorisation du tempsconst long interval_dep   = 5000; // Délai avant ETAT_1 (ms)
unsigned long previousMillis_3 = 0;  // Mémorisation du temps 
const long interval_final = 100000; // Durée totale avant ARRET (ms)
unsigned long interval_rm = 100; // Durée totale avant ARRET (ms)
const long interval_dep = 85000; // 85 secondes
unsigned long previousMillisLed = 0;

const long intervalLed = 100;

unsigned long previousMillisServo = 0;  // Pour mémoriser le dernier temps de mouvement du servo
const long intervalServo = 50;          // Interv

 
// ----- PROTOTYPES DE FONCTIONS -----
 
void countPulse_M1();
 
void countPulse_M2();
 
void f_avancer(long ticks);
 
void f_tourner(long ticks);

void f_tourner_bleu(long ticks);
 
void f_arret();
 
void f_servomoteur();

void f_avancer_jaune(long ticks);

void f_avancer_bleu(long ticks);
 
void testAllSensors();

void equipe();

void demarre(); 
 
void setup() {
  
  Serial.begin(115200);

  //initialisation capteurs

Serial.println("Démarrage de trois VL6180X");

// Initialisation du SR
  pinMode(SRCLK_PIN, OUTPUT);
  digitalWrite(SRCLK_PIN, HIGH);
  digitalWrite(SRCLK_PIN, LOW);
 
  // Initialisation I2C
  Wire.begin(SDA, SCL);
for (int i = 0; i < 3; i++) {
    // Activer le capteur suivant
    digitalWrite(SRCLK_PIN, HIGH);
    digitalWrite(SRCLK_PIN, LOW);
    
    if (!tof[i].begin()) {
      Serial.print("Erreur init capteur ");
      Serial.println(tofName[i]);
      while(1);
    }
    tof[i].setAddress(tofAdr[i]);
    
    Serial.print("Capteur ");
    Serial.print(tofName[i]);
    Serial.print(" prêt à l'adresse 0x");
    Serial.println(tofAdr[i], HEX);
  }
Serial.println("Tous les capteurs sont initialisés");
 
  // --- Initialisation servos ---
 
  myServo1.attach(servoPin);     // Attache servo 1
 
 
  // --- Moteurs et encodeur ---
 
  pinMode(motor1, OUTPUT);
 
  pinMode(motor2, OUTPUT);
 
  pinMode(encoder_1, INPUT_PULLUP);
 
  pinMode(encoder_2, INPUT_PULLUP);

  pinMode(tirette, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(encoder_1), countPulse_M1, CHANGE);
 
  attachInterrupt(digitalPinToInterrupt(encoder_2), countPulse_M2, CHANGE);

  
 
 
    //Initialisation led

   FastLED.addLeds<WS2812B, ledPin, GRB>(leds, 1);
  FastLED.setBrightness(ledBrightness);
}
 
void loop() {
  //unsigned long currentMillis = millis();  // Temps actuel
  //if (currentMillis - previousMillis_1 >= interval_rm) {
  demarre();
  if (Start && !chronoStarted) {
    chronoStarted = true;
    unsigned long now = millis();
    previousMillis_1   = now;
    previousMillis_2   = now;
    previousMillis_3   = now;
    previousMillisLed  = now;
    previousMillisServo= now;
    // si besoin, réinitialise aussi pulseCount_M1/M2, posServo, etc.
  }
  //Start=true;
  if(Start) {
      equipe();
      unsigned long currentMillis = millis();  // Temps actuel
      
      
// --- Vérification du temps écoulé ---
      if (currentMillis - previousMillis_1 >= interval_rm) {   // Ouverture de la condition if
        previousMillis_1 = currentMillis;  // Réinitialise le dernier temps
    
    //Mesure capteurs
        testAllSensors();
    
 
  // --- Passage à ETAT_1 ---
 
                 if (currentMillis - previousMillis_2 >= interval_dep && currentState == INITIALISATION) { //si 85 secondes écoulées
 
                      previousMillis_2 = currentMillis;     // Réinitialise
 
                      currentState = ETAT_1;             // Activation
 
                      }
 
  // --- Arrêt final ---
 
                  if (currentMillis - previousMillis_3 >= interval_final) { //si 100 secondes écoulées
 
                          currentState = ETAT_SERVOS;
 
                       }
 
  // --- Machine d'états ---
 
                  switch (currentState) {
 
                  case INITIALISATION :
 
      // Affichage d'un message d'initialisation
                  Serial.println("Initialisation du robot...");
 
    // Exemple : Réinitialiser les compteurs d'impulsions des moteurs
                  pulseCount_M1 = 0;
                  pulseCount_M2 = 0;
 
                  f_arret();
 
                  break;
                    
                  case ETAT_1:
 
       // Avance initiale tant que pas d'obstacle
 
                  if (obstacle) { f_arret(); break; }
 
                   f_avancer(x1);
 
      // Si distance atteinte → ETAT_2
 
                  if (pulseCount_M1 >= x1 && pulseCount_M2 >= x1) {
 
                       currentState = ETAT_2;
 
                      pulseCount_M1 = 0;                 // Reset compteur
                      pulseCount_M2 = 0;
                    }
 
                    break;
 
                 case ETAT_2:
 
      // tourner
 
                if (obstacle) { f_arret(); break; }
 		          
			          //f_tourner_bleu(x2);

                f_tourner(x2);
                if (strcmp(var_equipe, "Bleu") == 0) {
 
                    if ( pulseCount_M1 >= x2) {
 
                    currentState = ETAT_3;
 
                    pulseCount_M1 = 0;
                    pulseCount_M2 = 0;
                    }}else{
                    if ( pulseCount_M2 >= x2) {
 
                    currentState = ETAT_3;
 
                    pulseCount_M1 = 0;
                    pulseCount_M2 = 0;

                        }
                }
 
                break;
 
                case ETAT_3:
 
      // Avance finale
 
                if (obstacle) { f_arret(); break; }
 
                f_avancer(x3);
 
                if (pulseCount_M1 >= x3 && pulseCount_M2 >= x3) {
 
 
                currentState = ARRET;
 
                pulseCount_M1 = 0;
                pulseCount_M2 = 0;
 
                }
 
              break;
 
              case ETAT_SERVOS:
 
      // Balayage servomoteurs
 
              f_arret();                     // Stop moteurs d'abord
 
              f_servomoteur();               // Exécute balayage
 
              currentState = ETAT_SERVOS;
 
              break;
 
              case ARRET:
 
              default:
 
      // Freinage complet
 
              f_arret();
      //f_servomoteur(); 
              break;
 
  }
}
  
  }

}

 
// ----- FONCTIONS MOUVEMENT -----
 
// Avance en ligne droite sur 'ticks' impulsions
 
void f_avancer(long ticks) {
 if (strcmp(var_equipe, "Bleu") == 0) {
  f_avancer_bleu(x1);
 
} else{
  f_avancer_jaune(x1);
}
}

void f_avancer_jaune(long ticks) {
 
    analogWrite(motor1,197);
 
  analogWrite(motor2, 190);
  
}
 
void f_avancer_bleu(long ticks) {
 
  analogWrite(motor1,195);
 
  analogWrite(motor2, 190);
 
}
 


// tourner
void f_tourner(long ticks) {
  
  // Si équipe bleu, moteur droit activé,  moteur gauche éteint
  // Sinon,  moteur gauche activé, moteur droit éteint
  if (strcmp(var_equipe, "Bleu") == 0) {
    //analogWrite(motor1, 0);
    //analogWrite(motor2, 255);
    f_tourner_bleu(x2);
  } else {
    analogWrite(motor1, 230);
    analogWrite(motor2, 150);
  }
}
// Arrêt des deux moteurs
 
void f_arret() {
 
  analogWrite(motor1, 255);
 
  analogWrite(motor2, 255);
 
}
 
// Balayage 0→180° sur servos
 
void f_servomoteur() {
  //unsigned long currentMillis = millis();

  // si l’intervalle est écoulé, on fait un pas
  //if (currentMillis - previousMillisServo >= intervalServo) {
    //previousMillisServo = currentMillis;

    // mise à jour de la position selon le sens
    if (ascending) {
      posServo+=10;
      if (posServo >= 180) {
        posServo = 180;
        ascending = false;  // on inverse au sommet
      }
    } else {
      posServo-=10;
      if (posServo <= 0) {
        posServo = 0;
        ascending = true;   // on inverse au bas
      }
    }

    myServo1.write(posServo);  // déplace le servo
    // FastLED.show();         // décommenter si vous voulez mettre à jour une LED
  //}
}

 

 
// Incrémentation impulsions encodeur moteur M1
 
void countPulse_M1() {
 
  pulseCount_M1++;
 
}
 
// Incrémentation impulsions encodeur moteur M2
 
void countPulse_M2() {
 
  pulseCount_M2++;
 
}
 
 /*// Fonction led_équipe
 
 void f_led(){
  unsigned long currentMillis = millis();  // Temps actuel
  
  if (currentMillis - previousMillisLed >= intervalLed) {
    previousMillisLed = currentMillis;  // Réinitialise le dernier temps
    
    if (strcmp(var_equipe, "Bleu") == 0) {
      // Allumer la LED en bleu
      leds[0] = CRGB::Blue;  // Définit la couleur de la LED en bleu
    } else {
      // Allumer la LED en jaune
      leds[0] = CRGB::Yellow;  // Définit la couleur de la LED en jaune
    }
    FastLED.show();  // Met à jour la LED
  }
}*/

 
 void testAllSensors() {
  uint8_t range, status;
  obstacle = false;  // on part du principe qu’il n’y a pas d’obstacle
 
  for (int i = 0; i < 3; i++) {
    // on commute physiquement sur le capteur i
    digitalWrite(SRCLK_PIN, HIGH);
    digitalWrite(SRCLK_PIN, LOW);
 
    // on lit une seule fois la distance et le statut
    range  = tof[i].readRange();
    status = tof[i].readRangeStatus();
 
    // si OK ET distance sous le seuil, on prend obstacle = true et on sort
    if (status == VL6180X_ERROR_NONE && range <= DETECTION_THRESHOLD) {
      obstacle = true;
      break;
    }
  }
}

 void demarre() {
  if (digitalRead(tirette) == LOW) {
  Start = true;
  
  }
  else{
Start = false;
   f_arret();
    
  }
  }
void f_tourner_bleu(long ticks){
if (strcmp(var_equipe, "Bleu") == 0) {
    analogWrite(motor1, 150);
    analogWrite(motor2, 230);
  } 

}

 void equipe() {
  if (digitalRead(interrupteur) == HIGH) {
    strcpy(var_equipe, "Jaune");
   led = CRGB::Yellow;
    
    
  } else {
    strcpy(var_equipe, "Bleu");
   led = CRGB::Blue;
  }
  leds[0] = led;
  FastLED.show();
}

 