#include <avr/wdt.h>  // add a watch_dog librairie 
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//pour l'ecran
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C //See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 oled(128, 64, &Wire, OLED_RESET);


//Inclusion des bibliotheques personnelles
#include "rtc.h"
#include "ds18.h"
#include "moteur.h"

// leds pour le control de la temperature
#define RED_LED_T 1
#define GREEN_LED_T 10

//AUTRES
#define BUZZER 13
#define RELAIS_RES 8

// variables gerant le clignotement des led et le son du buzzer
unsigned long temp_lcd, temp_red_led, temp_buzzer;

bool state_red_led =0;
bool state_buzzer =0;

void beginer(){
  
  valider = false;
  Serial.begin(9600);
  Wire.begin(); //initialisation de la voie i2c
  oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  pinMode(RED_LED_T , OUTPUT);
  pinMode(GREEN_LED_T, OUTPUT);
    
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAIS_RES , OUTPUT);
  //pinMode(RELAIS_BRIS, OUTPUT);

  //pins du moteur
  pinMode(PIN_MOTEUR_a, OUTPUT);
  pinMode(PIN_MOTEUR_d, OUTPUT);

  //initialisation des entres de fin de course
  pinMode(PIN_FIN_de_COURSE_G, INPUT);
  pinMode(PIN_FIN_de_COURSE_D, INPUT);
  pinMode(PIN_RETOURNEMENT, INPUT);

  digitalWrite(PIN_MOTEUR_a, LOW);
  digitalWrite(PIN_MOTEUR_d, LOW);

}

void setup() {

    wdt_enable(WDTO_4S); //initialisation du chien de garde a 8 secondes
    beginer();
    temp_lcd = millis();
    temp_red_led = millis();
    temp_buzzer = millis();
    
  //(sec, mins, heur, dow, dom, moi, an) mise a jours de l'heure et de la date
  //update_time(0, 53, 16, 5, 5, 5, 23);
  HourNow = DateTime.mins;
  initial_retournement();
  wdt_reset(); // remise a zero du compteur de watch dog avant la boucle principale: loop()
 } 

void loop() {
  
  appel_fonction();
  if(( millis() - temp_lcd) >= 1000){
   temp_lcd = millis();
     
     // telechargement des donnees apres chaque seconde
      download_time(&DateTime); // mise a jour de l'heure      
      getTemperature(&tempe);  //mise a jour de la temperature 
      humidy = (tempe * 4)/3;
      Serial.println(DateTime.incremente_hours);           
      affichage();

  }
  wdt_reset(); // a la fin de chaque boucle on initialise le compteur */
}

void appel_fonction(){
  
  control_leds();
   //ON GERE LE RETOURNEMENT GRACE AU TEMPS
  retournement();

   //ON GERE LA TEMPERATURE ET L'HUMIDITE
  control_temperature();

    //CONTROL BUZZER
  control_buzzer();
}


void control_temperature(){

  if(tempe <= 37.5){
   digitalWrite(RELAIS_RES, HIGH);
  }

  else if(tempe > 37.76){
   digitalWrite(RELAIS_RES, LOW);
    }
}


void control_leds(){

  //initialisation des leds

  if((tempe > 36) && (tempe < 37.9)){
    digitalWrite(GREEN_LED_T, HIGH);
    digitalWrite(RED_LED_T, LOW);
  }

 else if(tempe <= 35 || tempe > 38.9) {
       if(( millis() - temp_red_led) >= 500){
        temp_red_led= millis();
        state_red_led= !state_red_led;
        digitalWrite(RED_LED_T, state_red_led);
    }
    digitalWrite(GREEN_LED_T, LOW);
  }
}


void control_buzzer(){
 
  if(tempe > 38.4 || tempe < 25 || valider){  
       if(( millis() - temp_buzzer) >= 500){
        temp_buzzer= millis();
        state_buzzer= !state_buzzer;
      }
     digitalWrite(BUZZER, state_buzzer);
    }
    
  else 
    digitalWrite(BUZZER, LOW);
}
