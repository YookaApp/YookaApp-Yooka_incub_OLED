
// FICHIER POUR AFFICHAGE DES DONNEES.
#ifndef Oled
#define Oled
#include "prototypes.h"

void affichage(){

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(40,0);
  oled.println("Incubator");
  
  oled.setTextSize(2);
  oled.setCursor(0,15);
  oled.print(tempe, 1);
  oled.setCursor(50,20);
  oled.setTextSize(1);
  oled.print(char(247));
  oled.print("C");
  
  oled.setTextSize(2);
  oled.setCursor(70,15);
  oled.print(humidy,1);
  oled.setCursor(120,20);
  oled.setTextSize(1);
  oled.print("%");


  oled.setTextSize(1);
  oled.setCursor(30,40);
  if (DateTime.hours < 10)
  oled.print("0");
  
  oled.print(DateTime.hours);
  oled.print(":");
 
  if (DateTime.mins < 10){
  oled.print("0");
  }
  oled.print(DateTime.mins);  
  oled.print("'");
  oled.print(":");

  if (DateTime.sec < 10){
  oled.print("0");
  }
  oled.print(DateTime.sec);
  oled.print('"');

  oled.setTextSize(1);
  oled.setCursor(20,50);
  oled.print(decode_dow(DateTime.dow));
  oled.print(" ");
  if (DateTime.dom < 10)
  oled.print("0");
  
  oled.print(DateTime.dom);
  oled.print(" ");
  oled.print(decode_month(DateTime.month));
  oled.print(" ");
  oled.print(DateTime.year + 2000);  oled.display();
}

#endif //Oled
