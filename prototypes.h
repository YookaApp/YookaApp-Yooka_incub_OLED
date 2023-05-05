#ifndef proto
#define proto
 
//Structure pour permettant de bien gerer le temps creation d'une variable personalisee
struct dateTime_t{

   byte sec;
   byte mins;
   byte hours;
   byte dow;   //dayOfWeek(1-7)
   byte dom;  //dayOfMonth(1-30/31)
   byte month;
   byte year;
   byte incremente_hours;
   
}DateTime;

//QUELQUES VARIABLES GLOBALES DU PROGRAMME 
//variable pour la temperature et l'humidity
float tempe;
float humidy;

//FONCTIONS POUR LA LECTURE DU CAPTEUR DHT22

 //FONCTIONS POUR LE CONTROL DE tempe,humid,leds, etc...
void control_temperature();
void control_humidity();
void control_leds();
void control_buzzer();

void affichage();
void appel_fonction();
void initial_retournement();
void retournement();
void manuel();
void result_bt(char, bool);

    //Fonctions pour le module RTC et le retournement
void Clock(bool);//controle de l'horloge du module 

// fonction pour le decodage du jour de la semaine et celui du moi 
String decode_dow(byte);
String decode_month(byte);

//fonction de mise ajour du temp
void update_time(byte, byte, byte, byte, byte, byte, byte);
void download_time(dateTime_t *);

//convertisseur des donnees
byte decimal_hexa(byte);
byte hexa_decimal(byte);

// fonction pour le decodage du jour de la semaine et celui du moi 
String decode_dow(byte);
String decode_month(byte);

#endif //prototype
