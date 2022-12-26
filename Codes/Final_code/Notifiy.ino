void Call() {

  gsm.println("ATD" + user_sim_number + ";");
  previousTime = millis();
  unsigned long currentTime;

  while (1) {
    currentTime = millis();
    if (currentTime - previousTime > 25000) {
      gsm.println("ATH");                // Hangout the call after 25 seconds
      break;
    }
    else {
      Alarm(1);                          // Until 25 seconds elapse, Alarm will continously beep
      continue;
    }

  }

}

void Sendtext(String message) {

  gsm.println("AT+CMGS=\"" + user_sim_number + "\"\r");
  delay(2000);
  gsm.println(message);
  delay(1000);
  gsm.println((char)26);      // Ascii value for Ctrl+z , which indicates the end of a message
  delay(100);
}

void Alarm(int cycles) {      // Alarm tone for the buzzer

  int i = 0;
  while (i < cycles) {

    tone(buzz, 700);
    delay(500);
    noTone(buzz);
    delay(200);
    i++;

  }

}
