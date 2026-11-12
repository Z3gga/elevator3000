// Pines del motor
int motorup = 13;     // D7
int motordown = 15;   // D8
int ena = 3;          // RX (GPIO3) — PWM

// Joystick
int joystick = A0;    // Entrada analógica

void setup() {
  pinMode(motorup, OUTPUT);
  pinMode(motordown, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(joystick, INPUT);

  analogWrite(ena, 100);  // Velocidad fija media (0–1023)
  Serial.begin(115200);
}

void loop() {
  int joyVal = analogRead(joystick);
  Serial.println(joyVal);  // Para depurar

  // Zona muerta en el centro
  if (joyVal > 600) {
    // Mover hacia arriba
    digitalWrite(motorup, HIGH);
    digitalWrite(motordown, LOW);
  } else if (joyVal < 300) {
    // Mover hacia abajo
    digitalWrite(motorup, LOW);
    digitalWrite(motordown, HIGH);
  } else {
    // Quieto
    digitalWrite(motorup, LOW);
    digitalWrite(motordown, LOW);
  }

  delay(50);  // Estabilidad
}
