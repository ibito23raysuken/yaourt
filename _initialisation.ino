/*************************************************
 initialisation des composante
 ******************************************************/
#include <Keypad.h>
#include <DS3231.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <avr/wdt.h>
//#include "Adafruit_Sensor.h"
#define DHTPIN 11
#define DHTTYPE DHT22   // DHT 11
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT dht(DHTPIN, DHTTYPE);
/*
RTClib RTC ;
DS3231 rtc ;
*/
DS3231 clock;
RTCDateTime dt;
//definition des variables globales
char key1 ;
char data ;
//definition des colonnes et lignes du clavier matricielle
const uint8_t lignes = 4 ;
const uint8_t colonnes = 4 ;

//pin ampoule 
const int chauffage = 10 ;

//variable globale 
int annee = 0 ;
int mois = 0 ;
int jour = 0 ;
int temperature = 0 ;
int heure = 0 ;
int minute = 0 ;
int seconde = 0 ;
int heure_consigne=0,Temp_consigne=0; 
String k2 ;
int processus = 0 ;
// mapping du clavier
char boutton[lignes][colonnes] = {
                                {'1','2','3','A'},
                                {'4','5','6','B'},
                                {'7','8','9','C'},
                                {'*','0','#','D'}
                              };
                              
//definition des pins du clavier
byte lignePins[lignes] = {9, 8, 7, 6}; 
byte colPins[colonnes] = {5, 4, 3, 2};  
      
//instanciation de la classe keypad
Keypad keypad = Keypad( makeKeymap(boutton), lignePins, colPins, lignes, colonnes );

byte  compteur100ms = 10;

const int NBTACHE = 3;             // Nb de tâches à réserver

//****************************************************************************************************

//****************************************************************************************************

/******** déclaration des tâches ********/

void lireClavier() ;

/******** N° des tâches **************/

void initTimer2() 
{
  noInterrupts(); // désactiver toutes les interruptions
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  TCCR2A |= (1 << WGM21);   // CTC mode
  TCCR2B |= (1 << CS22);  // 64 prescaler
  //TCCR2B |= (1 << CS21);    // 8 prescaler

  OCR2A = 250; // 16MHz/64/1000Hz => Base de Temps = 1 ms
  //OCR2A = 25; // 16MHz/64/10000Hz => Base de Temps = 100 µs

  TIMSK2 |= (1 << OCIE2A); // Activer l'IT du mode comparaison
  
  interrupts(); // valiser les interruptions
}

