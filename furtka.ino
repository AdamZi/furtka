
#define pin_czujnika 2
#define pin_domofonu 4
#define pin_przycisku 6
#define pin_zamka 8
#define pin_kontrolki 13

int minuta = 0;
int poprzednia_minuta = 0;
volatile bool sygnal_domofonu = false;
volatile bool sygnal_czujnika = false;
volatile bool furtka_otwarta;
volatile bool zamek_zwolniony = false;
volatile bool czekaj_na_zamkniecie = false;
volatile bool stan_przycisku;
volatile bool stan_diody = true;
volatile bool sygnal_otwierania_aktywny = false;
unsigned long poprzedni_czas = 0;
unsigned long biezacy_czas;



volatile bool flaga = false;
volatile bool buzzer_aktywny = false;


void setup() 
{
  //Serial.begin(9600); 
  pinMode(pin_czujnika,INPUT_PULLUP);
  pinMode(pin_domofonu,INPUT_PULLUP);
  pinMode(pin_przycisku,INPUT_PULLUP);
  pinMode(pin_kontrolki,OUTPUT);
  pinMode(pin_zamka,OUTPUT);

  furtka_otwarta = !digitalRead(pin_czujnika);
  digitalWrite(pin_zamka,HIGH);
  digitalWrite(pin_kontrolki,LOW);
  
}

void loop()
{
  furtka_otwarta=!digitalRead(pin_czujnika);
  if (furtka_otwarta)
     {
     //  if (!czekaj_na_zamkniecie) 
       
      // {
        
        if (poprzedni_czas<biezacy_czas-250)
           {
              poprzedni_czas=biezacy_czas;
              if (stan_diody==LOW) {stan_diody=HIGH;} else {stan_diody=LOW;}
               digitalWrite(pin_kontrolki,stan_diody);
            } 

        
        //digitalWrite(pin_kontrolki,HIGH);
        
        
        
       // }
       if (zamek_zwolniony) {czekaj_na_zamkniecie=true;}
     }
   else
     {
       if (!zamek_zwolniony) {digitalWrite(pin_kontrolki,LOW);}
       if ((zamek_zwolniony)&&(czekaj_na_zamkniecie)) {zamek_zwolniony=false; czekaj_na_zamkniecie=false;}
      }
  if (!furtka_otwarta)
     {
         if ((digitalRead(pin_przycisku)==LOW)||(digitalRead(pin_domofonu)==LOW))
          {
            if ((!sygnal_otwierania_aktywny)&&(!zamek_zwolniony))
                {
                  digitalWrite(pin_kontrolki,HIGH);
                  digitalWrite(pin_zamka,LOW);
                  delay(500);
                  digitalWrite(pin_zamka,HIGH);
                  sygnal_otwierania_aktywny=true;
                  zamek_zwolniony=true;
                 } else {delay(20);}
          }
         else
          {
            sygnal_otwierania_aktywny=false;
            delay(20);
          }
     
     }
     
 biezacy_czas=millis();  
 if ((zamek_zwolniony)&&(!furtka_otwarta)) 
 {
  //  if (poprzedni_czas<biezacy_czas-250)
  //   {
  //       poprzedni_czas=biezacy_czas;
  //       if (stan_diody==LOW) {stan_diody=HIGH;} else {stan_diody=LOW;}
  //        digitalWrite(pin_kontrolki,stan_diody);
  //    }  
  digitalWrite(pin_kontrolki,HIGH); 
 
  } 
}




 
