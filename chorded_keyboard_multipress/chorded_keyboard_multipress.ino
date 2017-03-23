/*********************************************************************

  Human Interface Design (HID)
  Basic Chorded Keyboard
  with chord delay and auto repeat

  by Scott Mitchell
  RMIT University

  based on Adafruit Bluefruit code.
  MIT license

  This code is designed for use with the Adafruit Bluefruit Feather board

*********************************************************************/

#include "keyboardSetup.h"
String KEYBOARD_NAME = "myKeyboardName";

const int maxChar = 6;

const String keyMap [5][maxChar] = {
  {"A", "B", "C", "D", "E", ","},
  {"F", "G", "H", "I", "J", "?"},
  {"K", "L", "M", "N", "O", "."},
  {"P", "Q", "R", "S", "T", "!"},
  {"U", "V", "W", "X", "Y", "Z"}
}

// pin settings
const int button0 = 6;
const int button1 = 9;
const int button2 = 10;
const int button3 = 11;
const int LEDpin = 5;

// variables to control button repeat
byte lastButtonState = B000000;
// delay time in milliseconds before button press is counted
const int keyPressDelay = 800;
// the last time the buttons were pressed
long timeOfLastKeyPress = 0;
// the time in milliseconds before timeout
const int buttonTimeout = 500;

int count_button_presses = 0;

int current_button = 0;

//
// Setup the system - run once
//
void setup(void)
{
  while (!Serial);  // wait for Serial to startup - maybe don't need this?
  delay(500);

  Serial.begin(115200);
  Serial.println("Basic Chorded Keyboard");
  Serial.println("---------------------------------------");

  setupKeyboard(KEYBOARD_NAME);

  // setup pins
  pinMode(button0, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);
}


//
// Loop the program - run forever
//
void loop(void)
{
  // button states are represented by 0s and 1s in a binary number
  readButtonState();

  // if the button state has changed wait a short time
  // this will prevent incomplete chords from being read
  if (buttonState != lastButtonState) delay(keyPressDelay);
  // check buttons again - this is considered a valid chord
  buttonState = readButtonState();

  // the result will be a number between 0 (no buttons pressed) and 63 (all buttons pressed)
  // This number is used to select a char from the key mapping array
  if (buttonState > 0) {

    // auto repeat
    if (buttonState == lastButtonState) {
      if (millis() - autoRepeatTime > timeOfLastKeyPress) {
        // send String
        sendStr(buttonState);
      }
    } else {
      timeOfLastKeyPress = millis();
      // send String
      sendStr(buttonState);
    }
  }

  // remember the button state
  lastButtonState = buttonState;
}



void readButtonState() {
  int new_button = 0;
  // turn on the bits if the button is being pressed
  if (digitalRead(button0) == false) new_button = 1;
  if (digitalRead(button1) == false) new_button = 2;
  if (digitalRead(button2) == false) new_button = 3;
  if (digitalRead(button3) == false) new_button = 4;
  if (digitalRead(button4) == false) new_button = 5;

  if (new_button = 0) {
    // register the last button press as valid

  } else {
    // a button has been pressed
    if (new_button != current_button) {
      // trigger the last button to enter
      count_button_presses = 1;
      // remember the new button for next time
      current_button = new_button;
    } else {
      // button has been pressed multiple times
      count_button_presses++;
    }
    // remember the time of the button press
    timeOfLastKeyPress = millis();
    // account for button bounce
    delay(100);
  }


}

void sendStr(byte buttonState) {
  Serial.print("Sending Byte: ");
  Serial.print(buttonState, BIN);
  Serial.print(" Number: ");
  Serial.print(buttonState, DEC);
  Serial.print(", String: ");
  Serial.println(keyMap[buttonState]);

  // copy string to char array
  const unsigned int len = 128;
  char keys[len];
  keyMap[buttonState].toCharArray(keys, len);

  ble.print("AT+BleKeyboard=");
  ble.println(keys);

  // wait for feedback
  if ( ble.waitForOK() )
  {
    Serial.println("OK!");
  } else
  {
    Serial.println("FAILED!");
  }
}
