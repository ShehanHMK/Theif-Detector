#include <SoftwareSerial.h>

#define rx 2
#define tx 3
#define pir 7
#define buzz 6

//#define led 8

String user_sim_number = "+94773751023" ;      // Change this to your number

unsigned long previousTime ;

bool SEND_NOTI = true ;

SoftwareSerial gsm(rx, tx);               // Creating SoftwareSerial object

void setup() {
  Serial.begin(9600); // Remove this
  gsm.begin(9600);
  pinMode(pir, INPUT);     // Input pin to get the signal from PIR sensor
  pinMode(buzz, OUTPUT);   // to connect the buzzer
  //pinMode(led, OUTPUT);

  gsm.println("AT+CNMI=2,2,0,0,0");        // Recieve the messages in text type , (1,2,0,0,0) is for recieve messages as indexes
  delay(2000);
  
  gsm.println("AT+CMGF=1");                // AT+CMGF=0 is (SMS PDU mode)  -> calling alert mode
  delay(2000);                                        // AT+CMGF=1 is (SMS text mode) -> SMS alert mode

  //gsm.println("AT+CSCS='GSM'");
  //delay(1000);
                                           // Here we use SMS alert mode by default
}
                                                      // Take 2 + 2 + 1 = 5 seconds to initialize

void loop() {

  SearchForCommands();

  main_function();

}


void main_function()
{
  int pir_val = digitalRead(pir);             // Taking the Output value of the PIR Sensor
  Serial.println(pir_val);
  if (pir_val == 1)
  {

    if (SEND_NOTI) {                    // If notification feature has been enabled, Send a text "Motion Detected"

      Sendtext("Motion Detected");      // Here you can choose notifying method either call or SMS, by default it is SMS
      //Call();
      
    }


    Alarm(5);              //After the call or SMS,again beep the alarm 20 times to ensure the security, This can be change to whatever value you preserve

  }

  

}


void SearchForCommands() {

  if (gsm.available() > 0) {

    String msg = gsm.readString();
    //Serial.println(msg);
    if (msg.indexOf("+CMT") >= 0) {                 // Make sure we are reading SMS , otherwise it could be something else

      //String incoming_number = msg.substring(9, 21); // Extracting the incoming number from text

      if (msg.indexOf(user_sim_number)>=0) {     // Ensure that gsm can be controlled by only user

        String msg_context = msg.substring(msg.indexOf("TD "),msg.indexOf("TD ")+10);     // Extracting the message context

        msg_context.trim();                         // removing unwanted newlines and characters
        Serial.println(msg_context);
        if (msg_context.equals("TD ON")) {

          SEND_NOTI = true;
          Sendtext("Notifications turned ON");                 // Do responsible tasks that have been assigned to specific commands sent by user

        }
        else if (msg_context.equals("TD OFF")) {

          SEND_NOTI = false;
          Sendtext("Notifications turned OFF");

        }
        else if (msg_context.equals("TD HELP")) {

          Sendtext("ON   - turn on notifications \nOFF - turn off notifications");

        }
        else {

          Sendtext("Invalid command !... type 'TD HELP'");

        }
      }
    }
  }
}
