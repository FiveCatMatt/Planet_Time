long timer;
long trydelay;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  trydelay++;
  
  timer = millis();
  timer /= 1000;
  Serial.print("Millis: ");
  Serial.println(timer);
  Serial.print("Delay: ");
  Serial.println(trydelay);
  delay(2000);                  // Halt all operations for 2 secs
}
