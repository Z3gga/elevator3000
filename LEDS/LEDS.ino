v// Posiciones posibles (1 = LED encendido, 0 = apagado)
int pos[6][3] = {
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0}
};

// Pines de los 3 LEDs
int led1 = 2;
int led2 = 3;
int led3 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  randomSeed(analogRead(0));  // Semilla aleatoria
}

void loop() {
  int index = random(0, 6); // Escoge aleatoriamente una posición de 0 a 5

  // Aplica la combinación al estado de los LEDs
  digitalWrite(led1, pos[index][0]);
  digitalWrite(led2, pos[index][1]);
  digitalWrite(led3, pos[index][2]);

  delay(2000); // Espera 2 segundos
}
