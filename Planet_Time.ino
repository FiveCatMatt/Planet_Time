#include <Adafruit_GFX.h>         //Core graphics library
#include <Adafruit_ST7735.h>      //Hardware-specific library
#include <SPI.h>                  //Interface for LCD
#define TFT_CS 10                 //SPI Pins
#define TFT_RST 8
#define TFT_DC 9
#define SPI_SCK 15  //13
#define SPI_DO 16 //11
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
// LCD 128 x 160 -- ALL lines above are specifict to the SainSmart 1.8" TFT LCD, Change to suit your hardware

// TO DO all arrays set at 10 to allow 9 planets - only 7 fit on this LCD so two slots are wasted
int Num_Planets = 7;

// Planets - 0:Mercury 1:Venus 2:Earth 3:Mars 4:Jupiter 5:Saturn 6:Uranus 7:Neptune

// Display
String Planet[10] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
int PrintY[10] = {20, 35, 50, 65, 80, 95, 110, 125, 140, 155};  // Y axis location of each display row

int Seconds[10];
int Minutes[10];
int Hours[10];
int Days[10];
long previousMillis[10];
long interval[10];

unsigned long currentMillis;

void setup() {
  tft.initR(INITR_BLACKTAB);      //Initialize a ST7735S chip, fill screen with black, and set rotation
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);             //Rotate screen
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);

  // Time delay for planets -- from NASA fact sheets i.e. http://nssdc.gsfc.nasa.gov/planetary/factsheet/marsfact.html
  interval[0] = 175942;           // Mercury
  interval[1] = 116750;           // Venus
  interval[2] = 1000;             // Earth
  interval[3] = 1027;             // Mars
  interval[4] = 414;              // Jupiter
  interval[5] = 444;              // Saturn
  interval[6] = 718;              // Uranus
  interval[7] = 1208;             // Neptune

  tft.setCursor(5, 5);            // Print title on LCD
  tft.print("Planet");
  tft.setCursor(70, 5);
  tft.print("Days");
  tft.setCursor(105, 5);
  tft.print("HH:MM:SS");

  for (int i = 0; i < Num_Planets; i++) {       // Run both functions once for each planet to display all clocks, also sets all seconds to 1
    StepUp(i);
    DisplayMe(i);
  }

  Serial.begin(9600);
}

void StepUp(int PlanetNum) {
  previousMillis[PlanetNum] = currentMillis;    // Set previous to current marking this event as last
  Seconds[PlanetNum]++;                         // Increment specific planet seconds

  if (Seconds[PlanetNum] == 60) {               // The following uses seconds to increment mins, hours, then days
    Seconds[PlanetNum] = 0;                     // When 1 min (60 secs) is hit set seconds to zero and increment mins - same for each below
    Minutes[PlanetNum]++;

    if (Minutes[PlanetNum] == 60) {
      Minutes[PlanetNum] = 0;
      Hours[PlanetNum]++;

      if (Hours[PlanetNum] == 24) {
        Hours[PlanetNum] = 0;
        Days[PlanetNum]++;
        if (Days[PlanetNum] == 99) {
          Days[PlanetNum] == 0;
        }
      }
    }
  }
}

void DisplayMe(int PlanetNum) {
  // This function prints to the LCD - Change all code below to suit your hardware
  
  // 0:Mercury 1:Venus 2:Earth 3:Mars 4:Jupiter 5:Saturn 6:Uranus 7:Neptune
  // TO DO find a way to use a variable to set color - char required but string to char didn't work
  switch (PlanetNum) {                          // Sets the text color for each planet                
    case 0:
      tft.setTextColor(0x8C72, 0x0000);
      break;
    case 1:
      tft.setTextColor(0xF52C, 0x0000);
      break;
    case 2:
      tft.setTextColor(0x43FB, 0x0000);
      break;
    case 3:
      tft.setTextColor(0xB201, 0x0000);
      break;
    case 4:
      tft.setTextColor(0xEBA0, 0x0000);
      break;
    case 5:
      tft.setTextColor(0xFE60, 0x0000);
      break;
    case 6:
      tft.setTextColor(0x0CD7, 0x0000);
      break;
  }

  tft.setCursor(5, PrintY[PlanetNum]);                  // The following just displays the times - specific to this LCD
  tft.print(Planet[PlanetNum]);

  tft.setCursor(75, PrintY[PlanetNum]);
  if (Days[PlanetNum] < 10) {
    tft.print("0");
    tft.print(Days[PlanetNum]);
  } else {
    tft.print(Days[PlanetNum]);
  }
  tft.setCursor(105, PrintY[PlanetNum]);
  if (Hours[PlanetNum] < 10) {
    tft.print("0");
    tft.print(Hours[PlanetNum]);
  } else {
    tft.print(Hours[PlanetNum]);
  }
  tft.print(":");
  if (Minutes[PlanetNum] < 10) {
    tft.print("0");
    tft.print(Minutes[PlanetNum]);
  } else {
    tft.print(Minutes[PlanetNum]);
  }

  tft.print(":");
  if (Seconds[PlanetNum] < 10) {
    tft.print("0");
    tft.print(Seconds[PlanetNum]);
  } else {
    tft.print(Seconds[PlanetNum]);
  }
}

void loop() {
  currentMillis = millis();                                     // Grab current time in millis

  for (int i = 0; i < Num_Planets; i++) {                       // Loop through all planets
    if (currentMillis - previousMillis[i] > interval[i]) {      // Check if current time is greater than each planets set interval
      StepUp(i);                                                // If interval is met step up secs, min, hour, and day for planet defined by i
      DisplayMe(i);                                             // Display current planet(i) time since it incremented
    }
  }
}
