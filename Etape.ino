/* 
 *  Simple Etape demo app
 *  
 *  Calibration software not yet completed
 */

int buzzerPin = 9;

int length = 15; // the number of notes

/*
char tune[]     = "eeddfedcdcedceeddefffedcccdedcfedcdcedc "; // a space represents a rest
char silence[] = "               "; // a space represents a rest
int beats[] = { 1, 1, 1, 1,
                2, 1, 1, 1,
                1, 1, 2, 1, 1,
                1, 1, 1, 1,
                1, 2, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1,
                2, 1, 1, 1, 2, 1, 1, 1, 1 };
*/

char tune[]     = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };

int tempo = 200;

// ETAPE Parameters
const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to

const float res = 324;       // Resistor Value

int sensorValue0 = 0;        // value read from the pot
int sensorValue1 = 0;        // value read from the pot

float height = 0;

int i=0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(13, OUTPUT);
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void loop() {
  // read the analog in value:
  sensorValue0 = analogRead(analogInPin0);
  sensorValue1 = analogRead(analogInPin1);

  Serial.print(" h0 = ");
  height = ((float)sensorValue1 + 5.0 - (float)sensorValue0)/(float)1023.0;
  height = 60*height;
  Serial.print(height);

  Serial.print(" sensor 0 = ");
  Serial.print(sensorValue0);

  Serial.print(" sensor 1 = ");
  Serial.print(sensorValue1);
  Serial.print("\n");

  if (height > 3.0)
  {
        if (tune[i] == ' ') {
          delay(beats[i] * tempo); // rest
        } else {
          playNote(tune[i], beats[i] * tempo);
        }
        // pause between notes
        delay(tempo / 2);
        if (i%2 == 0)  digitalWrite(13, HIGH);
        else digitalWrite(13, LOW);
  } else {
    delay(200);
    i=0;
    digitalWrite(13, LOW);
  }

  i++;
  if ( i >= length) i=0;
  
}

