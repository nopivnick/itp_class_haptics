//vibrating motor pins
const PINA 11
const PINB 10
const PINC 9

//force sensor pins
int fsrA = A0;
int fsrB = A1;

int buzzThreshold = 255;  //max strength of cat purr
int petThreshold = 40;
int fsrAreading;          // the analog reading from the FSR resistor divider
int fsrBreading;          // the analog reading from the FSR resistor divider
bool pettingNow = false;

void setup() {
  Serial.begin(9600);     // We'll send debugging information via the Serial monitor
}

void loop() {
  fsrAreading = analogRead(fsrA);
  fsrBreading = analogRead(fsrB);
  Serial.print("A reading: ");
  Serial.print(fsrAreading);
  Serial.print("  | B reading: ");
  Serial.println(fsrBreading);

  //Easy option: nested if
  if (fsrAreading >= petThreshold) {
    Serial.println("first sensor stroked");
    if (fsrBreading >= petThreshold) {
      Serial.println("second sensor stroked too");
      pettingNow = true;
      if (pettingNow == true) {
        purr(); purr(); purr();
        pettingNow = false;
      }
    }
  }
}

void purr() {
  for (int fadeValue = 0 ; fadeValue <= buzzThreshold; fadeValue += 4) {
    // sets the value (range from 0 to 255):
    analogWrite(PINA, fadeValue);
    analogWrite(PINB, fadeValue);
    analogWrite(PINC, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(20);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = buzzThreshold; fadeValue >= 0; fadeValue -= 4) {
    // sets the value (range from 0 to 255):
    analogWrite(PINA, fadeValue);
    analogWrite(PINB, fadeValue);
    analogWrite(PINC, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(20);
  }
}
