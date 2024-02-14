#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
#define FONA_RI_INTERRUPT  0

SoftwareSerial fonaSoftwareSerial = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
char PHONE1[21] = "0772536321"; // Enter the required mobile number here.
char theftalertmessage[141]= "Intruder Alert !!!!!"  ;
int pir = 0; 
void setup()
{
  pinMode(5,INPUT);
  Serial.begin(115200);
  Serial.println(F("Initializing...."));
  delay(5000);
  fonaSoftwareSerial.begin(9600); 
  if (! fona.begin(fonaSoftwareSerial)) {        
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

   fona.print ("AT+CSMP=17,167,0,0\r");
    Serial.println(F("FONA is OK")); 
}

void loop(){  
  int pir = digitalRead(5);
  Serial.print("Sensor Value:");
  Serial.println(pir);
  if(pir==1)
  {     
     Serial.println("Theft Alert");
     makecall();
     send_sms();
  }
  else  
  { 
    pir = 0;
    Serial.println("Safe");
  }
 
  
 }

void send_sms()
{
  if(PHONE1 != ""){
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE1,theftalertmessage);
    delay(20000);
  } 
}
void makecall()
{
  if(PHONE1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE1);
    delay(5000);
  } 
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(20000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}
