
void regulation() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    AffichageLCD("erreur DHT", 0 ,0 ) ;
  } else {
    if(t > 44){
      AffichageLCD( "Temp : " + String(t) + " C" , 1 , 0 ) ;
      digitalWrite(chauffage , HIGH) ;
    }else if(t < 42){
      AffichageLCD( "Temp : " + String(t) + " C" , 1 , 0 ) ;
      digitalWrite(chauffage , LOW );
    }
  }

}

void AffichageLCD(String texte , int ligne , int colonne) {
  lcd.setCursor(colonne , ligne ) ;
  lcd.print("                  ");
  lcd.setCursor(colonne , ligne ) ;
  lcd.print(texte);
}

void AffichageLCD_With_Clear(String texte , int ligne , int colonne) {
  lcd.clear();
  lcd.setCursor(colonne , ligne ) ;
  lcd.print("                   ");
  lcd.setCursor(colonne , ligne ) ;
  lcd.print(texte);
}

void Reset() {
  wdt_enable(WDTO_15MS);
  for (;;) {

  }
}

void verifTemp(){
//    DateTime now = RTC.now();
    //annee = now.year() ;
    //mois = now.month() ;
    dt = clock.getDateTime();
    int J = dt.day ;
    int H = dt.hour;  
    int M = dt.minute ; 
    AffichageLCD( "csg h:"+String(heure_consigne) + "-temp:" + String(Temp_consigne) , 0 ,0 ) ;
           
}

void lireClavier(){
  
    key1 == NO_KEY ;
    key1 = keypad.getKey();
    /*
    if(key1 != NO_KEY){ 
      AffichageLCD(String(key1), 0 ,0 ) ;
      Serial.println(key1) ;
      if(key1 == 'A' ){
        
      }
      else if(key1 == 'B')  ;
      else if(key1 == 'C') {
         processus = 3 ;
      }
      else if(key1 == 'D')  ;  
    }
    */
     switch(key1) {
           case (NO_KEY) :
           break;
           case ('A') :
              processus = 3 ;
           break;
           case ('B') :
              processus = 4 ;
           break;  
           case ('C') :
              processus = 5 ;
           break;     
           default : 

           break;
      }
         
}

void SetClock(int heure , int minute ){
/*   rtc.setClockMode(false) ;
   rtc.setHour(heure);
   rtc.setMinute(minute);
   rtc.setSecond(0) ;
   */
   clock.setDateTime(2014, 4, 13, heure, minute, 00);
}
void lecture_clavier(){
  int i=0,pos=65;
  char k3 ,key[5];
  String k;
  boolean sortie=true;
  key[0] = NO_KEY ;
  key[1] = NO_KEY ;
  key[2] = NO_KEY ;
  key[3] = NO_KEY ;
  key[i] = keypad.getKey();
  do{
     key[i] = keypad.getKey();
      switch(key[i]) {
           case (NO_KEY) :
              //Serial.println("no key"); 
           break;
           case ('*') :
              Serial.println("valider");
              sortie=false;
           break;
           case ('#') :
           if(i!=0){
              Serial.print("effacer");
              k=k.substring(0,k.length()-1 );
              i--;
              pos=pos-1;
           }
           break;     
           default : 
            if(i<4){
              Serial.println(key[i]);
             // k= key[i] - '0' ; 
              k=k+ (key[i] - '0' ) ;                
              i++;
              pos=pos+1;
            }
           break;
      }   
      k2=k;
      AffichageLCD(k, 1 ,6 ) ;
 }while(sortie);
 Serial.print("sortie");
}
int lire2chiffres(){
        //lcd.setCursor(0,1);
          char key = NO_KEY ;
          char key2 = NO_KEY ;
          int k1 , k2 ;    
         while(key == NO_KEY ) {
              key = keypad.getKey();
              if(key != NO_KEY ) lcd.print(key); 
              k1 = key - '0' ; 
         }
          while(key2 == NO_KEY ){
                    key2 = keypad.getKey();
                    if(key2 != NO_KEY ) lcd.print(key2);
                    k2 = key2 - '0' ;
         }
 return ( k1 * 10 + k2 ) ;
}

void reglage_horloge(){
  
  int heure = 0 , minute = 0 , seconde = 0 ,jour,mois,annee;
  lcd.clear() ;
  AffichageLCD("reglage horloge" ,0 ,0) ;
  AffichageLCD("JOUR :" , 1 ,0 ) ;
  lecture_clavier();
  jour=k2.toInt();
  lcd.clear() ;
  AffichageLCD("reglage horloge" ,0 ,0) ;
  AffichageLCD("MOIS :" , 1 ,0 ) ;
  lecture_clavier();
  mois=k2.toInt();
  lcd.clear() ;
   AffichageLCD("reglage horloge" ,0 ,0) ;
  AffichageLCD("ANNEE:" , 1 ,0 ) ;
  lecture_clavier();
  annee=k2.toInt();
  lcd.clear() ;
   AffichageLCD("reglage horloge" ,0 ,0) ;
  AffichageLCD("HEURE :" , 1 ,0 ) ;
  lecture_clavier();
  heure=k2.toInt();
  lcd.clear() ;
   AffichageLCD("reglage horloge" ,0 ,0) ;
  AffichageLCD("MIN:" , 1 ,0 ) ;
  lecture_clavier();
  minute=k2.toInt();; 
  lcd.clear() ;
   clock.setDateTime(annee, mois, jour, heure, minute, 00);
  processus = 0 ;
  
}
void reglage_consigne(){
  Serial.println("reglage consigne") ;
  lcd.clear() ;
  AffichageLCD("Heure consigne" ,0 ,0) ;
  AffichageLCD("Heure :" , 1 ,0 ) ;
  lecture_clavier();
  heure_consigne=k2.toInt();
  lcd.clear() ;
  AffichageLCD("Heure consigne" ,0 ,0) ;
  AffichageLCD("Temp:" , 1 ,0 ) ;
  lecture_clavier();
  Temp_consigne=k2.toInt();
  lcd.clear() ;
  //SetClock( heure , minute  ) ; 
  processus = 0 ;
  
}
void Commencer(){
  //DateTime now = RTC.now();
  //annee = now.year() ;
  //mois = now.month() ;
  dt = clock.getDateTime();
  jour =dt.day;
  heure = dt.hour ;
  minute =dt.minute ;
  mois=dt.month;
  annee=dt.year;  
  AffichageLCD_With_Clear( String(jour) + "/" + String(mois) + "/" + String(annee)  , 0 ,0 ) ;
  AffichageLCD( String(heure) + ":" + String(minute) , 1 ,0 ) ;
  delay(3000);
  processus = 0 ;
}

