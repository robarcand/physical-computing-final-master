#include "PulseSensorPlaygroundh.h"

// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>

#define PIN_OLED_RST D6  // Connect RST to pin 6
#define PIN_OLED_DC  D5  // Connect DC to pin 5 (required for SPI)
#define PIN_OLED_CS  A2  // Connect CS to pin A2 (required for SPI)
MicroOLED oled(MODE_SPI, PIN_OLED_RST, PIN_OLED_DC, PIN_OLED_CS);

//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED = 7;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 3250;            // Determine which Signal to "count as a beat", and which to ingore.


void setup() {
    
    pinMode(LED,OUTPUT);         // pin that will blink to your heartbeat!
    Serial.begin(9600);         // Set's up Serial Communication at certain speed.
    
    oled.begin();
    oled.clear(ALL);
    oled.display();
    
    delay(1000);

    oled.clear(PAGE);
    
    oled.setFontType(0);
}

void loop() {
    
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     //digitalWrite(LED,HIGH);
     text("healthy");
   } else {
    //digitalWrite(LED,LOW);  //  Else, the sigal must be below "550", so "turn-off" this LED.
    text("unhealthy");
        }


delay(10);

}

void text(String textToPrint) {
    int middleX = oled.getLCDWidth() / 2;
    int middleY = oled.getLCDHeight() / 2;
    
     oled.clear(PAGE);
     
     oled.setCursor(middleX - (oled.getFontWidth() * (textToPrint.length()/2)), middleY - (oled.getFontWidth() / 2));
     oled.print(textToPrint);
     oled.display();
}

