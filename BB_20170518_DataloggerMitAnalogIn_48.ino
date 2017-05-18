/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10  //Kann optional auch auf anderen Pin

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
// libraries to communicate with the SD-Card
#include <SPI.h>
#include <SD.h>

// library to communicate with the MuxShield
#include <MuxShield.h>

//Initialize the Mux Shield
MuxShield muxShield;

// global variables
int reference = 700;
const int chipSelect = 10;

// Arrays to store analog values after recieving them
int IO1AnalogVals[16];
int IO2AnalogVals[16];
int IO3AnalogVals[16];

void setup() {
  //Set I/O 1, I/O 2, and I/O 3 as analog inputs
  muxShield.setMode(1, ANALOG_IN);
  muxShield.setMode(2, ANALOG_IN);
  muxShield.setMode(3, ANALOG_IN);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("Card initialized.");
}

void loop() {

  // make a string for assembling the data to log:
  String dataString = "";

  for (int i = 0; i < 16; i++)
  {
    //Analog read on all 16 inputs on IO1, IO2, and IO3
    IO1AnalogVals[i] = muxShield.analogReadMS(1, i);
    IO2AnalogVals[i] = muxShield.analogReadMS(2, i);
    IO3AnalogVals[i] = muxShield.analogReadMS(3, i);
  }

  for (int analogVals = 0; analogVals < 16; analogVals++) {
    int sensor = IO1AnalogVals[analogVals];
    dataString += String(sensor);
    if (analogVals < 16) {
      dataString += ",";
    }
  }

    for (int analogVals = 0; analogVals < 16; analogVals++) {
      int sensor = IO2AnalogVals[analogVals];
      dataString += String(sensor);
      if (analogVals < 16) {
        dataString += ",";
      }
    }

      for (int analogVals = 0; analogVals < 16; analogVals++) {
        int sensor = IO3AnalogVals[analogVals];
        dataString += String(sensor);
        if (analogVals < 16) {
          dataString += ",";
        }
      }

        /*
          // read three sensors and append to the string:
          for (int analogPin = 0; analogPin < 3; analogPin++) {
            int sensor = analogRead(analogPin);
            dataString += String(sensor);
            if (analogPin < 2) {
              dataString += ",";
            }
          }
        */


        // open the file. note that only one file can be open at a time,
        // so you have to close this one before opening another.
        File dataFile = SD.open("DataMux.txt", FILE_WRITE);
        // if the file is available, write to it:
        if (dataFile) {
          dataFile.println(dataString);
          dataFile.close();
          // print to the serial port too:
          Serial.println(dataString);
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening DataMux.txt");
        }
      }









