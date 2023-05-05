#ifndef moteur
#define moteur

#define PIN_MOTEUR_a 2
#define PIN_MOTEUR_d 4

#define PIN_FIN_de_COURSE_G 6  // fin de course au fond de l'incubateur
#define PIN_FIN_de_COURSE_D 5  //fin de course pres de la porte
#define PIN_RETOURNEMENT 7
// deadline
#define DEADLINE 4
int HourNow = 0; // variable content a Hour now

//ce fichier contient les fonction permettant le retournement des oeufs grace au moteur
boolean valider = false, etat_bts = true;
bool memorie_btG = false, memorie_btD = false, flag_manuelRetour = false; // detections d'apuis sur le boutons

void initial_retournement(){
  bool datag = digitalRead(PIN_FIN_de_COURSE_G);
  bool datad = digitalRead(PIN_FIN_de_COURSE_D);

  if (datag){
    etat_bts = 1; //dans l'autre cas on change de sens
  }

  if(datad) {
    etat_bts = 0; //dans l'autre cas on change de sens
  }
}


void control_hour() {
  int deadlineNow = DateTime.incremente_hours;
   
   if(HourNow != DateTime.hours){
      HourNow = DateTime.hours;
      deadlineNow = deadlineNow + 1;

        if(deadlineNow >= DEADLINE){
                 deadlineNow = 0;
                 valider = true;
                 }    
      update_deadline_Hours(deadlineNow); // save incremente hour
      Serial.print("Incremente OK ");
   }
}

void control_Fin_de_course() {
  bool data1 = digitalRead(PIN_FIN_de_COURSE_G);
  bool data2 = digitalRead(PIN_FIN_de_COURSE_D);

  if ( (data1 != memorie_btG) && (data1 == true) ) {
    valider = false ;  //arret moteurs
    etat_bts = 1; //dans l'autre cas on change de sens
  }

  if ((data2 != memorie_btD) && (data2 == true)) {
    valider = false ;  //arret moteurs
    etat_bts = 0; //dans l'autre cas on change de sens
  }
  
  memorie_btG = data1;
  memorie_btD = data2; // Enregistrement d'etats
}


void manuel(){
  bool data3 = digitalRead(PIN_RETOURNEMENT);
  
  if(data3){
    valider = true;
    flag_manuelRetour = true;
  }

  if(!data3 && flag_manuelRetour){
    valider = false;
    flag_manuelRetour = false;
  }
  
}

void retournement() {
  control_hour(); //on verifie l'heure enfin d'activer les flag pour le retournement si 1heure est passee
  manuel(); // verification du bouton de retournement manuel

  if (valider) {
    control_Fin_de_course(); // on verifie nos boutons

    if (etat_bts) { // de Droite vers le Gauche
      digitalWrite(PIN_MOTEUR_a, HIGH);
      digitalWrite(PIN_MOTEUR_d, LOW);
    }

    if (!etat_bts) { // de Gauche vers la Droite
      digitalWrite(PIN_MOTEUR_a, LOW);
      digitalWrite(PIN_MOTEUR_d, HIGH);
    }
    
  }
 

  if (valider == false){
    digitalWrite(PIN_MOTEUR_a, LOW);
    digitalWrite(PIN_MOTEUR_d, LOW);
  }
 }
#endif //moteur
