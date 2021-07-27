// Example simulation encoder

#include <LiquidCrystal.h> 

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);; //set up LCD

#define outputA 8
#define outputB 9
#define button 6

int counter = 50;
int aState;
int aLastState;

// the follow variables is a long because the time, measured in miliseconds
// will quickly become a bigger number than can be stored in an int.

long interval = 20; // interval at which to blink (milliseconds)
void setup() {
pinMode (outputA, INPUT);
pinMode (outputB, INPUT);
pinMode (button, INPUT);

// Reads the initial state of the outputA
aLastState = digitalRead(outputA);

lcd.begin(16, 2);

}
void loop() {

lcd.setCursor(0, 0);
lcd.print("Count: ");
if (counter >= 10) {
lcd.setCursor(7, 0);
lcd.print(counter);
}
if (counter <= 9) {
lcd.setCursor(7, 0);
lcd.print(" ");
lcd.println(counter);
}

if (digitalRead(button) == LOW) {
counter = 50;
}

aState = digitalRead(outputA); // Reads the "current" state of the outputA
// If the previous and the current state of the outputA are different, that means a Pulse has occured
if (aState != aLastState) {
// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
if (digitalRead(outputB) != aState) {
counter ++;
} else {
counter --;
}

if (counter >= 100) {
counter = 0;
}
if (counter < 0) {
counter = 99;
}
}
aLastState = aState; // Updates the previous state of the outputA with the current stat
}
