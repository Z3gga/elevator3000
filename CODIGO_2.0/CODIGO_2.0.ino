// Pines de motor
int motorup = 13;     // D7
int motordown = 12;   // D6
int ena = 3;          // RX

// Pines de LEDs
int led1 = 0;         // D3
int led2 = 2;         // D4
int led3 = 15;        // D8

// Pines de sensores
int sensor1 = 4;      // D1
int sensor2 = 14;     // D2
int sensor3 = 5;      // D5

// Joystick
int joystick = A0;

// Agrupaciones
int leds[3] = {led1, led2, led3};
int sensores[3] = {sensor1, sensor2, sensor3};
int lvls[6][3] = {
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0}
};

int nivelActual[3] = {0, 0, 0};
unsigned long tiempoInicio = 0;
int estado = 0;

void Up() {
  digitalWrite(motorup, HIGH);
  digitalWrite(motordown, LOW);
  analogWrite(ena, 200);
}

void Down() {
  digitalWrite(motorup, LOW);
  digitalWrite(motordown, HIGH);
  analogWrite(ena, 100);
}

void Rest() {
  digitalWrite(motorup, LOW);
  digitalWrite(motordown, LOW);
  analogWrite(ena, 0);
}

void setRandomLevel() {
  int index = random(0, 6);
  for (int i = 0; i < 3; i++) {
    nivelActual[i] = lvls[index][i];
    digitalWrite(leds[i], nivelActual[i]);
  }
}

void apagarLuces() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
    nivelActual[i] = 0;
  }
  Serial.println("LED:000,JOY:" + String(analogRead(joystick)));
}

void parpadeoError() {
  Rest();
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 3; i++) digitalWrite(leds[i], HIGH);
    Serial.println("LED:111,JOY:" + String(analogRead(joystick)));
    delay(150);

    for (int i = 0; i < 3; i++) digitalWrite(leds[i], LOW);
    Serial.println("LED:000,JOY:" + String(analogRead(joystick)));
    delay(150);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(motorup, OUTPUT);
  pinMode(motordown, OUTPUT);
  pinMode(ena, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(sensores[i], INPUT_PULLUP);
  }

  randomSeed(micros());
  setRandomLevel();
  tiempoInicio = millis();
  estado = 1;
}

void loop() {
  int joyVal = analogRead(joystick);
  if (joyVal < 200) Up();
  else if (joyVal > 800) Down();
  else Rest();

  unsigned long tiempoActual = millis();

  if (estado == 1 && tiempoActual - tiempoInicio >= 3000) {
    bool acierto = false;
    for (int i = 0; i < 3; i++) {
      if (nivelActual[i] == 1 && digitalRead(sensores[i]) == LOW) {
        acierto = true;
        break;
      }
    }

    if (acierto) {
      apagarLuces();
      tiempoInicio = tiempoActual;
      estado = 2;
    } else {
      parpadeoError();
      setRandomLevel();
      tiempoInicio = millis();
      estado = 1;
    }
  }

  if (estado == 2 && tiempoActual - tiempoInicio >= 1000) {
    setRandomLevel();
    tiempoInicio = tiempoActual;
    estado = 1;
  }

  // Enviar estado actual si no está parpadeando
  Serial.print("LED:");
  for (int i = 0; i < 3; i++) Serial.print(nivelActual[i]);
  Serial.print(",JOY:");
  Serial.println(joyVal);
}
