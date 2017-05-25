/*********************************************************************

  Human Interface Design (HID)
  SMS send using mouse control

  by Scott Mitchell
  RMIT University

  based on Adafruit Bluefruit code.
  MIT license

  Note that not all devices support BLE Mouse!
  - OSX, Windows 10 both work
  - Android has limited support
  - iOS completely ignores mouse

  This code is designed for use with the Adafruit Bluefruit Feather board

*********************************************************************/

#include "keyboardSetup.h"
String KEYBOARD_NAME = "myKeyboardName";

const int sendPin = 2;

String moveIncrement = "50";
const int numXmoves = 8;
const int numYmoves = 13;
bool mouseInPos = false;


//
// Setup the system - run once
//
void setup(void)
{
  while (!Serial);  // required for Flora & Micro
  delay(500);

  setupKeyboard(KEYBOARD_NAME);

  Serial.begin(115200);
  Serial.println("Using the HID Mouse to Send an SMS");
  Serial.println("---------------------------------------");

  // setup pins
  pinMode(sendPin, INPUT_PULLUP);
}


//
// Loop the program - run forever
//
void loop(void)
{
  if (digitalRead(sendPin) == LOW) {

    sendMessage();

    while (digitalRead(sendPin) == LOW) {
      // wait here until button is released
      delay(10);
    }

  }
}


//
// There doesn't seem to be any absolute mouse coordinate system - mouse location is relative to start possition
// on HTC-M8 the mouse starts in the center of screen. Send button is at 400, 650.
// AT+BleHidMouseMove=400,650 returns an error, so mouse must be moved in small increments. #!?
//
bool sendMessage() {
  // move mouse to send button location
  if (!mouseInPos) {
    Serial.println("Move mouse to Send button location");
    int i = 0;

    while (i <= numXmoves || i <= numYmoves) {
      // Move mouse to location
      ble.print(F("AT+BleHidMouseMove="));
      if (i <= numXmoves) ble.print(moveIncrement);
      else ble.print("0");
      ble.print(",");
      if (i <= numYmoves) ble.println(moveIncrement);
      else ble.println("0");

      if ( ble.waitForOK() )
      {
        Serial.println("OK!");
      } else
      {
        Serial.println("FAILED!");
      }

      i++;

      delay(100);
    }

    mouseInPos = true;
  }

  // Press (and hold) the Left mouse's button
  ble.sendCommandCheckOK(F("AT+BleHidMouseButton=L,press"));

  // delay a bit
  delay(200);

  // Release the Left mouse's button
  ble.sendCommandCheckOK(F("AT+BleHidMouseButton=0"));
}

