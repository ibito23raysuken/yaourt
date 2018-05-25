
void Initialisation_lcd() ;
void ClavierSetup() ;
void Initialisation_rtc();

void setup(){
  pinMode(chauffage , OUTPUT ) ;
  Serial.begin(9600) ;
  Wire.begin();
  Initialisation_dht() ;
  Initialisation_lcd() ;
  Initialisation_rtc();
  ClavierSetup();
  initTimer2();   // initialise TIMER2 comme Base de Temps 
  
  digitalWrite(chauffage , HIGH ) ;
  /*DateTime now = RTC.now();
  for (int i = 0 ; i > 20 ; i ++ ) Serial.print(now.second()); */

}

void loop(){
    //=========== balayage des tâches ==============
    
   switch(processus){
     case 0 :
        verifTemp() ; 
        break;
     case 1 :
        regulation() ;
        break;
     case 2 :
        lireClavier() ;
        break ;
     case 3 :
        reglage_horloge() ;
        break;
     case 4 :
        reglage_consigne();
     break;
     case 5:
        Commencer();
     break;
     default : 
     break;
   }
}

/********************************************************************** 
*                      BASE DE TEMPS 1 ms
**********************************************************************/

ISR(TIMER2_COMPA_vect)  // fonction appelée sur interruption du TIMER2
{  
  
  if(compteur100ms == 0 ){
    //Serial.print(processus) ;
    compteur100ms = 100 ;
    if(processus != 3) {
      processus++ ;
      if(processus == NBTACHE ) processus = 0  ;
    }
  }else {
    compteur100ms-- ;   
  }  
 
}

