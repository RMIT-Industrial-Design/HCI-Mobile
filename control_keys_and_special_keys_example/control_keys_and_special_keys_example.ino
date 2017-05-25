/*********************************************************************

  Human Interface Design (HID)
  Sending Control Key Modifiers and Special Keys

  by Scott Mitchell
  RMIT University

  based on Adafruit Bluefruit code.
  MIT license

  This code is designed for use with the Adafruit Bluefruit Feather board

// Testing with a HTC-M8 running Android 6.0 & Google Messages
//
// With cursor in the text entry field the following key combinations produce:
// Return: new line.
// Enter: new line.
// Tab: highlight '+' symbol. then emoji symbol. Doesn't cycle through items.
// Right Arrow: move cursor to the right.
// Left Arrow: move cursor to the left. If on emoji symbol then move cursor back into text entry.
// Down Arrow: move cursor down.
// Up Arrow: move cursor up.
// Home: no effect.
// Page Up: moves to top of text entry.
// End: goes to end of line.
// Page Down: moves to end of text entry.
// Control-Return: no effect.
// Control-Enter: no effect.
// Control-Tab: no effect.
// Control-Right Arrow: move cursor to end of word (or end of next word if currently at the end of a word).
// Control-Left Arrow: move cursor to start of word (or start of next word if currently at the start of a word).
// Control-Down Arrow: no effect.
// Control-Up Arrow: no effect.
// Control-Home: moves to top of text entry.
// Control-Page Up: no effect.
// Control-End: moves to end of text entry.
// Control-Page Down: no effect.
// Shift-Return: new line.
// Shift-Enter: new line.
// Shift-Tab: no effect.
// Shift-Right Arrow: highlight (and extend/reduce selection) one char to right.
// Shift-Left Arrow: highlight (and extend/reduce selection) one char to left.
// Shift-Down Arrow: highlight (and extend/reduce selection) one line down.
// Shift-Up Arrow: highlight (and extend/reduce selection) one line up.
// Shift-Home: highlight from cursor position to start of word.
// Shift-Page Up: highlight from cursor position to start of message.
// Shift-End: highlight from cursor position to end of word.
// Shift-Page Down: highlight from cursor position to end of message.
// Alt-Return: no effect.
// Alt-Enter: no effect.
// Alt-Tab: opens recent apps screen.
// Alt-Right Arrow: move cursor to end of line.
// Alt-Left Arrow: move cursor to start of line.
// Alt-Down Arrow: move cursor to end of message.
// Alt-Up Arrow: move cursor to start of message.
// Alt-Home: no effect.
// Alt-Page Up: moves to top of text entry.
// Alt-End: no effect.
// Alt-Page Down: moves to end of text entry.
// Window-Return: move to home screen.
// Window-Enter: no effect.
// Window-Tab: no effect.
// Window-Right Arrow: no effect.
// Window-Left Arrow: no effect.
// Window-Down Arrow: no effect.
// Window-Up Arrow: no effect.
// Window-Home: no effect.
// Window-Page Up: no effect.
// Window-End: no effect.
// Window-Page Down: no effect.
// Control-Shift-Return: no effect.
// Control-Shift-Enter: no effect.
// Control-Shift-Tab: no effect.
// Control-Shift-Right Arrow: highlight from cursor position to end of word.
// Control-Shift-Left Arrow: highlight from cursor position to start of word.
// Control-Shift-Down Arrow: no effect.
// Control-Shift-Up Arrow: no effect.
// Control-Shift-Home: highlight from cursor position to start of message.
// Control-Shift-Page Up: no effect.
// Control-Shift-End: highlight from cursor position to end of message.
// Control-Shift-Page Down: no effect.
// Control-Alt-Return: no effect.
// Control-Alt-Enter: no effect.
// Control-Alt-Tab: no effect.
// Control-Alt-Right Arrow: no effect.
// Control-Alt-Left Arrow: no effect.
// Control-Alt-Down Arrow: no effect.
// Control-Alt-Up Arrow: no effect.
// Control-Alt-Home: no effect.
// Control-Alt-Page Up: no effect.
// Control-Alt-End: no effect.
// Control-Alt-Page Down: no effect.
// Control-Window-Return: move to home screen.
// Control-Window-Enter: no effect.
// Control-Window-Tab: no effect.
// Control-Window-Right Arrow: no effect.
// Control-Window-Left Arrow: no effect.
// Control-Window-Down Arrow: no effect.
// Control-Window-Up Arrow: no effect.
// Control-Window-Home: no effect.
// Control-Window-Page Up: no effect.
// Control-Window-End: no effect.
// Control-Window-Page Down: no effect.
// Shift-Alt-Return: no effect.
// Shift-Alt-Enter: no effect.
// Shift-Alt-Tab: opens recent apps screen.
// Shift-Alt-Right Arrow: no effect.
// Shift-Alt-Left Arrow: no effect.
// Shift-Alt-Down Arrow: highlight from cursor position to end of message.
// Shift-Alt-Up Arrow: highlight from cursor position to start of message.
// Shift-Alt-Home: no effect.
// Shift-Alt-Page Up: highlight from cursor position to start of message.
// Shift-Alt-End: no effect.
// Shift-Alt-Page Down: highlight from cursor position to end of message.
// Shift-Window-Return: move to home screen.
// Shift-Window-Enter: no effect.
// Shift-Window-Tab: no effect.
// Shift-Window-Right Arrow: no effect.
// Shift-Window-Left Arrow: no effect.
// Shift-Window-Down Arrow: no effect.
// Shift-Window-Up Arrow: no effect.
// Shift-Window-Home: no effect.
// Shift-Window-Page Up: no effect.
// Shift-Window-End: no effect.
// Shift-Window-Page Down: no effect.
// Alt-Window-Return: move to home screen.
// Alt-Window-Enter: no effect.
// Alt-Window-Tab: no effect.
// Alt-Window-Right Arrow: no effect.
// Alt-Window-Left Arrow: no effect.
// Alt-Window-Down Arrow: no effect.
// Alt-Window-Up Arrow: no effect.
// Alt-Window-Home: no effect.
// Alt-Window-Page Up: no effect.
// Alt-Window-End: no effect.
// Alt-Window-Page Down: no effect.
// Control-Shift-Alt-Return: no effect.
// Control-Shift-Alt-Enter: no effect.
// Control-Shift-Alt-Tab: no effect.
// Control-Shift-Alt-Right Arrow: no effect.
// Control-Shift-Alt-Left Arrow: no effect.
// Control-Shift-Alt-Down Arrow: no effect.
// Control-Shift-Alt-Up Arrow: no effect.
// Control-Shift-Alt-Home: no effect.
// Control-Shift-Alt-Page Up: no effect.
// Control-Shift-Alt-End: no effect.
// Control-Shift-Alt-Page Down: no effect.
// Control-Shift-Window-Return: move to home screen.
// Control-Shift-Window-Enter: no effect.
// Control-Shift-Window-Tab: no effect.
// Control-Shift-Window-Right Arrow: no effect.
// Control-Shift-Window-Left Arrow: no effect.
// Control-Shift-Window-Down Arrow: no effect.
// Control-Shift-Window-Up Arrow: no effect.
// Control-Shift-Window-Home: no effect.
// Control-Shift-Window-Page Up: no effect.
// Control-Shift-Window-End: no effect.
// Control-Shift-Window-Page Down: no effect.
// Control-Alt-Window-Return: move to home screen.
// Control-Alt-Window-Enter: no effect.
// Control-Alt-Window-Tab: no effect.
// Control-Alt-Window-Right Arrow: no effect.
// Control-Alt-Window-Left Arrow: no effect.
// Control-Alt-Window-Down Arrow: no effect.
// Control-Alt-Window-Up Arrow: no effect.
// Control-Alt-Window-Home: no effect.
// Control-Alt-Window-Page Up: no effect.
// Control-Alt-Window-End: no effect.
// Control-Alt-Window-Page Down: no effect.
// Shift-Alt-Window-Return: move to home screen.
// Shift-Alt-Window-Enter: no effect.
// Shift-Alt-Window-Tab: no effect.
// Shift-Alt-Window-Right Arrow: no effect.
// Shift-Alt-Window-Left Arrow: no effect.
// Shift-Alt-Window-Down Arrow: no effect.
// Shift-Alt-Window-Up Arrow: no effect.
// Shift-Alt-Window-Home: no effect.
// Shift-Alt-Window-Page Up: no effect.
// Shift-Alt-Window-End: no effect.
// Shift-Alt-Window-Page Down: no effect.

// With '+' symbol highlighted
// Return: open attachment pane
// Enter: same as Return.
// Tab: highlight emoji symbol.
// Right Arrow: unpredictable: moves highlight to emoji or moves cursor back into text entry.
// Left Arrow: unpredictable: no effect or selection disappears.
// Down Arrow: unpredictable: no effect or selection disappears.
// Up Arrow: unpredictable: selection disappears or move cursor back into text entry.
// Home: no effect.
// Page Up: no effect.
// End: no effect.
// Page Down: no effect.

// With emoji symbol highlighted
// Return: opens emoji panel
// Enter: same as Return.
// Tab: selection disappears.
// Right Arrow: no effect.
// Left Arrow: unpredictable: moves highlight to '+' or move cursor back into text entry.
// Down Arrow: selection disappears.
// Up Arrow: unpredictable: selection disappears or move cursor back into text entry.
// Home: no effect.
// Page Up: no effect.
// End: no effect.
// Page Down: no effect.
// Shift-Tab: highlight emoji symbol.

*********************************************************************/


#include "keyboardSetup.h"
String KEYBOARD_NAME = "myKeyboardName";

// Control Keys are passed as summed bytes
// Bit 0 (0x01): Left Control
// Bit 1 (0x02): Left Shift
// Bit 2 (0x04): Left Alt
// Bit 3 (0x08): Left Window
// Bit 4 (0x10): Right Control
// Bit 5 (0x20): Right Shift
// Bit 6 (0x40): Right Alt
// Bit 7 (0x80): Right Window

const unsigned int numControlKeys = 4;
String controlKeyNames[numControlKeys] = {"Left Control", "Left Shift", "Left Alt", "Left Window"};
byte controlKeyBytes[numControlKeys] = {B00001, B00010, B00100, B01000};

// control keys are connected to the following pins
const int controlButtons[numControlKeys] = {A2, A3, A4, A5};


const int numKeys = 11;
String keys[numKeys][2] = {
  {"28-00-00", "Return"},
  {"58-00-00", "Enter"},
  {"2B-00-00", "Tab"},
  {"4F-00-00", "Right Arrow"},
  {"50-00-00", "Left Arrow"},
  {"51-00-00", "Down Arrow"},
  {"52-00-00", "Up Arrow"},
  {"4A-00-00", "Home"},
  {"4B-00-00", "Page Up"},
  {"4D-00-00", "End"},
  {"4E-00-00", "Page Down"},
};

// Special Keys are connected to the following pins
const int keyButtons[numKeys] = {2, 3, 5, 6, 9, 10, 11, 12, 13, A0, A1};

void setup(void)
{
  while (!Serial);  // Required for Flora & Micro
  delay(500);

  setupKeyboard(KEYBOARD_NAME);

  Serial.begin(115200);
  Serial.println("Control and Special Keys HID Keyboard Code Example");
  Serial.println("---------------------------------------");

  // setup control keys
  for (int x = 0; x < numControlKeys; x++) {
    pinMode(controlButtons[x], INPUT_PULLUP);
  }
  // setup keys
  for (int x = 0; x < numKeys; x++) {
    pinMode(keyButtons[x], INPUT_PULLUP);
  }
}


void loop(void)
{
  // check keys
  for (int x = 0; x < numKeys; x++) {
    if (digitalRead(keyButtons[x]) == LOW) {

      String controlKeys = getControlKeys();

      Serial.print("with ");
      Serial.println(keys[x][1]);

      ble.print("AT+BLEKEYBOARDCODE=");
      ble.print(controlKeys);
      ble.print("-00-");
      ble.println(keys[x][0]);

      if ( ble.waitForOK() )
      {
        Serial.println( F("OK!") );
      } else
      {
        Serial.println( F("FAILED!") );
        // Failed, probably pairing is not complete yet
        Serial.println( F("Please make sure Bluefruit is paired and try again") );
      }

      ble.print("AT+BLEKEYBOARDCODE=");
      ble.println("00-00");

      delay(500);

      while (digitalRead(keyButtons[x]) == LOW) {
        // wait here until button is released
        delay(10);
      }
    }
  }
}


String getControlKeys() {
  byte controlByte = B00000;

  for (int x = 0; x < numControlKeys; x++) {
    if (digitalRead(controlButtons[x]) == LOW) {
      controlByte = controlByte | controlKeyBytes[x];
      Serial.print(controlKeyNames[x]);
      Serial.print(" ");
    }
  }

  // construct the byte as a 2 digit hex string
  String keyString = String(controlByte, HEX);
  if (keyString.length() < 2) keyString = '0' + keyString;

  return keyString;
}

