
void Initialisation_lcd(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("DEMARRAGE");
 // lcd.setCursor(

}

void ClavierSetup(){
  //configuration du clavier matricielle
    unsigned int attente = 4;
    keypad.setHoldTime(attente);
    unsigned int anti_rebond = 4 ;  //4 ms
    keypad.setDebounceTime(anti_rebond);
}

void Initialisation_dht(){
  dht.begin();
}
void Initialisation_rtc(){
  clock.begin();
  // Initialize DS3231
  dt = clock.getDateTime();
  jour =dt.day;
  heure = dt.hour ;
  if(jour==0 && heure==0){
      Serial.println("Initialize DS3231");;
      
      // Set sketch compiling time
      clock.setDateTime(__DATE__, __TIME__);
      Serial.println("fin de l'intialisation DS3231");
  }
}


