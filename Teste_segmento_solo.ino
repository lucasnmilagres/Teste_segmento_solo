void setup() {
  Serial.begin(9600);
}

void loop() {
  serialEventRun();
}

void serialEventRun(void) {
  if (Serial.available()) 
    serialEvent();
}

void serialEvent(){
    //Se a mensagem recebida for igual a S, responde com um K
    if('S'==Serial.read())
      Serial.write("K");      
}


