long timer;                     // Store millis() value
long trydelay;                  // Variable to show the difference between delaying a loop and using millis

void setup() {
  Serial.begin(9600);
}

void loop() {
  trydelay++;                   // Increment this variable each time void loop runs
  
  timer = millis();             // Grab current millis value - always assign it to a variable since it changes so quickly
  timer /= 1000;                // Divide it by 1000 to convert to seconds to make it easier to read on the serial monitor
  
  Serial.print("Millis: ");     // Print values to serial
  Serial.println(timer);        
  Serial.print("Delay: ");
  Serial.println(trydelay);
  
  delay(2000);                  // Halt all operations for 2 secs - Change this value to see millis vs delay effect
}
