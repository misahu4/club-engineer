int CTimeToDelay = 1000;  

void setup() {
   Serial.begin(9600);
}

void loop() {  
  // print labels 
  Serial.println("Hello World");
  delay(CTimeToDelay / 2);
  Serial.println("            ");
  delay(CTimeToDelay / 2);
}
