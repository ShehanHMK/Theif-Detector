#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

void setup()

{

  mySerial.begin(9600);   // Setting the baud rate of GSM Module 

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);

  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  //mySerial.println("AT+CSCS='GSM'");
  delay(1000);
}

void SendMessage(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+94773751023\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);
}


void DialCall(){
  mySerial.println("AT+CMGF=0");
  mySerial.println("ATD+94773751023;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);
}



void loop()

{

  if (Serial.available()>0)

   switch(Serial.read())

    {

    case 's':

      SendMessage();

      break;

    case 'd':

      DialCall();

      break;
    }

    if (mySerial.available()>0){
    
      String msg = mySerial.readString();
      Serial.println(msg);
      if (msg.indexOf("+CMT") >=0){
        Serial.println("Hari yakooooo");

        
        Serial.println(msg.substring(msg.indexOf("+94"),msg.indexOf("+94")+12));

        //String incoming_number = msg.substring(9, 21);
      }

    }
}


String remove_char(String msg){
  String new_msg= msg.substring(msg.indexOf("")
}














    
