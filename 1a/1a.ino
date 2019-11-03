int calibrationTime=5;
long unsigned int lowIn; 
long unsigned int pause=2000; 
boolean lockLow= true; 
boolean takeLowTime; 
int pirPin=12;
int ledPin=6; 

void setup() {
  Serial.begin(9600); 
  pinMode(pirPin, INPUT); 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(pirPin, LOW); 
  Serial.print("calibrating sensor"); 
  for(int i=0; i< calibrationTime; i++){ 
      Serial.print("."); 
      delay(1000);
  }
  // print in serial  
  Serial.println("done"); 
  Serial.println("Sensor Active"); 
  delay(50);
}

void loop() {
  // when off pirPin
  if(digitalRead(pirPin)==HIGH){ 
      digitalWrite(ledPin, HIGH); 
      if(lockLow){ 
          lockLow= false; 
          Serial.println("---"); 
          Serial.print("motion detected at"); 
          Serial.print(millis()/1000); 
          Serial.println("sec"); 
          delay(50);
      }
      takeLowTime= true;  
  } 
  // when on pir pin
  if(digitalRead(pirPin)==LOW){
    // mematikan lampu
      digitalWrite(ledPin, LOW); 
      if(takeLowTime){ 
          lowIn= millis(); 
          takeLowTime= false;
      } 
      if(!lockLow && millis() - lowIn > pause){ 
          lockLow= true; 
          Serial.print("motion ended at"); 
          Serial.print((millis()- pause)/1000); 
          Serial.println("sec"); 
          delay(50);  
      }  
  }
}
