#define buzz 6

int val;

void setup() {
  Serial.begin(9600);
  pinMode(7,INPUT);
  
  pinMode(buzz,OUTPUT);
  pinMode(12,OUTPUT);

}

void loop() {
   val=digitalRead(7);

   Serial.println(val);
   
   if (val==1){
     
     digitalWrite(12,HIGH);
     delay(2000);
   }

   else {
     
     digitalWrite(12,LOW);
   } 
   
   

}
