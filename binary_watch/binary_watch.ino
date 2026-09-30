const int quartzPin = 2;                      // Broche D2 : signal quartz
const int ledPins[6] = {3, 4, 5, 6, 7, 8};     // LEDs binaire (secondes)
const int ledTemoin = 9;                       // LED témoin sur D9

volatile unsigned long pulses = 0;             // Compteur de fronts montants
int secondes = 0;                              // Compteur de secondes

void countPulse() {
  pulses++;
}

void setup() {
  pinMode(quartzPin, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(ledTemoin, OUTPUT);  // on configure la LED témoin

  attachInterrupt(digitalPinToInterrupt(quartzPin), countPulse, RISING);
  Serial.begin(9600);
}

void loop() {
  if (pulses >= 32768) {
    pulses = 0;
    secondes++;
    if (secondes >= 60) {
      secondes = 0;
    }

    // Affichage binaire
    for (int i = 0; i < 6; i++) {
      bool bitOn = bitRead(secondes, i);
      digitalWrite(ledPins[i], bitOn);
    }

    // Clignotement LED témoin
    digitalWrite(ledTemoin, HIGH); // ON
    delay(50);                     // Attente 50 ms
    digitalWrite(ledTemoin, LOW);  // OFF

    Serial.print("Seconde : ");
    Serial.println(secondes);
  }
  Serial.print("pulses : ");
  Serial.println(pulses);
  delay(1000); // 1 seconde d'attente réelle
}
