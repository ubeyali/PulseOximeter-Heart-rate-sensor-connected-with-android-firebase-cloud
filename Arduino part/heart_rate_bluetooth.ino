
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000
///blue
#include <SoftwareSerial.h>       //import Software Serial library
SoftwareSerial myStream(5, 6);  //pins for Rx and Tx respectively
String command = "";              //read and store user's choice
boolean is_written = false;       //to control printing of data
String choice;                    //store sensor data in string
int sensorValue; 
PulseOximeter pox;

uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
    
}

void setup()
{
    Serial.begin(115200);

    Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    myStream.begin(9600);
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 int i=0;
void loop()
{
    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        int  heart_rate=pox.getHeartRate();
        Serial.print(pox.getHeartRate());
        delay(100);
        
      myStream.print(" ");
    
        myStream.print(heart_rate);
        //myStream.print("\n");
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();
    }
}
