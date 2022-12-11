
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
  oled.setCursor(0,25);
  oled.println(tempe, 1);
  oled.setCursor(50,30);
  oled.setTextSize(1);
  oled.print(char(247));
  oled.print("C");
  
  oled.setTextSize(2);
  oled.setCursor(90,30);
  oled.print("Nan");


  oled.setTextSize(2);
  oled.setCursor(30,50);
  oled.print("Nan");
  oled.display();
 /*
//affichage du temps et de la date   
  
  lcd_tempe.setCursor(5, 2);
  if (dateTime.hours < 10)
  lcd_tempe.print("0");
  
  lcd_tempe.print(dateTime.hours);
  lcd_tempe.print(":");
 
  if (dateTime.mins < 10){
  lcd_tempe.print("0");
  }
  lcd_tempe.print(dateTime.mins);  
  lcd_tempe.print("'");
  lcd_tempe.print(":");

  if (dateTime.sec < 10){
  lcd_tempe.print("0");
  }
  lcd_tempe.print(dateTime.sec);
  lcd_tempe.print('"');
    
  lcd_tempe.setCursor(2, 3);
  lcd_tempe.print(decode_dow(dateTime.dow));
  lcd_tempe.print(" ");
  if (dateTime.dom < 10)
  lcd_tempe.print("0");
  
  lcd_tempe.print(dateTime.dom);
  lcd_tempe.print(" ");
  lcd_tempe.print(decode_month(dateTime.month));
  lcd_tempe.print(" ");
  lcd_tempe.print(dateTime.year + 2000);
*/}

#endif //Oled
