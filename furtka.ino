
#define sensor_pin 2
#define sensor_intercom 4
#define button_pin 6
#define lock_pin 8
#define indicator_pin 13

int minute = 0;
int previous_minute = 0;
volatile bool intercom_signal = false;
volatile bool sensor_signal = false;
volatile bool door_open;
volatile bool lock_relased = false;
volatile bool wait_for_close = false;
volatile bool button_state;
volatile bool led_state = true;
volatile bool open_signal_active = false;
unsigned long previous_time = 0;
unsigned long current_time;

volatile bool flaga = false;
volatile bool buzzer_aktywny = false;

void setup() 
{ 
  pinMode(sensor_pin,INPUT_PULLUP);
  pinMode(sensor_intercom,INPUT_PULLUP);
  pinMode(button_pin,INPUT_PULLUP);
  pinMode(pin_kontrolki,OUTPUT);
  pinMode(lock_pin,OUTPUT);

  door_open = !digitalRead(sensor_pin);
  digitalWrite(lock_pin,HIGH);
  digitalWrite(pin_kontrolki,LOW);
  
}

void loop()
{
  door_open=!digitalRead(sensor_pin);
  if (door_open)
     {
     
        if (previous_time<current_time-250)
           {
              previous_time=current_time;
              if (led_state==LOW) {led_state=HIGH;} else {led_state=LOW;}
               digitalWrite(pin_kontrolki,led_state);
            } 

       if (lock_relased) {wait_for_close=true;}
     }
   else
     {
       if (!lock_relased) {digitalWrite(pin_kontrolki,LOW);}
       if ((lock_relased)&&(wait_for_close)) {lock_relased=false; wait_for_close=false;}
      }
  if (!door_open)
     {
         if ((digitalRead(button_pin)==LOW)||(digitalRead(sensor_intercom)==LOW))
          {
            if ((!open_signal_active)&&(!lock_relased))
                {
                  digitalWrite(pin_kontrolki,HIGH);
                  digitalWrite(lock_pin,LOW);
                  delay(500);
                  digitalWrite(lock_pin,HIGH);
                  open_signal_active=true;
                  lock_relased=true;
                 } else {delay(20);}
          }
         else
          {
            open_signal_active=false;
            delay(20);
          }
          }
     
 current_time=millis();  
 if ((lock_relased)&&(!door_open)) 
 {
   digitalWrite(pin_kontrolki,HIGH); 
   } 
}




 
